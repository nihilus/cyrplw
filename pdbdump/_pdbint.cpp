/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of internal DiaLib utilities                          */
/************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "_pdbint.h"


/// <summary>Throw a windows error as a runtime error</summary>
///
/// <exception cref="runtime_error">Always thrown</exception>
///
void throwError() {
  // get the error
  DWORD lastError = GetLastError();
  if (lastError == S_OK) {
    throw runtime_error("Unknown error");
  }
  
  // Get the error text
  LPVOID lpMsgBuf;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                FORMAT_MESSAGE_FROM_SYSTEM | 
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                lastError,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                (LPTSTR) &lpMsgBuf,
                0, NULL);
  string errStr = (char*) lpMsgBuf;
  LocalFree( lpMsgBuf );

  // throw it!
  throw runtime_error(errStr);
}


/// <summary>Get name for a type</summary>
///
/// <param name="symbol">Symbol to extract name from</param>
///
/// <returns>The name of the type. Will make up a name if the type is 
/// unnamed in some way</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring _getName(IDiaSymbol* symbol) {
  // get the name
  BSTR nameB = NULL;
  if (FAILED(symbol->get_name(&nameB)) || !nameB) {
    throwError();
  }
  wstring name = nameB;
  LocalFree(nameB);

  // if the name is "__unnamed", make up a name
  if (name.find(L"__unnamed") != wstring::npos) {
    wchar_t buf[512];

    // get unqiue type code
    DWORD typeId = 0;
    if (FAILED(symbol->get_symIndexId(&typeId))) {
      throwError();
    }

    // make up name
    wsprintfW(buf, L"%ws_%x_", name.c_str(), typeId);
    name = buf;
  }

  // return the name
  return name;
}

