#include "ida.h"
/*#if (IDP_INTERFACE_VERSION < 61)
# include <windows.h>
#endif */

funcset_t *RP_Funcs = NULL;

int IDA_version()
{
  return 610;
}

int
init_IDC()
{
  if ( NULL  != RP_Funcs )
    return 1;
/*#if (IDP_INTERFACE_VERSION < 61)
  HMODULE hmod = GetModuleHandle("ida.wll");
  if ( hmod == NULL )
    return 0;
#endif */
  RP_Funcs = (funcset_t *)
//#if (IDP_INTERFACE_VERSION >= 61)
   &IDCFuncs;
/*#else
  ((DWORD)hmod + (DWORD)
   0xB4DA8	// IDA 4.17
//   0xb6c38    // IDA 4.30 Adv
//   0xB6B40	// IDA 4.30
//   0x8d9c0	// IDA 4.15
 );
#endif*/
 return 1;
}