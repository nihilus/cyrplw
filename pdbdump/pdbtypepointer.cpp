/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypePointer                                     */
/************************************************************************/


#include "pdbtypes.h"
#include "pdbutils.h"
#include "_pdbint.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagPointerType</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypePointer::PdbTypePointer(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagPointerType, "PdbTypePointer");
  
  // make sure it isn't a reference type
  BOOL isReference;
  if (FAILED(symbol->get_reference(&isReference))) {
    throwError();
  }
  if (isReference) {
    throw runtime_error("Attempt to make a pointer out of a reference");
  }

  // remember the symbol
  this->symbol = symbol;
  pointeeType = NULL;
  pointerDepth = 1;
  pointerPopulated = false;
}


/// <summary>Populate the pointer data structure</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypePointer::populatePointer() {
  // find the actual type being pointed to
  DWORD pointeeTag;
  CComPtr<IDiaSymbol> diaPointeeType;
  if (FAILED(symbol->get_type(&diaPointeeType))) {
    throwError();
  }

  // get symtag of type being pointed to
  if (FAILED(diaPointeeType->get_symTag(&pointeeTag))) {
    throwError();
  }

  // If the type being pointed to is a pointer itself, handle multiple 
  // levels of indirection
  BOOL isReference;
  while(pointeeTag == SymTagPointerType) {
    // check it IS a pointer (pointers to references are not allowed)
    if (FAILED(diaPointeeType->get_reference(&isReference))) {
      throwError();
    }
    if (isReference) {
      throw runtime_error("Found a pointer to a reference");
    }
    
    // increment pointer depth
    pointerDepth++;

    // Get the next type down
    CComPtr<IDiaSymbol> tmpPointeeType;
    if (FAILED(diaPointeeType->get_type(&tmpPointeeType))) {
      throwError();
    }
    diaPointeeType.Release();
    diaPointeeType = tmpPointeeType;

    // get symtag of next type down
    if (FAILED(diaPointeeType->get_symTag(&pointeeTag))) {
      throwError();
    }
  }

  // make up the pointee type (i.e. the final non-pointer type)
  pointeeType = pdbTypeMake(diaPointeeType);
}


/// <summary>Destructor</summary>
///
PdbTypePointer::~PdbTypePointer() {
  if (pointeeType != NULL) {
    delete pointeeType;
  }
}


/// <summary>Gets the depth of the pointer</summary>
///
/// <returns>How many levels of indirection</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
int PdbTypePointer::getIndirectionDepth() {
  if (!pointerPopulated) {
    populatePointer();
    pointerPopulated = true;
  }
  return pointerDepth;
}


/// <summary>Gets the type being pointed to</summary>
///
/// <returns>PdbType structure describing the type being pointed to.</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbType* PdbTypePointer::getPointeeType() {
  if (!pointerPopulated) {
    populatePointer();
    pointerPopulated = true;
  }
  return pointeeType;
}

