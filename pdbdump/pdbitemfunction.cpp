/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbItemFunction                                    */
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
PdbItemFunction::PdbItemFunction(IDiaSymbol* symbol) {
  // Check the tag of the symbol
  DWORD tag;
  if (FAILED(symbol->get_symTag(&tag))) {
    throwError();
  }
  if (tag == SymTagFunction) {
    isThunkFlag = false;
  } else if (tag == SymTagThunk) {
    isThunkFlag = true;
  } else {
    throw runtime_error("Unexpected tag detected at PdbItemFunction");
  }

  // remember the symbol
  this->symbol = symbol;
  functionType = NULL;
  parentUDT = NULL;
  objectPointer = NULL;
  dataPopulated = false;
  labelsPopulated = false;

  // work out if it has a parent UDT 
  CComPtr<IDiaSymbol> diaParentUDT;
  if (FAILED(symbol->get_classParent(&diaParentUDT))) {
    throwError();
  }
  if (diaParentUDT != NULL) {
    hasParentUDTFlag = true;
  } else {
    hasParentUDTFlag = false;
  }

  // check it has a valid location
  DWORD val;
  if (FAILED(symbol->get_locationType(&val))) {
    throwError();
  }
  if (!isThunkFlag) {
    if ((val != LocIsStatic) && (val != LocInMetaData) && (val != LocIsNull)) {
      throw runtime_error("Unexpected function location");
    }
  } else {
    if (val != LocIsStatic) {
      throw runtime_error("Unexpected thunk location");
    }
  }
}


/// <summary>Destructor</summary>
///
PdbItemFunction::~PdbItemFunction() {
  if (functionType != NULL) {
    delete functionType;
  }
  if (parentUDT != NULL) {
    delete parentUDT;
  }
  if (objectPointer != NULL) {
    delete objectPointer;
  }
  unsigned int i;
  for(i=0; i< parameters.size(); i++) {
    delete parameters[i];
  }
  for(i=0; i< locals.size(); i++) {
    delete locals[i];
  }
  for(i=0; i< staticLocals.size(); i++) {
    delete staticLocals[i];
  }
  for(i=0; i< constants.size(); i++) {
    delete constants[i];
  }
  for(i=0; i< labels.size(); i++) {
    delete labels[i];
  }
}


/// <summary>Get name of function</summary>
///
/// <returns>The name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbItemFunction::getName() {
  // get the name
  BSTR nameB = NULL;
  if (FAILED(symbol->get_name(&nameB)) || !nameB) {
    throwError();
  }
  wstring name = nameB;
  LocalFree(nameB);

  // return name
  return name;
}


/// <summary>Determines if the function is a thunk</summary>
///
/// <returns>true if it is a thunk</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbItemFunction::isThunk() {
  return isThunkFlag;
}


/// <summary>Get function access</summary>
///
/// <returns>One of the CV_access_e enumeration</returns>
///
/// <exception c_ref="runtime_error">If the function is a thunk</exception>
///
CV_access_e PdbItemFunction::getAccess() {
  if (isThunkFlag) throw runtime_error("Attempt to call function-only method for a thunk");

  DWORD access;
  if (FAILED(symbol->get_access(&access))) {
    throwError();
  }
  return (CV_access_e) access;
}


/// <summary>Determines if the function is virtual</summary>
///
/// <returns>true if it is</returns>
///
/// <exception c_ref="runtime_error">If the function is a thunk</exception>
///
bool PdbItemFunction::isVirtual() {
  if (isThunkFlag) throw runtime_error("Attempt to call function-only method for a thunk");

  BOOL boolVal;
  if (FAILED(symbol->get_virtual(&boolVal))) {
    throwError();
  }
  return (bool) boolVal;
}


/// <summary>Determines if the function is pure virtual</summary>
///
/// <returns>true if it is</returns>
///
/// <exception c_ref="runtime_error">If the function is a thunk</exception>
///
bool PdbItemFunction::isPureVirtual() {
  if (isThunkFlag) throw runtime_error("Attempt to call function-only method for a thunk");

  BOOL boolVal;
  if (FAILED(symbol->get_pure(&boolVal))) {
    throwError();
  }
  return (bool) boolVal;
}


/// <summary>Determines if the function is introducing a virtual for 
/// the first time</summary>
///
/// <returns>true if it is</returns>
///
/// <exception c_ref="runtime_error">If the function is a thunk</exception>
///
bool PdbItemFunction::isIntroVirtual() {
  if (isThunkFlag) throw runtime_error("Attempt to call function-only method for a thunk");

  BOOL boolVal;
  if (FAILED(symbol->get_intro(&boolVal))) {
    throwError();
  }
  return (bool) boolVal;
}


/// <summary>Get function location</summary>
///
/// <returns>Either static or metadata from LocationType enumeration. 
/// Thunks can only be static</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
LocationType PdbItemFunction::getLocation() {
  DWORD val;
  if (FAILED(symbol->get_locationType(&val))) {
    throwError();
  }
  return (LocationType) val;
}


/// <summary>Get size of function/thunk in bytes</summary>
///
/// <returns>Size in bytes</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned __int64 PdbItemFunction::getSizeBytes() {
  unsigned __int64 val;
  if (FAILED(symbol->get_length(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Gets the metadata token if the function's location is 
/// metadata</summary>
///
/// <returns>The token</returns>
///
/// <exception c_ref="runtime_error">If the function is a thunk</exception>
///
unsigned long PdbItemFunction::getMetadataToken() {
  if (isThunkFlag) throw runtime_error("Attempt to call function-only method for a thunk");

  unsigned long val;
  if (FAILED(symbol->get_token(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Gets the RVA if the function's location is static</summary>
///
/// <returns>The RVA</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbItemFunction::getRVA() {
  unsigned long val;
  if (FAILED(symbol->get_relativeVirtualAddress(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Gets the type of a thunk</summary>
///
/// <returns>One of the THUNK_ORDINAL enumeration</returns>
///
/// <exception c_ref="runtime_error">If the function is NOT a thunk</exception>
///
THUNK_ORDINAL PdbItemFunction::getThunkType() {
  if (!isThunkFlag) throw runtime_error("Attempt to call thunk-only method for a function");

  DWORD val;
  if (FAILED(symbol->get_thunkOrdinal(&val))) {
    throwError();
  }
  return (THUNK_ORDINAL) val;
}


/// <summary>Gets the function type</summary>
///
/// <returns>The function type signature. WARNING: It is legal for
/// this call to return NULL. In this case, the function has no type
/// information available.</returns>
///
/// <exception c_ref="runtime_error">If the function is a thunk</exception>
///
PdbTypeFunction* PdbItemFunction::getFunctionType() {
  if (isThunkFlag) throw runtime_error("Attempt to call function-only method for a thunk");
  if (functionType == NULL) {
    populateFunctionType();
  }
  return functionType;
}


/// <summary>Determines if the function has a parent UDT</summary>
///
/// <returns>true if it does</returns>
///
/// <exception c_ref="runtime_error">If the function is a thunk</exception>
///
bool PdbItemFunction::hasParentUDT() {
  return hasParentUDTFlag;
}


/// <summary>Gets the UDT this function is a member of</summary>
///
/// <returns>The UDT</returns>
///
/// <exception c_ref="runtime_error">If there is no enclosing UDT</exception>
///
PdbTypeUDT* PdbItemFunction::getParentUDT() {
  if (!hasParentUDTFlag) throw runtime_error("Attempt to retrieve parent UDT when one does not exist");
  if (parentUDT == NULL) {
    populateParentUDT();
  }
  return parentUDT;
}


/// <summary>Gets the virtual base offset for a function</summary>
///
/// <returns>The virtual base offset</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbItemFunction::getVirtualBaseOffset() {
  unsigned long val;
  if (FAILED(symbol->get_virtualBaseOffset(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Get parameters to the function</summary>
///
/// <returns>Vector of parameters</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemData*> PdbItemFunction::getParameters() {
  if (!dataPopulated) {
    populateData();
    dataPopulated = true;
  }

  // otherwise, return normally derived params
  return parameters;
}


/// <summary>Get locals of the function</summary>
///
/// <returns>Vector of locals</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemData*> PdbItemFunction::getLocals() {
  if (!dataPopulated) {
    populateData();
    dataPopulated = true;
  }
  return locals;
}


/// <summary>Get static locals of the function</summary>
///
/// <returns>Vector of static locals</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemData*> PdbItemFunction::getStaticLocals() {
  if (!dataPopulated) {
    populateData();
    dataPopulated = true;
  }
  return staticLocals;
}


/// <summary>Get object pointer of the function</summary>
///
/// <returns>Object pointer. NULL if there IS no object pointer</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbItemData* PdbItemFunction::getObjectPointer() {
  if (!dataPopulated) {
    populateData();
    dataPopulated = true;
  }
  return objectPointer;
}


/// <summary>Get constants of the function</summary>
///
/// <returns>Vector of constants</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemData*> PdbItemFunction::getConstants() {
  if (!dataPopulated) {
    populateData();
    dataPopulated = true;
  }
  return constants;
}


/// <summary>Get labels of the function</summary>
///
/// <returns>Vector of labels</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemLabel*> PdbItemFunction::getLabels() {
  if (!labelsPopulated) {
    populateLabels();
    labelsPopulated = true;
  }
  return labels;
}


/// <summary>Populate the function type</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbItemFunction::populateFunctionType() {
  // get the funtion type
  CComPtr<IDiaSymbol> diaFunctionType;
  if (FAILED(symbol->get_type(&diaFunctionType))) {
    throwError();
  }

  // 16 Feb 2007 - dirty hack !
  if ( NULL == diaFunctionType )
   return;
  // if its NOT of type function, see if it has no type info
  DWORD tag;
  if (FAILED(diaFunctionType->get_symTag(&tag))) {
    throwError();
  }
  if (tag != SymTagFunctionType) {
    // it should be SymTagBaseType though
    if (tag != SymTagBaseType) {
      throw runtime_error("Invalid function type");
    }

    // it should also have btNoType
    DWORD baseType;
    if (FAILED(diaFunctionType->get_baseType(&baseType))) {
      throwError();
    }
    if (baseType != btNoType) {
      throw runtime_error("Invalid function type");
    }
    
    // OK function has no type info
    return;
  }

  // Otherwise, decode the function type as expected
  functionType = new PdbTypeFunction(diaFunctionType);
}


/// <summary>Populate the parent UDT</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbItemFunction::populateParentUDT() {
  // Now, get the class parent
  CComPtr<IDiaSymbol> diaParentUDT;
  if (FAILED(symbol->get_classParent(&diaParentUDT))) {
    throwError();
  }
  parentUDT = dynamic_cast<PdbTypeUDT*>(pdbTypeMake(diaParentUDT));
}


/// <summary>Populate data</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbItemFunction::populateData() {
  CComPtr<IDiaEnumSymbols> dataEnum;
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurData;

  // find all data symbols
  if (FAILED(symbol->findChildren(SymTagData, NULL, nsNone, &dataEnum))) {
    throwError();
  }

  // If a function has come from a UDT, the above call fails... need to
  // check for this
  if (dataEnum == NULL) {
    return;
  }

  // Otherwise, iterate over 'em
  if (FAILED(dataEnum->Next(1, &diaCurData, &count))) {
    throwError();
  }
  while(count) {
    // wrap data item
    PdbItemData* curData = new PdbItemData(diaCurData);

    // deal with the different kinds
    switch(curData->getDataKind()) {
    case DataIsLocal:
      locals.insert(locals.end(), curData);
      break;

    case DataIsStaticLocal:
      staticLocals.insert(staticLocals.end(), curData);
      break;

    case DataIsParam:
      parameters.insert(parameters.end(), curData);
      break;

    case DataIsObjectPtr:
      if (objectPointer != NULL) {
        throw runtime_error("Function has more than one object pointer");
      }
      objectPointer = curData;
      break;

    case DataIsConstant:
      constants.insert(constants.end(), curData);
      break;

    default: 
      delete curData;
      throw runtime_error("Unexpected data kind in function");
    }
    
    // next
    diaCurData.Release();
    if (FAILED(dataEnum->Next(1, &diaCurData, &count))) {
      throwError();
    }
  }
}


/// <summary>Populate labels</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbItemFunction::populateLabels() {
  // get list of labels
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(symbol->findChildren(SymTagLabel, NULL, nsNone, &itemsEnum))) {
    throwError();
  }
  
  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    throwError();
  }
  while(count) {
    // add it in
    labels.insert(labels.end(), new PdbItemLabel(diaCurItem));

    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      throwError();
    }
  }
}

