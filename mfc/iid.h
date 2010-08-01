#ifndef RP_IID_H
# define RP_IID_H	"Written by Red Plait 4-IV-2000"

struct win_IID
{
  unsigned long l;
  unsigned short w1;
  unsigned short w2;
  unsigned char b[8];
};

struct iid_item
{
  unsigned char bytes[16];
  const char *name;
};

extern struct iid_item known_iids[];

#if __cplusplus
 extern "C"
 {
#endif

const struct iid_item * find_iid(struct win_IID *);
char *print_IID(const struct win_IID *iid);
int check_keys();

#if __cplusplus
 };
#endif
#endif /* RP_IID_H */