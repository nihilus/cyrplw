/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Wrappers for Items (functions, variables etc)                        */
/************************************************************************/

#ifndef PDBITEMS_H
#define PDBITEMS_H

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <vector>
#include <atlbase.h>
#include <dia2.h>
#include "pdbtypes.h"
using namespace std;

// forward declarations
class PdbTypeFunction;
class PdbTypeUDT;
class PdbType;
class PdbItemData;



//////////////////////////////////////////////////////////////////////////
// PdbItemLabel

/// <remarks>Encapsulation of label items</remarks>
///
class PdbItemLabel {
protected:
  /// <value>The wrapped symbol</value>
  CComPtr<IDiaSymbol> symbol;

public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">Symbol to wrap</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbItemLabel(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbItemLabel() {}

  /// <summary>Get label name</summary>
  ///
  /// <returns>Name of the label</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  wstring getName();

  /// <summary>Get RVA of the label</summary>
  ///
  /// <returns>RVA</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getRVA();
};





//////////////////////////////////////////////////////////////////////////
// PdbItemPublicSymbol

/// <remarks>Encapsulation of PublicSymbol items</remarks>
///
class PdbItemPublicSymbol {
protected:
  /// <value>The wrapped symbol</value>
  CComPtr<IDiaSymbol> symbol;

public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">Symbol to wrap</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbItemPublicSymbol(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbItemPublicSymbol() {}

  /// <summary>Get name</summary>
  ///
  /// <returns>Name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  wstring getName();

  /// <summary>Get RVA</summary>
  ///
  /// <returns>RVA</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getRVA();

  /// <summary>Determines if the symbol is in managed code</summary>
  ///
  /// <returns>True if it is</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isInManagedCode();

  /// <sumary>Determines if the symbol is in MSIL code</summary>
  ///
  /// <returns>True if it is</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isInMSIL();

  /// <summary>Determines if the symbol is a function</summary>
  ///
  /// <returns>True if it is a function, false if it is data</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isFunction();

  /// <summary>Determines if the symbol is in code</summary>
  ///
  /// <returns>True if it is</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isInCode();
};



//////////////////////////////////////////////////////////////////////////
// PdbItemFunction

/// <remarks>Encapsulation of function</remarks>
///
class PdbItemFunction {
protected:
  // <value>The wrapped symbol</value>
  CComPtr<IDiaSymbol> symbol;

  // <value>is this a thunk?</value>
  bool isThunkFlag;

  // <value>Type of the function</value>
  PdbTypeFunction* functionType;

  // <value>UDT this function is a member of</value>
  PdbTypeUDT* parentUDT;

  // <value>Data items in this function</value>
  bool dataPopulated;
  vector<PdbItemData*> parameters;
  vector<PdbItemData*> locals;
  vector<PdbItemData*> staticLocals;
  vector<PdbItemData*> constants;
  PdbItemData* objectPointer;

  // <value>Flag indicating that getParameters() call should get 'em
  // from the function type</value>
  bool getParamsFromType;

  // <value>Labels in this function</value>
  bool labelsPopulated;
  vector<PdbItemLabel*> labels;

  // <value>Does this have a parent UDT?</value>
  bool hasParentUDTFlag;

  /// <summary>Populate the function type</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateFunctionType();

  /// <summary>Populate the parent UDT</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateParentUDT();

  /// <summary>Populate data</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateData();

  /// <summary>Populate labels</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateLabels();


public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">Symbol to wrap</param>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbItemFunction(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbItemFunction();

  /// <summary>Get name of function</summary>
  ///
  /// <returns>The name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  wstring getName();

  /// <summary>Determines if the function is a thunk</summary>
  ///
  /// <returns>true if it is a thunk</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool isThunk();

  /// <summary>Get function access</summary>
  ///
  /// <returns>One of the CV_access_e enumeration</returns>
  ///
  /// <exception c_ref="runtime_error">If the function is a thunk</exception>
  ///
  CV_access_e getAccess();

  /// <summary>Determines if the function is virtual</summary>
  ///
  /// <returns>true if it is</returns>
  ///
  /// <exception c_ref="runtime_error">If the function is a thunk</exception>
  ///
  bool isVirtual();

  /// <summary>Determines if the function is pure virtual</summary>
  ///
  /// <returns>true if it is</returns>
  ///
  /// <exception c_ref="runtime_error">If the function is a thunk</exception>
  ///
  bool isPureVirtual();

  /// <summary>Determines if the function is introducing a virtual for 
  /// the first time</summary>
  ///
  /// <returns>true if it is</returns>
  ///
  /// <exception c_ref="runtime_error">If the function is a thunk</exception>
  ///
  bool isIntroVirtual();

  /// <summary>Get function location</summary>
  ///
  /// <returns>Either static or metadata from LocationType enumeration. 
  /// Thunks can only be static</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  LocationType getLocation();

  /// <summary>Get size of function/thunk in bytes</summary>
  ///
  /// <returns>Size in bytes</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned __int64 getSizeBytes();

  /// <summary>Gets the metadata token if the function's location is 
  /// metadata</summary>
  ///
  /// <returns>The token</returns>
  ///
  /// <exception c_ref="runtime_error">If the function is a thunk</exception>
  ///
  unsigned long getMetadataToken();

  /// <summary>Gets the RVA if the function's location is static</summary>
  ///
  /// <returns>The RVA</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getRVA();

  /// <summary>Gets the type of a thunk</summary>
  ///
  /// <returns>One of the THUNK_ORDINAL enumeration</returns>
  ///
  /// <exception c_ref="runtime_error">If the function is NOT a thunk</exception>
  ///
  THUNK_ORDINAL getThunkType();
    
  /// <summary>Gets the function type</summary>
  ///
  /// <returns>The function type signature. WARNING: It is legal for
  /// this call to return NULL. In this case, the function has no type
  /// information available.</returns>
  ///
  /// <exception c_ref="runtime_error">If the function is a thunk</exception>
  ///
  PdbTypeFunction* getFunctionType();

  /// <summary>Determines if the function has a parent UDT</summary>
  ///
  /// <returns>true if it does</returns>
  ///
  /// <exception c_ref="runtime_error">If the function is a thunk</exception>
  ///
  bool hasParentUDT();

  /// <summary>Gets the UDT this function is a member of</summary>
  ///
  /// <returns>The UDT</returns>
  ///
  /// <exception c_ref="runtime_error">If there is no enclosing UDT</exception>
  ///
  PdbTypeUDT* getParentUDT();

  /// <summary>Gets the virtual base offset for a function</summary>
  ///
  /// <returns>The virtual base offset</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getVirtualBaseOffset();

  /// <summary>Get parameters to the function</summary>
  ///
  /// <returns>Vector of parameters</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemData*> getParameters();

  /// <summary>Get locals of the function</summary>
  ///
  /// <returns>Vector of locals</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemData*> getLocals();

  /// <summary>Get static locals of the function</summary>
  ///
  /// <returns>Vector of static locals</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemData*> getStaticLocals();

  /// <summary>Get object pointer of the function</summary>
  ///
  /// <returns>Object pointer. NULL if there IS no object pointer</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbItemData* getObjectPointer();

  /// <summary>Get constants of the function</summary>
  ///
  /// <returns>Vector of constants</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemData*> getConstants();

  /// <summary>Get labels of the function</summary>
  ///
  /// <returns>Vector of labels</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  vector<PdbItemLabel*> getLabels();
};



//////////////////////////////////////////////////////////////////////////
// PdbItemData


/// <remarks>Encapsulation of data</remarks>
///
class PdbItemData {
protected:
  // <value>The wrapped symbol</value>
  CComPtr<IDiaSymbol> symbol;

  // <value>does this have a parent UDT?</value>
  bool hasParentUDTFlag;

  /// <value>UDT this function is a member of</value>
  PdbTypeUDT* parentUDT;

  /// <value>Type of the data</value>
  PdbType* dataType;


  /// <summary>Populate the parent UDT</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateParentUDT();

  /// <summary>Populate the data type</summary>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  void populateDataType();

public:

  /// <summary>Constructor</summary>
  ///
  /// <param name="symbol">Symbol to wrap</symbol>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbItemData(IDiaSymbol* symbol);

  /// <summary>Destructor</summary>
  ///
  virtual ~PdbItemData();

  /// <summary>Get data access</summary>
  ///
  /// <returns>One of the CV_access_e enumeration</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  CV_access_e getAccess();

  /// <summary>Gets the RVA if the location is static</summary>
  ///
  /// <returns>The RVA</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getRVA();

  /// <summary>Gets the bitfield position if the location is bitfield</summary>
  ///
  /// <returns>The bitfield position</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getBitfieldPosition();

  /// <summary>Gets the bitfield size if the location is bitfield</summary>
  ///
  /// <returns>The bitfield size</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned __int64 getBitfieldSize();
   
  /// <summary>Determines if the data has a parent UDT or not</summary>
  ///
  /// <returns>true if it does</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  bool hasParentUDT();

  /// <summary>Gets the UDT this data is a member of</summary>
  ///
  /// <returns>The UDT</returns>
  ///
  /// <exception c_ref="runtime_error">If there is no enclosing UDT</exception>
  ///
  PdbTypeUDT* getParentUDT();

  /// <summary>Gets the data kind</summary>
  ///
  /// <returns>One of the DataKind enumeration</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  DataKind getDataKind();

  /// <summary>Gets the data location</summary>
  ///
  /// <returns>One of the LocationType enumeration</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  LocationType getLocation();

  /// <summary>Gets the name of the data</summary>
  ///
  /// <returns>The name</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  wstring getName();

  /// <summary>Gets the register data is stored in (only if the data has 
  /// enregistered location type)</summary>
  ///
  /// <returns>One of the CV_HREG_e enumeration</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  /// 
  CV_HREG_e getRegister();

  /// <summary>Gets the offset of the data</summary>
  ///
  /// <returns>Offset</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  /// 
  long getOffset();

  /// <summary>Gets the value of the data (only if the data has constant 
  /// location type) </summary>
  ///
  /// <returns>One of the CV_HREG_e enumeration</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  /// 
  VARIANT getValue();

  /// <summary>Gets the slot of the data (Only for LocIsSlot)</summary>
  ///
  /// <returns>The slot</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getSlot();

  /// <summary>Gets the metadata token of the data (Only for LocInMetaData)</summary>
  ///
  /// <returns>The token</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  unsigned long getToken();

  /// <summary>Gets the type of the data</summary>
  ///
  /// <returns>The data type</returns>
  ///
  /// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
  ///
  PdbType* getType();
};


#endif

