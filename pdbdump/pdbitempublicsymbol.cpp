/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbItemPublicSymbol                                */
/************************************************************************/

#include "pdbtypes.h"
#include "pdbitems.h"
#include "pdbutils.h"
#include "_pdbint.h"
#pragma warning(disable:4800)




/// <summary>Constructor</summary>
///
/// <param name="symbol">Symbol to wrap</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbItemPublicSymbol::PdbItemPublicSymbol(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagPublicSymbol, "PdbItemPublicSymbol");

  // remember the symbol
  this->symbol = symbol;

  // make sure it is has a static location
  DWORD val;
  if (FAILED(symbol->get_locationType(&val))) {
    throwError();
  }
  if (val != LocIsStatic) {
    throw runtime_error("Public symbol with unexpected location");
  }
}


/// <summary>Get name</summary>
///
/// <returns>Name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbItemPublicSymbol::getName() {
  return _getName(symbol);
}


/// <summary>Get RVA</summary>
///
/// <returns>RVA</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbItemPublicSymbol::getRVA() {
  unsigned long val;
  if (FAILED(symbol->get_relativeVirtualAddress(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Determines if the symbol is in managed code</summary>
///
/// <returns>True if it is</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbItemPublicSymbol::isInManagedCode() {
  BOOL val;
  if (FAILED(symbol->get_managed(&val))) {
    throwError();
  }
  return (bool) val;
}


/// <sumary>Determines if the symbol is in MSIL code</summary>
///
/// <returns>True if it is</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbItemPublicSymbol::isInMSIL() {
  BOOL val;
  if (FAILED(symbol->get_msil(&val))) {
    throwError();
  }
  return (bool) val;
}


/// <summary>Determines if the symbol is a function</summary>
///
/// <returns>True if it is a function, false if it is data</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbItemPublicSymbol::isFunction() {
  BOOL val;
  if (FAILED(symbol->get_function(&val))) {
    throwError();
  }
  return (bool) val;
}


/// <summary>Determines if the symbol is in code</summary>
///
/// <returns>True if it is</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbItemPublicSymbol::isInCode() {
  BOOL val;
  if (FAILED(symbol->get_code(&val))) {
    throwError();
  }
  return (bool) val;
}

