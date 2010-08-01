#include <windows.h>

#if __cplusplus
extern "C"
#endif
unsigned long __cdecl get_imp_va(void *ptr)
{
  IMAGE_NT_HEADERS *pe = (IMAGE_NT_HEADERS *)ptr;
  if ( !pe )
   return 0;
  return pe->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
}