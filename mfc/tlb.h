#ifndef TLB_H
# define TLB_H	"Typelibrary class"

#include <windows.h>
// #include <ocidl.h>

#include "dict.h"
#include "llist.h"

/* Achtung ! 
 * You are responsible for freeing memory returned by functions below */
extern "C" char *ole2str(OLECHAR *,int);
extern "C" OLECHAR *str2ole(char *,int);
extern "C" char *iid2str(IID *);
extern "C" IID *str2iid(char *);

/* declaration */
class tlb;
class tlb_storage;
class tinterface;

struct tfunc_arg
{
  char *name; // name of arg. Don`t free - alloced in global names dict !
  int type;   // actually field lprgelemdescParam[n].idldesc.wIDLFlags
};

struct tvars
{
  struct list list;
  DWORD id;
  char *name;
  DWORD VarFlags;  
};

struct titem
{
  titem();
  ~titem();
  int process_for_VB(int);

  char *name; // name of method. Don`t free - alloced in global names dict !
  int kind;   // kind of method
  int for_vb; // dirty hack - VB acceptable property of method
  int callconv; // calling convention
  int args_count;
  struct tfunc_arg *argz;
};

/* We need have two linked list:
 * 1) for index in VTBL of some method
 * 2) for ID of method
 * Both sorted
 */
struct id_table
{
  DWORD id;
  struct titem *ptr;
};

/* Holds method and members list */
class tinterface
{
  public:
   tinterface();
   ~tinterface();

   int read(LPTYPEINFO, LPTYPEATTR, dict_t *);

   struct titem *by_index(DWORD);
   struct titem *by_ID(DWORD, int type);
   char *find_var(DWORD);
   int get_min_index();
   /* 5 Nov 2004 - for IDA vtlb support */
   inline int index_len() { return m_index_len; }
   inline struct id_table *index_table() { return m_index; }
  protected:
   static int __cdecl compare_id_tables(const void *, const void *);

   int readVars(LPTYPEINFO, LPTYPEATTR, MEMBERID, dict_t *);
   struct titem *add(struct titem *, DWORD id, DWORD index);

   char *alloc_name(dict_t *, char *);
   void fix_tables();
   void sort(struct id_table *, int);

   struct id_table *m_index;
   int m_index_len;
   int m_indexz;
   struct id_table *m_id;
   int m_id_len;
   int m_idz;
   // 19 NOV 2002: added support for dispinterface variables
   lnlist m_vars;
};

/* definition */
struct one_interface
{
  int type;
  IID iid;    // stored in m_iidz as key. String representation stored
	      // in m_dict as key. This string must be killed
  char *name;
  union {
   tinterface *iface; // when type == TKIND_INTERFACE || TKIND_DISPATCH
   IID first_reffed;  // when type == TKIND_COCLASS
  };
};

class tlb
{
  public:
   tlb(tlb_storage *,LPTYPELIB);
   ~tlb();
   int fill();

  protected:
   int fill_typeinfo(LPTYPEINFO);
   int fill_coclass(LPTYPEINFO, struct one_interface *);
   tlb_storage *m_ts;
   LPTYPELIB m_TL;
};

struct one_tlb
{
  struct list list;
  IID iid;
  tlb *tlb;
};

/* registry reader helper class */
class tlb_registry
{
 public:
  tlb_registry()
  {}
  ~tlb_registry()
  {}
  char *get(IID *);
  char *get(char *);
  char *get_for_typelib(char *);
  char *getCLSIDforFullName(char *);

 protected:
  char *get_internal(char *);
  char *get_typelib_for_interface(char *, int &);
  char *resolve_tlb(char *);
  int get_win32_subkey(char *);
  DWORD unhex(char *);
};

class tlb_storage
{
  friend class tlb;

  public:
   tlb_storage();
   ~tlb_storage();
   int init();

   int read(char *);
   int read_dir(char *);

   int find_TLB(IID *);
   int find_for_VB4(char *fullname, IID *iid);
   struct one_interface *find(IID *, int demand = 1);
   struct one_interface *find(char *, int demand = 1);
   struct one_interface *find_for_FullName(char *, IID **);

   /* for debugging */
   const char *tkind(int);

  protected:
   int is_tlb(char *);
   int check_tlbs(IID *, int ignore_vb6dup = 1);
   int is_vb64_guid(IID *);
   struct one_interface *add(LPTYPEINFO);
   int dynamic_resolve(char *);
   int dynamic_resolve(IID *);

   lnlist modules;
   dict_t *m_iidz;
   dict_t *m_dict;
   dict_t *m_names; // for memory management
   int m_co;
   tlb_registry *m_reg;
};

#endif /* TLB_H */