/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of main entry point                                   */
/************************************************************************/

#include <dia2.h>
#include <dialib.h>
#include "utils.h"
#include "PdbRender.h"


/// <summary>Entry point</summary>
///
int main(int argc, char* argv[]) 
{
  int do_rpd = 0;
  if ( argc > 2 && argv[1][0] == '-' && argv[1][1] == 'r' && !argv[1][2] )
  {
    do_rpd++;
    argc--;
    argv++;
  }
  // Process args
  if (argc != 2) {
    fprintf(stderr, "Syntax: pdbdump <PDB filename>\n");
    return(1);
  }

  // Convert filename
  wchar_t pdbFilename[256];
  mbstowcs(pdbFilename, argv[1], 256);
  class CPdb *rpdb = NULL;
  if ( do_rpd )
    rpdb = new CPdb;

  try {
    // open the pdb file
    CComPtr<IDiaDataSource> diaDataSource;
    CComPtr<IDiaSession> diaSession;
    CComPtr<IDiaSymbol> globalScope;
    openPdbFile(pdbFilename, &diaDataSource, &diaSession, &globalScope);

    // dump typedefs
    wprintf(L"\n//////////////////////////////////////////////////////////////////////////\n");
    wprintf(L"Typedefs\n\n");
    renderTypedefs(stdout, globalScope);

    // dump enumerations at the global scope
    wprintf(L"\n//////////////////////////////////////////////////////////////////////////\n");
    wprintf(L"Enumerations\n\n");
    renderEnumerations(stdout, globalScope);

    // dump constants at the global scope
    wprintf(L"\n//////////////////////////////////////////////////////////////////////////\n");
    wprintf(L"Constants\n\n");
    renderConstants(stdout, globalScope);

    // dump structs at the global scope
    wprintf(L"\n//////////////////////////////////////////////////////////////////////////\n");
    wprintf(L"Structs\n\n");
    renderStructs(stdout, globalScope, rpdb);

    // dump classes at the global scope
    wprintf(L"\n//////////////////////////////////////////////////////////////////////////\n");
    wprintf(L"Classes\n\n");
    renderClasses(stdout, globalScope, rpdb);

    // dump unions at the global scope
    wprintf(L"\n//////////////////////////////////////////////////////////////////////////\n");
    wprintf(L"Unions\n\n");
    renderUnions(stdout, globalScope, rpdb);

    // dump functions at the global scope
    wprintf(L"\n//////////////////////////////////////////////////////////////////////////\n");
    wprintf(L"Functions\n\n");
    renderFunctions(stdout, globalScope);

    // dump globals and statics at the global scope
    wprintf(L"\n//////////////////////////////////////////////////////////////////////////\n");
    wprintf(L"Globals/Statics\n\n");
    renderStaticAndGlobalData(stdout, globalScope);

    // dump public symbols at the global scope
    wprintf(L"\n//////////////////////////////////////////////////////////////////////////\n");
    wprintf(L"Public symbols\n\n");
    renderPublicSymbols(stdout, globalScope);

  } catch (runtime_error& e) {
    // deal with exception
    if ( rpdb )
      delete rpdb;
    fprintf(stderr, "ERROR: ");
    fprintf(stderr, e.what());
    fprintf(stderr, "\n");
    exit(1);
  }
  if ( rpdb )
  {
    FILE *out = fopen("out.rpd", "wb");
    if ( out != NULL )
    {
       rpdb->write(out);
       fclose(out);
    }
    delete rpdb;
  }
  // All was OK
  return(0);
}

