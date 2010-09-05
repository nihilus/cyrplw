/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Rendering functions                                                  */
/************************************************************************/

#ifndef PDBRENDER_H
#define PDBRENDER_H

#include <dia2.h>
#include <dialib.h>
#include "hierarchy.h"


//////////////////////////////////////////////////////////////////////////
// Group rendering functions


/// <summary>Render typedefs from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderTypedefs(FILE* outStream, IDiaSymbol* scope);


/// <summary>Render structs from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderStructs(FILE* outStream, IDiaSymbol* scope, CPdb *rpdb);


/// <summary>Render classes from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderClasses(FILE* outStream, IDiaSymbol* scope, CPdb *rpdb);


/// <summary>Render unions from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderUnions(FILE* outStream, IDiaSymbol* scope, CPdb *rpdb);


/// <summary>Render functions from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderFunctions(FILE* outStream, IDiaSymbol* scope);


/// <summary>Render enumerations from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderEnumerations(FILE* outStream, IDiaSymbol* scope);


/// <summary>Render static and global data from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderStaticAndGlobalData(FILE* outStream, IDiaSymbol* scope);


/// <summary>Render constants from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderConstants(FILE* outStream, IDiaSymbol* scope);


/// <summary>Render public symbols from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderPublicSymbols(FILE* outStream, IDiaSymbol* scope);


//////////////////////////////////////////////////////////////////////////
// Item-specific calls

/// <summary>Render a specific enumeration</summary>
/// 
/// <param name="curEnum">Enumeration to render</param>
///
/// <returns>Rendered enumeration</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderEnumeration(PdbTypeEnumeration* curEnum);


/// <summary>Render a specific function</summary>
/// 
/// <param name="curFunc">Function to render</param>
///
/// <returns>Rendered function</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderFunction(PdbItemFunction* curFunc, bool for_rpd = false);


/// <summary>Render a specific data item</summary>
/// 
/// <param name="item">Data item to render</param>
///
/// <returns>Rendered data item</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderDataItem(PdbItemData* item, bool for_rpd = false);


/// <summary>Render a specific thunk</summary>
/// 
/// <param name="curThunk">Thunk to render</param>
///
/// <returns>Rendered thunk</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderThunk(PdbItemFunction* curThunk);


/// <summary>Render a specific typedef</summary>
/// 
/// <param name="curTypedef">Typedef to render</param>
///
/// <returns>Rendered typedef</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderTypedef(PdbTypeTypedef* curTypedef);


/// <summary>Render a specific public symbol</summary>
/// 
/// <param name="curItem">Public symbol to render</param>
///
/// <returns>Rendered symbol</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderPublicSymbol(PdbItemPublicSymbol* curItem);


/// <summary>Render a specific UDT</summary>
/// 
/// <param name="curUDT">UDT to render</param>
///
/// <returns>Rendered UDT</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderUDT(PdbTypeUDT* curStruct, CPdb *rpdb);


/// <summary>Render a hex offset (negative or positive)</summary>
///
/// <param name="tmp">The value to render</param>
///
/// <returns>Rendered offset</returns>
///
wstring renderHexOffset(int tmp);


/// <summary>Render a register</summary>
///
/// <param name="registerId">One of the CV_HREG_e enumeration</param>
///
/// <returns>String representing the register</returns>
///
wstring renderRegister(CV_HREG_e registerId);


/// <summary>Render the short version of a type</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="type">Type to render</param>
/// <param name="withName">Should the supplied name be included?</param>
/// <param name="dataName">Name of data item</param>
/// <param name="functionParams">Overriding list of parameters when 
/// rendering a function. (Set to NULL to extract list from function type)</param>
/// <param name="functionCC">Function calling convention string</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderTypeShort(PdbType* type, bool withName, wstring dataName,
                        vector<PdbItemData*>* functionParameters = NULL,
                        wstring functionCC = L"", bool for_rpd = false);

#endif

