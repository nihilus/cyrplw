#include "pdb_pool.h"
#include <diskio.hpp>
#include <kernwin.hpp>
#include <name.hpp>
#include <segment.hpp>
#include "mfc_cfg.h"

char * idaapi read_zero_ended_string(ea_t ea);
char * idaapi read_zero_ended_unicode_string(ea_t ea);

extern bool is_mfc_dlled;
extern "C" char *ole2str(wchar_t *,int);

static char *what_to_find = "AfxWnd";
static wchar_t *what_to_find_unicode = L"AfxWnd";
static int what_to_find_len = 6;

static void free_pdbz(dnode_t *node, void *)
{
  char *key = (char *)dnode_getkey(node);
  if ( key )
   qfree(key);
  CPdb *p = (CPdb *)dnode_get(node);
  if ( p )
   delete p;
  free(node);
}

extern int imp_cmp(const void *a, const void *b);

PDB_pool::PDB_pool()
 : Imp_Dlls(),
   m_rpd_list(RPD_LIST_NETNODE_NAME, 0, true)
{
  m_pdbs = dict_create(DICTCOUNT_T_MAX, imp_cmp);
  dict_set_allocator(m_pdbs, NULL, free_pdbz, NULL);
  m_ida_dir = NULL;
  if ( mfc_cfg )
    m_ida_dir = mfc_cfg->rpd_data_dir();
  if ( !m_ida_dir )
    m_ida_dir = idadir(NULL);
  m_len = strlen(m_ida_dir);
  // for RPD list
  m_rpd_index = m_rpd_list.suplast();
//  __asm int 3
  if ( m_rpd_index == BADNODE )
   m_rpd_index = 0;
  else
  {
    m_rpd_index++; // to add next element
    load_rpd_list();
  }
}

int PDB_pool::add_to_rpd_list(char *full_name)
{
  char *name = full_name;
  char *res = NULL;
  if ( !strnicmp(full_name, m_ida_dir, m_len) ) // is was get from standard RPD dir ?
  {
    name = full_name + m_len;
    if ( *name == '\\' || *name == '/' )
      name++;
    if ( !strnicmp(name, "rpd", 3) )
    {
      name += 3;
      if ( *name == '\\' || *name == '/' )
        name++;
      int res_len = strlen(name);
      res = (char *)malloc( 2 + res_len);
      res[0] = '/';
      strcpy(res + 1, name);
      res[res_len + 1] = 0;
    } else
      name = full_name;
  }
  int ret = m_rpd_list.supset(m_rpd_index, res != NULL ? res : name);
  if ( ret )
    m_rpd_index++;
  else
    msg("Cannot store '%s' in RPD list\n", name);
  if ( res != NULL )
    free(res);
  return ret;
}

PDB_pool::~PDB_pool()
{
  if ( m_pdbs )
  {
    dict_free(m_pdbs);
    dict_destroy(m_pdbs);
    m_pdbs = NULL;
  }
}

struct pdb_class *PDB_pool::find_class(char *name)
{
  dnode_t *node;
  struct pdb_class *res;
  CPdb *p;
  for ( node = dict_last(m_pdbs); node; node = dict_prev(m_pdbs, node) )
  {
    p = (CPdb *)dnode_get(node);
    res = p->find_class(name);
    if ( res )
     return res;
  }
  return NULL;
}

/* Warning: you are responsible for freeing of returned string
   Returns only name without extention
 */
char *PDB_pool::get_name(char *name)
{
  if ( !name || !*name )
   return NULL;
  int len = strlen(name);
  char *dot = NULL;
  char *ptr = name + len - 1;
  while( ptr >= name )
  {
    if ( *ptr == '.' && !dot )
     dot = ptr;
    if ( *ptr == '/' || *ptr == '\\' )
     break;
    ptr--;
  }
  if ( ptr < name )
   ptr = name;
  int dot_len = 0;
  if ( dot )
    dot_len = 1 + len - (dot - name);
  if ( *ptr == '/' || *ptr == '\\' )
   ptr++;
  int res_len = strlen(ptr) + 1 - dot_len;
  char *res = (char *)qalloc(res_len);
  strncpy(res, ptr, res_len);
  res[res_len] = 0;
  return res;
}

void PDB_pool::load_rpd_list()
{
  if ( m_rpd_index == BADNODE )
    return;
  char name[1024];
  for ( int i = 0; i < m_rpd_index; i++ )
  {
    m_rpd_list.supval(i, name, 1024);
    if ( name == NULL || !*name )
     continue;
    load_from_rpd(name);
  }
}

void PDB_pool::load_from_rpd(char *name)
{
  // 1) lets check if name starts with '/'
  char *fname = NULL;
  if ( *name == '/' )
  {
    name++;
    int len = strlen(name);
    fname = (char *)malloc(m_len + len + 6);
    strcpy(fname, m_ida_dir);
    if ( fname[m_len - 1] != '\\' )
    {
      fname[m_len] = '\\';
      fname[m_len + 1] = 0;
    }
    strcat(fname, "rpd\\");
    strcat(fname, name);
  }
  FILE *fp = fopen(fname != NULL ? fname : name, "rb");
  if ( fp == NULL )
  {
    msg("Cannot open '%s' from RPD list\n", fname != NULL ? fname : name);
    if ( fname != NULL )
      free(fname);
    return;
  }
  CPdb *p = new CPdb;
  int res = p->read(fp);
  fclose(fp);
  if ( !res )
  {
    dict_alloc_insert(m_pdbs, get_name( fname != NULL ? fname : name), p);
///// Because this already contains in IDA base
/////    after_loading(p);
    msg("Loaded RPD file %s\n", fname != NULL ? fname : name);
  } else {
    msg("Cannot read RPD file %s", fname != NULL ? fname : name);
    delete p;
  }
  if ( fname != NULL )
    free(fname);
}

// Other version loading rpd file - to ask it from user
int PDB_pool::add_pdb()
{
  // lets make mask for RPD dir (add \\rpd\\*.rpd to idadir)
  char *mask = (char *)malloc(m_len + 12);
  strcpy(mask, m_ida_dir);
  if ( mask[m_len - 1] != '\\' )
  {
    mask[m_len] = '\\';
    mask[m_len + 1] = 0;
  }
  strcat(mask, "rpd\\*.rpd");
  char *answer = askfile_c(0, mask, "RPD file to load");
  free(mask);

  if ( !answer || !*answer )
   return 0;
  // check if have .prd file
  const char *ext = get_file_ext(answer);
  if ( stricmp(ext, "rpd") )
  {
    msg("Invalid extension PRD file - %s\n", ext);
    return 0;
  }
  // O`k, lets check first if we already have such RPD
  char *name = get_name(answer);
  if ( !name )
   return 0;
  if ( !check_pdb(name) )
  {
    warning("Duplicated file '%s' - already loaded", name);
    qfree(name);
    return 0;
  }
  FILE *fp = fopen(answer, "rb");
  if ( !fp )
  {
    msg("File %s not found\n", answer);
    qfree(name);
    return 0;
  }
  CPdb *p = new CPdb;
  int res = p->read(fp);
  fclose(fp);
  if ( !res )
  {
    dict_alloc_insert(m_pdbs, name, p);
    after_loading(p);
    msg("Loaded PRD file %s\n", answer);
    add_to_rpd_list(answer);
  } else {
    msg("Cannot read RPD file %s", answer);
    qfree(name);
    delete p;
  }
  return res;
}

// We must free fname and name if loading of PDB was unsuccessfull
int PDB_pool::add_pdb(char *name)
{
  char *only_name = get_name(name);
  if ( !check_pdb(only_name) )
  {
    qfree(only_name);
    return 0;
  }
  if ( only_name )
   qfree(only_name);
  int len = strlen(name);
  char *fname = (char *)qalloc(m_len + len + 10);
  strcpy(fname, m_ida_dir);
  if ( fname[m_len - 1] != '\\' )
  {
    fname[m_len] = '\\';
    fname[m_len + 1] = 0;
  }
  strcat(fname, "rpd\\");
  strcat(fname, name);
  strcat(fname, ".rpd");
  FILE *fp = fopen(fname, "rb");
  if ( !fp )
  {
    msg("File %s not found\n", fname);
    qfree(fname);
    qfree(name);
    return 1;
  }
  CPdb *p = new CPdb;
  int res = p->read(fp);
  fclose(fp);
  if ( !res )
  {
    dict_alloc_insert(m_pdbs, name, p);
    after_loading(p);
    add_to_rpd_list(fname);
  } else {
    msg("Cannot read RPD file for %s\n", name);
    qfree(fname);
    delete p;
  }
  qfree(fname);
  return res;
}

// Warning - names inside m_pdbs must be withous extension !!!
int PDB_pool::check_pdb(char *name)
{
  if ( NULL == name || !*name )
   return 0;
  dnode_t *node = dict_lookup(m_pdbs, name);
  if ( !node )
   return 1;
  return 0;
}

int PDB_pool::pdb_count()
{
  if ( !m_pdbs )
   return 0;
  return dict_count(m_pdbs);
}

int PDB_pool::read_pdbs()
{
  int imp_res = Imp_Dlls::get_dlls();
  if ( imp_res )
   return imp_res;
  dnode_t *node;
  char *name;
  char *imp_name;
  for ( node = dict_first(Imp_Dlls::m_dict);
        node != NULL;
        node = dict_next(Imp_Dlls::m_dict, node) )
  {
    imp_name = (char *)dnode_getkey(node);
    name = get_name(imp_name);
    if ( !name )
     continue;
    if ( !strnicmp(name, "mfc", 3) )
    {
      is_mfc_dlled = true;
      add_pdb(name);
      continue;
    }
    if ( !strnicmp(name, "atl", 3) )
    {
      add_pdb(name);
      continue;
    }
    qfree(name);
  }
  if ( !is_mfc_dlled )
   autodetect_static_version();
  return 0;
}

void PDB_pool::after_loading(CPdb *pdb)
{
  if ( !pdb )
   return;
  dict_t *dict = pdb->get_dict();
  if ( !dict )
   return;
  struct pdb_class *pc;
  // lets add VTBLs and members
  dnode_t *node;
  for ( node = dict_first(dict); node; node = dict_next(dict, node) )
  {
    pc = (struct pdb_class *)dnode_get(node);
    if ( !pc )
     continue;
    if ( pc->get_vtbl_count() )
     add_VTBL(pc);
    if ( (pc->type != DIAID_UNION) && pc->get_member_count() )
     add_struct(pc);
  }
}

void PDB_pool::add_struct(struct pdb_class *pc)
{
  // 1) check if we already have this struct
  char *valid_name = _strdup(pc->m_name);
  char *v_named = validate_name(valid_name);
  if ( !v_named )
  {
    msg("Bad %s %s\n", pc->what_type(), pc->m_name);
    free(valid_name);
    return;
  }
  tid_t tid = get_struc_id(v_named);
  if ( tid != BADADDR ) // already loaded
  {
    free(valid_name);
    return;
  }
  // O`k, we must add this VTBL as IDA struct
  tid = add_struc(BADADDR, v_named, false);
  if ( tid == BADADDR )
  {
    msg("Cannot add %s %s\n", pc->what_type(), pc->m_name);
    free(valid_name);
    return;
  }
  struc_t *s = get_struc(tid);
  free(valid_name);
  add_members(s, pc);
}

void PDB_pool::add_VTBL(struct pdb_class *pc)
{
  // 1) check if we already have this struct
  char *valid_name = _strdup(pc->m_name);
  char *v_named = validate_name(valid_name);
  if ( !v_named )
  {
    msg("Bad %s %s\n", pc->what_type(), pc->m_name);
    free(valid_name);
    return;
  }
  // contruct VTBL struct name - with _vtbl suffix
  int len = strlen(v_named);
  char *vtbl_struct_name = (char *)qalloc(len + 6);
  strcpy(vtbl_struct_name, v_named);
  strcat(vtbl_struct_name, "_vtbl");
  free(valid_name);

  tid_t tid = get_struc_id(vtbl_struct_name);
  if ( tid != BADADDR ) // already loaded
  {
    qfree(vtbl_struct_name);
    return;
  }
  // O`k, we must add this VTBL as IDA struct
  tid = add_struc(BADADDR, vtbl_struct_name, false);
  if ( tid == BADADDR )
  {
    msg("Cannot add %s %s VTBL\n", pc->what_type(), pc->m_name);
    qfree(vtbl_struct_name);
    return;
  }
  struc_t *s = get_struc(tid);
  qfree(vtbl_struct_name);
  add_methods(s, pc);
}

struct pdb_class *PDB_pool::get_parent(struct pdb_class *pc)
{
  if ( !pc )
   return NULL;
  // lets check if we have one presented in this PDB parent
  if ( !pc->parents || (1 != pc->parents->all) )
   return NULL;
  struct pdb_parent *pp = (struct pdb_parent *)pc->parents->fist;
  if ( pp->what == 3 )
   return pp->c;
  if ( pp->what == 2 )
    return find_class(pp->name);
  return NULL;
}

// recursive add all methods from VTBL
void PDB_pool::add_methods(struc_t *s, struct pdb_class *pc)
{
  if ( !pc )
   return;
  if ( pc->vtbls && pc->vtbls->all )
  {
   struct vtbl_method *vm;
   char *only_name;
   member_t *ida_m;
   for ( vm = (struct vtbl_method *)pc->vtbls->fist;
         vm != NULL;
         vm = (struct vtbl_method *)vm->list.next )
   {
     only_name = vm->get_name_only();
////msg("Add %s to %X offset %X\n", only_name, s, vm->index);
     add_struc_member(s, only_name, vm->index, dwrdflag() /*| offflag() */, NULL, sizeof(ea_t));
     free(only_name);
     ida_m = get_member(s, vm->index);
     if ( ida_m )
       set_member_cmt(ida_m, vm->name, true);
   }
  }
  struct pdb_class *my_parent = get_parent(pc);
  if ( my_parent )
   add_methods(s, my_parent);
}

static int get_flags(int type)
{
  switch(type)
  {
    case IDA_BYTE:
     return byteflag();
    case IDA_WORD:
     return wordflag();
    case IDA_DWORD:
     return dwrdflag();
    case IDA_QWORD:
     return qwrdflag();
    case IDA_FLOAT:
     return floatflag();
    case IDA_DOUBLE:
     return doubleflag();
  }
  return byteflag();
}

// recursive add all members
void PDB_pool::add_members(struc_t *s, struct pdb_class *pc)
{
  if ( !pc )
   return;
  if ( pc->members && pc->members->all )
  {
   struct class_member *cm;
   for ( cm = (struct class_member *)pc->members->fist;
         cm != NULL;
         cm = (struct class_member *)cm->list.next )
   {
     add_struc_member(s, cm->name, cm->index, get_flags(cm->type), NULL, cm->size);
   }
  }
  struct pdb_class *my_parent = get_parent(pc);
  if ( my_parent )
   add_members(s, my_parent);
}

char *PDB_pool::extract_unicode(ea_t ea)
{
  char *n = read_zero_ended_unicode_string(ea);
  if ( !n )
   return NULL;
  char *res = ole2str((wchar_t *)n, -1);
  if ( !res )
  {
    qfree(n);
    return NULL;
  }
  char *ida_res = qstrdup(res);
  free(res);
  qfree(n);
  return ida_res;
}

int PDB_pool::parse_found_string(char *str)
{
// for debugging only
  msg("Static autodetect on \"%s\"\n", str);

  str += what_to_find_len; // AfxWnd
  if ( ! *str )
    return 0;
  int unicode = 0;
  int debug = 0;
  int is_static = 0;
  int version = 0;
  // first - check version of MFC
  if ( str[0] == '4' )
  {
    if ( str[1] == '0' )
      version = 40;
    else if ( str[1] == '2' )
      version = 42;
    else
      return 0;
  }
  else if ( str[0] == '7' )
  {
     if ( str[1] == '0' )
       version = 70;
      else if ( str[1] == '1' )
       version = 71;
      else
       return 0;
  } 
  else if ( str[0] == '1' )
  {
    if ( str[1] == '1' )
      version = 110;
    else if ( str[1] == '2' )
      version = 120;
    else
      version = 100;
  }
  else if ( str[0] == '9' )
  {
    version = 90;
  }
  else if ( str[0] == '8' )
  {
    version = 80;
  } else
    return 0;
  for ( str += 3; *str; str++ )
  {
    switch(*str)
    {
      case 's': is_static = 1;
       break;
      case 'u': unicode = 1;
       break;
      case 'd': debug = 1;
       break;
      default:
       return 0;
    }
  }
  /* lets check if we have .RPD for this combination */
  if ( !is_static )
    return 0;
  if ( debug && unicode )
    return 0;
  char *added = (char *)qalloc(12);
  sprintf(added, "%2.2d\\", version);
  if ( !debug && !unicode )
   strcat(added, "nafxcw");
  else if ( debug && !unicode )
   strcat(added, "nafxcwd");
  else
   strcat(added, "uafxcw");
// for debugging only
  msg("try load static version: %s\n", added);

  add_pdb(added);
  return 1;
}

int PDB_pool::process_found(ea_t ea, int is_unicode)
{
  char *extracted;
  if ( is_unicode )
    extracted = extract_unicode(ea);
  else
    extracted = read_zero_ended_string(ea);
  if ( !extracted )
    return 0;
  int res = parse_found_string(extracted);
  qfree(extracted);
  return res;
}

int PDB_pool::autodetect_static_version()
{
  int s_count = segs.get_area_qty();
  segment_t *s;
  ea_t found;
  int res;
  for ( int i = 0; i < s_count; i++ )
  {
    s = getnseg(i);
    found = bin_search(s->startEA, s->endEA, (uchar *)what_to_find, NULL, what_to_find_len, BIN_SEARCH_FORWARD, BIN_SEARCH_CASE );
    if ( found != BADADDR )
    {
      res = process_found(found);
      return res;
    }
    found = bin_search(s->startEA, s->endEA, (uchar *)what_to_find_unicode, NULL, what_to_find_len << 1, BIN_SEARCH_FORWARD, BIN_SEARCH_CASE );
    if ( found != BADADDR )
    {
      res = process_found(found, 1);
      return res;
    }
  }
  return 0;
}