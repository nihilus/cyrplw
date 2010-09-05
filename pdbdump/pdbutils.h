/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Exposed DiaLib utilities                                             */
/************************************************************************/

#ifndef PDBUTILS_H
#define PDBUTILS_H

#define WIN32_LEAN_AND_MEAN
#pragma warning ( disable : 4786 )
#include <string>
#include <dia2.h>
// #include <diacreate.h>
#include "pdbtypes.h"
using namespace std;


long __stdcall NoRegCoCreate(char const *name, REFIID g1, REFIID g2, void **lp);

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
                 IDiaSymbol** globalScope);


/// <summary>Wrap an IDiaSymbol in a suitable PdbType</summary>
///
/// <param name="symbol">IDiaSymbol to wrap</param>
///
/// <returns>Appropriate PdbType</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
PdbType* pdbTypeMake(IDiaSymbol* symbol);

#endif

