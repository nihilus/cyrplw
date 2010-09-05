#include <windows.h>
#include <ole2.h>


long __stdcall NoRegCoCreate(char const *name, REFIID g1, REFIID g2, void **lp)
{
  HMODULE m = LoadLibrary(name);
  long (__stdcall *fn)(REFCLSID, REFIID, LPVOID *);

  if ( NULL == m )
   return 1;
  fn = (long (__stdcall *)(REFCLSID, REFIID, LPVOID *))GetProcAddress(m, "DllGetClassObject");
  if ( NULL == fn )
   return 1;
  IClassFactory *cf;
  long res = fn(g1, IID_IClassFactory, (LPVOID *)&cf);
//  _asm int 3
  cf->CreateInstance(0,  g2, lp);
  cf->Release();
  return (*lp == NULL);
}