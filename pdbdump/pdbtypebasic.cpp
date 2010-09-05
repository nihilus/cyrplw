/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeBasic                                       */
/************************************************************************/

#include "pdbtypes.h"
#include "_pdbint.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagBaseType</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeBasic::PdbTypeBasic(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagBaseType, "PdbTypeBasic");

  // remember the symbol
  this->symbol = symbol;
}


/// <summary>Destructor</summary>
///
PdbTypeBasic::~PdbTypeBasic() {}


/// <summary>Get the code of the wrapped BasicType</summary>
///
/// <returns>One of the DIA SDK BasicType enumeration</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
BasicType PdbTypeBasic::getBasicTypeCode() {
  // get the base type id
  DWORD baseTypeId = 0;
  if (FAILED(symbol->get_baseType(&baseTypeId))) {
    throwError();
  }

  // return it
  return (BasicType) baseTypeId;
}

