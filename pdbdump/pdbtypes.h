/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Wrappers for Types (classes, enums etc)                              */
/************************************************************************/

#ifndef PDBTYPES_H
#define PDBTYPES_H

#define WIN32_LEAN_AND_MEAN
#pragma warning ( disable : 4786 )
#include <string>
#include <vector>
#include <atlbase.h>
#include <dia2.h>
#include "pdbitems.h"
using namespace std;


// forward type definitions
class PdbTypeUDT;
class PdbType;


//////////////////////////////////////////////////////////////////////////
// Core datatypes
#include "pdb_ctypes.h"

/// <remarks>Abstract class that all PdbType wrappers inherit from</remarks>
///
class PdbType {
protected:
  /// <value>the wrapped symbol</value>
  CComPtr<IDiaSymbol> symbol;

public:

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbType() {};

  /// <summary>PdbType accessor</summary>
  ///
  /// <returns>One of the PdbTypeId enumeration</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() = 0;

  /// <summary>Accessor for the unique type code</summary>
  ///
  /// <returns>The unique type code</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual unsigned long getUniqueTypeCode();

  /// <summary>Get the size of the type in bytes</summary>
  ///
  /// <returns>Size in bytes</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual unsigned __int64 getSizeBytes();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeUDTFriend

/// <remarks>Type for a friend of a UDT</remarks>
///
class PdbTypeUDTFriend {
protected:
  /// <value>The wrapped symbol</value>
  CComPtr<IDiaSymbol> symbol;

  /// <value>Parent UDT of the friend</value>
  PdbTypeUDT* parentUDTType;

  /// <value>Type of the befriended UDT</value>
  PdbTypeUDT* befriendedUDT;

  /// <value>Type of the befriended UDT</value>
  PdbItemFunction* befriendedFunction;

  // <value>Is the befriended details populated</value>
  bool befriendedPopulated;

  /// <summary>Populate parent udt type</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateParentUDTType();

  /// <summary>Populate befriended item</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateBefriended();


public:

  /// <summary>Constructor</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeUDTFriend(IDiaSymbol* symbol);

  /// <summary>Get the name of the friend</summary>
  ///
  /// <returns>The name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  wstring getName();

  /// <summary>Get the type of the parent UDT</summary>
  ///
  /// <returns>The parent UDT type</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeUDT* getParentUDTType();

  /// <summary>Is it a UDT that has been befriended</summary>
  ///
  /// <returns>True if it is a UDT that has been befriended</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isBefriendedUDT();

  /// <summary>Is it a function that has been befriended</summary>
  ///
  /// <returns>True if it is a function that has been befriended</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isBefriendedFunction();

  /// <summary>Is it a UDT that has been befriended</summary>
  ///
  /// <returns>True if it is a UDT that has been befriended</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeUDT* getBefriendedUDT();

  /// <summary>Is it a function that has been befriended</summary>
  ///
  /// <returns>True if it is a function that has been befriended</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbItemFunction* getBefriendedFunction();

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeUDTFriend();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeUDTBaseClass


/// <remarks>Structure holding a base class</remarks>
///
class PdbTypeUDTBaseClass {
protected:
  /// <value>The wrapped symbol</value>
  CComPtr<IDiaSymbol> symbol;

  /// <value>Type of the base class</value>
  PdbTypeUDT* baseClassType;

  /// <summary>Populate the base class type</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateBaseClass();

public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">Symbol to wrap</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeUDTBaseClass(IDiaSymbol* symbol);

  /// <summary>Is the base class an indirect base class</summary>
  ///
  /// <returns>True if it is</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isIndirectBaseClass();

  /// <summary>Is the base class a virtual class</summary>
  ///
  /// <returns>True if it is</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isVirtual();

  /// <summary>Get offset in structure of sub-object representing this baseclass</summary>
  ///
  /// <returns>The offset</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  long getOffset();

  /// <summary>Get index into virtual base displacement table</summary>
  ///
  /// <returns>The index</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getVirtualBaseDispIndex();

  /// <summary>Get virtual base pointer offset</summary>
  ///
  /// <returns>The offset</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  long getVirtualBasePointerOffset();

  /// <summary>Get type of the base class</summary>
  ///
  /// <returns>The type</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeUDT* getBaseClassType();

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeUDTBaseClass();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeUDT

/// <remarks>Abstract class that all UDTs inherit from</remarks>
///
class PdbTypeUDT : public virtual PdbType {
protected:

  // <value>List of friends of this UDT</value>
  bool friendsPopulated;
  vector<PdbTypeUDTFriend*> friends;

  // <value>List of direct base classes of this UDT</value>
  bool baseClassesPopulated;
  vector<PdbTypeUDTBaseClass*> baseClasses;

  // <value>Data members</value>
  bool dataPopulated;
  vector<PdbItemData*> nonStaticData;
  vector<PdbItemData*> staticData;

  // <value>Function members</value>
  bool functionsPopulated;
  vector<PdbItemFunction*> staticFunctions;
  vector<PdbItemFunction*> nonVirtualFunctions;
  vector<PdbItemFunction*> virtualFunctions;


  /// <summary>Populate data of this UDT</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateData();

  /// <summary>Populate functions of this UDT</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateFunctions();

  /// <summary>Populate friends of this UDT</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateFriends();

  /// <summary>Populate base classes of this UDT</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateBaseClasses();


public:

  /// <summary>Constructor</summary>
  ///
  PdbTypeUDT() : 
      friendsPopulated(false), 
      baseClassesPopulated(false),
      dataPopulated(false),
      functionsPopulated(false)
  {}

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeUDT();

  /// <summary>Get friends of this UDT</summary>
  ///
  /// <returns>Vector of friends</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual vector<PdbTypeUDTFriend*> getFriends();

  /// <summary>Get base classes of this UDT</summary>
  ///
  /// <returns>Vector of base classes</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual vector<PdbTypeUDTBaseClass*> getBaseClasses();

  /// <summary>Get name of the UDT</summary>
  ///
  /// <returns>The name</returns>
  ///
  virtual wstring getName() = 0;

  /// <summary>Does the UDT have any constructors</summary>
  ///
  /// <returns>True if it does</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual bool hasConstructors();

  /// <summary>Does the UDT have any assignment operators</summary>
  ///
  /// <returns>True if it does</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual bool hasAssignmentOperators();

  /// <summary>Does the UDT have any cast operators</summary>
  ///
  /// <returns>True if it does</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual bool hasCastOperators();

  /// <summary>Does the UDT have any overloaded operators</summary>
  ///
  /// <returns>True if it does</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual bool hasOverloadedOperators();

  /// <summary>Is the UDT nested</summary>
  ///
  /// <returns>True if it is</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual bool isNested();

  /// <summary>Is the UDT packed?</summary>
  ///
  /// <returns>True if it is</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual bool isPacked();

  /// <summary>Does the UDT appear in a non-global lexical scope?</summary>
  ///
  /// <returns>True if it does</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual bool isScoped();

  /// <summary>Get the number of entries in the vtable</summary>
  ///
  /// <returns>Number of entries</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getVtableSize();

  /// <summary>Get list of virtual functions in order</summary>
  ///
  /// <returns>Vector of virtual functions</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemFunction*> getVirtualFunctions();

  /// <summary>Get list of non-virtual and non-static functions in order</summary>
  ///
  /// <returns>Vector of non-virtual and non-static functions</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemFunction*> getNonVirtualFunctions();

  /// <summary>Get list of static functions in order</summary>
  ///
  /// <returns>Vector of static functions</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemFunction*> getStaticFunctions();
    
  /// <summary>Get list of non-static data in order</summary>
  ///
  /// <returns>Vector of non-static data</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemData*> getNonStaticData();

  /// <summary>Get list of static data in order</summary>
  ///
  /// <returns>Vector of all the static data</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemData*> getStaticData();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeBasic

/// <remarks>A Basic type... ints etc</remarks>
///
class PdbTypeBasic : public virtual PdbType {
public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagBaseType</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeBasic(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeBasic();

  /// <summary>Get the ID of this type</summary>
  ///
  /// <returns>DIAID_BASIC</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_BASIC; }

  /// <summary>Get the code of the wrapped BasicType</summary>
  ///
  /// <returns>One of the DIA SDK BasicType enumeration</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  BasicType getBasicTypeCode();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypePointer

/// <remarks>A type which points to other types</remarks>
///
class PdbTypePointer : public virtual PdbType {
private:
  /// <value>Pointer depth</value>
  int pointerDepth;

  /// <value>The type being pointed to</value>
  PdbType* pointeeType;

  /// <value>Has the pointer been populated</value>
  bool pointerPopulated;

  /// <summary>Populate the pointer data structure</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populatePointer();


public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagPointerType</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypePointer(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypePointer();

  /// <summary>Get the ID of this type</summary>
  ///
  /// <returns>DIAID_POINTER</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_POINTER; }

  /// <summary>Gets the depth of the pointer</summary>
  ///
  /// <returns>How many levels of indirection</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  int getIndirectionDepth();

  /// <summary>Gets the type being pointed to</summary>
  ///
  /// <returns>PdbType structure describing the type being pointed to.</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbType* getPointeeType();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeReference


/// <remarks>A C++-style reference type</remarks>
///
class PdbTypeReference : public virtual PdbType {
private:
  /// <value>The type being referred to</value>
  PdbType* refereeType;

  /// <summary>Populate referee type</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateRefereeType();

public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagReferenceType</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeReference(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeReference();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_REFERENCE</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_REFERENCE; }

  /// <summary>Gets the type being pointed to</summary>
  ///
  /// <returns>PdbType structure describing the type being pointed to.</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbType* getRefereeType();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeArray

/// <summary>Type for storing array indices</summary>
///
typedef pair<PdbTypeBasic*, unsigned __int64> PdbTypeArrayIndex;

/// <summary>Array type</summary>
///
class PdbTypeArray : public virtual PdbType {
private:
  /// <value>The type of array elements</value>
  PdbType* elementType;

  /// <value>Dimensions of the array</value>
  vector<PdbTypeArrayIndex> arrayIndices;

  /// <value>Has the array structure been populated?</value>
  bool arrayPopulated;

  /// <summary>Populates the array structure with data</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateArray();

public:

  /// <summary>Constructor</summary>
  /// 
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagArrayType</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeArray(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeArray();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_ARRAY</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_ARRAY; }

  /// <summary>Gets the array element type</summary>
  ///
  /// <returns>PdbType structure describing the array element type.</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbType* getElementType();

  /// <summary>Get a vector of the array indices</summary>
  ///
  /// <returns>Vector containing all array indices</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbTypeArrayIndex> getArrayIndices();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeManaged

/// <remarks>Managed type</remarks>
///
class PdbTypeManaged : public virtual PdbType {
private:

public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagManagedType</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeManaged(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeManaged();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_MANAGED</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_MANAGED; }

  /// <summary>Gets the name of the managed type</summary>
  ///
  /// <returns>The name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  wstring getName();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeCustom

/// <remarks>Custom type</remarks>
///
class PdbTypeCustom : public virtual PdbType {
private:

public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagCustomType</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeCustom(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeCustom();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_CUSTOM</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_CUSTOM; }

  /// <summary>Gets the GUID of the custom type</summary>
  ///
  /// <returns>The guid</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  GUID getGuid();

  /// <summary>Gets the OemId of the custom type</summary>
  ///
  /// <returns>The oemId</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  DWORD getOemId();

  /// <summary>Gets the OemSymbolId of the custom type</summary>
  ///
  /// <returns>The oemSymbolId</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  DWORD getOemSymbolId();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeEnumeration

/// <remarks>Type for representing a value of the enumation</remarks>
///
typedef pair<wstring, unsigned long> PdbTypeEnumerationValue;

/// <remarks>Enumeration type</remarks>
///
class PdbTypeEnumeration : public virtual PdbType {
private:
  /// <value>Vector of values of the enumeration</value>
  bool valuesPopulated;
  vector<PdbTypeEnumerationValue> values;

  // <value>Base type of the enumeration</value>
  PdbTypeBasic* enumType;

  /// <summary>Populate values of the enumeration</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateValues();

  /// <summary>Populate enumType</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateEnumType();


public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagCustomType</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeEnumeration(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeEnumeration();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_ENUMERATION</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_ENUMERATION; }

  /// <summary>Gets the name of the enumeration</summary>
  ///
  /// <returns>The name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  wstring getName();

  /// <summary>Is the enumeration nested</summary>
  ///
  /// <returns>True if it is</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isNested();

  /// <summary>Does the enumeration appear in a non-global lexical scope </summary>
  ///
  /// <returns>True if it is</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isScoped();

  /// <summary>Gets the underlying enumeration type</summary>
  ///
  /// <returns>The type on which the enumeration is based (Must be a PdbTypeBasic)</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeBasic* getEnumType();

  /// <summary>Gets the values of the enumeration</summary>
  ///
  /// <returns>Vector of PdbTypeEnumerationValues</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbTypeEnumerationValue> getValues();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeClass

/// <remarks>UDT Class type</remarks>
///
class PdbTypeClass : public virtual PdbTypeUDT {
private:
public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagUDTType</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeClass(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeClass();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_CLASS</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_CLASS; }

  /// <summary>Get name of the class</summary>
  ///
  /// <returns>The name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual wstring getName();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeStruct

/// <remarks>UDT Struct type</remarks>
///
class PdbTypeStruct : public virtual PdbTypeUDT {
private:
public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagUDTType</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeStruct(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeStruct();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_STRUCT</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_STRUCT; }

  /// <summary>Get name of the struct</summary>
  ///
  /// <returns>The name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual wstring getName();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeUnion

/// <remarks>UDT Union type</remarks>
///
class PdbTypeUnion : public virtual PdbTypeUDT {
private:
public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagUDTType</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeUnion(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeUnion();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_UNION</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_UNION; }

  /// <summary>Get name of the union</summary>
  ///
  /// <returns>The name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual wstring getName();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeTypedef

/// <remarks>PDB typedef type</remarks>
///
class PdbTypeTypedef : public virtual PdbType {
private:
  /// <value>Sub type</value>
  PdbType* subType;

  /// <summary>Populate sub-type</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateSubType();

public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagTypedef</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeTypedef(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeTypedef();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_TYPEDEF</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_TYPEDEF; }

  /// <summary>Get name of the typedef</summary>
  ///
  /// <returns>The name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual wstring getName();

  /// <summary>Get sub type of the typedef</summary>
  ///
  /// <returns>The sub-type</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  virtual PdbType* getSubType();
};



//////////////////////////////////////////////////////////////////////////
// PdbTypeFunction

/// <remarks>PDB function type</remarks>
///
class PdbTypeFunction : public virtual PdbType {
private:

  /// <value>Arguments to the function</value>
  bool argumentsPopulated;
  vector<PdbType*> arguments;

  /// <value>Type of this function's "this" pointer</value>
  PdbTypePointer* thisPointerType;

  /// <value>Return type of the function</value>
  PdbType* returnType;

  /// <summary>Populate the arguments</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateArguments();

  /// <summary>Populate the return type</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateReturnType();

  /// <summary>Populate the "this" pointer type</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateThisPointerType();

public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagFunctionType</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypeFunction(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbTypeFunction();

  /// <summary>Implementation of typeId accessor</summary>
  ///
  /// <returns>DIAID_FUNCTION</returns>
  ///
  virtual PdbTypeIds getPdbTypeId() { return DIAID_FUNCTION; }

  /// <summary>Calling convention of the function</summary>
  ///
  /// <returns>One of the CV_call_e enumeration</returns>
  ///
  /// <exception c_ref="runtime_error">On internal error or if the function is a thunk</exception>
  ///
  CV_call_e getCallingConvention();

  /// <summary>Logical this adjustor for the method</summary>
  ///
  /// <returns>The value</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  long getThisAdjust();
  
  /// <summary>Get list of function arguments</summary>
  ///
  /// <returns>Vector of types in order</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbType*> getArguments();

  /// <summary>Get return type of function </summary>
  ///
  /// <returns>The return type</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbType* getReturnType();
    
  /// <summary>Get type of this function's "this" pointer</summary>
  ///
  /// <returns>The UDT type of the "this" pointer. May be NULL if the 
  /// function has no "this" pointer.. e.g. a static member or global function</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbTypePointer* getThisPointerType();
};


#endif

