/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeCustom                                      */
/************************************************************************/

#include "pdbtypes.h"
#include "_pdbint.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagCustomType</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeCustom::PdbTypeCustom(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagCustomType, "PdbTypeCustom");

  // remember the symbol
  this->symbol = symbol;
}


/// <summary>Destructor</summary>
///
PdbTypeCustom::~PdbTypeCustom() {}


/// <summary>Gets the GUID of the custom type</summary>
///
/// <returns>The guid</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
GUID PdbTypeCustom::getGuid() {
  // get guid
  GUID guid;
  if (FAILED(symbol->get_guid(&guid))) {
    throwError();
  }

  // return it
  return guid;
}


/// <summary>Gets the OemId of the custom type</summary>
///
/// <returns>The oemId</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
DWORD PdbTypeCustom::getOemId() {
  // get oemId
  DWORD oemId;
  if (FAILED(symbol->get_oemId(&oemId))) {
    throwError();
  }

  // return it
  return oemId;
}


/// <summary>Gets the OemSymbolId of the custom type</summary>
///
/// <returns>The oemSymbolId</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
DWORD PdbTypeCustom::getOemSymbolId() {
  // get oemSymbolId
  DWORD oemSymbolId;
  if (FAILED(symbol->get_oemSymbolId(&oemSymbolId))) {
    throwError();
  }

  // return it
  return oemSymbolId;
}

