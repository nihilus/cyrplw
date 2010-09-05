/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbItemLabel                                       */
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
PdbItemLabel::PdbItemLabel(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagLabel, "PdbItemLabel");

  // remember the symbol
  this->symbol = symbol;

  // make sure it is has a static location
  DWORD val;
  if (FAILED(symbol->get_locationType(&val))) {
    throwError();
  }
  if (val != LocIsStatic) {
    throw runtime_error("Label with unexpected location");
  }
}


/// <summary>Get label name</summary>
///
/// <returns>Name of the label</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbItemLabel::getName() {
  return _getName(symbol);
}


/// <summary>Get RVA of the label</summary>
///
/// <returns>RVA</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbItemLabel::getRVA() {
  unsigned long val;
  if (FAILED(symbol->get_relativeVirtualAddress(&val))) {
    throwError();
  }
  return val;
}

