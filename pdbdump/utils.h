/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Miscellaneous utilities                                              */
/************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <assert.h>
#include <string>
#include <exception>
#include <stdexcept>
using namespace std;



// Ensure an iDiaSymbol is correct
#define CHECKTAG(__SYM, __TAGID, __WHENCE) { \
    DWORD __tag; \
    __SYM->get_symTag(&__tag); \
    if (__TAGID != __tag) { \
      throw runtime_error("Unexpected tag detected at " __WHENCE); \
    } \
}


/// <summary>Report a windows error</summary>
///
void reportError();

/// <summary>Report a program-generated error</summary>
///
/// <param name="errText">String to report</param>
///
void error(char* errStr);


/// <summary>Render a GUID</summary>
///
/// <param name="guid">GUID to render</param>
///
/// <returns>Rendered string</returns>
///
wstring renderGUID(GUID* guid);

#endif

