#include <windows.h>
#include <ole2.h>


HRESULT __stdcall NoRegCoCreate(char const *name, REFIID g1, REFIID g2, void **lp)
{
  HMODULE m = LoadLibrary(name);
  HRESULT (__stdcall *fn)(REFCLSID, REFIID, LPVOID *);

  if ( NULL == m )
   return TYPE_E_CANTLOADLIBRARY;
  fn = (HRESULT (__stdcall *)(REFCLSID, REFIID, LPVOID *))GetProcAddress(m, "DllGetClassObject");
  if ( NULL == fn )
   return TYPE_E_BADMODULEKIND;
  IClassFactory *cf = NULL;
  HRESULT res = fn(g1, IID_IClassFactory, (LPVOID *)&cf);
  if ( cf == NULL )
    return res;
//  _asm int 3
  res = cf->CreateInstance(0,  g2, lp);
  cf->Release();
  return res;
}