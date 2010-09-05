/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeTypedef                                     */
/************************************************************************/

#include "pdbtypes.h"
#include "pdbutils.h"
#include "_pdbint.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagTypedef</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeTypedef::PdbTypeTypedef(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagTypedef, "PdbTypeTypedef");

  // remember the symbol
  this->symbol = symbol;
  subType = NULL;
}


/// <summary>Destructor</summary>
///
PdbTypeTypedef::~PdbTypeTypedef() {
  if (subType != NULL) {
    delete subType;
  }
}


/// <summary>Get name of the typedef</summary>
///
/// <returns>The name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbTypeTypedef::getName() {
  return _getName(symbol);
}


/// <summary>Populate sub-type</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeTypedef::populateSubType() {
  // get the sub-type
  CComPtr<IDiaSymbol> diaTypedefType;
  if (FAILED(symbol->get_type(&diaTypedefType))) {
    throwError();
  }
  subType = pdbTypeMake(diaTypedefType);
}


/// <summary>Get sub type of the typedef</summary>
///
/// <returns>The sub-type</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbType* PdbTypeTypedef::getSubType() {
  if (subType == NULL) {
    populateSubType();
  }
  return subType;
}

