/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbUtils                                           */
/************************************************************************/

#include "pdbutils.h"
#include "pdbtypes.h"
#include "_pdbint.h"
#include "dia_dll_name.h"


/// <summary>Open a PDB file</summary>
///
/// <param name="filename">Filename of PDB file</param>
/// <param name="diaDataSource">Where to put the IDiaDataSource object</param>
/// <param name="diaSession">Where to put the IDiaSession object</param>
/// <param name="globalScope">Where to put the global scope object</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void openPdbFile(wstring filename, 
                 IDiaDataSource** diaDataSource, IDiaSession** diaSession, 
                 IDiaSymbol** globalScope) {
  // get an instance of a DiaDataSource
  if (FAILED(NoRegCoCreate(DIA_DLL_NAME, _uuidof(DiaSourceAlt), 
                           _uuidof(IDiaDataSource), 
                           (void **) diaDataSource))) {
    throwError();
  }

  if ( !*diaDataSource )
  {
    throwError();
  }
  // Load the PDB file
  if (FAILED((*diaDataSource)->loadDataFromPdb(filename.c_str()))) {
    throwError();
  }

  // Open a session
  if (FAILED((*diaDataSource)->openSession(diaSession))) {
    throwError();
  }

  // Get the global scope
  if (FAILED((*diaSession)->get_globalScope(globalScope))) {
    throwError();
  }
}


/// <summary>Wrap an IDiaSymbol in a suitable PdbType</summary>
///
/// <param name="symbol">IDiaSymbol to wrap</param>
///
/// <returns>Appropriate PdbType</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbType* pdbTypeMake(IDiaSymbol* symbol) {
  // get the tag of the symbol
  DWORD symTag;
  if ( NULL == symbol )
   throwError();
  if (FAILED(symbol->get_symTag(&symTag))) {
    throwError();
  }

  // Deal with tag appropriately
  switch(symTag) {
  case SymTagBaseType:
    return (PdbType*) new PdbTypeBasic(symbol);

  case SymTagPointerType: {
    // get whether it is a reference or not
    BOOL isReference;
    if (FAILED(symbol->get_reference(&isReference))) {
      throwError();
    }
    
    // Create types appropriately
    if (isReference) {
      return (PdbType*) new PdbTypeReference(symbol);
    } else {
      return (PdbType*) new PdbTypePointer(symbol);
    }
  }
      
  case SymTagArrayType:
    return (PdbType*) new PdbTypeArray(symbol);

  case SymTagManagedType:
    return (PdbType*) new PdbTypeManaged(symbol);

  case SymTagCustomType:
    return (PdbType*) new PdbTypeCustom(symbol);

  case SymTagEnum:
    return (PdbType*) new PdbTypeEnumeration(symbol);

  case SymTagTypedef:
    return (PdbType*) new PdbTypeTypedef(symbol);

  case SymTagFunctionType:
    return (PdbType*) new PdbTypeFunction(symbol);

  case SymTagUDT: {
    // get the udtKind
    DWORD udtKind;
    if (FAILED(symbol->get_udtKind(&udtKind))) {
      throwError();
    }
    
    // Create types appropriately
    switch(udtKind) {
    case UdtStruct: 
      return (PdbType*) new PdbTypeStruct(symbol);

    case UdtClass:
      return (PdbType*) new PdbTypeClass(symbol);

    case UdtUnion:
      return (PdbType*) new PdbTypeUnion(symbol);

    default:
      throw runtime_error("Unknown UdtKind");
    }
  }

  default:
    throw runtime_error("Unknown symtag");
  }
}
