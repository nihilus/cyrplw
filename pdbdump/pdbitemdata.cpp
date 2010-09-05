/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/************************************************************************/

#include "pdbtypes.h"
#include "pdbitems.h"
#include "pdbutils.h"
#include "_pdbint.h"
#pragma warning(disable:4800)


/// <summary>Constructor</summary>
///
/// <param name="symbol">Symbol to wrap</symbol>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbItemData::PdbItemData(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagData, "PdbItemData");

  // remember the symbol
  this->symbol = symbol;
  parentUDT = NULL;
  dataType = NULL;

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
}


/// <summary>Destructor</summary>
///
PdbItemData::~PdbItemData() {
  if (parentUDT != NULL) {
    delete parentUDT;
  }
  if (dataType != NULL) {
    delete dataType;
  }
}


/// <summary>Get data access</summary>
///
/// <returns>One of the CV_access_e enumeration</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
CV_access_e PdbItemData::getAccess() {
  DWORD access;
  if (FAILED(symbol->get_access(&access))) {
    throwError();
  }
  return (CV_access_e) access;
}


/// <summary>Gets the RVA if the location is static</summary>
///
/// <returns>The RVA</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbItemData::getRVA() {
  unsigned long val;
  if (FAILED(symbol->get_relativeVirtualAddress(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Gets the bitfield position if the location is bitfield</summary>
///
/// <returns>The bitfield position</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbItemData::getBitfieldPosition() {
  unsigned long val;
  if (FAILED(symbol->get_bitPosition(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Gets the bitfield size if the location is bitfield</summary>
///
/// <returns>The bitfield size</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned __int64 PdbItemData::getBitfieldSize() {
  unsigned __int64 val;
  if (FAILED(symbol->get_length(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Determines if the data has a parent UDT or not</summary>
///
/// <returns>true if it does</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbItemData::hasParentUDT() {
  return hasParentUDTFlag;
}


/// <summary>Gets the UDT this data is a member of</summary>
///
/// <returns>The UDT</returns>
///
/// <exception c_ref="runtime_error">If there is no enclosing UDT</exception>
///
PdbTypeUDT* PdbItemData::getParentUDT() {
  if (!hasParentUDTFlag) throw runtime_error("Attempt to retrieve parent UDT when one does not exist");
  if (parentUDT == NULL) {
    populateParentUDT();
  }
  return parentUDT;
}


/// <summary>Gets the data kind</summary>
///
/// <returns>One of the DataKind enumeration</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
DataKind PdbItemData::getDataKind() {
  DWORD val;
  if (FAILED(symbol->get_dataKind(&val))) {
    throwError();
  }
  return (DataKind) val;
}


/// <summary>Gets the data location</summary>
///
/// <returns>One of the LocationType enumeration</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
LocationType PdbItemData::getLocation() {
  DWORD val;
  if (FAILED(symbol->get_locationType(&val))) {
    throwError();
  }
  return (LocationType) val;
}


/// <summary>Gets the name of the data</summary>
///
/// <returns>The name</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring PdbItemData::getName() {
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


/// <summary>Gets the register data is stored in (only if the data has 
/// enregistered location type)</summary>
///
/// <returns>One of the CV_HREG_e enumeration</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
CV_HREG_e PdbItemData::getRegister() {
  DWORD val;
  if (FAILED(symbol->get_registerId(&val))) {
    throwError();
  }
  return (CV_HREG_e) val;
}


/// <summary>Gets the offset of the data</summary>
///
/// <returns>Offset</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
long PdbItemData::getOffset() {
  LONG val;
  if (FAILED(symbol->get_offset(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Gets the value of the data (only if the data has constant 
/// location type) </summary>
///
/// <returns>One of the CV_HREG_e enumeration</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
VARIANT PdbItemData::getValue() {
  VARIANT val;
  if (FAILED(symbol->get_value(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Gets the slot of the data (Only for LocIsSlot)</summary>
///
/// <returns>The slot</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbItemData::getSlot() {
  DWORD val;
  if (FAILED(symbol->get_slot(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Gets the metadata token of the data (Only for LocInMetaData)</summary>
///
/// <returns>The token</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbItemData::getToken() {
  DWORD val;
  if (FAILED(symbol->get_token(&val))) {
    throwError();
  }
  return val;
}


/// <summary>Gets the type of the data</summary>
///
/// <returns>The data type</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbType* PdbItemData::getType() {
  if (dataType == NULL) {
    populateDataType();
  }
  return dataType;
}


/// <summary>Populate the parent UDT</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbItemData::populateParentUDT() {
  // Now, get the class parent
  CComPtr<IDiaSymbol> diaParentUDT;
  if (FAILED(symbol->get_classParent(&diaParentUDT))) {
    throwError();
  }
  parentUDT = dynamic_cast<PdbTypeUDT*>(pdbTypeMake(diaParentUDT));
}


/// <summary>Populate the data type</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbItemData::populateDataType() {
  // Now, get the calling convention
  CComPtr<IDiaSymbol> diaDataType;
  if (FAILED(symbol->get_type(&diaDataType))) {
    throwError();
  }
  if (  (IDiaSymbol *)NULL == (IDiaSymbol *)diaDataType )
	return;
  dataType = pdbTypeMake(diaDataType);
}

