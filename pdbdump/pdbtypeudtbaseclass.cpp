/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeUDTBaseClass                                */
/************************************************************************/

#include "pdbtypes.h"
#include "pdbutils.h"
#include "_pdbint.h"
#pragma warning(disable:4800)


/// <summary>Constructor</summary>
///
/// <param name="symbol">Symbol to wrap</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeUDTBaseClass::PdbTypeUDTBaseClass(IDiaSymbol* symbol) {
  // remember the symbol
  this->symbol = symbol;
  baseClassType = NULL;
}


/// <summary>Populate the base class type</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeUDTBaseClass::populateBaseClass() {
  // get base class UDT
  CComPtr<IDiaSymbol> diaBaseClassType;
  if (FAILED(symbol->get_type(&diaBaseClassType))) {
    throwError();
  }
  baseClassType = dynamic_cast<PdbTypeUDT*>(pdbTypeMake(diaBaseClassType));
}


/// <summary>Is the base class an indirect base class</summary>
///
/// <returns>True if it is</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDTBaseClass::isIndirectBaseClass() {
  BOOL boolVal;
  if (FAILED(symbol->get_indirectVirtualBaseClass(&boolVal))) {
    throwError();
  }
  return (bool) boolVal;
}


/// <summary>Is the base class a virtual class</summary>
///
/// <returns>True if it is</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDTBaseClass::isVirtual() {
  BOOL boolVal;
  if (FAILED(symbol->get_virtualBaseClass(&boolVal))) {
    throwError();
  }
  return (bool) boolVal;
}


/// <summary>Get offset in structure of sub-object representing this baseclass</summary>
///
/// <returns>The offset</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
long PdbTypeUDTBaseClass::getOffset() {
  long value;
  if (FAILED(symbol->get_offset(&value))) {
    throwError();
  }
  return value;
}


/// <summary>Get index into virtual base displacement table</summary>
///
/// <returns>The index</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbTypeUDTBaseClass::getVirtualBaseDispIndex() {
  unsigned long value;
  if (FAILED(symbol->get_virtualBaseDispIndex(&value))) {
    throwError();
  }
  return value;
}


/// <summary>Get virtual base pointer offset</summary>
///
/// <returns>The offset</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
long PdbTypeUDTBaseClass::getVirtualBasePointerOffset() {
  long value;
  if (FAILED(symbol->get_virtualBasePointerOffset(&value))) {
    throwError();
  }
  return value;
}


/// <summary>Get type of the base class</summary>
///
/// <returns>The type</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeUDT* PdbTypeUDTBaseClass::getBaseClassType() {
  if (baseClassType == NULL) {
    populateBaseClass();
  }
  return baseClassType;
}


/// <summary>Destructor</summary>
///
PdbTypeUDTBaseClass::~PdbTypeUDTBaseClass() {
  if (baseClassType != NULL) {
    delete baseClassType;
  }
}

