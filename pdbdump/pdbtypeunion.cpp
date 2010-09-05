/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeUnion                                       */
/************************************************************************/

#include "pdbtypes.h"
#include "_pdbint.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagUDTType</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeUnion::PdbTypeUnion(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagUDT, "PdbTypeUnion");

  // check it is a union
  DWORD kind;
  if (FAILED(symbol->get_udtKind(&kind))) {
    throwError();
  }
  if (kind != UdtUnion) {
    throw runtime_error("Attempt to make a PdbTypeUnion out of something not a union");
  }

  // remember the symbol
  this->symbol = symbol;
}


/// <summary>Destructor</summary>
///
PdbTypeUnion::~PdbTypeUnion() {}


/// <summary>Get name of the union</summary>
///
/// <returns>The name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbTypeUnion::getName() {
  return _getName(symbol);
}

