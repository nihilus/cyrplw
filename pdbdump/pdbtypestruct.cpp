/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeStruct                                      */
/************************************************************************/

#include "pdbtypes.h"
#include "_pdbint.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagUDTType</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeStruct::PdbTypeStruct(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagUDT, "PdbTypeStruct");

  // check it is a struct
  DWORD kind;
  if (FAILED(symbol->get_udtKind(&kind))) {
    throwError();
  }
  if (kind != UdtStruct) {
    throw runtime_error("Attempt to make a PdbTypeStruct out of something not a struct");
  }

  // remember the symbol
  this->symbol = symbol;
}


/// <summary>Destructor</summary>
///
PdbTypeStruct::~PdbTypeStruct() {}


/// <summary>Get name of the struct</summary>
///
/// <returns>The name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbTypeStruct::getName() {
  return _getName(symbol);
}

