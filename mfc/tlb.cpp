#include "tlb.h"
#include <stdio.h>
#include <windows.h>

#define MAX_NAMES   64     // max parameters to a function

/* convertation routines */
char *ole2str(OLECHAR *wide, int len)
{
  int count = WideCharToMultiByte(CP_ACP, 0, wide, len, NULL, 0, NULL, NULL);
  char *res = (char *)malloc(count + 1);
  WideCharToMultiByte(CP_ACP, 0, wide, len, res, count, NULL, NULL);
  res[count] = 0;
  return res;
}

OLECHAR *str2ole(char *sz, int len)
{
  int count = MultiByteToWideChar(CP_ACP, 0, sz, len, NULL, NULL);
  OLECHAR *res = (OLECHAR *)malloc((count+1) * sizeof(OLECHAR));
  MultiByteToWideChar(CP_ACP, 0, sz, len, res, count);
  res[count] = 0;
  return res;
}

char *iid2str(IID *iid)
{
  char *res = (char *)malloc(39);
  sprintf(res, "{%.8lX-%.4X-%.4X-%.2X%.2X-%.2X%.2X%.2X%.2X%.2X%.2X}",
   iid->Data1,
   iid->Data2,
   iid->Data3,
   iid->Data4[0],
   iid->Data4[1],
   iid->Data4[2],
   iid->Data4[3],
   iid->Data4[4],
   iid->Data4[5],
   iid->Data4[6],
   iid->Data4[7]
 );
 return res;
}

static char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

static DWORD unhex_dword(char *str)
{
  int i, j;
  char c;
  DWORD res = 0;
  for ( j = 0; j < 8; j++ )
  {
    c = tolower(str[j]);
    for ( i = 0; i <= 15; i++ )
     if ( digits[i] == c )
     {
      res = (res << 4) + i;
      break;
     }
    if ( i >= 15 )
     return 0;
  }
  return res;
}

static WORD unhex_word(char *str)
{
  int i, j;
  char c;
  WORD res = 0;
  for ( j = 0; j < 4; j++ )
  {
    c = tolower(str[j]);
    for ( i = 0; i <= 15; i++ )
     if ( digits[i] == c )
     {
      res = (res << 4) + i;
      break;
     }
    if ( i >= 15 )
     return 0;    
  }
  return res;
}

static BYTE unhex_byte(char *str)
{
  char c;
  int i;
  BYTE res = 0;
  c = tolower(str[0]);
  for ( i = 0; i <= 15; i++ )
     if ( digits[i] == c )
     {
      res = (res << 4) + i;
      break;
     }
  if ( i > 15 )
     return 0;
  c = tolower(str[1]);
  for ( i = 0; i <= 15; i++ )
    if ( digits[i] == c )
     {
      res = (res << 4) + i;
      break;
     }
  if ( i > 15 )
     return 0;
  return res;
}

IID *str2iid(char *str)
{
  static IID res;
  while( *str )
   if ( isspace(*str) )
    str++;
   else
    break;
  if ( *str == '{' )
   str++;
  // read dword
  res.Data1 = unhex_dword(str);
  str += 8;
  if ( *str == '-' )
   str++;
  // read word
  res.Data2 = unhex_word(str);
  str += 4;
  if ( *str == '-' )
   str++;
  // read second word
  res.Data3 = unhex_word(str);
  str += 4;
  if ( *str == '-' )
   str++;
  // read two byte
  res.Data4[0] = unhex_byte(str);
  str += 2;
  res.Data4[1] = unhex_byte(str);
  str += 2;
  if ( *str == '-' )
   str++;
  for ( int i = 0; i < 6; i++, str+= 2 )
   res.Data4[i + 2] = unhex_byte(str);
  return &res;
}

/* * * titem * * */
titem::titem()
{
  name = NULL;
  args_count = 0;
  argz = NULL;
  for_vb = 0;
}

titem::~titem()
{
  /* You cannot free name here because names holded in global dictionary in
   * tlb_storage and one name can be reffered several times from different
   * interfaces */
  if ( argz != NULL )
   free(argz);
}

int titem::process_for_VB(int cArgs)
{
  int res = cArgs;
  switch(kind)
  {
    case INVOKE_FUNC:
      res |= 0x80;
     break;
    case INVOKE_PROPERTYGET:
      res |= 0x100;
     break;
    case INVOKE_PROPERTYPUT:
    case INVOKE_PROPERTYPUTREF:
      res--;
      res |= 0x200;
  }
  for_vb = res;
  return res;
}

/* * * tinterface * * */
tinterface::tinterface()
{
  m_index = NULL;
  m_index_len = 0;
  m_id = NULL;
  m_id_len = 0;
  // reset index vars
  m_indexz = m_idz = 0;
  // reset vars list
  m_vars = NULL;
}

tinterface::~tinterface()
{
  if ( m_vars != NULL )
    delllist(m_vars);

  if ( m_index != NULL )
   free(m_index);

  if ( m_id != NULL )
  {  
   for ( int i = 0; i < m_id_len; i++ )
    delete m_id[i].ptr;
   free(m_id);
  }
}

struct titem *tinterface::by_index(DWORD index)
{
  if ( NULL == m_index )
   return NULL;
  for ( int i = 0; i < m_index_len; i++ )
   if ( m_index[i].id == index )
    return m_index[i].ptr;
  return NULL;
}

char *tinterface::find_var(DWORD id)
{
  if ( m_vars == NULL )
   return NULL;
  for ( struct tvars *tv = (struct tvars *)m_vars->fist;
        tv != NULL;
        tv = (struct tvars *)tv->list.next )
   if ( tv->id == id )
   {
     if ( tv->name )
      return tv->name;
     return "nameless";
   }
  return NULL; // not found
}

struct titem *tinterface::by_ID(DWORD id, int type)
{
  int i;
  int such_ID = 0;
  for ( i = 0; i < m_id_len; i++ )
  {
    if ( m_id[i].id == id )
    {
      if ( m_id[i].ptr->kind == type )
       return m_id[i].ptr;
      such_ID++;
    }
  }
  if ( !such_ID )
   return NULL;
  if (type != INVOKE_PROPERTYPUT && type != INVOKE_PROPERTYPUTREF)
   return NULL;
  for ( i = 0; i < m_id_len; i++ )
  {
    if ( m_id[i].id == id )
    {
      if ( m_id[i].ptr->kind == INVOKE_PROPERTYPUT || 
           m_id[i].ptr->kind == INVOKE_PROPERTYPUTREF )
       return m_id[i].ptr;
    }
  }
  return NULL;
}

int __cdecl tinterface::compare_id_tables(const void *elem1, const void *elem2)
{
  struct id_table *i1 = (struct id_table *)elem1,
                  *i2 = (struct id_table *)elem2;
  if ( i1->id < i2->id )
   return -1;
  if ( i1->id > i2->id )
   return 1;
  return 0;
}

void tinterface::sort(struct id_table *table, int count)
{
  qsort(table, count, sizeof(struct id_table), compare_id_tables);
}

void tinterface::fix_tables()
{
  // sort indexes
  m_indexz = m_index_len;
  if ( m_indexz )
  {
   /* lets check what we have */
   int i;
   int res = 0;
   for ( i = 0; i < m_indexz; i++ )
    if ( m_index[i].id )
    {
      res++;
      break;
    }
   if ( m_indexz > 1 && !res )
   {
     /* My not humble opinion - if we have all zero indexes - lets enum it by myself from 0 */
     for ( i = 0; i < m_indexz; i++ )
       m_index[i].id = i * 4;
   } else
    sort(m_index, m_indexz);
  }
  // sort IDs
  m_idz = m_id_len;
  if ( m_idz )
   sort(m_id, m_idz);
}

/* warning! name in this function will be deleted. You need use result */
char *tinterface::alloc_name(dict_t *dict, char *name)
{
  dnode_t *node = dict_lookup(dict, (const void *)name);
  if ( node != NULL ) // already have such name
  {
    free(name);
    return (char *)dnode_getkey(node);
  }
  dict_alloc_insert(dict, name, NULL);
  return name;
}

struct titem *tinterface::add(struct titem *item, DWORD id, DWORD index)
{
  // first - insert into index list
  m_index[m_indexz].ptr = item;
  m_index[m_indexz].id = index;
  m_indexz++;
  // next - insert into ID list
  m_id[m_idz].ptr = item;
  m_id[m_idz].id = id;
  m_idz++;
 
  return item;
}

int tinterface::get_min_index()
{
  if ( !m_indexz )
   return 0;
  return m_index[0].id;
}

int tinterface::readVars(LPTYPEINFO pti, LPTYPEATTR pattr, MEMBERID memid, dict_t *names_dict)
{
  HRESULT hr = S_OK;
  VARDESC *pvardesc = NULL;
  if ( FAILED(hr = pti->GetVarDesc(memid, &pvardesc)) )
  {
    fprintf(stderr,"Cannot read variable description %X error %X\n",
     memid, hr);
    return 0;
  }
  if ( pvardesc->varkind == VAR_CONST ) // no constant support
    return 0;
  // let extract name of variable
  UINT cNames;
  BSTR rgbstrNames[1];
  if ( FAILED(hr = pti->GetNames( pvardesc->memid, rgbstrNames, 1, (UINT FAR*)&cNames )) )
  {
    fprintf(stderr, "Cannot read variable name %X error %X\n",
     memid, hr);
    return 0;
  }
  if ( m_vars == NULL )
   m_vars = newllist(sizeof(struct tvars));
  struct tvars *tv = (struct tvars *)putobj(m_vars, m_vars->last);
  tv->id = pvardesc->memid;
  tv->VarFlags = pvardesc->wVarFlags;
  if ( rgbstrNames[0] )
   tv->name = alloc_name(names_dict, ole2str(rgbstrNames[0], -1) );
  else
   tv->name = NULL; // (nameless)
  pti->ReleaseVarDesc( pvardesc );
  return 1; // all O`k
}

int tinterface::read(LPTYPEINFO lpTI, LPTYPEATTR lpAttr, dict_t *global_names)
{
  if ( lpAttr->cFuncs )
  {
    m_index_len = lpAttr->cFuncs;
    m_id_len = m_index_len;
  }
  // 19 NOV 2002: added support for dispinterface variables
  if ( lpAttr->typekind == TKIND_DISPATCH && lpAttr->cVars )
   for ( UINT nv = 0; nv < lpAttr->cVars; nv++ )
    readVars(lpTI, lpAttr, nv, global_names);
  if ( m_index_len )
  {
    m_index = (struct id_table *)calloc(m_index_len, sizeof(struct id_table));
  }
  if ( m_id_len )
  {
    m_id = (struct id_table *)calloc(m_id_len, sizeof(struct id_table));
  }
  /* lets enum functions */
  FUNCDESC *pFuncDesc;
  BSTR funcName;
  char *func_name;
  struct titem *f_item;
  BSTR strNames[MAX_NAMES];
  int ui;
  unsigned int cnames;

  for ( unsigned i = 0; i < lpAttr->cFuncs; i++ )
  {
    /* init array with paramz names */
    for ( ui = 0; ui < MAX_NAMES; ui++ )
      strNames[ui] = NULL;

    lpTI->GetFuncDesc(i, &pFuncDesc);
    if ( pFuncDesc == NULL )
    {
      return 1;
      continue;
    }
    lpTI->GetDocumentation( pFuncDesc->memid, &funcName, 0, 0, 0 );
    // get uniq name for this method
    func_name = alloc_name(global_names, ole2str(funcName, -1) );
    SysFreeString(funcName);
    // lets contruct method short description
    f_item = new titem();
    f_item->name = func_name;
    f_item->kind = pFuncDesc->invkind;
    f_item->callconv = pFuncDesc->callconv;
    add(f_item, pFuncDesc->memid, pFuncDesc->oVft);
    /* lets find paramz names */
    if ( S_OK == lpTI->GetNames( pFuncDesc->memid, strNames, MAX_NAMES, &cnames) )
    {
      /* first name is function name - skip it */
      if ( cnames > 1 )
      {
        f_item->args_count = cnames - 1;
        f_item->argz = (struct tfunc_arg *)calloc(f_item->args_count, sizeof(struct tfunc_arg));
        for ( ui = 1; ui < cnames; ui++ )
        {
          if ( strNames[ui] )
            f_item->argz[ui-1].name = alloc_name(global_names, ole2str(strNames[ui], -1));
          f_item->argz[ui-1].type = pFuncDesc->lprgelemdescParam[ui-1].idldesc.wIDLFlags;
        }
      }
      /* free paramz names */
      for ( ui = 0; ui < MAX_NAMES; ui++ )
       if ( strNames[ui] )
         SysFreeString(strNames[ui]);
    }
    f_item->process_for_VB(pFuncDesc->cParams);

    lpTI->ReleaseFuncDesc(pFuncDesc);
  }
  fix_tables();
  return 0;
}

/* * * tlb * * */
tlb::tlb(tlb_storage *ts, LPTYPELIB pI)
{
  m_ts = ts;
  m_TL = pI;
}

tlb::~tlb()
{
  if ( m_TL != NULL )
   m_TL->Release();
}

int tlb::fill()
{
  UINT tiCount = m_TL->GetTypeInfoCount();
  for ( UINT i = 0; i < tiCount; i++ )
  {
    LPTYPEINFO pTI;
    HRESULT hr = m_TL->GetTypeInfo(i, &pTI);
    if ( S_OK == hr )
    {
      fill_typeinfo(pTI);
      pTI->Release();
    }
  }
  return 1;
}

int tlb::fill_coclass(LPTYPEINFO pTI, struct one_interface *oi)
{
  TYPEATTR *pattr = NULL;
  HRESULT hr = S_OK;

  if ( FAILED(hr = pTI->GetTypeAttr(&pattr)) )
   return 1;
  if ( pattr->cImplTypes )
  {
    ITypeInfo*      ptiImpl = NULL;
    TYPEATTR*       pattrImpl = NULL;
    HREFTYPE href = NULL;

    if (FAILED(hr = pTI->GetRefTypeOfImplType(0, &href)))
     goto end;
    if (FAILED(hr = pTI->GetRefTypeInfo( href, &ptiImpl )))
     goto end;
    if (FAILED(hr = ptiImpl->GetTypeAttr( &pattrImpl)))
    {
      ptiImpl->Release();
      goto end;
    }
    memcpy(&oi->first_reffed, &pattrImpl->guid, sizeof(IID));
    ptiImpl->ReleaseTypeAttr( pattrImpl );
    ptiImpl->Release();
    hr = S_OK;
  } else
   return 2; // not content inside coclass
end:
  pTI->ReleaseTypeAttr(pattr);
  return (hr != S_OK);
}

int tlb::fill_typeinfo(LPTYPEINFO pTI)
{
  HRESULT hr;
  TYPEATTR *ta;
  int res;

  hr = pTI->GetTypeAttr(&ta);
  if ( S_OK != hr )
   return 0;  
  struct one_interface *oi = m_ts->add(pTI);
  if ( oi == NULL )
  {
    pTI->ReleaseTypeAttr(ta);
    return NULL;
  }
  /* lets check what kind we have */
  switch( ta->typekind )
  {
    case TKIND_COCLASS:
     res = fill_coclass(pTI, oi);
     if ( res )
     {
       char *str = iid2str(&oi->iid);
       fprintf(stderr, "Cannot load coclass %s (%s)\n", oi->name, str);
       free(str);
     }
     break;
    case TKIND_INTERFACE:
    case TKIND_DISPATCH:
       oi->iface = new tinterface();
       res = oi->iface->read(pTI, ta, m_ts->m_names);
       if ( res )
       {
         char *str = iid2str(&oi->iid);
         fprintf(stderr, "Cannot load interface %s (%s)\n", oi->name, str);
         free(str);
         delete oi->iface;
         oi->iface = NULL;
       }
     break;
  }
  pTI->ReleaseTypeAttr(ta);
  return 1;
}

/* * * tlb_storage * * */
static void free_tlbz(object o)
{
  struct one_tlb *ot = (struct one_tlb *)o;
  if ( ot->tlb != NULL )
   delete ot->tlb;
  free(ot);
}

static int my_iid_cmp(const void *a, const void *b)
{
  IID *aa = (IID *)a,
      *bb = (IID *)b;
  return memcmp(aa, bb, sizeof(IID));
}

static int my_str_cmp(const void *a, const void *b)
{
  return strcmp((const char *)a, (const char *)b);
}

static void kill_m_iid_node(dnode_t *node, void *)
{
  struct one_interface *oi = (struct one_interface *)dnode_get(node);
  if ( oi->name != NULL )
   free(oi->name);
  if ( oi->type == TKIND_INTERFACE ||
       oi->type == TKIND_DISPATCH )
   if ( oi->iface != NULL )
    delete oi->iface;
  free(oi);
  free(node);
}

static void kill_m_dict_node(dnode_t *node, void *)
{
  char *striid = (char *)dnode_getkey(node);
  if ( striid != NULL )
   free(striid);
  free(node);
}

tlb_storage::tlb_storage()
{
  m_co = 0;
  modules = newllist(sizeof(struct one_tlb));
 
  m_iidz = dict_create(DICTCOUNT_T_MAX, my_iid_cmp);
  dict_set_allocator(m_iidz, NULL, kill_m_iid_node, NULL);

  m_dict = dict_create(DICTCOUNT_T_MAX, my_str_cmp);
  dict_set_allocator(m_dict, NULL, kill_m_dict_node, NULL);

  m_names = dict_create(DICTCOUNT_T_MAX, my_str_cmp);
  dict_set_allocator(m_names, NULL, kill_m_dict_node, NULL); // same destructor as in m_dict

  m_reg = NULL;
}

tlb_storage::~tlb_storage()
{
  dict_free(m_iidz);
  dict_destroy(m_iidz);

  dict_free(m_dict);
  dict_destroy(m_dict);

  fast_delllist(modules, free_tlbz);

  dict_free(m_names);
  dict_destroy(m_names);

  if ( m_reg != NULL )
   delete m_reg;

  if ( m_co )
   CoUninitialize();
}

int tlb_storage::init()
{
  if ( m_co )
   return 1;
  if ( S_OK == CoInitialize(0) )
  {
   m_co = 1;
   return 1;
  }
  return 0;
}

int tlb_storage::check_tlbs(IID *iid, int ignore_vb6dup)
{
  struct one_tlb *ot;
  if ( ignore_vb6dup && is_vb64_guid(iid) )
   return 0;
  for ( ot = (struct one_tlb *)modules->fist;
        ot != NULL;
        ot = (struct one_tlb *)ot->list.next )
  {
    if ( !memcmp(&ot->iid, iid, sizeof(IID)) )
     return 1;
  }
  return 0;
}

int tlb_storage::is_vb64_guid(IID *iid)
{
  const IID vb_tlb = { 0xFCFB3D2E, 0xA0FA, 0x1068, { 0xA7, 0x38, 0x08, 0x00, 0x2B, 0x33, 0x71, 0xB5 } };
  return !memcmp(iid, &vb_tlb, sizeof(IID));
}

int tlb_storage::read(char *str)
{
  OLECHAR *name = str2ole(str, -1);
  LPTYPELIB pI;
#ifdef RP_DEBUG
  printf("LOAD %s\n", str);
#endif
  HRESULT hr = LoadTypeLib(name, &pI);
  free(name);
  if ( TYPE_E_CANTLOADLIBRARY == hr )
  {
    char big_buffer[4096];
    int len = GetSystemDirectory(big_buffer, 4096);
    if ( !len )
      return 0;
    if ( big_buffer[len - 1] != '\\' )
    {
      big_buffer[len] = '\\';
      len++;
    }
    strcpy(big_buffer + len, str);
    name = str2ole(big_buffer, -1);
    hr = LoadTypeLib(name, &pI);
    free(name);
  }
  if ( S_OK != hr )
  {
    fprintf(stderr, "LoadLib failed on %s\n", str);
    return 0;
  }
  /* lets check if we already readed this .tlb */
  LPTLIBATTR attr;
  hr = pI->GetLibAttr(&attr);
  if ( S_OK != hr )
  {
    fprintf(stderr, "GetLibAttr failed\n");
    pI->Release();
    return 0;
  }
  if ( check_tlbs(&attr->guid) )
  {
    fprintf(stderr, "Duplicated typelibrary %s\n", str);
    pI->ReleaseTLibAttr(attr);
    pI->Release();
    return 0;
  }
  struct one_tlb *ot = (struct one_tlb *)putobj(modules, modules->last);
  memcpy(&ot->iid, &attr->guid, sizeof(IID));
  pI->ReleaseTLibAttr(attr);
  ot->tlb = new tlb(this, pI);
  return ot->tlb->fill();
}

int tlb_storage::is_tlb(char *fn)
{
  if ( NULL == fn )
   return 0;
  char *ptr;
  int len = strlen(fn);
  ptr = fn + len - 1;
  while( ptr > fn )
  {
   if ( *ptr == '.' )
    break;
   ptr--;
  }
  if ( *ptr != '.' )
   return 0;
  if ( !stricmp(ptr, ".tlb") || !stricmp(ptr, ".olb") )
   return 1;
  return 0;
}

int tlb_storage::read_dir(char *dir)
{
  if ( NULL == dir )
   return 0;

  int len = strlen(dir);
  int slen = len;
  char *fname;
  char *d = (char *)malloc(len + 3);

  strcpy(d, dir);
  if ( d[slen-1] != '\\' )
  {
   d[slen] = '\\';
   slen++;
  }
  d[slen] = '*';
  d[slen+1] = 0;

  WIN32_FIND_DATAA lp;
  HANDLE h = FindFirstFileA(d, &lp);
  free(d);
  if ( h != INVALID_HANDLE_VALUE )
  {
   do {
    if ( FILE_ATTRIBUTE_DIRECTORY == ( lp.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
     goto next;
    if ( !is_tlb(lp.cFileName) )
     goto next;
    fname = (char *)malloc(len + 2 + strlen(lp.cFileName));
    slen = len;
    strcpy(fname, dir);
    if ( fname[slen-1] != '\\' )
    {
      fname[slen] = '\\';
      slen++;
    }
    strcpy(fname + slen, lp.cFileName);
    if ( !read(fname) )
     return 0;
    free(fname);
next:
    if ( !FindNextFileA(h, &lp) )
     break;
   } while(1);
   FindClose(h);
  }
  return 1;
}

struct one_interface *tlb_storage::find(IID *iid, int demand)
{
  dnode_t *node = dict_lookup(m_iidz, (const void *)iid);
  if ( node == NULL )
  {
    if ( !demand )
     return NULL;
    if ( !dynamic_resolve(iid) )
     return NULL;
    node = dict_lookup(m_iidz, (const void *)iid);
    if ( node == NULL )
     return NULL;
  }
  return (struct one_interface *)dnode_get(node);
}

struct one_interface *tlb_storage::find(char *str, int demand)
{
  dnode_t *node = dict_lookup(m_dict, (const void *)str);
  if ( node == NULL )
  {
    if ( !demand )
     return NULL;
    if ( !dynamic_resolve(str) )
     return NULL;
    node = dict_lookup(m_dict, (const void *)str);
    if ( node == NULL )
     return NULL;
  }
  return (struct one_interface *)dnode_get(node);
}

int tlb_storage::dynamic_resolve(IID *iid)
{
  if ( m_reg == NULL )
   m_reg = new tlb_registry;
  char *res = m_reg->get(iid);
  if ( NULL == res )
   return 0;
  int v = read(res);
  free(res);
  return v;
}

int tlb_storage::dynamic_resolve(char *str)
{
  if ( m_reg == NULL )
   m_reg = new tlb_registry;
  char *res = m_reg->get(str);
  if ( NULL == res )
   return 0;
  int v = read(res);
  free(res);
  return v;
}

int tlb_storage::find_TLB(IID *iid)
{
  if ( check_tlbs(iid, 0) )
   return 1;
  if ( m_reg == NULL )
   m_reg = new tlb_registry;
  char *ids = iid2str(iid);
  char *res = m_reg->get_for_typelib(ids);
  free(ids);
  if ( res == NULL )
   return 0; // cannot resolve
  int v = read(res);
  free(res);
  return v;
}

int tlb_storage::find_for_VB4(char *fullname, IID *iid)
{
  struct one_interface *oi = find(iid);
  if ( oi != NULL )
   return 1; // already loaded
  if ( m_reg == NULL )
   m_reg = new tlb_registry;
  char *clsid = m_reg->getCLSIDforFullName(fullname);
  if ( clsid == NULL )
   return 0; // no such control found in this system
  char *resolved = m_reg->get(clsid);
  free(clsid);
  if ( resolved == NULL )
   return 0;
  int v = read(resolved);
  free(resolved);
  return v;
}

struct one_interface *tlb_storage::find_for_FullName(char *name, IID **ppRes)
{
  if ( m_reg == NULL )
   m_reg = new tlb_registry;
  if ( ppRes )
   *ppRes = NULL;
  char *clsid = m_reg->getCLSIDforFullName(name);
  if ( clsid == NULL )
   return NULL;
  // lets check if we already have this CLSID
  struct one_interface *oi = find(clsid, 0);
  if ( oi != NULL )
  {
    free(clsid);
    if ( ppRes )
     *ppRes = &oi->iid;
    return find(&oi->first_reffed,0);
  }
  char *resolved = m_reg->get(clsid);
  if ( resolved == NULL )
  {
   free(clsid);
   return NULL;
  }
  read(resolved);
  free(resolved);
  oi = find(clsid);
  free(clsid);
  if ( oi != NULL && ppRes )
   *ppRes = &oi->iid;
  if ( oi == NULL )
   return NULL;
  return find(&oi->first_reffed,0);
}

struct one_interface *tlb_storage::add(LPTYPEINFO ti)
{
  if ( ti == NULL )
   return NULL;

  HRESULT hr;

  TYPEATTR *ta;
  hr = ti->GetTypeAttr(&ta);
  if ( S_OK != hr )
   return NULL;
  struct one_interface *oi = find(&ta->guid, 0);
  if ( NULL != oi )
  {
    ti->ReleaseTypeAttr(ta);
#ifdef DUP_WARNING
    fprintf(stderr, "Duplicated type %s\n", oi->name);
#endif
    return NULL; // already presented
  }
  /* well we need to add this type */
  BSTR ti_name;
  hr = ti->GetDocumentation(MEMBERID_NIL, &ti_name, 0,0,0);
  if ( hr != S_OK )
  {
    char *guid = iid2str(&ta->guid);
    fprintf(stderr, "Cannot get name for %s\n", guid);
    free(guid);
    ti->ReleaseTypeAttr(ta);
    return NULL;
  }
  oi = (struct one_interface *)malloc(sizeof(struct one_interface));
  oi->type = ta->typekind;
  oi->iface = NULL;
  memcpy(&oi->iid, &ta->guid, sizeof(IID));
  oi->name = ole2str(ti_name, -1);
#ifdef RP_DEBUG
  printf("Add %s %s\n", tkind(oi->type), oi->name);
#endif
  SysFreeString(ti_name);
  ti->ReleaseTypeAttr(ta);
  dict_alloc_insert(m_iidz,  (const void *)&oi->iid, (void *)oi);
  dict_alloc_insert(m_dict, (const void *)iid2str(&oi->iid), (void *)oi);
  return oi;
}

const char *tlb_storage::tkind(int kind)
{
  const char *kindz[] = {
   "Enum",
   "Record",
   "Module",
   "Interface",
   "Dispinterface",
   "Coclass",
   "Alias",
   "Union",
  };
  if ( kind > sizeof(kindz)/sizeof(kindz[0]) )
   return NULL;
  return kindz[kind];
}

static char *find_stub(char *ids)
{
  DWORD type = REG_SZ;
  int len =  38   // {IID}
            +  7  // \CLSID
            + 15  // InprocServer32
            + 1;  // leading zero symbol
  char *key = (char *)malloc(len);
  strcpy(key, "\\CLSID\\");
  strcat(key, ids);
  int mod_len = strlen(key);
  strcat(key, "\\InprocServer32");
  HKEY handle = NULL;
  if ( ERROR_SUCCESS == RegOpenKeyA(HKEY_CLASSES_ROOT, key, &handle) )
  {
    /* there is key InprocServer32 - just return default value for this key */
    DWORD vlen;
    if ( ERROR_SUCCESS == RegQueryValueExA(handle, NULL, NULL, &type, NULL, &vlen) )
    {
      char *res = (char *)malloc(vlen + 1);
      RegQueryValueExA(handle, NULL, NULL, &type, (BYTE *)res, &vlen);
      res[vlen] = 0;
      free(key);
      RegCloseKey(handle);
      return res;
    }
  }
  free(key);
  return NULL;
}

/* registry reader helper class */
char *tlb_registry::get_typelib_for_interface(char *ids, int &skip)
{
  DWORD type = REG_SZ;
  int len =   38 // {IID}
            + 1  // slash
            + 28 // \Interface\TypeLib | ProxyStubClsid32
            + 1; // leading zero symbol
  skip = 0;
  char *key = (char *)malloc(len);
  strcpy(key, "\\Interface\\");
  strcat(key, ids);
  strcat(key, "\\TypeLib");
  DWORD vlen;
  HKEY handle;
  if ( ERROR_SUCCESS != RegOpenKeyA(HKEY_CLASSES_ROOT, key, &handle) )
  {
    strcpy(key + 38 + 1 + 11, "ProxyStubClsid32");
    if ( ERROR_SUCCESS == RegOpenKeyA(HKEY_CLASSES_ROOT, key, &handle) )
    {
      char st_buf[40];
      vlen = 40;
      if ( ERROR_SUCCESS == RegQueryValueExA(handle, NULL, NULL, &type, PBYTE(st_buf), &vlen) )
      {
        char *what = find_stub(st_buf);
        skip = 1;
        free(key);
        RegCloseKey(handle);
        return what;
      }
      RegCloseKey(handle);
    }
    free(key);
    return NULL;
  }
  free(key);
  char *res = NULL;
  if ( ERROR_SUCCESS == RegQueryValueExA(handle, NULL, NULL, &type, NULL, &vlen) )
  {
    res = (char *)malloc(vlen + 1);
    RegQueryValueExA(handle, NULL, NULL, &type, (BYTE *)res, &vlen);
    res[vlen] = 0;
  }
  RegCloseKey(handle);
  return res;
}

char *tlb_registry::get(IID *iid)
{
  char *ids = iid2str(iid);
  char *res = get_internal(ids);
  if ( NULL != res )
  {
    free(ids);
    return res;
  }
  for ( char *ptr = ids; *ptr; ptr++ )
   *ptr = tolower(*ptr);
  res = get_internal(ids);
  free(ids);
  return res;
}

char *tlb_registry::get(char *str)
{
  char *res = get_internal(str);
  if ( NULL != res )
   return res;
  char *ptr;
  for ( ptr = str ; *ptr ; ptr++ )
   *ptr = tolower(*ptr);
  res = get_internal(str); 
  if ( res != NULL )
   return res;
  for ( ptr = str; *ptr; ptr++ )
   *ptr = toupper(*ptr);
  return get_internal(str);
}

/* terrible function - try to get filename where is located object with IID */
char *tlb_registry::get_internal(char *ids)
{
  DWORD type = REG_SZ;
  int len =   38  // {IID}
            +  7  // \CLSID
            + 15  // \InProcServer32
            +  1; // leading zero symbol
  char *key = (char *)malloc(len);
  strcpy(key, "\\CLSID\\");
  strcat(key, ids);
  int mod_len = strlen(key);
  strcat(key, "\\InprocServer32");
  HKEY handle = NULL;
  if ( ERROR_SUCCESS == RegOpenKeyA(HKEY_CLASSES_ROOT, key, &handle) )
  {
    /* there is key InprocServer32 - just return default value for this key */
    DWORD vlen;
    if ( ERROR_SUCCESS == RegQueryValueExA(handle, NULL, NULL, &type, NULL, &vlen) )
    {
      char *res = (char *)malloc(vlen + 1);
      RegQueryValueExA(handle, NULL, NULL, &type, (BYTE *)res, &vlen);
      res[vlen] = 0;
      free(key);
      RegCloseKey(handle);
      return res;
    }
  }
  if ( handle != NULL )
   RegCloseKey(handle);
  handle = NULL;
  /* Lets try TreatAs key */
  strcpy(key + mod_len, "\\TreatAs");
  if ( ERROR_SUCCESS == RegOpenKeyA(HKEY_CLASSES_ROOT, key, &handle) )
  {
    DWORD vlen;
    type = REG_SZ;
    if ( ERROR_SUCCESS == RegQueryValueExA(handle, NULL, NULL, &type, NULL, &vlen) )
    {
      char *res = (char *)malloc(vlen + 1);
      RegQueryValueExA(handle, NULL, NULL, &type, (BYTE *)res, &vlen);
      res[vlen] = 0;
      free(key);
      RegCloseKey(handle);
      char *res2 = get(res); // yeah - recursion
      free(res);
      return res2;
    }
  }
  if ( handle != NULL )
   RegCloseKey(handle);
  handle = NULL;
  /* hm, there is no InprocServer32 key. Lets try typelib ? */
  strcpy(key + mod_len, "\\TypeLib");
  if ( ERROR_SUCCESS == RegOpenKeyA(HKEY_CLASSES_ROOT, key, &handle) )
  {
    DWORD vlen;
    type = REG_SZ;
    if ( ERROR_SUCCESS == RegQueryValueExA(handle, NULL, NULL, &type, NULL, &vlen) )
    {
      char *res = (char *)malloc(vlen + 1);
      RegQueryValueExA(handle, NULL, NULL, &type, (BYTE *)res, &vlen);
      res[vlen] = 0;
      free(key);
      RegCloseKey(handle);
      char *res2 = get_for_typelib(res);
      free(res);
      return res2;
    }
  }
  /* Yo! May be this is interface ? */
  if ( handle != NULL )
   RegCloseKey(handle);
  int skip = 0;
  char *iface = get_typelib_for_interface(ids, skip);
  if ( iface != NULL )
  {
    free(key);
    if ( skip )
      return iface;
    char *res = get_for_typelib(iface);
    free(iface);
    return res;
  }
  /* HZ what is it */
  free(key);
  return NULL;
}

char *tlb_registry::get_for_typelib(char *ids)
{
  char *key;
  int len =  38  // {GUID}
            + 9  // /TypeLib/
            + 1; // leading zero
  key = (char *)malloc(len);
  strcpy(key, "\\TypeLib\\");
  strcat(key, ids);
  char *res = resolve_tlb(key);
  if ( NULL != res )
  {
    free(key);
    return res;
  }
  char *ptr;
  for ( ptr = key + 10; *ptr; ptr++ )
   *ptr = tolower(*ptr);
  res = resolve_tlb(key);
  if ( NULL != res )
  {
    free(key);
    return res;
  }
  for ( ptr = key + 10; *ptr; ptr++ )
   *ptr = toupper(*ptr);
  res = resolve_tlb(key);
  free(key);
  return res;
}

DWORD tlb_registry::unhex(char *ptr)
{
  DWORD res = 0;
  int c;
  int i;
  for ( ; *ptr; ptr++ )
  {
    c = tolower(*ptr);
    for ( i = 0; i <= 15; i++ )
     if ( digits[i] == c )
     {
      res = (res << 4) + i;
      break;
     }
    if ( i >= 15 )
     return 0;
  }
  return res;
}

/* Get subkey for win32 entry */
int tlb_registry::get_win32_subkey(char *section)
{
  HKEY handle;
  if ( ERROR_SUCCESS != RegOpenKeyA(HKEY_CLASSES_ROOT, section, &handle) )
   return 0;

  char sbuf[1024];
  int max = 0;
  int curr;
  DWORD index = 0;
  DWORD vlen;

  for ( vlen = 1023;
        ERROR_SUCCESS == RegEnumKeyExA(handle, index, sbuf, &vlen, NULL, NULL, NULL, NULL); 
        vlen = 1023, index++ )
  {
    if ( !isdigit(*sbuf) )
     continue; // bad key
    curr = atoi(sbuf);
    if ( curr > max )
     max = curr;
  }
  RegCloseKey(handle);
  return max;
}

/* Horror function for typelibrary location resolving */
char *tlb_registry::resolve_tlb(char *key)
{
  HKEY handle;
  if ( ERROR_SUCCESS != RegOpenKeyA(HKEY_CLASSES_ROOT, key, &handle) )
   return NULL;
  // hm, we opened some TypeLib subkey. Lets enum it to find major version
  DWORD index = 0;
  DWORD vlen = 0;
  DWORD m1 = 0, m2 = 0;
  DWORD mm1, mm2;
  char sbuf[1024];
  char *major = NULL;

  for ( vlen = 1023; 
        ERROR_SUCCESS == RegEnumKeyExA(handle, index, sbuf, &vlen, NULL, NULL, NULL, NULL); 
        vlen = 1023, index++ )
  {
    char *c = strchr(sbuf, '.');
    if ( NULL == c )
     continue; // bad key
    if ( major == NULL )
    {
      major = strdup(sbuf);
      *c = 0;
      mm1 = unhex(sbuf);
      mm2 = unhex(c + 1);
      continue;
    }
    *c = 0;
    m1 = unhex(sbuf);
    m2 = unhex(c + 1);
    if ( m1 < mm1 )
     continue;
    if ( m1 > mm1 || m2 >= mm2 )
    {
      mm1 = m1;
      mm2 = m2;
      *c = '.';
      if ( major != NULL )
       free(major);
      major = strdup(sbuf);
    }
  }
  RegCloseKey(handle);
  if ( NULL == major )
   return NULL;
  int len = strlen(key) + 1 + strlen(major) + 1 + 9;
  char *last = (char *)malloc(len);
  strcpy(last, key);
  strcat(last, "\\");
  strcat(last, major);
  free(major);
  sprintf(last + strlen(last), "\\%d\\win32", get_win32_subkey(last) );
  char *res = NULL;
  if ( ERROR_SUCCESS == RegOpenKeyA(HKEY_CLASSES_ROOT, last, &handle) )
  {
    DWORD vlen = 0;
    DWORD type = REG_SZ;
    if ( ERROR_SUCCESS == RegQueryValueExA(handle, NULL, NULL, &type, NULL, &vlen) )
    {
      res = (char *)malloc(vlen + 1);
      type = REG_SZ;
      RegQueryValueExA(handle, NULL, NULL, &type, (BYTE *)res, &vlen);
      res[vlen] = 0;
    }
  }
  free(last);
  if ( NULL != handle )
   RegCloseKey(handle);
  return res;
}

/* 13 NOV 2002: support for searching OCX by full name of object */
// Warning: you are responsible for freeing returned string !
char *tlb_registry::getCLSIDforFullName(char *fname)
{
  HKEY handle;
  if ( fname == NULL )
   return NULL;
  int len = strlen(fname);
  char *key = (char *)malloc(7 + len);
  strcpy(key, fname);
  strcat(key, "\\CLSID");
  if ( ERROR_SUCCESS != RegOpenKeyA(HKEY_CLASSES_ROOT, key, &handle) )
  {
   free(key);
   return NULL;
  }
  // lets read default value
  key = (char *)malloc(50); // I think this value is enough
  DWORD type;
  len = 50;
  int result = RegQueryValueExA(handle, NULL, NULL, &type, (PBYTE)key, (PDWORD)&len);
  RegCloseKey(handle);
  if ( result == ERROR_SUCCESS )
   return key;
  free(key);
  return NULL;
}
