#ifndef RP_CLASSTREE_HPP
# define RP_CLASSTREE_HPP	"Classes tree structures"

#ifndef RP_RECOGN_HPP
# include "recogn.hpp"
#endif

struct RP_class
{
  struct RP_class *parent;
  ea_t CRuntime;
  ea_t vtbl;
  size_t namelen;
  size_t total;
  size_t alloced;
  struct RP_class **children;
};

extern struct RP_class *CObject;
extern ulong total_classes;

// some extern functions
void process_AfxMessages(ea_t);
char *OLECMDID_name(ulong id);
void processIID(ea_t);


// functions from classtree.cpp
void classes_deinit(void);
void pdb_deinit(void);
void process_RT();
void process_VTBL();
void process_VTBL2();
bool build_rt_tree(ea_t);
bool check_rt_tree(ea_t);
ea_t auto_find_root_addr();
struct RP_class *find_rt_by_name(const char *);
struct RP_class *find_rt_by_vtbl(ea_t);
void jump_to_vtbl_by_name();
void load_RPD();

#endif /* RP_CLASSTREE_HPP */