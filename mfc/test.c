#include "iid.h"
#include <stdio.h>

int
main()
{
  struct win_IID test = { 0xeb16cb08, 0xd271, 0x11ce,
   { 0xac, 0x48, 0x00, 0x00, 0xc0, 0x38, 0x25, 0xa1 } };
   
  const struct RP_IID *res = find_iid(&test);
  printf("Address of array %X\n", known_iids );    
  if ( NULL != res )
  {
    printf("Name is %s\n", res->name);
    printf("IID: %s\n", print_IID(&test) );
  }
  else
    printf("Not found\n");  
  printf("Check keys: %d\n", check_keys() );
  return 0;
}