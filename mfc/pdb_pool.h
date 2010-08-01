#ifndef PDB_POOL_H
# define PDB_POOL_H	"PDBs pool class"

#include "hierarchy.h"
#include "imp_dlls.h"
#include "dict.h"
#include <bytes.hpp>
#include <struct.hpp>
#include <netnode.hpp>

#define RPD_LIST_NETNODE_NAME	"$ RPD list"

class PDB_pool: public Imp_Dlls
{
 public:
  PDB_pool();
  ~PDB_pool();
  int read_pdbs();
  int add_pdb(char *name); // used for authomatic PDB loading
  int add_pdb();           // asks user which PDB to load
  struct pdb_class *find_class(char *name);
  int pdb_count();
 protected:
  char *get_name(char *);
  int check_pdb(char *name);
  // after loading method(s)
  void after_loading(CPdb *);
  void add_VTBL(struct pdb_class *);
  void add_struct(struct pdb_class *);
  void add_methods(struc_t *, struct pdb_class *);
  void add_members(struc_t *, struct pdb_class *);
  struct pdb_class *get_parent(struct pdb_class *);
  // for RPD list storing/loading from IDA base
  int add_to_rpd_list(char *);
  void load_rpd_list();
  void load_from_rpd(char *);
  // 18 Sep 2003 - for statically linked MFC recognization
  char *extract_unicode(ea_t);
  int parse_found_string(char *);
  int process_found(ea_t, int is_unicode = 0);
  int autodetect_static_version();

  int m_rpd_index;
  netnode m_rpd_list;
  const char *m_ida_dir;
  int m_len;
  dict_t *m_pdbs;
};
#endif /* PDB_POOL_H */