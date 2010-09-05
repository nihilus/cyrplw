/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeManaged                                     */
/************************************************************************/

#include "pdbtypes.h"
#include "_pdbint.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagManagedType</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeManaged::PdbTypeManaged(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagManagedType, "PdbTypeManaged");

  // remember the symbol
  this->symbol = symbol;
}


/// <summary>Destructor</summary>
///
PdbTypeManaged::~PdbTypeManaged() {}


/// <summary>Gets the name of the managed type</summary>
///
/// <returns>The name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbTypeManaged::getName() {
  return _getName(symbol);
}

