#ifndef OFF_DS_HPP
# define OFF_DS_HPP	"Written by RedPlait, 24-APR-2001"

#include "dict.h"
#include <stdio.h>
#include <sys/types.h>
#include <ida.hpp>

class RP_mapping {
 public:
  RP_mapping(char *, int verbose = 1);
  ~RP_mapping();
  int successfull_creating();
  void clear();
  int read_config();
  static char *find_path(const char *);
  dnode_t *is_presented(ea_t);
  dict_t *dict()
  {
    return mapping;
  }
  char *config_name()
  {
   return our_file;
  }
 protected:
  int read_file(FILE *);
  int process_string(char *, int);
 private:
  int verbose;
  dict_t *mapping;
  time_t old_time;
  char *our_file;
};

#endif /* OFF_DICT_HPP */