/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeClass                                       */
/************************************************************************/

#include "pdbtypes.h"
#include "_pdbint.h"
#include "pdbitems.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagUDTType</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeClass::PdbTypeClass(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagUDT, "PdbTypeClass");

  // check it is a class
  DWORD kind;
  if (FAILED(symbol->get_udtKind(&kind))) {
    throwError();
  }
  if (kind != UdtClass) {
    throw runtime_error("Attempt to make a PdbTypeClass out of something not a class");
  }

  // remember the symbol
  this->symbol = symbol;
}


/// <summary>Destructor</summary>
///
PdbTypeClass::~PdbTypeClass() {}


/// <summary>Get name of the class</summary>
///
/// <returns>The name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbTypeClass::getName() {
  return _getName(symbol);
}

