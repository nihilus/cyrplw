/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of miscellaneous utilities                            */
/************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


/// <summary>Report a windows error</summary>
///
void reportError() {
  LPVOID lpMsgBuf;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                FORMAT_MESSAGE_FROM_SYSTEM | 
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                (LPTSTR) &lpMsgBuf,
                0, NULL);

  fprintf(stderr, "%s\n", lpMsgBuf);
  
  LocalFree( lpMsgBuf );

  exit(1);
}


/// <summary>Report a program-generated error</summary>
///
/// <param name="errText">String to report</param>
///
void error(char* errStr) {
  fprintf(stderr, "%s\n", errStr);
  exit(1);
}


/// <summary>Render a GUID</summary>
///
/// <param name="guid">GUID to render</param>
///
/// <returns>Rendered string</returns>
///
wstring renderGUID(GUID* guid) {
  wchar_t buf[256];

  wsprintfW(buf, L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", 
    guid->Data1, guid->Data2, guid->Data3, guid->Data4[0], guid->Data4[1], 
    guid->Data4[2], guid->Data4[3], guid->Data4[4], guid->Data4[5], 
    guid->Data4[6], guid->Data4[7]);

  return buf;
}

