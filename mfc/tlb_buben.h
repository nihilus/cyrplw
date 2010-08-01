#ifndef TLB_BUBEN_H
# define TLB_BUBEN_H

#if __cplusplus
extern "C"
 {
#endif

#define METHOD_GET  1
#define METHOD_PUT  2
#define METHOD_PUTREF 3

struct buben_methods
{
  char *name;
  int offset;
};

int init_tlb_buben();
void finit_tlb_buben();
char *find_tlb_buben(void *arg);
int is_tlb_buben_has_vtbl();
struct buben_methods *get_buben_vtlb_methods(int &size);
void free_buben_methods(struct buben_methods *, int size);

#if __cplusplus
 }
#endif
#endif /* TLB_BUBEN_H */