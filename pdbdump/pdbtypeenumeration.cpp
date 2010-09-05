/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeEnumeration                                 */
/************************************************************************/

#include "pdbtypes.h"
#include "_pdbint.h"
#pragma warning(disable:4800)


/// <summary>Constructor</summary>
///
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagCustomType</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeEnumeration::PdbTypeEnumeration(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagEnum, "PdbTypeEnumeration");

  // remember the symbol
  this->symbol = symbol;

  // setup other fields
  valuesPopulated = false;
  enumType = NULL;
}


/// <summary>Destructor</summary>
///
PdbTypeEnumeration::~PdbTypeEnumeration() {
  if (enumType != NULL) {
    delete enumType;
  }
}


/// <summary>Populate values of the enumeration</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeEnumeration::populateValues() {
  // Get all values of the enumeration
  CComPtr<IDiaEnumSymbols> enumValuesEnum;
  if (FAILED(symbol->findChildren(SymTagData, NULL, nsNone, &enumValuesEnum))) {
    throwError();
  }

  // Enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> curValue;
  if (FAILED(enumValuesEnum->Next(1, &curValue, &count))) {
    throwError();
  }
  while(count) {
    // check it is a constant value
    DWORD locationType;
    if (FAILED(curValue->get_locationType(&locationType))) {
      throwError();
    }
    if (locationType != LocIsConstant) {
      throw runtime_error("Enumeration with a non-constant value");
    }

    // get the value
    VARIANT value;
    if (FAILED(curValue->get_value(&value))) {
      throwError();
    }
    
    // extract the value
    unsigned long valueL;
    switch(value.vt) {
    case VT_UI1: valueL = value.bVal; break;
    case VT_UI2: valueL = value.uiVal; break;
    case VT_UI4: valueL = value.ulVal; break;
    case VT_UINT: valueL = value.uintVal; break;
    case VT_INT: valueL = value.intVal; break;
    case VT_I1: valueL = value.cVal; break;
    case VT_I2: valueL = value.iVal; break;
    case VT_I4: valueL = value.lVal; break;
    default:
      throw runtime_error("Enumeration with a value of non-integer type");
    }

    // get the name
    BSTR valueName = NULL;
    if (FAILED(curValue->get_name(&valueName)) || !valueName) {
      throwError();
    }

    // store it in the vector
    values.insert(values.end(), PdbTypeEnumerationValue(valueName, valueL));

    // move to next
    LocalFree(valueName);
    curValue.Release();
    if (FAILED(enumValuesEnum->Next(1, &curValue, &count))) {
      throwError();
    }
  }
}


/// <summary>Populate enumType</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeEnumeration::populateEnumType() {
  // Make up enumType
  CComPtr<IDiaSymbol> diaEnumType;
  if (FAILED(symbol->get_type(&diaEnumType))) {
    throwError();
  }
  enumType = new PdbTypeBasic(diaEnumType);
}


/// <summary>Gets the name of the enumeration</summary>
///
/// <returns>The name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbTypeEnumeration::getName() {
  return _getName(symbol);
}


/// <summary>Is the enumeration nested</summary>
///
/// <returns>True if it is</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeEnumeration::isNested() {
  BOOL boolValue;
  if (FAILED(symbol->get_nested(&boolValue))) {
    throwError();
  }
  return (bool) boolValue;
}


/// <summary>Does the enumeration appear in a non-global lexical scope </summary>
///
/// <returns>True if it is</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeEnumeration::isScoped() {
  BOOL boolValue;
  if (FAILED(symbol->get_scoped(&boolValue))) {
    throwError();
  }
  return (bool) boolValue;
}


/// <summary>Gets the underlying enumeration type</summary>
///
/// <returns>The type on which the enumeration is based (Must be a PdbTypeBasic)</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeBasic* PdbTypeEnumeration::getEnumType() {
  if (enumType == NULL) {
    populateEnumType();
  }
  return enumType;
}


/// <summary>Gets the values of the enumeration</summary>
///
/// <returns>Vector of PdbTypeEnumerationValues</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbTypeEnumerationValue> PdbTypeEnumeration::getValues() {
  if (!valuesPopulated) {
    populateValues();
    valuesPopulated = true;
  }
  return values;
}

