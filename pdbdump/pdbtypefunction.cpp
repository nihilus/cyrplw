/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeFunction                                    */
/************************************************************************/

#include "pdbtypes.h"
#include "_pdbint.h"
#include "pdbutils.h"


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagFunctionType</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeFunction::PdbTypeFunction(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagFunctionType, "PdbTypeFunction");

  // remember the symbol
  this->symbol = symbol;
  argumentsPopulated = false;
  thisPointerType = NULL;
  returnType = NULL;
}


/// <summary>Destructor</summary>
///
PdbTypeFunction::~PdbTypeFunction() {
  if (thisPointerType != NULL) {
    delete thisPointerType;
  }
  if (returnType != NULL) {
    delete returnType;
  }
  for(unsigned int i=0; i< arguments.size(); i++) {
    delete arguments[i];
  }
}


/// <summary>Logical this adjustor for the method</summary>
///
/// <returns>The value</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
long PdbTypeFunction::getThisAdjust() {
  // Now, get the this adjustor
  long val;
  if (FAILED(symbol->get_thisAdjust(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Get list of function arguments</summary>
///
/// <returns>Vector of types in order</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbType*> PdbTypeFunction::getArguments() {
  if (!argumentsPopulated) {
    populateArguments();
    argumentsPopulated = true;
  }
  return arguments;
}


/// <summary>Get return type of function </summary>
///
/// <returns>The return type</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbType* PdbTypeFunction::getReturnType() {
  if (returnType == NULL) {
    populateReturnType();
  }
  return returnType;
}


/// <summary>Get type of this function's "this" pointer</summary>
///
/// <returns>The UDT type of the "this" pointer. May be NULL if the 
/// function has no "this" pointer.. e.g. a static member or global function</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypePointer* PdbTypeFunction::getThisPointerType() {
  if (thisPointerType == NULL) {
    populateThisPointerType();
  }
  return thisPointerType;
}


/// <summary>Calling convention of the function</summary>
///
/// <returns>One of the CV_call_e enumeration</returns>
///
/// <exception c_ref="runtime_error">On internal error or if the function is a thunk</exception>
///
CV_call_e PdbTypeFunction::getCallingConvention() {
  // Now, get the calling convention
  DWORD val;
  if (FAILED(symbol->get_callingConvention(&val))) {
    throwError();
  }
  return (CV_call_e) val;
}


/// <summary>Populate the arguments</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeFunction::populateArguments() {
  // get enumeration of argument types
  CComPtr<IDiaEnumSymbols> argTypesEnum;
  if (FAILED(symbol->findChildren(SymTagFunctionArgType, NULL, nsNone, &argTypesEnum))) {
    throwError();
  }

  // Enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurArg;
  if (FAILED(argTypesEnum->Next(1, &diaCurArg, &count))) {
    throwError();
  }
  while(count) {
    // Get the actual type represented by the argument
    CComPtr<IDiaSymbol> curArgType;
    if (FAILED(diaCurArg->get_type(&curArgType))) {
      throwError();
    }

    // add it to the enumeration
    arguments.insert(arguments.end(), pdbTypeMake(curArgType));

    // Move to next
    diaCurArg.Release();
    if (FAILED(argTypesEnum->Next(1, &diaCurArg, &count))) {
      throwError();
    }
  }
}


/// <summary>Populate the return type</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeFunction::populateReturnType() {
  // Now, get the return type
  CComPtr<IDiaSymbol> diaReturnType;
  if (FAILED(symbol->get_type(&diaReturnType))) {
    throwError();
  }
  returnType = pdbTypeMake(diaReturnType);
}


/// <summary>Populate the "this" pointer type</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeFunction::populateThisPointerType() {
  // Now, get the calling convention
  CComPtr<IDiaSymbol> diaThisPointerType;
  if (FAILED(symbol->get_objectPointerType(&diaThisPointerType))) {
    throwError();
  }
  if (diaThisPointerType != NULL) {
    // this should always be a pointer
    thisPointerType = dynamic_cast<PdbTypePointer*>(pdbTypeMake(diaThisPointerType));
    if (thisPointerType == NULL) {
      throw runtime_error("Got unexpected non-pointer type for this pointer");
    }
  }
}

