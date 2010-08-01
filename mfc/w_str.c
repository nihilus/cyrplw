#include <windows.h>
#include <ocidl.h>

// for DIA71: C:\Program Files\Microsoft Visual Studio .NET 2003\Visual Studio SDKs\DIA SDK\include\

/* convertation routines */
char *ole2str(OLECHAR *wide, int len)
{
  int count = WideCharToMultiByte(CP_ACP, 0, wide, len, NULL, 0, NULL, NULL);
  char *res = (char *)malloc(count + 1);
  WideCharToMultiByte(CP_ACP, 0, wide, len, res, count, NULL, NULL);
  res[count] = 0;
  return res;
}
