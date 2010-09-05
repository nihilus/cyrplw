/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeReference                                   */
/************************************************************************/

#include "pdbtypes.h"
#include "pdbutils.h"
#include "_pdbint.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagReferenceType</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeReference::PdbTypeReference(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagPointerType, "PdbTypeReference");

  // make sure it IS a reference type
  BOOL isReference;
  if (FAILED(symbol->get_reference(&isReference))) {
    throwError();
  }
  if (!isReference) {
    throw runtime_error("Attempt to make a reference out of a pointer");
  }

  // remember the symbol
  this->symbol = symbol;

  // populate other fields
  refereeType = NULL;
}


/// <summary>Destructor</summary>
///
PdbTypeReference::~PdbTypeReference() {
  if (refereeType != NULL) {
    delete refereeType;
  }
}


/// <summary>Populate referee type</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeReference::populateRefereeType() {
  // Find the actual type being pointed to
  CComPtr<IDiaSymbol> diaRefereeType;
  if (FAILED(symbol->get_type(&diaRefereeType))) {
    throwError();
  }

  // make up the referee type
  refereeType = pdbTypeMake(diaRefereeType);
}


/// <summary>Gets the type being pointed to</summary>
///
/// <returns>PdbType structure describing the type being pointed to.</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbType* PdbTypeReference::getRefereeType() {
  if (refereeType == NULL) {
    populateRefereeType();
  }
  return refereeType;
}

