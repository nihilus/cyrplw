#ifndef HIERARCHY_H
# define HIERARCHY_H	"PDB classes hierarchy"

#include "pdb_ctypes.h"
#include <stdio.h>
#include "llist.h"
#include "dict.h"

extern "C" char *ole2str(wchar_t *,int);

// this structs will be in sorted order in linked list - for vtbl method
struct pdb_class;

struct vtbl_method
{
  struct list list;
  struct pdb_class *owner;
  unsigned long index;
  int len;
  char *name;
  int name_start;
  
  char *get_name_only();
  void set_name_only(char *);
};

#pragma pack(push)
#pragma pack(2)
struct class_member
{
  struct list list;
  struct pdb_class *owner;
  unsigned long index;
  char *name;
  int size;
  short type;

  const char *get_ida_type();
};
#pragma pack(pop)

struct pdb_class
{
  ~pdb_class();
  pdb_class(char *name);
  pdb_class(FILE *); // reader
  struct vtbl_method *add_method(char *name, unsigned long index, bool add_zero = false);
  struct class_member *add_member(char *name, unsigned long index);
  int write(FILE *);
  // for dumping only
  const char *what_type();
  void dump(FILE *out);
  // for vtbls using
  int find_right_range();
  struct vtbl_method *by_offset(unsigned long);
  // for IDA mostly
  inline int get_vtbl_count()
  {
    if ( !vtbls )
     return 0;
    return vtbls->all;
  }
  inline int get_member_count()
  {
    if ( !members )
     return 0;
    return members->all;
  }

  int new_added;
  char type;
  char *m_name; // name will be stored also in dictionary - so you not responsible for deleting name
  int number;
  int size;
  lnlist parents;
  lnlist vtbls;
  lnlist members;

 protected:
  void free_parents();
  void free_vtbls();
  void free_members();
  void read_members(FILE *);
  void write_members(FILE *);
  struct vtbl_method *add(object after, char *name, unsigned long index);
  struct class_member *add_m(object after, char *name, unsigned long index);
  char *read_string(FILE *fp, int *out_len);
  int is_zero_method(char *name, unsigned long *index);
};

struct pdb_parent
{
  struct list list;
  char what; // 1 - number, 2 - name, 3 - ref to pdb_class
  union {
     int number;
     char *name;
     struct pdb_class *c;
  };
};

class CPdb
{
  public:
   CPdb();
   ~CPdb();
   int read(FILE *);
   int write(FILE *);
   struct pdb_class *add_class(char *name, int type);
   struct pdb_class *find_class(char *name);
   struct pdb_class *find_class(int index);
   int add_parent(struct pdb_class *, char *name);
   // for dumping only
   void dump(FILE *out);
   // for IDA mostly - must be used only after read
   inline dict_t *get_dict()	{ return m_storage; }
  protected:
   int addparent(lnlist list, object after, char *name);
   int numerate_before_writing();
   void fix_parents();
   void fix_parents_list(lnlist);

   dict_t *m_numeral;
   dict_t *m_storage;
};

#endif /* HIERARCHY_H */