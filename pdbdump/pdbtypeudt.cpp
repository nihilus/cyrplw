/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeUDT                                         */
/************************************************************************/

#include "pdbtypes.h"
#include "pdbutils.h"
#include "_pdbint.h"
#include <map>
#include <algorithm>
#pragma warning(disable:4800)
using namespace std;


/// <summary>Populate friends of this UDT</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeUDT::populateFriends() {
  // Get all friends
  CComPtr<IDiaEnumSymbols> friendsEnum;
  if (FAILED(symbol->findChildren(SymTagFriend, NULL, nsNone, &friendsEnum))) {
    throwError();
  }

  // Enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> curFriend;
  if (FAILED(friendsEnum->Next(1, &curFriend, &count))) {
    throwError();
  }
  while(count) {
    // extract name of friend
    BSTR friendName;
    if (FAILED(curFriend->get_name(&friendName))) {
      throwError();
    }

    // extract type of friend
    CComPtr<IDiaSymbol> friendType;
    if (FAILED(curFriend->get_type(&friendType))) {
      throwError();
    }

    // process and add it to the vector
    friends.insert(friends.end(), 
                   new PdbTypeUDTFriend(friendType));

    // move to next friend
    LocalFree(friendName);
    curFriend.Release();
    if (FAILED(friendsEnum->Next(1, &curFriend, &count))) {
      throwError();
    }
  }
}


/// <summary>Populate base classes of this UDT</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeUDT::populateBaseClasses() {
  // Get all base classes 
  CComPtr<IDiaEnumSymbols> baseClassesEnum;
  if (FAILED(symbol->findChildren(SymTagBaseClass, NULL, nsNone, 
                                  &baseClassesEnum))) {
    throwError();
  }

  // Enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> curBaseClass;
  if (FAILED(baseClassesEnum->Next(1, &curBaseClass, &count))) {
    throwError();
  }
  while(count) {
    // process and add it to the vector
    baseClasses.insert(baseClasses.end(), 
                       new PdbTypeUDTBaseClass(curBaseClass));

    // move to next base class
    curBaseClass.Release();
    if (FAILED(baseClassesEnum->Next(1, &curBaseClass, &count))) {
      throwError();
    }
  }
}


/// <summary>Populate data of this UDT</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeUDT::populateData() {
  // work out data symbols
  CComPtr<IDiaEnumSymbols> dataEnum;
  if (FAILED(symbol->findChildren(SymTagData, NULL, nsNone, &dataEnum))) {
    throwError();
  }
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurData;
  if (FAILED(dataEnum->Next(1, &diaCurData, &count))) {
    throwError();
  }
  while(count) {
    // Allocate structure for the data item
    PdbItemData* curData = new PdbItemData(diaCurData);

    // deal with it
    switch(curData->getLocation()) {
    case LocIsThisRel:
    case LocIsBitField:
      nonStaticData.insert(nonStaticData.end(), curData);
      break;

    case LocIsStatic:
      staticData.insert(staticData.end(), curData);
      break;

    default:
      throw runtime_error("Unexpected data location found in class");
    }

    // Move onto the next one
    diaCurData.Release();
    if (FAILED(dataEnum->Next(1, &diaCurData, &count))) {
      throwError();
    }
  }
}


/// <summary>Populate functions of this UDT</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeUDT::populateFunctions() {
  // work out function symbols
  CComPtr<IDiaEnumSymbols> functionEnum;
  if (FAILED(symbol->findChildren(SymTagFunction, NULL, nsNone, &functionEnum))) {
    throwError();
  }
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurFunc;
  if (FAILED(functionEnum->Next(1, &diaCurFunc, &count))) {
    throwError();
  }
  while(count) {
    // Allocate structure for the function 
    PdbItemFunction* curFunc = new PdbItemFunction(diaCurFunc);

    // if the function is virtual, just add to the virtuals list
    if (curFunc->isVirtual()) {
      virtualFunctions.insert(virtualFunctions.end(), curFunc);
    } else {
      // if the function has a "this pointer", then it is a 
      // non-virtual member
      if ((curFunc->getFunctionType() != NULL) &&
          (curFunc->getFunctionType()->getThisPointerType() != NULL)) {
        nonVirtualFunctions.insert(nonVirtualFunctions.end(), curFunc);
      } else {
        // otherwise, it is a static member
        staticFunctions.insert(staticFunctions.end(), curFunc);
      }
    }

    // Move onto the next one
    diaCurFunc.Release();
    if (FAILED(functionEnum->Next(1, &diaCurFunc, &count))) {
      throwError();
    }
  }
}


/// <summary>Does the UDT have any constructors</summary>
///
/// <returns>True if it does</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDT::hasConstructors() {
  BOOL boolValue;
  if (FAILED(symbol->get_constructor(&boolValue))) {
    throwError();
  }
  return (bool) boolValue;
}


/// <summary>Does the UDT have any assignment operators</summary>
///
/// <returns>True if it does</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDT::hasAssignmentOperators() {
  BOOL boolValue;
  if (FAILED(symbol->get_hasAssignmentOperator(&boolValue))) {
    throwError();
  }
  return (bool) boolValue;
}


/// <summary>Does the UDT have any cast operators</summary>
///
/// <returns>True if it does</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDT::hasCastOperators() {
  BOOL boolValue;
  if (FAILED(symbol->get_hasCastOperator(&boolValue))) {
    throwError();
  }
  return (bool) boolValue;
}


/// <summary>Does the UDT have any overloaded operators</summary>
///
/// <returns>True if it does</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDT::hasOverloadedOperators() {
  BOOL boolValue;
  if (FAILED(symbol->get_overloadedOperator(&boolValue))) {
    throwError();
  }
  return (bool) boolValue;
}


/// <summary>Is the UDT nested</summary>
///
/// <returns>True if it is</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDT::isNested() {
  BOOL boolValue;
  if (FAILED(symbol->get_nested(&boolValue))) {
    throwError();
  }
  return (bool) boolValue;
}


/// <summary>Is the UDT packed?</summary>
///
/// <returns>True if it is</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDT::isPacked() {
  BOOL boolValue;
  if (FAILED(symbol->get_packed(&boolValue))) {
    throwError();
  }
  return (bool) boolValue;
}


/// <summary>Does the UDT appear in a non-global lexical scope?</summary>
///
/// <returns>True if it does</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
bool PdbTypeUDT::isScoped() {
  BOOL boolValue;
  if (FAILED(symbol->get_scoped(&boolValue))) {
    throwError();
  }
  return (bool) boolValue;
}


/// <summary>Get friends of this UDT</summary>
///
/// <returns>Vector of friends</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbTypeUDTFriend*> PdbTypeUDT::getFriends() {
  if (!friendsPopulated) {
    populateFriends();
    friendsPopulated = true;
  }
  return friends;
}


/// <summary>Get base classes of this UDT</summary>
///
/// <returns>Vector of base classes</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbTypeUDTBaseClass*> PdbTypeUDT::getBaseClasses() {
  if (!baseClassesPopulated) {
    populateBaseClasses();
    baseClassesPopulated = true;
  }
  return baseClasses;
}


/// <summary>Get the number of entries in the vtable</summary>
///
/// <returns>Number of entries</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
unsigned long PdbTypeUDT::getVtableSize() {
  CComPtr<IDiaSymbol> vtableShape;
  if (FAILED(symbol->get_virtualTableShape(&vtableShape))) {
    throwError();
  }
  DWORD size;
  if (FAILED(vtableShape->get_count(&size))) {
    throwError();
  }
  return size;
}


/// <summary>Destructor</summary>
///
PdbTypeUDT::~PdbTypeUDT() 
{
  // free up base classes
  unsigned int i;
  for(i=0; i < baseClasses.size(); i++) {
    delete baseClasses[i];
  }

  // free up friends
  for(i=0; i < friends.size(); i++) {
    delete friends[i];
  }

  // free up non-static data
  for(i=0; i < nonStaticData.size(); i++) {
    delete nonStaticData[i];
  }

  // free up static data
  for(i=0; i < staticData.size(); i++) {
    delete staticData[i];
  }

  // free up static functions
  for(i=0; i < staticFunctions.size(); i++) {
    delete staticFunctions[i];
  }

  // free up virtual funcitons
  for(i=0; i < virtualFunctions.size(); i++) {
    delete virtualFunctions[i];
  }

  // free up non virtual functions
  for(i=0; i < nonVirtualFunctions.size(); i++) {
    delete nonVirtualFunctions[i];
  }
}


/// <summary>Get list of static data in order</summary>
///
/// <returns>Vector of all the static data</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemData*> PdbTypeUDT::getStaticData() {
  if (!dataPopulated) {
    populateData();
    dataPopulated = true;
  }
  return staticData;
}


/// <summary>Get list of non-static data in order</summary>
///
/// <returns>Vector of non-static data</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemData*> PdbTypeUDT::getNonStaticData() {
  if (!dataPopulated) {
    populateData();
    dataPopulated = true;
  }
  return nonStaticData;
}


/// <summary>Get list of virtual functions in order</summary>
///
/// <returns>Vector of virtual functions</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemFunction*> PdbTypeUDT::getVirtualFunctions() {
  if (!functionsPopulated) {
    populateFunctions();
    functionsPopulated = true;
  }
  return virtualFunctions;
}


/// <summary>Get list of non-virtual and non-static functions in order</summary>
///
/// <returns>Vector of non-virtual and non-static functions</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemFunction*> PdbTypeUDT::getNonVirtualFunctions() {
  if (!functionsPopulated) {
    populateFunctions();
    functionsPopulated = true;
  }
  return nonVirtualFunctions;
}


/// <summary>Get list of static functions in order</summary>
///
/// <returns>Vector of static functions</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbItemFunction*> PdbTypeUDT::getStaticFunctions() {
  if (!functionsPopulated) {
    populateFunctions();
    functionsPopulated = true;
  }
  return staticFunctions;
}

