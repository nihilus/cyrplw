#include <ida.hpp>
#include "hierarchy.h"
#include <stdlib.h>
#include <string.h>

/*** * * pdb_class * * ***/
pdb_class::pdb_class(char *name)
{
  new_added = 1;
  size = 0;
  m_name = name;
  type = 0;
  number = 0;
  parents = NULL;
  vtbls = NULL;
  members = NULL;
}

void pdb_class::free_parents()
{
  if ( parents )
  {
    struct pdb_parent *pd, *next_pd;
    for ( pd = (struct pdb_parent *)parents->fist;
          pd != NULL;
          pd = next_pd )
    {
      next_pd = (struct pdb_parent *)pd->list.next;
      if ( pd->what == 2 && pd->name )
        free(pd->name);
      free(pd);
    } 
    free(parents);
    parents = NULL;
  }
}

void pdb_class::free_vtbls()
{
  if ( vtbls )
  {
    struct vtbl_method *vm, *next_vm;
    for ( vm = (struct vtbl_method *)vtbls->fist;
          vm != NULL;
          vm = next_vm )
    {
      next_vm = (struct vtbl_method *)vm->list.next;
      if ( vm->name )
       free(vm->name);
      free(vm);
    }
    free(vtbls);
    vtbls = NULL;
  }
}

void pdb_class::free_members()
{
  if ( members )
  {
    struct class_member *cm, *next_cm;
    for ( cm = (struct class_member *)members->fist;
          cm != NULL;
          cm = next_cm )
    {
      next_cm = (struct class_member *)cm->list.next;
      if ( cm->name )
        free(cm->name);
      free(cm);
    }
    free(members);
    members = NULL;
  }
}

pdb_class::~pdb_class()
{
  // free parents list
  free_parents();
  // free vtbl list
  free_vtbls();
  // free members
  free_members();
}

int pdb_class::find_right_range()
{
  if ( !vtbls || !vtbls->all )
   return 0;
  struct vtbl_method *vm;
  unsigned long max = 0;
  for ( vm = (struct vtbl_method *)vtbls->fist;
        vm != NULL;
        vm = (struct vtbl_method *)vm->list.next )
  {
    if ( vm->index > max )
      max = vm->index;
  }
  // O`k, lets check parents depth of VBTL
  if ( !parents || parents->all != 1 )
    return max;
  struct pdb_parent *pp = (struct pdb_parent *)parents->fist;
  if ( pp->what != 3 )
    return max;
  int p_max = pp->c->find_right_range();
  if ( p_max > max )
    max = p_max;
  return max;
}

struct vtbl_method *pdb_class::by_offset(unsigned long offset)
{
  if ( !vtbls || !vtbls->all )
   return NULL;
  // lets check in my class first
  struct vtbl_method *vm;
  for ( vm = (struct vtbl_method *)vtbls->fist;
        vm != NULL;
        vm = (struct vtbl_method *)vm->list.next )
  {
    if ( vm->index == offset )
     return vm;
    if ( vm->index > offset )
     break;
  }
  // check if have only one parent
  if ( !parents || parents->all != 1 )
    return NULL;
  struct pdb_parent *pp = (struct pdb_parent *)parents->fist;
  if ( pp->what != 3 )
    return NULL;
  return pp->c->by_offset(offset);
}

static char *find_first_bracket(char *name)
{
  if ( !name || !*name )
   return NULL;
  char *ptr;
  for ( ptr = name; *ptr; ptr++ )
  {
    if ( *ptr == '(' )
     return ptr;
  }
  return NULL;
}

static char *find_prev_space(char *start, char *from)
{
  while( from >= start )
  {
    if ( *from == ' ' )
     return from + 1;
    from--;
  }
  return start;
}

static char *find_second_colon(char *start)
{
  if ( !start || !*start )
   return NULL;
  char *ptr;
  for ( ptr = start; *ptr; ptr++ )
  {
    if ( *ptr == ':' )
    {
      ptr++;
      if ( *ptr == ':' )
       return ptr + 1;
      return ptr;
    }
  }
  return NULL;
}

// Warning: you responsible for freeing of returned string !
char *vtbl_method::get_name_only()
{
  char *from = name;
  if ( name_start )
    from = name + name_start;
  char *br = find_first_bracket(from);
  if ( name_start )
  {
    int len = strlen(from);
    if ( br )
     len = br - from;
    char *res = (char *)malloc(len + 1);
    strncpy(res, from, len);
    res[len] = 0;
    // lets check for ::
    char *colon = find_second_colon(res);
    if ( !colon )
     return res;
    for( br = res; *colon; br++, colon++ )
    {
      *br = *colon;
    }
    *br = *colon;
    return res;
  }
  if ( !br )
   return _strdup(name);
  from = find_prev_space(from, br);
  int len = br - from - 1;
  char *res = (char *)malloc(len + 1);
  strncpy(res, from, len);
  res[len] = 0;
  // lets check for ::
  char *colon = find_second_colon(res);
  if ( !colon )
   return res;
  for( br = res; *colon; br++, colon++ )
  {
    *br = *colon;
  }
  *br = *colon;
  return res;
}

void vtbl_method::set_name_only(char *only_name)
{
  char *w = strstr(name, only_name);
  if ( NULL != w )
  {
    name_start = w - name;
  } else {
    name_start = 0;
  }
  free(only_name);
}

struct vtbl_method *pdb_class::add(object after, char *name, unsigned long index)
{
  struct vtbl_method *vm = (struct vtbl_method *)putobj(vtbls, after);
  vm->index = index;
  vm->owner = this;
  vm->name = name;
  vm->len = strlen(name);
  vm->name_start = 0;
  return vm;
}

struct class_member *pdb_class::add_m(object after, char *name, unsigned long index)
{
  struct class_member *cm = (struct class_member *)putobj(members, after);
  cm->owner = this;
  cm->index = index;
  cm->type = 0;
  cm->size = 1; // default size is 1 byte
  // name can contains :: so lets check it
  char *is_colon = find_second_colon(name);
  if ( !is_colon )
  {
    cm->name = name;
  } else {
    cm->name = _strdup(is_colon);
    free(name);
  }
  return cm;
}

struct class_member *pdb_class::add_member(char *name, unsigned long index)
{
  if ( !name || !*name )
   return NULL;
  if ( members == NULL )
  {
    members = newllist(sizeof(struct class_member));
    return add_m(NULL, name, index);
  }
  // lets check if we already have such member
  struct class_member *cm;
  for ( cm = (struct class_member *)members->fist;
        cm != NULL;
        cm = (struct class_member *)cm->list.next )
  {
    if ( cm->index > index )
     return add_m(cm->list.prev, name, index);
    if ( cm->index == index )
    {
      free(name);
      return NULL; // already inserted ?
    }
  }
  return add_m(members->last, name, index);
}

int pdb_class::is_zero_method(char *name, unsigned long *index)
{
  if ( strstr(name, "Release()") )
  {
    if ( !*index )
     *index = 2 * sizeof(ea_t);
    return 1;
  }
  if ( strstr(name, "AddRef()") )
  {
    if ( !*index )
     *index = sizeof(ea_t);
    return 1;
  }
  if ( strstr(name, "QueryInterface") )
   return 1;
  if ( strstr(name, "GetRuntimeClass()") )
   return 1;
  return 0;
}

struct vtbl_method *pdb_class::add_method(char *name, unsigned long index, bool add_zero)
{
  if ( !index && !add_zero && !is_zero_method(name, &index) )
   return NULL; // for index == 0 we just skip adding
  if ( vtbls == NULL )
  {
    vtbls = newllist(sizeof(struct vtbl_method));
    return add(NULL, name, index);
  }
  // lets check if we already have such method
  struct vtbl_method *vm;
  for ( vm = (struct vtbl_method *)vtbls->fist;
        vm != NULL;
        vm = (struct vtbl_method *)vm->list.next )
  {
    if ( vm->index > index )
     return add(vm->list.prev, name, index);
    if ( vm->index == index )
    {
      free(name);
      return NULL; // aready inserted ?
    }
  }
  return add(vtbls->last, name, index);
}

char *pdb_class::read_string(FILE *fp, int *out_len)
{
  int len = 0;
  fread(&len, 4, 1, fp);
  if ( out_len )
   *out_len = len;
  if ( !len )
   return NULL;
  char *res = (char *)malloc(len + 1);
  fread(res, len, 1, fp);
  res[len] = 0;
  return res;
}

// read constructor
pdb_class::pdb_class(FILE *fp)
{
  parents = NULL;
  vtbls = NULL;
  members = NULL;
  m_name = NULL;
  // first - lets read our index
  fread(&this->number, 4, 1, fp);
  // second - read type ID
  char c = fgetc(fp);
  this->type = c;
  // third - name
  m_name = read_string(fp, NULL);
  // fourth - size
  fread(&this->size, 4, 1, fp);
  // parents list
  int size = 0;
  fread(&size, 4, 1, fp);
  if ( size )
  {
    parents = newllist(sizeof(struct pdb_parent));
    struct pdb_parent *pp;
    for ( int i = 0; i < size; i++ )
    {
      pp = (struct pdb_parent *)putobj(parents, parents->last);
      c = fgetc(fp);
      pp->what = c;
      switch(c)
      {
        case 3: // ref
          pp->what = 1;
        case 1: // number
          fread(&pp->number, 4, 1, fp);
         break;
        case 2: // name
          pp->name = read_string(fp, NULL);
         break;
      }
    }
  }
  // read all virtual methods
  size = 0;
  fread(&size, 4, 1, fp);
  if ( size )
  {
    vtbls = newllist(sizeof(struct vtbl_method));
    struct vtbl_method *vm;
    for ( int i = 0; i < size; i++ )
    {
      vm = (struct vtbl_method *)putobj(vtbls, vtbls->last);
      fread(&vm->index, sizeof(vm->index), 1, fp);
      vm->name = read_string(fp, &vm->len);
      fread(&vm->name_start, sizeof(vm->name_start), 1, fp);
    }
  }
  // read all class members
  size = 0;
  fread(&size, 4, 1, fp);
  if ( size )
  {
    members = newllist(sizeof(struct class_member));
    struct class_member *cm;
    int fake_len;
    for ( int i = 0; i < size; i++ )
    {
      cm = (struct class_member *)putobj(members, members->last);
      fread(&cm->index, sizeof(cm->index), 1, fp);
      fread(&cm->type, sizeof(cm->type), 1, fp);
      fread(&cm->size, sizeof(cm->size), 1, fp);
      cm->name = read_string(fp, &fake_len);
    }
  } 
}

int pdb_class::write(FILE *fp)
{
  // first - lets write our index
  fwrite(&this->number, 4, 1, fp);
  // second - lets write type ID
  char typeID = (char)type;
  fputc(typeID, fp);
  // third - lets write our name
  int len = strlen(m_name);
  fwrite(&len, 4, 1, fp);
  if ( len )
   fwrite(m_name, len, 1, fp);
  // fourth - write size
  fwrite(&this->size, 4, 1, fp);
  // next lets write parents graph
  int size = 0;
  if ( parents )
    size = parents->all;
  fwrite(&size, 4, 1, fp);
  if ( size )
  {
    struct pdb_parent *pp;
    for ( pp = (struct pdb_parent *)parents->fist;
          pp != NULL;
          pp = (struct pdb_parent *)pp->list.next )
    {
      typeID = (char)pp->what;
      fputc(typeID, fp);
      switch(typeID)
      {
        case 1: // number
          fwrite(&pp->number, 4, 1, fp);
         break;
        case 2: // name
          len = strlen(pp->name);
          fwrite(&len, 4, 1, fp);
          if ( len )
           fwrite(pp->name, len, 1, fp);
         break;
        case 3: // ref to pdb_class
          fwrite(&pp->c->number, 4, 1, fp);
         break;
      }
    }
  }
  // write all virtual methods
  size = 0;
  if ( vtbls )
   size = vtbls->all;
  fwrite(&size, 4, 1, fp);
  if ( size )
  {
    struct vtbl_method *vm;
    for ( vm = (struct vtbl_method *)vtbls->fist;
          vm != NULL;
          vm = (struct vtbl_method *)vm->list.next )
    {
      fwrite(&vm->index, sizeof(vm->index), 1, fp);
      fwrite(&vm->len, sizeof(vm->len), 1, fp);
      if ( vm->len )
        fwrite(vm->name, vm->len, 1, fp);
      fwrite(&vm->name_start, sizeof(vm->name_start), 1, fp);
    }
  }
  // write all methods
  size = 0;
  if ( members )
    size = members->all;
  fwrite(&size, 4, 1, fp);
  if ( size )
  {
    struct class_member *cm;
    int cm_name_len;
    for ( cm = (struct class_member *)members->fist;
          cm != NULL;
          cm = (struct class_member *)cm->list.next )
    {
      fwrite(&cm->index, sizeof(cm->index), 1, fp);
      fwrite(&cm->type, sizeof(cm->type), 1, fp);
      fwrite(&cm->size, sizeof(cm->size), 1, fp);
      // write cm->name
      cm_name_len = 0;
      if ( cm->name )
       cm_name_len = strlen(cm->name);
      fwrite(&cm_name_len, sizeof(cm_name_len), 1, fp);
      if ( cm_name_len )
       fwrite(cm->name, cm_name_len, 1, fp);
    }
  }
  return 1;
}

const char *pdb_class::what_type()
{
  switch(type)
  {
    case DIAID_STRUCT:
      return "struct";
    case DIAID_CLASS:
      return "class";
    case DIAID_UNION:
      return "union";
  }
  return NULL;
}

const char *class_member::get_ida_type()
{
  switch(type)
  {
    case IDA_BYTE:
     return "BYTE";
    case IDA_WORD:
     return "WORD";
    case IDA_DWORD:
     return "DWORD";
    case IDA_QWORD:
     return "QWORD";
    case IDA_FLOAT:
     return "FLOAT";
    case IDA_DOUBLE:
     return "DOUBLE";
  }
  return "Unknown_IDA_type";
}

void pdb_class::dump(FILE *out)
{
  fprintf(out, "%s %s", what_type(), m_name);
  if ( parents && parents->all )
  {
    fprintf(out, " :");
    struct pdb_parent *pp;
    for ( pp = (struct pdb_parent *)parents->fist;
          pp != NULL;
          pp = (struct pdb_parent *)pp->list.next )
    {
      switch(pp->what)
      {
        case 1:
          fprintf(out, " indexed class %X", pp->number);
         break;
        case 2:
          fprintf(out, " named class %s", pp->name);
         break;
        case 3:
          fprintf(out, " %s", pp->c->m_name);
         break;
      }
      if ( pp->list.next )
       fprintf(out, " , ");
    }
  }
  fprintf(out, "\n");
  fprintf(out, "Size %X\n", this->size);
  if ( get_vtbl_count() )
  {
    fprintf(out, "VTBL:\n");
    struct vtbl_method *vm;
    char *only_name;
    for ( vm = (struct vtbl_method *)vtbls->fist;
          vm != NULL;
          vm = (struct vtbl_method *)vm->list.next )
    {
     only_name = vm->get_name_only();
     fprintf(out, "[%X] %s\n", vm->index, vm->name);
     fprintf(out, "\t[%d] %s\n", vm->name_start, only_name);
     free(only_name);
    }
  }
  if ( get_member_count() )
  {
    fprintf(out, "Memberz:\n");
    struct class_member *cm;
    const char *what;
    for ( cm = (struct class_member *)members->fist;
          cm != NULL;
          cm = (struct class_member *)cm->list.next )
    {
      what = cm->get_ida_type();
      fprintf(out, " [%X] %d %s - %s\n", cm->index, cm->size, cm->name, what);
    }
  }
  fprintf(out, "\n");
}

/*** * * CPdb * * ***/
int cmp2string(const void *a, const void *b)
{
  return strcmp((const char *)a, (const char *)b);
}

int cmp2int(const void *a, const void *b)
{
  int aa = (int)a;
  int bb = (int)b;
  if ( aa < bb )
    return -1;
  if ( aa > bb )
    return 1;
  return 0;
}

static void delete_pdb_node(dnode_t *node, void *unused)
{
  struct pdb_class *pc = (struct pdb_class *)dnode_get(node);
  if ( pc )
   delete pc;
  char *name = (char *)dnode_getkey(node);
  if ( name )
   free(name);
  free(node);
}

CPdb::CPdb()
{
  m_numeral = NULL;
  m_storage = dict_create(DICTCOUNT_T_MAX, cmp2string);
  dict_set_allocator(m_storage, NULL, delete_pdb_node, NULL);
}

CPdb::~CPdb()
{
  if ( m_numeral )
  {
    dict_free(m_numeral);
    dict_destroy(m_numeral);
  }
  if ( m_storage )
  {
    dict_free(m_storage);
    dict_destroy(m_storage);
  }
}

struct pdb_class * CPdb::add_class(char *name, int type)
{
  dnode_t *node = dict_lookup(m_storage, (const void *)name);
  struct pdb_class *pc;
  if ( node != NULL )
  {
    pc = (struct pdb_class *)dnode_get(node);
    pc->type = type;
    pc->new_added = 0;
    return pc;
  }
  pc = new pdb_class(name);
  pc->type = type;
  dict_alloc_insert(m_storage, (const void *)name, pc);
  return pc;
}

int CPdb::numerate_before_writing()
{
  if ( m_storage == NULL )
   return NULL;
  dnode_t *node;
  struct pdb_class *pc;
  int enumerator = 1;
  for ( node = dict_first(m_storage); 
        node != NULL; 
        enumerator++, node = dict_next(m_storage, node) )
  {
    pc = (struct pdb_class *)dnode_get(node);
    pc->number = enumerator;
  }
  return 1;
}

// Warning - when you add parent I responsible for deleting of name arg !
int CPdb::addparent(lnlist list, object after, char *name)
{
  dnode_t *node = dict_lookup(m_storage, (const void *)name);
  struct pdb_parent *pp = (struct pdb_parent *)putobj(list, after);
  if ( node )
  {
    pp->what = 3;
    pp->c = (struct pdb_class *)dnode_get(node);
    free(name);
  } else {
    pp->what = 2;
    pp->name = name;
  }
  return 1;
}

int CPdb::add_parent(struct pdb_class *to, char *name)
{
  if ( to->parents == NULL )
  {
    to->parents = newllist(sizeof(struct pdb_parent));
    return addparent(to->parents, NULL, name);
  } else
    return addparent(to->parents, to->parents->last, name);
}

void CPdb::fix_parents_list(lnlist list)
{
  struct pdb_parent *pp;
  for ( pp = (struct pdb_parent *)list->fist;
        pp != NULL;
        pp = (struct pdb_parent *)pp->list.next )
  {
    if ( pp->what == 3 )
     continue;
    if ( pp->what == 2 )
    {
      dnode_t *node = dict_lookup(m_storage, (const void *)pp->name);
      if ( node )
      {
        free(pp->name);
        pp->c = (struct pdb_class *)dnode_get(node);
        pp->what = 3;
      }
      continue;
    }
    if ( pp->what == 1 && m_numeral )
    {
      dnode_t *node = dict_lookup(m_numeral, (const void *)pp->number);
      if ( node )
      {
        pp->c = (struct pdb_class *)dnode_get(node);
        pp->what = 3;
      }
      continue;
    }
  }
}

void CPdb::fix_parents()
{
  dnode_t *node;
  struct pdb_class *pc;
  for ( node = dict_first(m_storage); node != NULL; node = dict_next(m_storage, node) )
  {
    pc = (struct pdb_class *)dnode_get(node);
    if ( !pc->parents )
     continue;
    fix_parents_list(pc->parents);
  }
}

int CPdb::write(FILE *fp)
{
  char sign[4];
  /* Initializations before writing */
  sign[0] = 'R';
  sign[1] = 'P';
  sign[2] = 'd';
  sign[3] = 'b';
  numerate_before_writing();
  fix_parents();
  // write signature
  fwrite(sign, 4, 1, fp);
  // write count of classes
  unsigned long count = dict_count(m_storage);
  fwrite(&count, 4, 1, fp);
  // next lets write all classes
  dnode_t *node;
  struct pdb_class *pc;
  for ( node = dict_first(m_storage); node != NULL; node = dict_next(m_storage, node) )
  {
    pc = (struct pdb_class *)dnode_get(node);
    pc->write(fp);
  }
  return 1; // all O`k
}

int CPdb::read(FILE *fp)
{
  char sign[4];
  // lets read signature
  fread(&sign, 4, 1, fp);
  if ( sign[0] != 'R' ||
       sign[1] != 'P' || 
       sign[2] != 'd' ||
       sign[3] != 'b' )
    return 1;
  dict_free(m_storage);
  unsigned long count = 0;
  fread(&count, 4, 1, fp);
  if ( !count )
    return 0; // empty file ?
  // some initializations
  if ( m_numeral == NULL )
  {
    m_numeral = dict_create(DICTCOUNT_T_MAX,cmp2int);
  } else {
    dict_free(m_numeral);
  }
  // lets read all classes
  struct pdb_class *pc;
  for ( unsigned long i = 0; i < count; i++ )
  {
    pc = new pdb_class(fp);
    if ( pc )
    {
      dict_alloc_insert(m_storage, (const void *)pc->m_name, pc);
      dict_alloc_insert(m_numeral, (const void *)pc->number, pc);
    }
  }
  // post-reading processing
  fix_parents();
  return 0;
}

struct pdb_class *CPdb::find_class(char *name)
{
  if ( m_storage == NULL )
   return NULL;
  dnode_t *node = dict_lookup(m_storage, (const void *)name);
  if ( NULL == node )
   return NULL;
  return (struct pdb_class *)dnode_get(node);
}

struct pdb_class *CPdb::find_class(int index)
{
  if ( m_numeral == NULL )
   return NULL;
  dnode_t *node = dict_lookup(m_numeral, (const void *)index);
  if ( NULL == node )
   return NULL;
  return (struct pdb_class *)dnode_get(node);
}

void CPdb::dump(FILE *out)
{
  if ( !m_storage )
   return;
  dnode_t *node;
  struct pdb_class *pc;
  for ( node = dict_first(m_storage); node != NULL; node = dict_next(m_storage, node) )
  {
    pc = (struct pdb_class *)dnode_get(node);
    pc->dump(out);
  }
}