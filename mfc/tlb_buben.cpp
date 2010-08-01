#include "tlb_buben.h"
#include "mfc_cfg.h"
#include "tlb.h"

tlb_storage *tlb_main = NULL;
struct one_interface *oi_buben = NULL;

void finit_tlb_buben()
{
  if ( tlb_main != NULL )
  {
    delete tlb_main;
    tlb_main = NULL;
  }
}

int init_tlb_buben()
{
  if ( tlb_main )
    return 1;
  if ( !mfc_cfg )
    return 0;
  char *dir = mfc_cfg->tlb_data_dir();
  if ( !dir )
    return 0;
  tlb_main = new tlb_storage();
  return tlb_main->read_dir(dir);
}

char *find_tlb_buben(void *arg)
{
  if ( tlb_main == NULL )
   return NULL;
  IID *iid = (IID *)arg;
  oi_buben = tlb_main->find(iid);
  if ( NULL == oi_buben )
   return NULL;
  return oi_buben->name;
}

void free_buben_methods(struct buben_methods *s, int size)
{
  if ( s == NULL )
   return;
  for ( int i = 0; i < size; i++ )
  {
    if ( s[i].name )
     free(s[i].name);
  }
  free(s);
}

int is_tlb_buben_has_vtbl()
{
  if ( oi_buben == NULL )
   return 0;
  if ( oi_buben->type != TKIND_INTERFACE &&
       oi_buben->type != TKIND_DISPATCH )
   return 0;
  return 1;
}

static char *get_vtbl_name(struct titem *item)
{
  int suffix_len = 0;
  char *suffix = NULL;
  switch( item->kind)
  {
    case INVOKE_FUNC:
     return strdup(item->name);
    case INVOKE_PROPERTYGET:
      suffix = "get_";
      suffix_len = 4;
     break;
    case INVOKE_PROPERTYPUT:
      suffix = "put_";
      suffix_len = 4;
     break;
    case INVOKE_PROPERTYPUTREF:
      suffix = "putref_";
      suffix_len = 7;
     break;
    default:
     return NULL;
  }
  int len = strlen(item->name);
  char *res = (char *)malloc(1 + suffix_len + len);
  strncpy(res, suffix, suffix_len);
  strcpy(res + suffix_len, item->name);
  return res;
}

struct buben_methods *get_buben_vtlb_methods(int &size)
{
  size = 0;
  if ( oi_buben == NULL )
   return NULL;
  size = oi_buben->iface->index_len();
  struct buben_methods *res = (struct buben_methods *)
    malloc( sizeof(struct buben_methods) * size );
  struct id_table *tt = oi_buben->iface->index_table();
  for ( int i = 0; i < size; i++ )
  {
    res[i].name = get_vtbl_name(tt[i].ptr);
    res[i].offset = tt[i].id;
  }
  return res;
}