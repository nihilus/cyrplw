/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of PdbTypeArray                                       */
/************************************************************************/

#include "pdbtypes.h"
#include "pdbutils.h"
#include "_pdbint.h"


/// <summary>Constructor</summary>
/// 
/// <param name="symbol">IDiaSymbol to wrap. Symbol must be of type SymTagArrayType</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbTypeArray::PdbTypeArray(IDiaSymbol* symbol) {
  CHECKTAG(symbol, SymTagArrayType, "PdbTypeArray");

  // remember the symbol
  this->symbol = symbol;
  arrayPopulated = false;
  elementType = NULL;
}


/// <summary>Populates the array structure with data</summary>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
void PdbTypeArray::populateArray() {
  // Get total size of top array symbol
  CComPtr<IDiaSymbol> curPdbTypeArrayIndex = symbol;
  unsigned __int64 arraySize;
  if (FAILED(curPdbTypeArrayIndex->get_length(&arraySize))) {
    throwError();
  }

  // We know we're in an array already
  DWORD curPdbTypeArrayIndexTag = SymTagArrayType;

  // get index type of top array index
  CComPtr<IDiaSymbol> curIndexType;
  if (FAILED(curPdbTypeArrayIndex->get_arrayIndexType(&curIndexType))) {
    throwError();
  }

  // Get type of top array indexes elements
  CComPtr<IDiaSymbol> diaElementType;
  if (FAILED(curPdbTypeArrayIndex->get_type(&diaElementType))) {
    throwError();
  }

  // Get size of of top array indexes elements
  unsigned __int64 curElementSize;
  if (FAILED(diaElementType->get_length(&curElementSize))) {
    throwError();
  }

  // Now, process the indices 
  while(curPdbTypeArrayIndexTag == SymTagArrayType) {
    // Add on a new array index for current index
    if (curElementSize != 0) {
      arrayIndices.insert(arrayIndices.end(), 
        PdbTypeArrayIndex(new PdbTypeBasic(curIndexType), arraySize / curElementSize));
    } else {
      arrayIndices.insert(arrayIndices.end(), 
        PdbTypeArrayIndex(new PdbTypeBasic(curIndexType), 0));
    }

    // See if there are any fortran Dimension elements, and moan if there are
    // I don't know Fortran, so I've no idea what these are, or how to support 'em
    CComPtr<IDiaEnumSymbols> dimensionEnum;
    if (SUCCEEDED(curPdbTypeArrayIndex->findChildren(SymTagDimension, NULL, nsNone, &dimensionEnum))) {
      long count = 0;
      if (SUCCEEDED(dimensionEnum->get_Count(&count))) {
        if (count) {
          throw runtime_error("Unsupported Fortran Dimension symbols detected");
        }
      }
    }
    DWORD rank = 0;
    if (SUCCEEDED(curPdbTypeArrayIndex->get_rank(&rank))) {
      if (rank) {
        throw runtime_error("Unsupported Fortran array rank detected");
      }
    }

    // Move down to next array index 
    curPdbTypeArrayIndex.Release();
    curPdbTypeArrayIndex = diaElementType;

    // Size of new array index
    arraySize = curElementSize;

    // get symtag of new array index
    if (FAILED(curPdbTypeArrayIndex->get_symTag(&curPdbTypeArrayIndexTag))) {
      throwError();
    }

    // if it ISNT an array, stop right now
    if (curPdbTypeArrayIndexTag != SymTagArrayType) {
      break;
    }

    // get index type of sub-array 
    curIndexType.Release();
    if (FAILED(curPdbTypeArrayIndex->get_arrayIndexType(&curIndexType))) {
      throwError();
    }

    // Get type of sub-array elements
    diaElementType.Release();
    if (FAILED(curPdbTypeArrayIndex->get_type(&diaElementType))) {
      throwError();
    }

    // get size in bytes of sub-array elements
    if (FAILED(diaElementType->get_length(&curElementSize))) {
      throwError();
    }
  }

  // make up element type
  elementType = pdbTypeMake(diaElementType);
}


/// <summary>Destructor</summary>
///
PdbTypeArray::~PdbTypeArray() {
  for(unsigned int i=0; i< arrayIndices.size(); i++) {
    PdbType* curType = arrayIndices[i].first;
    delete curType;
  }
  if (elementType != NULL) {
    delete elementType;
  }
}


/// <summary>Gets the array element type</summary>
///
/// <returns>PdbType structure describing the array element type.</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbType* PdbTypeArray::getElementType() {
  if (!arrayPopulated) {
    populateArray();
    arrayPopulated = true;
  }
  return elementType;  
}


/// <summary>Get a vector of the array indices</summary>
///
/// <returns>Vector containing all array indices</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
vector<PdbTypeArrayIndex> PdbTypeArray::getArrayIndices() {
  if (!arrayPopulated) {
    populateArray();
    arrayPopulated = true;
  }
  return arrayIndices;
}

