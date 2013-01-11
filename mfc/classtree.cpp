#ifndef RP_CLASSTREE_HPP
# include "classtree.hpp"
#endif

#include <search.h>
#include <ctype.h>
// IDA includes
#include <offset.hpp>
#include <kernwin.hpp>
#include <xref.hpp>
#include <name.hpp>
#include <diskio.hpp>
#include <funcs.hpp>

//#include <rp/rp.hpp>

// for Rpd classes
#include "hierarchy.h"
#include "pdb_pool.h"

#include "mfc_ord.c"

extern void idaapi
rp_set_comment(ea_t ea, const char *comment, bool is_before, bool rptbl = false);

/*** Rpd files support */
bool is_mfc_dlled = false;
PDB_pool *p_pool = NULL;

static int check_pdb_pool()
{
  if ( p_pool != NULL )
   return 1; // already readed
  p_pool = new PDB_pool;
  int res = p_pool->read_pdbs();
  // print all import modules
  dnode_t *node = NULL;
  for ( node = p_pool->get(node); node != NULL; node = p_pool->get(node) )
  {
    msg("Import %s\n", (char *)dnode_getkey(node));
  }
  return p_pool->pdb_count();
}

// for manual loading RPD file (5 service inside plugin)
void load_RPD()
{
  check_pdb_pool();
  if ( p_pool )
   p_pool->add_pdb();
}

void pdb_deinit(void)
{
  if ( p_pool != NULL )
  {
    delete p_pool;
    p_pool = NULL;
  }
}

static void do_dref(ea_t from, ea_t to)
{
  add_dref(from, to, dr_O);
  op_offset(from, OPND_MASK, REF_OFF32, to);  
}

void make_vtbl_entry(ea_t ea)
{
  ea_t ref;
  do_unknown_range(ea, sizeof(ea), false);
#ifdef __EA64__
  doQwrd(ea, sizeof(ea));
  ref = get_long(ea);
#else
  doDwrd(ea, sizeof(ea));
  ref = get_qword(ea);
#endif /* __EA64__ */
  do_dref(ea, ref);
}

// recursive processing of olecmd mapz
#ifdef __EA64__
# define CMDMAP_ENTRY_SIZE	0x10
#else
# define CMDMAP_ENTRY_SIZE	12
#endif /* __EA64__ */

void process_command_map(ea_t ptr)
{
  do_unknown_range(ptr, 2 * sizeof(ea_t), true);
  ea_t prev = get_long(ptr);
  ea_t my = get_long(ptr + sizeof(ea_t));
  if ( get_long(my) )
  {
    do_dref(ptr+4, my);
    char *cmd_name;
    ea_t iid_ea;
    /*                            32 64
     * AFX_OLECMDMAP_ENTRY: offset 0 0 - ptr to GUID
     *                             4 8 - cmd ID
     *                             8 C - WM_COMMAND message ID
     */
    while( get_long(my) )
    {
      do_unknown_range(my, CMDMAP_ENTRY_SIZE, true);
      iid_ea = get_long(my);
      if ( iid_ea ) // ptr to IID
      {
        do_dref(my, iid_ea);
        processIID(iid_ea);
      } else {
        doDwrd(my, 4);
      }
      doDwrd(my+4, 4);
      doDwrd(my+8, 4);
      cmd_name = OLECMDID_name( get_long(my+4) );
      if ( cmd_name )
       rp_set_comment(my + 4, cmd_name, false);
      my += CMDMAP_ENTRY_SIZE;
    }
  } else {
    doDwrd(ptr+4,4);
  }
  if ( prev )
  {
    do_dref(ptr, prev);
    if ( !is_mfc_dlled )
     process_command_map(prev);
  } else {
    doDwrd(ptr, 4);
  }
}

// recursive processing of message mapz
void process_message_map(ea_t ptr, char *class_name = NULL)
{
  if ( class_name && *class_name )
  {
    int len = strlen(class_name);
    char *mm_name = (char *)qalloc(len + 8);
    strcpy(mm_name, class_name);
    strcat(mm_name, "_MsgMap");
    set_name(ptr, mm_name, SN_NOWARN | SN_AUTO);
    qfree(mm_name);
  }
  do_unknown_range(ptr, 8, true);
  ea_t prev = get_long(ptr);
  ea_t my = get_long(ptr + 4 );
  if ( get_long(my) )
  {
    do_dref(ptr + 4, my);
    process_AfxMessages(my);
  } else {
    doDwrd(ptr+4,4);
  }
  if ( prev )
  {
   do_dref(ptr, prev);
   if ( !is_mfc_dlled )
    process_message_map(prev);
  } else {
    doDwrd(ptr,4);
  }
}

// terrible function - tries to identify entries in VTBL
int fill_vtbl(char *name, ea_t vtbl, pdb_class *pc = NULL)
{
  if ( NULL == p_pool )
   return 0;
  if ( pc == NULL )
   pc = p_pool->find_class(name);
  if ( !pc )
   return -1; // no such class
  int max = pc->find_right_range();
  if ( !max )
   return 0; // empty vtbl ?
  struct vtbl_method *vm;
  int processed = 0;
///warning("processing %s (%d entries)", pc->m_name, max);
  ea_t mm = NULL; // message map
  ea_t cm = NULL; // command map
  // do_unknown_range(vtbl, max, false); - because first entry in VTBL is death
  for ( int i = 0; i <= max; i += sizeof(ea_t), vtbl += sizeof(ea_t))
  {
    make_vtbl_entry(vtbl);
    vm = pc->by_offset(i);
    if ( vm != NULL )
    {
      processed++;
      /* check for message map */
      if ( !mm )
      {
        mm = is_message_map_func(vtbl, vm->name);
        if ( mm )
         process_message_map(mm, name);
      }
      /* check for command map */
      if ( !cm )
      {
        cm = is_command_map_func(vtbl, vm->name);
        if ( cm )
         process_command_map(cm);
      }
      // set comment for entry in this VTBL
      rp_set_comment(vtbl, vm->name, false);
      // set function comment
      func_t *f = get_func(get_long(vtbl));
      if ( f )
      {
        char *fcmt = get_func_cmt(f, true);
        if ( fcmt )
         del_func_cmt(f, false);
        set_func_cmt(f, vm->name, true);
      }
    }
  }
  return processed;
}

/*************** CONSTANTS ***************/
#define RP_INITIAL	4
#define RP_INCREMENT	4
#define RT_len		20
#define ROOT_LEN 	7
uchar *root_name = (uchar *)"CObject";

/*************** GLOBAL VARS ***************/
struct RP_class *CObject = NULL;
struct RP_class **rt_database = NULL;
ulong total_classes = 0;

/* for internal using */
static int filler_index = 0;
static size_t max_size = 0;
static char *misc_buffer1 = NULL,
            *misc_buffer2 = NULL;

/*************** FUNCTIONS ***************/
struct RP_class *
alloc_class(ea_t adr, size_t namelen, struct RP_class *parent)
{
  struct RP_class *res = (struct RP_class *)qalloc(sizeof(struct RP_class));
  res->parent = parent;
  res->CRuntime = adr;
  res->vtbl = 0;
  res->total = 0;
  res->namelen = namelen;
  res->children = (struct RP_class **)qalloc(sizeof(struct RP_class *) * (res->alloced = RP_INITIAL));
  total_classes++;
  return res;
}

void
add_class(struct RP_class *root, ea_t adr, size_t namelen)
{
  if ( root->total == root->alloced )
   root->children = 
     (struct RP_class **)qrealloc(root->children,
       sizeof(struct RP_class *) * (root->alloced += RP_INCREMENT));
  root->children[root->total++] = alloc_class(adr, namelen, root);
  if ( namelen > max_size )
   max_size = namelen;
}

void 
kill_class(struct RP_class *root)
{
  int i;
  if ( NULL == root )
   return;
  if ( root->children != NULL && root->total )
   for ( i = 0; i < root->total; i++ )
    kill_class(root->children[i]);
  if ( root->children != NULL )
   qfree(root->children);
  qfree(root);
}

void
classes_deinit(void)
{
  if ( rt_database != NULL )
  {
    qfree(rt_database);
    rt_database = NULL;
  }
  if ( NULL != CObject )
  {
    kill_class(CObject);
    CObject = NULL;
  }
  if ( NULL != misc_buffer1 )
  {
    qfree(misc_buffer1);
    misc_buffer1 = NULL;
  }
  if ( NULL != misc_buffer2 )
  {
    qfree(misc_buffer2);
    misc_buffer2 = NULL;
  }
  total_classes = 0;
  max_size = 0;
}

/* Horror function - tries to recognize CRuntimeClass */
size_t
check_for_RTStruct(ea_t adr)
{
  if ( !is_defined_area(adr, RT_len) )
   return 0;
  size_t namesize = rp_is_class_name(get_long(adr)); /* check for name */
  ulong schema = get_long(adr + 8);
  if ( schema != 0xffff && schema)	/* all schemas must be 0xffff or 0
   See afx.h for IMPLEMENT_SERIAL, IMPLEMENT_DYNAMIC & IMPLEMENT_DYNCREATE macros */
   return 0;
  if ( is_contain_ptr(adr + 16) )
   return namesize; /* Yes - possible we really have CRuntimeClass :-) */
  if ( 0 != get_long(adr + 16) )
   return 0; /* bad addr ? */
#if 0 
  /* This code is very strange - CRunTimeClass has size only 20 bytes... */
  if ( is_contain_ptr(adr + 20) )
   return namesize;
  if (0 != get_long(adr + 20) )
   return 0;
#endif
  return namesize;
}

void
make_RTStruct(ea_t adr, size_t namelen)
{
  /* form struct */
  do_unknown_range(adr, RT_len, true);
  doDwrd(adr,4);
  doDwrd(adr+4,4);
  doDwrd(adr+8,4);
  doDwrd(adr+12,4);
  doDwrd(adr+16,4);
//  doDwrd(adr+20,4);
  /* add dref to class name */
  ea_t ptr = get_long(adr);
  make_ascii_string(ptr, namelen, ASCSTR_C);
  add_dref(adr, ptr, dr_O);
  op_offset(adr, OPND_MASK, REF_OFF32, ptr);
  rp_set_comment(adr+4, "Size", false);
  /* add cref to constructor */
  ptr = get_long(adr+12);
  if ( ptr )
  {
    add_cref(adr+12, ptr, fl_CN);
    op_offset(adr+12, OPND_MASK, REF_OFF32, ptr);
  }
  /* add dref to base class struct */
  ptr = get_long(adr+16);
  if ( ptr )
  {
    add_dref(adr+16,ptr,dr_O);
    op_offset(adr+16, OPND_MASK, REF_OFF32, ptr);
  }
  /* add dref to next class */
/*  ptr = get_long(adr+20);
  if ( ptr )
  {
    add_dref(adr+20,ptr,dr_O);
    op_offset(adr+20, OPND_MASK, REF_OFF32, ptr);
  }
*/
}

static void
set_vtbl_name(char *name, ea_t vtbl)
{
  if ( !name || !*name )
    return;
  int len = strlen(name);
  char *name2 = (char *)qalloc(len + 6);
  name2[0] = 'v';
  name2[1] = 't';
  name2[2] = 'b';
  name2[3] = 'l';
  name2[4] = '_';
  strcpy(name2 + 5, name);
  set_name(vtbl, name2, SN_AUTO);
  qfree(name2);
}

static void
setter(char *name, ea_t rt, ea_t vtbl, bool latch)
{
  if ( !name || !*name )
    return;
  int len = strlen(name);
  char *name2 = (char *)qalloc(len + 6);
  // fill CRunTime record
  name2[0] = 'R';
  name2[1] = 'T';
  name2[2] = '_';
  strcpy(name2 + 3, name); 
  set_name(rt, name2, SN_AUTO);
  make_RTStruct(rt, len);
  if ( !latch )
  {
    qfree(name2);
    return;
  }
  if ( vtbl )
  {
   // vtbl processing
   name2[0] = 'v';
   name2[1] = 't';
   name2[2] = 'b';
   name2[3] = 'l';
   name2[4] = '_';
   strcpy(name2 + 5, name);
   set_name(vtbl, name2, SN_AUTO);
  }
  qfree(name2);
}

pdb_class *try_find_by_name(ea_t ea, char **name, bool *free_name, bool is_deref_name = true)
{
  pdb_class *res = NULL;
  char buf[256];
  *free_name = false;
  char *t_name = NULL;
  if ( is_deref_name )
    t_name = get_true_name(ea, get_long(ea), buf, 255);
  else
    t_name = get_true_name(ea, ea, buf, 255);
  if ( t_name )
  {
    *name = get_parent_class(t_name);
    if ( *name )
    {
      res = p_pool->find_class(*name);
      if ( !res )
       qfree(*name);
      else
       *free_name = true;
      return res;
    }
  }
  return NULL;
}

pdb_class *try_to_find_from_rt(ea_t ea, char **name, bool *free_name)
{
  pdb_class *res = NULL;
  if ( !ea || ea == BADADDR )
   return NULL;
  // check for ref to const parent CRunTime class from DLL
  ea_t rt = check_for_cruntimeclass2(ea);
  if ( rt )
  {
    res = try_find_by_name(rt, name, free_name, false);
    if ( res )
     return res;
  }
  // check for ref to base CRunTime class
  rt = check_for_cruntimeclass(ea);
  if ( rt )
  {
    res = try_find_by_name(rt, name, free_name);
    if ( res )
     return res;
  }
  size_t len;
  // check for name from static CRunTime class
  if ( !rt )
  {
    len = check_for_RTStruct(ea);
    rt = ea;
  }
  else
   len = check_for_RTStruct(rt);
  if ( len )
  {
    *name = (char *)qalloc(len + 1);
    get_many_bytes(get_long(rt), *name, len);
    (*name)[len] = 0;
    setter(*name, rt, 0, true);
    res = p_pool->find_class(*name);
    if ( res )
    {
     *free_name = true;
     return res;
    }
    qfree(*name);
    // lets check all hierarchy
    res = try_to_find_from_rt(get_long(rt + 0x10), name, free_name);
  }
  return res;
}

/* try to find this class or one of parent class in our pdb pool */
pdb_class *try_to_find_this_or_parent(ea_t ea, char **name, bool *free_name, bool *named)
{
  // 1st - lets check if have some fuzzy name as first entry to VTBL
  if ( !p_pool || !name )
   return NULL;
  *named = false;
  pdb_class *res = try_find_by_name(ea, name, free_name);
  if ( res )
  {
    set_vtbl_name(*name, ea);
    return res;
  }
  return try_to_find_from_rt(get_long(ea), name, free_name);
}

void mark_name_from_static_RT(ea_t ea)
{
  ea_t rt = check_for_cruntimeclass( get_long(ea) );
  if ( !rt || rt == BADADDR )
   return;
  size_t len = check_for_RTStruct(rt);
  if ( len )
  {
    char *name = (char *)qalloc(len + 1);
    get_many_bytes(get_long(rt), name, len);
    name[len] = 0;
    set_vtbl_name(name, ea);
    qfree(name);
  }
}

/* tries to find CObject class */
ea_t
find_root(ea_t start, bool silent)
{
  char buffer[ROOT_LEN+1];
  /* check what we get */
  size_t len = check_for_RTStruct(start);
  if ( !len ) /* hm, lets try to find in -20..+20 range */
   for ( ea_t cptr = start - 20; cptr < cptr + 24; cptr += sizeof(ea_t) )
   {
     if ( start == cptr )
      continue;
     if ( len = check_for_RTStruct(cptr) )
     {
       start = cptr;
       break;
     }
   }
  if ( !len )
  {
    if ( !silent )
      warning("Passed address (0x%X) dont seems to be CRuntimeClass", start);
    return NULL;
  }
  while( NULL != start )
  {
    if ( len == ROOT_LEN ) /* Hm, may be */
    {
      if ( !get_many_bytes(get_long(start), buffer, ROOT_LEN) )
      {
        if ( !silent )
          warning("Cannot get %d bytes at 0x%X", len, get_long(start) );
        return NULL;
      }
      if ( !strncmp(buffer, (const char *)root_name, ROOT_LEN) )
       return start;
    }
    start = get_long(start+16);
    len = check_for_RTStruct(start);
    if ( !len )
     break;
  }
  if ( !silent )
    warning("Cannot find root");
  return NULL;
}

ea_t
is_indirect_link(ea_t ptr)
{
  if ( !is_defined_area(ptr,5) )
   return NULL;
  if ( get_byte(ptr) != 0xe9 ) /* jmp far */
   return NULL;
  ea_t res = NULL;
  int total = 0, iscode = 0, ok;
  xrefblk_t xb;
  for ( ok = xb.first_to(ptr,XREF_ALL); ok; ok=xb.next_to() )
  {
    total++;
    iscode = xb.iscode;
    res = xb.from;
  }
  if ( 1 != total )
   return NULL;
  if ( !iscode )
   return res;
  return is_indirect_link(res);
}

ea_t
check_for_cruntimeclass2(ea_t ptr)
{
#ifdef __EA64__
  if ( get_byte(ptr)   == 0x48 && /* 48 8D 05 - lea rax [rip + XX] */
       get_byte(ptr+1) == 0x8d &&
       get_byte(ptr+2) == 0x5  &&
       get_byte(ptr+7) == 0xC3    /* retn */
     )
  {
    long off = get_long(ptr+3);
    return ptr + 6 + off;
  }
#else
  if ( get_byte(ptr) == 0xa1 /* mov eax, ds: */ &&
       get_byte(ptr+5) == 0xc3 /* retn */ 
     )
   return get_long(ptr+1);
#endif /* __EA64__ */
  return 0;
}

/* very strange */
ea_t
check_for_cruntimeclass(ea_t ptr)
{
  if ( get_byte(ptr) != 0xb8 /* mov eax */ ||
       get_byte(ptr+5) != 0xc3 /* ret */ )
   return 0;
  return get_long(ptr+1);
}

/* pure euristic */
ea_t
check_for_vtbl(ea_t ptr)
{
  if ( get_byte(ptr) != 0xb8 /* mov eax */ ||
       get_byte(ptr+5) != 0xc3 /* ret */ )
   return 0;

  xrefblk_t xb;
  int ok, total = 0;
  ea_t res;
  for ( ok = xb.first_to(ptr,XREF_ALL); ok; ok=xb.next_to() )
  {
    if ( xb.iscode )
    {
     ea_t ind = is_indirect_link(xb.from);
     if ( NULL != ind )
     {
      total++;
      res = xb.from;
     }
     continue;
    }
    total++;
    res = xb.from;
  }
  if ( total != 1)
   return 0;
  return res;
}

/* build tree from back refs */
void
back_trace_rt(struct RP_class *root)
{
 xrefblk_t xb;
 size_t namelen;
 int ok;

 for ( ok = xb.first_to(root->CRuntime,XREF_ALL); ok; ok=xb.next_to() )
 {
   if ( xb.iscode )
    continue;
   namelen = check_for_RTStruct(xb.from - 16);
   if ( !namelen )
   {
    /* check for possible vtbl */
    ea_t vtbl = check_for_vtbl(xb.from);
    if ( vtbl == NULL )
     continue;
    root->vtbl = vtbl; /* And what I have to do if we already have vtbl ? */
    continue;
   }
   add_class(root, xb.from - 16, namelen);
   make_RTStruct(xb.from - 16, namelen);
 }
 /* go to next level */
 for ( ok = 0; ok < root->total; ok++ )
   back_trace_rt(root->children[ok]);
}

static int __cdecl
rt_compare_names(const void *a, const void *b)
{
  struct RP_class *a_c = *(struct RP_class **)a;
  struct RP_class *b_c = *(struct RP_class **)b;

  get_many_bytes(get_long(a_c->CRuntime), misc_buffer1, a_c->namelen);
  get_many_bytes(get_long(b_c->CRuntime), misc_buffer2, b_c->namelen);
  misc_buffer1[a_c->namelen] = 0x0;
  misc_buffer2[b_c->namelen] = 0x0;
  return strcmp(misc_buffer1, misc_buffer2);
}

static int __cdecl
rt_find_by_name(const void *key, const void *elem)
{
  const struct RP_class *cmp_with = *(const struct RP_class **)elem;
  get_many_bytes(get_long(cmp_with->CRuntime), misc_buffer1, cmp_with->namelen);
  misc_buffer1[cmp_with->namelen] = 0x0;
  return strcmp((const char *)key, misc_buffer1);
}

static void
sort_and_name_all(struct RP_class *root)
{
  /* first name RuntimeClass struct */
  misc_buffer1[0] = 'R';
  misc_buffer1[1] = 'T';
  misc_buffer1[2] = '_';
  get_many_bytes(get_long(root->CRuntime), misc_buffer1 + 3, root->namelen);
  // 29 APR 2003 - rpd support
  if ( p_pool != NULL && root->vtbl )
   fill_vtbl(misc_buffer1 + 3, root->vtbl);

  misc_buffer1[3 + root->namelen] = 0x0;
  set_name(root->CRuntime, misc_buffer1, SN_AUTO);
  /* next name vtbl if found */
  if ( NULL != root->vtbl )
  {
    misc_buffer1[0] = 'v';
    misc_buffer1[1] = 't';
    misc_buffer1[2] = 'b';
    misc_buffer1[3] = 'l';
    misc_buffer1[4] = '_';
    get_many_bytes(get_long(root->CRuntime), misc_buffer1 + 5, root->namelen);
    misc_buffer1[5 + root->namelen] = 0x0;
    set_name(root->vtbl, misc_buffer1, SN_AUTO);
  }
  /* sort children by name */
  if ( !root->total )
   return;
  qsort(root->children, root->total, sizeof(struct RP_class *), rt_compare_names);
  /* and finally do it recirsive for all children */
  int i;
  for ( i = 0; i < root->total; i++ )
   sort_and_name_all(root->children[i]);
}

void
fill_rt_database(struct RP_class *root)
{
  if ( NULL == root )
   return;
  rt_database[filler_index++] = root;
  for ( int i = 0; i < root->total; i++ )
   fill_rt_database(root->children[i]);
}

static bool
internal_build_rt_tree(ea_t adr)
{
 /* check what we have */
 ea_t root = find_root(adr & ~4, true); /* RT struct must be aligned on 4 bytes */
 if ( NULL == root )
   return false;
 if ( NULL != CObject )
   classes_deinit();
 /* make root class */
 CObject = alloc_class(root, ROOT_LEN, NULL);
 make_RTStruct(root, ROOT_LEN);
 back_trace_rt(CObject);
 misc_buffer1 = (char *)qalloc(6 + max_size); /* 'vtbl_' + one for leading zero */
 misc_buffer2 = (char *)qalloc(1 + max_size);
 sort_and_name_all(CObject);
 /* next fill linear array and sort it too */
 rt_database = (struct RP_class **)qalloc(total_classes * sizeof(struct RP_class *));
 filler_index = 0;
 fill_rt_database(CObject);
 qsort(rt_database, total_classes, sizeof(struct RP_class *), rt_compare_names);
 return true;
}

bool
check_rt_tree()
{
  if ( NULL != CObject )
   return true;
  ea_t adr = auto_find_root_addr();
  if ( NULL == adr )
  {
    warning("Cannot find start for class hierarchy");
    return false;
  }
  check_pdb_pool();
  return internal_build_rt_tree(adr);
}

/* function to ensure that we have RT tree and to build it if not */
bool
build_rt_tree(ea_t adr)
{
 if ( NULL != CObject )
 {
   int i = askbuttons_cv("Yes", "No", "Cancel", 0, 
    "Database for RT map already collected\nDo you want to repeat ?", NULL );
   if ( !i )
    return true;
   if ( 1 != i )
    return false;
 }
 return internal_build_rt_tree(adr);
}

static void
rt_put_margin(int len, FILE *fp)
{
  while(len >= 8)
  {
    fputc('\t', fp);
    len -= 8;
  }
  for ( int i = 0; i < len; i++ )
   fputc(' ', fp);
}

void
output_rt_tree(FILE *fp, struct RP_class *root, int margin)
{
  if ( NULL == root )
   return;
  rt_put_margin(margin,fp);
  get_many_bytes(get_long(root->CRuntime), misc_buffer1, root->namelen);
  misc_buffer1[root->namelen] = 0x0;
  if ( root->vtbl )
   fprintf(fp, "%s: adr 0x%X, vtbl 0x%X\n", misc_buffer1, root->CRuntime, root->vtbl);
  else
   fprintf(fp, "%s: adr 0x%X\n", misc_buffer1, root->CRuntime );
  int i;
  margin += 4;
  for ( i = 0; i < root->total; i++ )
   output_rt_tree(fp, root->children[i], margin);
}

int check_rpd_count(bool is_silent = false)
{
  check_pdb_pool();
  if ( NULL == p_pool )
    return 0;
  if ( !p_pool->pdb_count() && !is_silent )
  {
    warning("No RPD files was loaded. You must load at least one RPD file before VTBL processing");
    return 0;
  }
  return 1;   
}

void
process_VTBL2()
{
  ea_t curr = get_screen_ea();
  if ( !is_contain_ptr(curr) )
   return;

  if ( !check_rpd_count() )
   return;
  
  char *ask = askstr(0, "", "Class name");
  if ( !ask || !*ask )
   return;
  pdb_class *pc = p_pool->find_class(ask);
  if ( !pc )
  {
    warning("Don`t known class '%s'", ask);
    return;
  }
  fill_vtbl(ask, curr, pc);
}

void
process_from_founded_sig(dict_t *dict)
{
  if ( !dict || !dict_count(dict) )
   return;
  if ( !check_rpd_count(true) )
   return;
  dnode_t *node;
  pdb_class *pc;
  char *c_name;
  ea_t ea;
  for ( node = dict_first(dict); node; node = dict_next(dict, node) )
  {
    c_name = (char *)dnode_get(node);
    ea = (ea_t)dnode_getkey(node);
    pc = p_pool->find_class(c_name);
    if ( !pc )
     continue;
    fill_vtbl(c_name, ea, pc);
  }
}

void
process_VTBL()
{
//  check_rt_tree();
  ea_t curr = get_screen_ea();
  if ( !is_contain_ptr(curr) )
   return;

  if ( !check_rpd_count() )
   return;

  char *name = NULL;
  bool free_name = false;
  bool named = false;
  pdb_class *pc = try_to_find_this_or_parent(curr, &name, &free_name, &named);
  if ( !pc )                                   
  {
    msg("Cannot detect class for VTBL at %X\n", curr);
    return;
  }
  msg("Class %s\n", name);
  fill_vtbl(name, curr, pc);
  if ( !named )
    mark_name_from_static_RT(curr);
  if ( free_name )
    qfree(name);
}

void
process_RT()
{
  if ( !check_rt_tree() )
   return;

  FILE *fp;
  fp = fopen("rt.map", "w");
  if ( fp == NULL )
  {
    warning("Cannot create output file");
    return;
  }
  output_rt_tree(fp,CObject,0);
  fclose(fp);
}

ea_t
auto_find_root_addr()
{
  int i;
  segment_t *s;
  ea_t start, end, found;

  for ( i = 0; i < segs.get_area_qty(); i++ )
  {
    s = getnseg(i);
    if ( NULL == s )
     continue;
    start = s->startEA;
    end = s->endEA;
    while(start < end)
    {
     found = bin_search(start, end, root_name, NULL, ROOT_LEN + 1,
      BIN_SEARCH_FORWARD, BIN_SEARCH_CASE);
     if ( BADADDR == found )
      break;
     start = found + ROOT_LEN; /* for next iteration */
     xrefblk_t xb;
     int ok;
     for ( ok = xb.first_to(found,XREF_ALL); ok; ok=xb.next_to() )
     {
       if ( xb.iscode ) /* we want data ref */
         continue;
       if ( NULL != ( found = find_root(found, true) ) )
         return found;
     }
    }
  }
  return NULL;
}

/* find functions - assumed that we already have builded rt tree */
struct RP_class *
find_rt_by_vtbl(ea_t adr)
{
  for ( int i = 0; i < total_classes; i++ )
   if ( rt_database[i]->vtbl == adr )
    return rt_database[i];
  return NULL;
}

struct RP_class *
find_rt_by_name(const char *name)
{
  if ( !total_classes )
   return NULL;
  struct RP_class **ref2 = (struct RP_class **)bsearch(name, rt_database, 
   total_classes, sizeof(struct RP_class *), rt_find_by_name);
  if ( NULL == ref2 )
   return NULL;
  return *ref2;
}

void
jump_to_vtbl_by_name()
{
  char *res = askstr(0, "", "Class name");
  if ( NULL == res || !*res )
   return;
  if ( !check_rt_tree() )
   return;
  struct RP_class *ptr = find_rt_by_name(res);
  if ( NULL == ptr )
  {
   warning("Class '%s' not found\n", res);
   return;
  }
  if ( NULL == ptr->vtbl )
  {
   msg("Cannot find vtbl for '%s'\n", res);
   jumpto(ptr->CRuntime);
   return;
  }
  jumpto(ptr->vtbl);
}