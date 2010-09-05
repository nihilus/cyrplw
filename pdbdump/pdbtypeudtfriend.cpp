/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeUDTFriend                                   */
/************************************************************************/

#include "pdbtypes.h"
#include "pdbutils.h"
#include "_pdbint.h"
#pragma warning(disable:4800)



/// <summary>Constructor</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeUDTFriend::PdbTypeUDTFriend(IDiaSymbol* symbol) {
  // remember the symbol
  this->symbol = symbol;
  parentUDTType = NULL;
  befriendedUDT = NULL;
  befriendedFunction = NULL;
  befriendedPopulated = false;
}


/// <summary>Populate parent udt type</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeUDTFriend::populateParentUDTType() {
  CComPtr<IDiaSymbol> diaParentUDTType;
  if (FAILED(symbol->get_type(&diaParentUDTType))) {
    throwError();
  }
  parentUDTType = dynamic_cast<PdbTypeUDT*>(pdbTypeMake(diaParentUDTType));
}


/// <summary>Populate befriended item</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeUDTFriend::populateBefriended() {
  // get the befriended symbol
  CComPtr<IDiaSymbol> diaBefriendedType;
  if (FAILED(symbol->get_type(&diaBefriendedType))) {
    throwError();
  }

  // work out the type
  DWORD symTag;
  if (FAILED(symbol->get_symTag(&symTag))) {
    throwError();
  }

  // extract befriended thing
  switch(symTag) {
  case SymTagUDT:
    befriendedUDT = dynamic_cast<PdbTypeUDT*>(pdbTypeMake(diaBefriendedType));
    break;

  case SymTagFunction:
    befriendedFunction = dynamic_cast<PdbItemFunction*>(new PdbItemFunction(diaBefriendedType));
    break;

  default:
    throw runtime_error("Unknown befriended type");
  }
}


/// <summary>Get the name of the friend</summary>
///
/// <returns>The name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbTypeUDTFriend::getName() {
  return _getName(symbol);
}


/// <summary>Get the type of the parent UDT</summary>
///
/// <returns>The parent UDT type</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeUDT* PdbTypeUDTFriend::getParentUDTType() {
  if (parentUDTType == NULL) {
    populateParentUDTType();
  }
  return parentUDTType;
}


/// <summary>Get the befriended UDT</summary>
///
/// <returns>The befriended UDT type, or NULL if it is not a UDT that was befriended</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeUDT* PdbTypeUDTFriend::getBefriendedUDT() {
  if (befriendedUDT == NULL) {
    populateBefriended();
  }
  return befriendedUDT;
}


/// <summary>Get the befriended function</summary>
///
/// <returns>The befriended function, or NULL if it is not a function that was befriended</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbItemFunction* PdbTypeUDTFriend::getBefriendedFunction() {
  if (befriendedFunction == NULL) {
    populateBefriended();
  }
  return befriendedFunction;
}


/// <summary>Is it a UDT that has been befriended</summary>
///
/// <returns>True if it is a UDT that has been befriended</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDTFriend::isBefriendedUDT() {
  if (!befriendedPopulated) {
    populateBefriended();
    befriendedPopulated = true;
  }
  return befriendedUDT != NULL ? true : false;
}


/// <summary>Is it a function that has been befriended</summary>
///
/// <returns>True if it is a function that has been befriended</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDTFriend::isBefriendedFunction() {
  if (!befriendedPopulated) {
    populateBefriended();
    befriendedPopulated = true;
  }
  return befriendedFunction != NULL ? true : false;
}


/// <summary>Destructor</summary>
///
PdbTypeUDTFriend::~PdbTypeUDTFriend() {
  if (parentUDTType != NULL) {
    delete parentUDTType;
  }
  if (befriendedUDT != NULL) {
    delete befriendedUDT;
  }
  if (befriendedFunction != NULL) {
    delete befriendedFunction;
  }
}

