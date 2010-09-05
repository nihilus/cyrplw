/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbType                                            */
/************************************************************************/

#include "pdbtypes.h"
#include "_pdbint.h"


/// <summary>Accessor for the unique type code</summary>
///
/// <returns>The unique type code</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbType::getUniqueTypeCode() {
  // get the base type id
  DWORD typeId = 0;
  if (FAILED(symbol->get_symIndexId(&typeId))) {
    throwError();
  }

  // return it
  return typeId;
}


/// <summary>Get the size of the type in bytes</summary>
///
/// <returns>Size in bytes</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned __int64 PdbType::getSizeBytes() {
  // get the size of the type in bytes
  unsigned __int64 typeSize = 0;
  if (FAILED(symbol->get_length(&typeSize))) {
    throwError();
  }

  // return it
  return typeSize;
}

