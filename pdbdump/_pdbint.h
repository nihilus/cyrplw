/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Internal DiaLib utilities                                            */
/************************************************************************/

#ifndef _PDBINT_H
#define _PDBINT_H

#include <assert.h>
#include <string>
#include <exception>
#include <stdexcept>
#include <dia2.h>
using namespace std;

// Ensure an iDiaSymbol is correct
#ifdef _DEBUG
#define CHECKTAG(__SYM, __TAGID, __WHENCE) { \
    DWORD __tag; \
    __SYM->get_symTag(&__tag); \
    if (__TAGID != __tag) { \
      throw runtime_error("Unexpected tag detected at " __WHENCE); \
    } \
}
#else 
#define CHECKTAG(__SYM, __TAGID, __WHENCE)
#endif


/// <summary>Throw a windows error as a runtime error</summary>
///
/// <exception cref="runtime_error">Always thrown</exception>
///
void throwError();


/// <summary>Get name for a type</summary>
///
/// <param name="symbol">Symbol to extract name from</param>
///
/// <returns>The name of the type. Will make up a name if the type is 
/// unnamed in some way</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring _getName(IDiaSymbol* symbol);


#endif

