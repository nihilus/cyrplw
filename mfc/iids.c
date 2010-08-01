#include "iid.h"
#include <search.h>
#include <string.h>

struct iid_item known_iids[] = {
#include "iid.c"
};

static int __cdecl cmp_guids(const void *key, const void *elem)
{
  struct iid_item *item = (struct iid_item *)elem;
  return memcmp(key, item->bytes, sizeof(item->bytes));
}

int
check_keys()
{
  int count;
  for ( count = 1; count < sizeof(known_iids)/sizeof(known_iids[0]); count++ )
   if ( -1 != cmp_guids(&known_iids[count-1].bytes, &known_iids[count]) )
     return count;
  return 0;
}

const struct iid_item *
find_iid(struct win_IID *key)
{
  return (const struct iid_item *)bsearch(key, known_iids, 
    sizeof(known_iids)/sizeof(known_iids[0]),
    sizeof(known_iids[0]), cmp_guids);
}

void
print_hex(char *ptr, unsigned char c)
{
  const char letterz[] = "0123456789ABCDEF";
  *ptr = letterz[(c & 0xf0) >> 4];
  *(ptr+1) = letterz[c & 0x0f];
}

char *
print_IID(const struct win_IID *iid)
{
  static char buffer[40];
  register char *p = buffer;
  const char *fake = (const char *)iid;
  
  *p++ = '{';
  print_hex(p, fake[3]); p+= 2;
  print_hex(p, fake[2]); p+= 2;
  print_hex(p, fake[1]); p+= 2;
  print_hex(p, fake[0]); p+= 2;
  *p++ = '-';
  print_hex(p, fake[5]); p+= 2;
  print_hex(p, fake[4]); p+= 2;
  *p++ = '-';
  print_hex(p, fake[7]); p+= 2;
  print_hex(p, fake[6]); p+= 2;
  *p++ = '-';
  print_hex(p, fake[8]); p+= 2;
  print_hex(p, fake[9]); p+= 2;
  *p++ = '-';
  print_hex(p, fake[10]); p+= 2;
  print_hex(p, fake[11]); p+= 2;
  print_hex(p, fake[12]); p+= 2;
  print_hex(p, fake[13]); p+= 2;
  print_hex(p, fake[14]); p+= 2;
  print_hex(p, fake[15]); p+= 2;
  *p++ = '}';
  *p = 0x0;
  return buffer;
}