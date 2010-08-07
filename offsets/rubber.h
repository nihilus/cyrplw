#ifndef RUBBER_H
#define RUBBER_H	"Written by Red Plait, 24-AUG-2000"

#include <stdio.h>

/* struct for memory buffer with unlimited length */
#define INITIAL_RUBBER		64
#define INCREMENT		2

#if __cplusplus
 extern "C" {
#endif

struct Rubber_mem {
  char *p;
  int alloced;
  int size;
};

struct Rubber_mem *new_Rubber();
void del_Rubber(struct Rubber_mem *ptr);
void add_Rubber(struct Rubber_mem *ptr, const char *buffer, int len);
int rp_read_string(FILE *fp, struct Rubber_mem *);
char *trimstring(char *);

#if __cplusplus
 };
#endif

#endif /* RUBBER_H */
