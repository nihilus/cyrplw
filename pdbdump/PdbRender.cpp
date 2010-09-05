/************************************************************************/
/* Copyright 2002 Andrew de Quincey                                     */
/* All Rights Reserved                                                  */
/*                                                                      */
/* Released under a BSD-style license. See file LICENSE.txt for info.   */
/*                                                                      */
/* Implementation of rendering functions                                */
/************************************************************************/

#include "PdbRender.h"
#include "utils.h"

//////////////////////////////////////////////////////////////////////////
// Group rendering functions


void render_IDA_type(PdbType* type, struct class_member *cm);

/// <summary>Render typedefs from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderTypedefs(FILE* outStream, IDiaSymbol* scope) {
  // get the enumeration of stuff
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(scope->findChildren(SymTagTypedef, NULL, nsNone, &itemsEnum))) {
    reportError();
  }

  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    reportError();
  }
  while(count) {
    // get current typedef & dump it
    PdbTypeTypedef curItem(diaCurItem);
    fwprintf(outStream, L"%ws\n", renderTypedef(&curItem).c_str());

    // extra space
    fwprintf(outStream, L"\n");

    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      reportError();
    }
  }
}


/// <summary>Render structs from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderStructs(FILE* outStream, IDiaSymbol* scope, CPdb *rpdb)
{
  // get the enumeration of stuff
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(scope->findChildren(SymTagUDT, NULL, nsNone, &itemsEnum))) {
    reportError();
  }

  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    reportError();
  }
  while(count) {
    // skip non-structs
    DWORD type;
    if (FAILED(diaCurItem->get_udtKind(&type))) {
      reportError();
    }
    if (type == UdtStruct) {
      // get current struct & dump it
      PdbTypeStruct curItem(diaCurItem);
      fwprintf(outStream, renderUDT(&curItem, rpdb).c_str());
      fwprintf(outStream, L"\n");

      // output size
      fwprintf(outStream, L"// <size 0x%x>\n", curItem.getSizeBytes());

      // extra space
      fwprintf(outStream, L"\n");
    }

    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      reportError();
    }
  }
}


/// <summary>Render classes from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderClasses(FILE* outStream, IDiaSymbol* scope, CPdb *rpdb) 
{
  // get the enumeration of stuff
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(scope->findChildren(SymTagUDT, NULL, nsNone, &itemsEnum))) {
    reportError();
  }

  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    reportError();
  }
  while(count) {
    // skip non-structs
    DWORD type;
    if (FAILED(diaCurItem->get_udtKind(&type))) {
      reportError();
    }
    if (type == UdtClass) {
      // get current struct & dump it
      PdbTypeClass curItem(diaCurItem);
      fwprintf(outStream, renderUDT(&curItem, rpdb).c_str());
      fwprintf(outStream, L"\n");

      // output size
      fwprintf(outStream, L"// <size 0x%x>\n", curItem.getSizeBytes());

      // extra space
      fwprintf(outStream, L"\n");    
    }

    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      reportError();
    }
  }
}


/// <summary>Render unions from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderUnions(FILE* outStream, IDiaSymbol* scope, CPdb *rpdb) 
{
  // get the enumeration of stuff
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(scope->findChildren(SymTagUDT, NULL, nsNone, &itemsEnum))) {
    reportError();
  }

  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    reportError();
  }
  while(count) {
    // skip non-unions
    DWORD type;
    if (FAILED(diaCurItem->get_udtKind(&type))) {
      reportError();
    }
    if (type == UdtUnion) {
      // get current union & dump it
      PdbTypeUnion curItem(diaCurItem);
      fwprintf(outStream, renderUDT(&curItem, rpdb).c_str());
      fwprintf(outStream, L"\n");

      // output size
      fwprintf(outStream, L"// <size 0x%x>\n", curItem.getSizeBytes());

      // extra space
      fwprintf(outStream, L"\n");
    }

    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      reportError();
    }
  }
}


/// <summary>Render functions from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderFunctions(FILE* outStream, IDiaSymbol* scope) {
  // get the enumeration of stuff
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(scope->findChildren(SymTagFunction, NULL, nsNone, &itemsEnum))) {
    reportError();
  }
  
  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    reportError();
  }
  unsigned int i;
  while(count) {
    // get current function & dump it
    PdbItemFunction curItem(diaCurItem);
    
    // different call for thunks or functions
    if (!curItem.isThunk()) {
      // render initial function data
      fwprintf(outStream, L"%ws;\n", renderFunction(&curItem).c_str());
      
      // output location
      switch(curItem.getLocation()) {
      case LocIsStatic:
        fwprintf(outStream, L"// <rva 0x%x>\n", curItem.getRVA());
        break;

      case LocInMetaData:
        fwprintf(outStream, L"// <metatoken 0x%x>\n", curItem.getMetadataToken());
        break;
      }

      // output size
      fwprintf(outStream, L"// <size 0x%x>\n", curItem.getSizeBytes());

      // output object pointer
      if (curItem.getObjectPointer() != NULL) {
        // get it
        PdbItemData* objectPointer = curItem.getObjectPointer();

        // render it
        fwprintf(outStream, L"// <objectptr %ws>\n", 
                 renderDataItem(objectPointer).c_str());
      }

      // output labels
      vector<PdbItemLabel*> labels = curItem.getLabels();
      for(i=0; i< labels.size(); i++) {
        fwprintf(outStream, L"// <label %ws: RVA:0x%x>\n", 
                 labels[i]->getName().c_str(),
                 labels[i]->getRVA());
      }

      // constants
      vector<PdbItemData*> data = curItem.getConstants();
      for(i=0; i< data.size(); i++) {
        fwprintf(outStream, L"// <constant %ws>\n", renderDataItem(data[i]).c_str());
      }

      // static locals
      data = curItem.getStaticLocals();
      for(i=0; i< data.size(); i++) {
        fwprintf(outStream, L"// <staticlocal %ws>\n", renderDataItem(data[i]).c_str());
      }

      // locals
      data = curItem.getLocals();
      for(i=0; i< data.size(); i++) {
        fwprintf(outStream, L"// <local %ws>\n", renderDataItem(data[i]).c_str());
      }
    } else {
      // render it as a thunk
      fwprintf(outStream, L"thunk %ws\n", renderThunk(&curItem).c_str());
      fwprintf(outStream, L"// <rva: 0x%x>\n", curItem.getRVA());
      fwprintf(outStream, L"// <size: 0x%x>\n", curItem.getSizeBytes());
    }

    // extra space
    fwprintf(outStream, L"\n");

    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      reportError();
    }
  }
}


/// <summary>Render static and global data from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderStaticAndGlobalData(FILE* outStream, IDiaSymbol* scope) {
  // get the enumeration of stuff
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(scope->findChildren(SymTagData, NULL, nsNone, &itemsEnum))) {
    reportError();
  }
  
  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    reportError();
  }
  while(count) {
    // encapsulate data item
    PdbItemData curItem(diaCurItem);

    // check the data kind (skip constants and static locals)
    DataKind dataKind = curItem.getDataKind();
    if ((dataKind != DataIsConstant) &&
        (dataKind != DataIsStaticLocal)) {
      switch(dataKind) {
      case DataIsFileStatic:
        fwprintf(outStream, L"filestatic");
        break;

      case DataIsGlobal:
        fwprintf(outStream, L"global");
        break;

      default: // other data kinds are handled elsewhere
        throw runtime_error("Unexpected data kind");
      }
      
      // output stuff    
      fwprintf(outStream, L" %ws\n", renderDataItem(&curItem).c_str());

      // extra space
      fwprintf(outStream, L"\n");  
    }

    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      reportError();
    }
  }
}


/// <summary>Render constants from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderConstants(FILE* outStream, IDiaSymbol* scope) {
  // get the enumeration of stuff
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(scope->findChildren(SymTagData, NULL, nsNone, &itemsEnum))) {
    reportError();
  }
  
  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    reportError();
  }
  while(count) {
    // encapsulate data item
    PdbItemData curItem(diaCurItem);

    // check the data kind
    DataKind dataKind = curItem.getDataKind();
    if (dataKind == DataIsConstant) {
      fwprintf(outStream, L"const");
      fwprintf(outStream, L" %ws\n", renderDataItem(&curItem).c_str());
      fwprintf(outStream, L";\n");  
    }

    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      reportError();
    }
  }
}


/// <summary>Render enumerations from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderEnumerations(FILE* outStream, IDiaSymbol* scope) {
  // get the enumeration of stuff
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(scope->findChildren(SymTagEnum, NULL, nsNone, &itemsEnum))) {
    reportError();
  }

  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    reportError();
  }
  while(count) {
    // get current enumeration & dump it
    PdbTypeEnumeration curItem(diaCurItem);
    fwprintf(outStream, L"%ws\n", renderEnumeration(&curItem).c_str());

    // extra space
    fwprintf(outStream, L"\n");
    
    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      reportError();
    }
  }
}


/// <summary>Render public symbols from a scope</summary>
/// 
/// <param name="outStream">Stream to output to</param>
/// <param name="scope">DiaSymbol to render from</param>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
void renderPublicSymbols(FILE* outStream, IDiaSymbol* scope) {
  // get the enumeration of stuff
  CComPtr<IDiaEnumSymbols> itemsEnum;
  if (FAILED(scope->findChildren(SymTagPublicSymbol, NULL, nsNone, &itemsEnum))) {
    reportError();
  }

  // enumerate over them
  ULONG count = 0;
  CComPtr<IDiaSymbol> diaCurItem;
  if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
    reportError();
  }
  while(count) {
    // get current public symbol & dump it
    PdbItemPublicSymbol curItem(diaCurItem);
    fwprintf(outStream, L"%ws\n", renderPublicSymbol(&curItem).c_str());

    // extra space
    fwprintf(outStream, L"\n");

    // next 
    diaCurItem.Release();
    if (FAILED(itemsEnum->Next(1, &diaCurItem, &count))) {
      reportError();
    }
  }
}



//////////////////////////////////////////////////////////////////////////
// Item-specific rendering functions


/// <summary>Render a specific enumeration</summary>
/// 
/// <param name="curEnum">Enumeration to render</param>
///
/// <returns>Rendered enumeration</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderEnumeration(PdbTypeEnumeration* curEnum) {
  wstring result;

  // print header
  result.append(L"enum ");
  result.append(curEnum->getName());
  result.append(L" {\n");

  // output the items
  vector<PdbTypeEnumerationValue> items = curEnum->getValues();
  for(unsigned int i=0; i< items.size(); i++) {
    wchar_t buf[256];

    // print it
    result.append(L"  ");
    result.append(items[i].first.c_str());
    result.append(L" = 0x");
    wsprintfW(buf, L"%x", items[i].second);
    result.append(buf);
    result.append(L",\n");
  }

  // render trailer
  result.append(L"};");

  // return it
  return result;
}


/// <summary>Render a specific function</summary>
/// 
/// <param name="curFunc">Function to render</param>
///
/// <returns>Rendered function</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderFunction(PdbItemFunction* curFunc, bool for_rpd) 
{
  vector<PdbItemData*> data;
  wstring result;
  
  // get the function's type
  PdbTypeFunction* type = curFunc->getFunctionType();

  // check for functions with no type info
  wstring functionDetails;
  if (type == NULL) {
    // output initial function stuff
    functionDetails.append(L"/*?*/ ");
    functionDetails.append(curFunc->getName());
    functionDetails.append(L"(");

    // output args
    vector<PdbItemData*> functionParameters = curFunc->getParameters();
    for(unsigned int i=0; i< functionParameters.size(); i++) {
      // append the current arg
      functionDetails.append(renderTypeShort(functionParameters[i]->getType(), 
                                             true, 
                                             functionParameters[i]->getName(), NULL, L"", for_rpd));

      // add on the separating comma
      if (i < (functionParameters.size() - 1)) {
        functionDetails.append(L", ");
      }
    }

    // if there were no args, warn the user that no type info was available
    if (functionParameters.size() == 0) {
      functionDetails.append(L"/*?*/");
    }

    // finish off the function name
    functionDetails.append(L")");
  } else {
    // work out the calling convention
    wstring callingConvention;
    CV_call_e ca_c = dynamic_cast<PdbTypeFunction*>(type)->getCallingConvention();
    switch(ca_c) {
/*    case 0xd4:
    case 0x4c:
    case 0x6d: 
    case 0x16: */
    case CV_CALL_FAR_C:
    case CV_CALL_NEAR_C:
      callingConvention = L"__cdecl";
      break;

    case CV_CALL_NEAR_PASCAL:
    case CV_CALL_FAR_PASCAL:
      callingConvention = L"__pascal";
      break;

    case CV_CALL_FAR_FAST:
    case CV_CALL_NEAR_FAST:
      callingConvention = L"__fastcall";
      break;

    case CV_CALL_FAR_STD:
    case CV_CALL_NEAR_STD:
      callingConvention = L"__stdcall";
      break;
      
    case CV_CALL_FAR_SYS:
    case CV_CALL_NEAR_SYS:
      callingConvention = L"__syscall";
      break;

    case CV_CALL_THISCALL:
      callingConvention = L"__thiscall";
      break;

    case CV_CALL_CLRCALL:
      callingConvention = L"__clrcall";
      break;

    default:
	fprintf(stderr, "Unknown calling convention %d\n", ca_c);
//      throw runtime_error("Unknown calling convention in function");
    }

    // render... 
    functionDetails = renderTypeShort(type, 
                                      true, 
                                      curFunc->getName(),
                                      &(curFunc->getParameters()),
                                      callingConvention, for_rpd);
  }
  
  // output function details
  result.append(functionDetails);
  return result;
}


/// <summary>Render a specific data item</summary>
/// 
/// <param name="item">Data item to render</param>
///
/// <returns>Rendered data item</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderDataItem(PdbItemData* item, bool for_rpd) {
  wstring result;
  wchar_t buf[256];

  buf[0] = 0;
  // deal with data item
  wstring beforeType;
  wstring afterType;
  switch(item->getLocation()) {
  case LocIsStatic:
    wsprintfW(buf, L"/*<rva 0x%x>*/", item->getRVA()); 
    beforeType = buf;
    break;

  case LocIsTLS:
    wsprintfW(buf, L"/*<tls 0x%x>*/", item->getRVA()); 
    beforeType = buf;
    break;

  case LocIsRegRel:
    if ( !for_rpd )
    {
     wsprintfW(buf, L"/*<regrel %ws%ws>*/", 
              renderRegister(item->getRegister()).c_str(),
              renderHexOffset(item->getOffset()).c_str());
     beforeType = buf;
    }
    break;

  case LocIsThisRel:
    wsprintfW(buf, L"/*<thisrel this%ws>*/",
              renderHexOffset(item->getOffset()).c_str());
    beforeType = buf;
    break;

  case LocIsEnregistered:
    wsprintfW(buf, L"/*<register %ws>*/", 
              renderRegister(item->getRegister()).c_str());
    beforeType = buf;
    break;

  case LocIsBitField:
    wsprintfW(buf, L"/*<bitfield this%ws>*/",
              renderHexOffset(item->getOffset()).c_str());
    beforeType = buf;
    wsprintfW(buf, L":%x:%x",
              item->getBitfieldPosition(),
              item->getBitfieldSize());
    afterType = buf;
    break;

  case LocIsSlot:
    wsprintfW(buf, L"/*<slot 0x%x>*/", item->getSlot()); 
    beforeType = buf;
    break;

  case LocIsIlRel:
    wsprintfW(buf, L"/*<ilrel %ws>*/", 
              renderHexOffset(item->getOffset()).c_str());
    beforeType = buf;
    break;

  case LocInMetaData:
    wsprintfW(buf, L"/*<metatoken 0x%x>*/", item->getToken()); 
    beforeType = buf;
    break;

  case LocIsConstant: {
    // get the value
    VARIANT value = item->getValue();
    
    // extract the value
    unsigned long valueL;
    switch(value.vt) {
    case VT_UI1: valueL = value.bVal; break;
    case VT_UI2: valueL = value.uiVal; break;
    case VT_UI4: valueL = value.ulVal; break;
    case VT_UINT: valueL = value.uintVal; break;
    case VT_INT: valueL = value.intVal; break;
    case VT_I1: valueL = value.cVal; break;
    case VT_I2: valueL = value.iVal; break;
    case VT_I4: valueL = value.lVal; break;
    default:
      throw runtime_error("Non-integer constant detected");
    }
    
    // make up string
    wsprintfW(buf, L" = 0x%x", valueL);
    afterType = buf;
    break;
  }

  default:
    throw runtime_error("Unexpected data location");
  }

  // calculate the size of the item
  if ( !for_rpd )
  {
    PdbType *type = item->getType();
	if ( NULL != type )
     wsprintfW(buf, L"/*|0x%x|*/", type->getSizeBytes());
	else
	 wsprintfW(buf, L"/*|ZERO TYPE|*/");
  }
  wstring itemSize = buf;

  // add on the type and name
  result.append(beforeType);
  if (beforeType.size() > 0) result.append(L" ");
  result.append(itemSize);
  result.append(L" ");
  result.append(renderTypeShort(item->getType(), true, item->getName()));
  result.append(afterType);

  // return it
  return result;
}


/// <summary>Render a specific thunk</summary>
/// 
/// <param name="curThunk">Thunk to render</param>
///
/// <returns>Rendered thunk</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderThunk(PdbItemFunction* curThunk) {
  wstring result; 

  // work out the type of thunk
  wstring thunkType;
  switch(curThunk->getThunkType()) {
  case THUNK_ORDINAL_NOTYPE:
    thunkType = L"/*__stdthunk*/";
    break;

  case THUNK_ORDINAL_ADJUSTOR:
    thunkType = L"/*__thisadjustor*/";
    break;

  case THUNK_ORDINAL_VCALL:
    thunkType = L"/*__virtualcall*/";
    break;

  case THUNK_ORDINAL_PCODE:
    thunkType = L"/*__pcode*/";
    break;

  case THUNK_ORDINAL_LOAD:
    thunkType = L"/*__delayload*/";
    break;

  default:
    throw runtime_error("Unknown thunk type");
  }

  // render it. N.B. Thunks always have static locations
  result.append(thunkType);
  result.append(L" ");
  result.append(curThunk->getName());

  // return results
  return result;
}


/// <summary>Render a specific typedef</summary>
/// 
/// <param name="curTypedef">Typedef to render</param>
///
/// <returns>Rendered typedef</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderTypedef(PdbTypeTypedef* curTypedef) {
  wstring result;

  // render it
  result.append(L"typedef ");
  result.append(renderTypeShort(curTypedef->getSubType(), true, curTypedef->getName()));
  result.append(L";");

  // return it
  return result;
}


/// <summary>Render a specific public symbol</summary>
/// 
/// <param name="curItem">Public symbol to render</param>
///
/// <returns>Rendered symbol</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderPublicSymbol(PdbItemPublicSymbol* curItem) {
  wstring result;

  // header 
  result.append(L"// pubsym ");

  // add on the RVA
  wchar_t buf[100];
  wsprintfW(buf, L"<rva 0x%x>", curItem->getRVA());
  result.append(buf);

  // add on additional flags
  if (curItem->isInCode()) {
    result.append(L" <code>");
  }
  if (curItem->isInManagedCode()) {
    result.append(L" <managed>");
  }
  if (curItem->isInMSIL()) {
    result.append(L" <msil>");
  }
  result.append(L" ");

  // add on the name
  result.append(curItem->getName());

  // return it
  return result;
}


/// <summary>Render a specific UDT</summary>
/// 
/// <param name="curUDT">UDT to render</param>
///
/// <returns>Rendered UDT</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderUDT(PdbTypeUDT* curUDT, CPdb *rpdb) 
{
  wstring result;
  wchar_t buf[256];

  // get needed data
  vector<PdbTypeUDTBaseClass*> bases = curUDT->getBaseClasses();
  vector<PdbTypeUDTFriend*> friends = curUDT->getFriends();
  vector<PdbItemData*> staticData = curUDT->getStaticData();
  vector<PdbItemData*> nonStaticData = curUDT->getNonStaticData();
  vector<PdbItemFunction*> staticFunctions = curUDT->getStaticFunctions();
  vector<PdbItemFunction*> nonVirtualFunctions = curUDT->getNonVirtualFunctions();
  vector<PdbItemFunction*> virtualFunctions = curUDT->getVirtualFunctions();

  // render header
  PdbTypeIds typeID = curUDT->getPdbTypeId();
  switch(typeID) 
  {
    case DIAID_CLASS:
      result.append(L"class ");
      break;

    case DIAID_STRUCT:
      result.append(L"struct ");
      break;

    case DIAID_UNION:
      result.append(L"union ");
      break;
  }

  // append name
  wstring my_name = curUDT->getName();
  result.append(my_name);
  struct pdb_class *pc = NULL;

  // append base classes
  unsigned int i;
  bool outputABase = false;
  vector<PdbTypeUDTBaseClass*> baseClasses = curUDT->getBaseClasses();

  int vfcount = virtualFunctions.size();
  if ( rpdb && vfcount )
  {
    pc = rpdb->add_class(ole2str((wchar_t *)my_name.c_str(), -1), typeID);
    if ( pc && pc->new_added )
     pc->size = curUDT->getSizeBytes();
  }

  for(i=0; i< baseClasses.size(); i++) 
  {
    // we're not gonna do indirect bases here
    if (!baseClasses[i]->isIndirectBaseClass()) {
      // add on a colon if necessary
      if (!outputABase) {
        result.append(L" :");
        outputABase = true;
      }

      // add on "virtual" if appropriate
      if (baseClasses[i]->isVirtual()) {
        result.append(L" ");
        result.append(L"virtual");
      }

      // add on the name
      result.append(L" ");
      
      PdbType *base_type = baseClasses[i]->getBaseClassType();
      wstring basename = renderTypeShort(base_type, false, L"");
      if ( pc && pc->new_added)
      {
        PdbType *base_type = baseClasses[i]->getBaseClassType();
        char *what_add = NULL;
        switch(base_type->getPdbTypeId())
        {
          case DIAID_CLASS:
            what_add = ole2str((wchar_t *)dynamic_cast<PdbTypeClass*>(base_type)->getName().c_str(), -1);
           break;
          case DIAID_STRUCT:
            what_add = ole2str((wchar_t *)dynamic_cast<PdbTypeStruct*>(base_type)->getName().c_str(), -1);
           break;
          case DIAID_UNION:
            what_add = ole2str((wchar_t *)dynamic_cast<PdbTypeUnion*>(base_type)->getName().c_str(), -1);
           break;
        }
        if ( rpdb && what_add )
         rpdb->add_parent(pc, what_add);
      }
      result.append(basename);
      
      // add on a comma
      result.append(L", ");
    }
  }
  
  // if we DID output some bases, knock off the last two characters
  // (the extra comma and space)
  if (outputABase) {
    result.erase(result.end() - 2);
  }

  // append trailer
  result.append(L" {\n");
  
  int sdata_count = staticData.size();
  if ( sdata_count )
  {
  // static data
   result.append(L"\n  // static data ------------------------------------\n");
   for(i=0; i< sdata_count; i++) {
    // output it
    result.append(L"  static ");
    result.append(renderDataItem(staticData[i]));
    result.append(L";\n");
   }
  }

  int nsdata_count = nonStaticData.size();
  // non-static data
  if ( nsdata_count )
  {
   result.append(L"\n  // non-static data --------------------------------\n");
   for(i=0; i< nsdata_count; i++) {
    // output it
    result.append(L"  ");
    result.append(renderDataItem(nonStaticData[i]));
    result.append(L";\n");             
    if ( pc && pc->new_added )
    {
      struct class_member *cm = pc->add_member(
       ole2str( (wchar_t *)nonStaticData[i]->getName().c_str(), -1),
       nonStaticData[i]->getOffset()
      );
      if ( cm )
      {
       cm->size = nonStaticData[i]->getType()->getSizeBytes();
       render_IDA_type(nonStaticData[i]->getType(), cm);
      }
    }
   }
  }

  // output complete base information
  result.append(L"\n  // base classes -----------------------------------\n");
  for(i=0; i< bases.size(); i++) {
    // add on the initial line stuff
    result.append(L"  // baseclass");
    if (bases[i]->isVirtual()) {
      result.append(L" virtual");
    }
    if (bases[i]->isIndirectBaseClass()) {
      result.append(L" indirect");
    }
    result.append(L" ");
    result.append(renderTypeShort(bases[i]->getBaseClassType(), false, L""));
    result.append(L"\n");

    // render base offset
    result.append(L"  // <base data offset");
    result.append(renderHexOffset(bases[i]->getOffset()));
    result.append(L">\n");

    // render additional virtual fields
    if (bases[i]->isVirtual()) {
      // render virtual base pointer offset
      result.append(L"  // <vbase pointer offset");
      result.append(renderHexOffset(bases[i]->getVirtualBasePointerOffset()));
      result.append(L">\n");

      // render base offset
      result.append(L"  // <vbase displacement index");
      result.append(renderHexOffset(bases[i]->getVirtualBaseDispIndex()));
      result.append(L">\n");
    }

    // extra spacing
    if (i < (bases.size() -1)) {
      result.append(L"\n");
    }
  }

  // output friends 
  int friends_count = friends.size();
  if ( friends_count )
  {
   result.append(L"\n  // friends ----------------------------------------\n");
   for(i=0; i< friends_count; i++) {
    // add on the initial line stuff
    result.append(L"  friend ");
    if (friends[i]->isBefriendedFunction()) {
      result.append(renderFunction(friends[i]->getBefriendedFunction()));
    } else if (friends[i]->isBefriendedUDT()) {
      result.append(renderTypeShort(friends[i]->getBefriendedUDT(), false, L""));
    } else {
      throw runtime_error("Found a friend which is neither a function or a UDT");
    }
    result.append(L";\n");
   }
  }

  // static functions
  int static_fcounts = staticFunctions.size();
  if ( static_fcounts )
  {
   result.append(L"\n  // static functions -------------------------------\n");
   for(i=0; i< static_fcounts; i++) {
    // output it
    result.append(L"  static ");
    result.append(renderFunction(staticFunctions[i]));
    result.append(L";\n");
   }
  }

  // non-virtual functions
  int nvirt_fcount = nonVirtualFunctions.size();
  if ( nvirt_fcount )
  {
   result.append(L"\n  // non-virtual functions --------------------------\n");
   for(i=0; i< nvirt_fcount; i++) {
    // output it
    result.append(L"  ");
    result.append(renderFunction(nonVirtualFunctions[i]));
    result.append(L";\n");             
   }
  }

  // virtual functions
//  int vfcount = virtualFunctions.size();
  if ( vfcount )
  {
   DWORD base_off;
   result.append(L"\n  // virtual functions ------------------------------\n");
   for(i=0; i< vfcount; i++) {
    // output it
    result.append(L"  virtual ");
    base_off = virtualFunctions[i]->getVirtualBaseOffset();
    wsprintfW(buf, L"/*<vtableoff 0x%x>*/ ", base_off);
    result.append(buf);
    wstring vname = renderFunction(virtualFunctions[i], (pc != NULL) );
    if ( /* base_off && */ pc )
    {
      struct vtbl_method *vm = pc->add_method( ole2str((wchar_t *)vname.c_str(), -1), base_off);
      if ( vm )
        vm->set_name_only( ole2str((wchar_t *)virtualFunctions[i]->getName().c_str(), -1) );

    }
    result.append(vname);
    if (virtualFunctions[i]->isPureVirtual()) {
      result.append(L" = 0");
    }
    result.append(L";\n");
   }
  }

  // trailer
  result.append(L"};");

  // return results
  return result;
}


/// <summary>Render a hex offset (negative or positive)</summary>
///
/// <param name="tmp">The value to render</param>
///
/// <returns>Rendered offset</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring renderHexOffset(int tmp) {
  wchar_t buf[30];
  if (tmp < 0) {
    wsprintfW(buf, L"-0x%x", -tmp);
  } else {
    wsprintfW(buf, L"+0x%x", tmp);
  }
  return buf;
}


/// <summary>Render a register</summary>
///
/// <param name="registerId">One of the CV_HREG_e enumeration</param>
///
/// <returns>String representing the register</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
///
wstring renderRegister(CV_HREG_e registerId) {
  switch(registerId) {
  case CV_REG_AL: return L"al";
  case CV_REG_CL: return L"cl";
  case CV_REG_DL: return L"dl";
  case CV_REG_BL: return L"bl";
  case CV_REG_AH: return L"ah";
  case CV_REG_CH: return L"ch";
  case CV_REG_DH: return L"dh";
  case CV_REG_BH: return L"bh";
  case CV_REG_AX: return L"ax";
  case CV_REG_CX: return L"cx";
  case CV_REG_DX: return L"dx";
  case CV_REG_BX: return L"bx";
  case CV_REG_SP: return L"sp";
  case CV_REG_BP: return L"bp";
  case CV_REG_SI: return L"si";
  case CV_REG_DI: return L"di";
  case CV_REG_EAX: return L"eax";
  case CV_REG_ECX: return L"ecx";
  case CV_REG_EDX: return L"edx";
  case CV_REG_EBX: return L"ebx";
  case CV_REG_ESP: return L"esp";
  case CV_REG_EBP: return L"ebp";
  case CV_REG_ESI: return L"esi";
  case CV_REG_EDI: return L"edi";
  case CV_REG_ES: return L"es";
  case CV_REG_CS: return L"cs";
  case CV_REG_SS: return L"ss";
  case CV_REG_DS: return L"ds";
  case CV_REG_FS: return L"fs";
  case CV_REG_GS: return L"gs";
  case CV_REG_IP: return L"ip";
  case CV_REG_FLAGS: return L"flags";
  case CV_REG_EIP: return L"eip";
  case CV_REG_EFLAGS: return L"eflags";
  case CV_REG_TEMP: return L"temp";            // PCODE Temp
  case CV_REG_TEMPH: return L"temph";          // PCODE TempH
  case CV_REG_QUOTE: return L"quote";          // PCODE Quote
  case CV_REG_PCDR3: return L"pcdr3";          // PCODE reserved
  case CV_REG_PCDR4: return L"pcdr4";          // PCODE reserved
  case CV_REG_PCDR5: return L"pcdr5";          // PCODE reserved
  case CV_REG_PCDR6: return L"pcdr6";          // PCODE reserved
  case CV_REG_PCDR7: return L"pcdr7";          // PCODE reserved
  case CV_REG_CR0: return L"cr0";              // CR0 -- control registers
  case CV_REG_CR1: return L"cr1";
  case CV_REG_CR2: return L"cr2";
  case CV_REG_CR3: return L"cr3";
  case CV_REG_CR4: return L"cr4";          // Pentium
  case CV_REG_DR0: return L"dr0";          // Debug register
  case CV_REG_DR1: return L"dr1";
  case CV_REG_DR2: return L"dr2";
  case CV_REG_DR3: return L"dr3";
  case CV_REG_DR4: return L"dr4";
  case CV_REG_DR5: return L"dr5";
  case CV_REG_DR6: return L"dr6";
  case CV_REG_DR7: return L"dr7";
  case CV_REG_GDTR: return L"gdtr";
  case CV_REG_GDTL: return L"gdtl";
  case CV_REG_IDTR: return L"idtr";
  case CV_REG_IDTL: return L"idtl";
  case CV_REG_LDTR: return L"ldtr";
  case CV_REG_TR: return L"tr";

  case CV_REG_PSEUDO1: return L"pseudo1";
  case CV_REG_PSEUDO2: return L"pseudo2";
  case CV_REG_PSEUDO3: return L"pseudo3";
  case CV_REG_PSEUDO4: return L"pseudo4";
  case CV_REG_PSEUDO5: return L"pseudo5";
  case CV_REG_PSEUDO6: return L"pseudo6";
  case CV_REG_PSEUDO7: return L"pseudo7";
  case CV_REG_PSEUDO8: return L"pseudo8";
  case CV_REG_PSEUDO9: return L"pseudo9";

  case CV_REG_ST0: return L"st0";
  case CV_REG_ST1: return L"st1";
  case CV_REG_ST2: return L"st2";
  case CV_REG_ST3: return L"st3";
  case CV_REG_ST4: return L"st4";
  case CV_REG_ST5: return L"st5";
  case CV_REG_ST6: return L"st6";
  case CV_REG_ST7: return L"st7";
  case CV_REG_CTRL: return L"ctrl";
  case CV_REG_STAT: return L"stat";
  case CV_REG_TAG: return L"tag";
  case CV_REG_FPIP: return L"fpip";
  case CV_REG_FPCS: return L"fpcs";
  case CV_REG_FPDO: return L"fpdo";
  case CV_REG_FPDS: return L"fpds";
  case CV_REG_ISEM: return L"isem";
  case CV_REG_FPEIP: return L"fpeip";
  case CV_REG_FPEDO: return L"fpedo";

  case CV_REG_MM0: return L"mm0";
  case CV_REG_MM1: return L"mm1";
  case CV_REG_MM2: return L"mm2";
  case CV_REG_MM3: return L"mm3";
  case CV_REG_MM4: return L"mm4";
  case CV_REG_MM5: return L"mm5";
  case CV_REG_MM6: return L"mm6";
  case CV_REG_MM7: return L"mm7";

  case CV_REG_XMM0: return L"xmm0"; // KATMAI registers
  case CV_REG_XMM1: return L"xmm1";
  case CV_REG_XMM2: return L"xmm2";
  case CV_REG_XMM3: return L"xmm3";
  case CV_REG_XMM4: return L"xmm4";
  case CV_REG_XMM5: return L"xmm5";
  case CV_REG_XMM6: return L"xmm6";
  case CV_REG_XMM7: return L"xmm7";

  case CV_REG_XMM00: return L"xmm00"; // KATMAI sub-registers
  case CV_REG_XMM01: return L"xmm01";
  case CV_REG_XMM02: return L"xmm02";
  case CV_REG_XMM03: return L"xmm03";
  case CV_REG_XMM10: return L"xmm10";
  case CV_REG_XMM11: return L"xmm11";
  case CV_REG_XMM12: return L"xmm12";
  case CV_REG_XMM13: return L"xmm13";
  case CV_REG_XMM20: return L"xmm20";
  case CV_REG_XMM21: return L"xmm21";
  case CV_REG_XMM22: return L"xmm22";
  case CV_REG_XMM23: return L"xmm23";
  case CV_REG_XMM30: return L"xmm30";
  case CV_REG_XMM31: return L"xmm31";
  case CV_REG_XMM32: return L"xmm32";
  case CV_REG_XMM33: return L"xmm33";
  case CV_REG_XMM40: return L"xmm40";
  case CV_REG_XMM41: return L"xmm41";
  case CV_REG_XMM42: return L"xmm42";
  case CV_REG_XMM43: return L"xmm43";
  case CV_REG_XMM50: return L"xmm50";
  case CV_REG_XMM51: return L"xmm51";
  case CV_REG_XMM52: return L"xmm52";
  case CV_REG_XMM53: return L"xmm53";
  case CV_REG_XMM60: return L"xmm60";
  case CV_REG_XMM61: return L"xmm61";
  case CV_REG_XMM62: return L"xmm62";
  case CV_REG_XMM63: return L"xmm63";
  case CV_REG_XMM70: return L"xmm70";
  case CV_REG_XMM71: return L"xmm71";
  case CV_REG_XMM72: return L"xmm72";
  case CV_REG_XMM73: return L"xmm73";

  case CV_REG_XMM0L: return L"xmm0l";
  case CV_REG_XMM1L: return L"xmm1l";
  case CV_REG_XMM2L: return L"xmm2l";
  case CV_REG_XMM3L: return L"xmm3l";
  case CV_REG_XMM4L: return L"xmm4l";
  case CV_REG_XMM5L: return L"xmm5l";
  case CV_REG_XMM6L: return L"xmm6l";
  case CV_REG_XMM7L: return L"xmm7l";

  case CV_REG_XMM0H: return L"xmm0h";
  case CV_REG_XMM1H: return L"xmm1h";
  case CV_REG_XMM2H: return L"xmm2h";
  case CV_REG_XMM3H: return L"xmm3h";
  case CV_REG_XMM4H: return L"xmm4h";
  case CV_REG_XMM5H: return L"xmm5h";
  case CV_REG_XMM6H: return L"xmm6h";
  case CV_REG_XMM7H: return L"xmm7h";

  case CV_REG_MXCSR: return L"mxcsr"; // XMM status register

  case CV_REG_EDXEAX: return L"edx:eax"; // EDX:EAX pair

  case CV_REG_EMM0L: return L"emm0l"; // XMM sub-registers (WNI integer)
  case CV_REG_EMM1L: return L"emm1l";
  case CV_REG_EMM2L: return L"emm2l";
  case CV_REG_EMM3L: return L"emm3l";
  case CV_REG_EMM4L: return L"emm4l";
  case CV_REG_EMM5L: return L"emm5l";
  case CV_REG_EMM6L: return L"emm6l";
  case CV_REG_EMM7L: return L"emm7l";

  case CV_REG_EMM0H: return L"emm0h";
  case CV_REG_EMM1H: return L"emm1h";
  case CV_REG_EMM2H: return L"emm2h";
  case CV_REG_EMM3H: return L"emm3h";
  case CV_REG_EMM4H: return L"emm4h";
  case CV_REG_EMM5H: return L"emm5h";
  case CV_REG_EMM6H: return L"emm6h";
  case CV_REG_EMM7H: return L"emm7h";

  // do not change the order of these regs, first one must be even too
  case CV_REG_MM00: return L"mm00";
  case CV_REG_MM01: return L"mm01";
  case CV_REG_MM10: return L"mm10";
  case CV_REG_MM11: return L"mm11";
  case CV_REG_MM20: return L"mm20";
  case CV_REG_MM21: return L"mm21";
  case CV_REG_MM30: return L"mm30";
  case CV_REG_MM31: return L"mm31";
  case CV_REG_MM40: return L"mm40";
  case CV_REG_MM41: return L"mm41";
  case CV_REG_MM50: return L"mm50";
  case CV_REG_MM51: return L"mm51";
  case CV_REG_MM60: return L"mm60";
  case CV_REG_MM61: return L"mm61";
  case CV_REG_MM70: return L"mm70";
  case CV_REG_MM71: return L"mm71";

  case CV_AMD64_RAX: return L"rax";
  case CV_AMD64_RBX: return L"rbx";
  case CV_AMD64_RCX: return L"rcx";
  case CV_AMD64_RDX: return L"rdx";
  case CV_AMD64_RSI: return L"rsi";
  case CV_AMD64_RDI: return L"rdi";
  case CV_AMD64_RBP: return L"rbp";
  case CV_AMD64_RSP: return L"rsp";

  case CV_AMD64_R8:  return L"r8";
  case CV_AMD64_R9:  return L"r9";
  case CV_AMD64_R10: return L"r10";
  case CV_AMD64_R11: return L"r11";
  case CV_AMD64_R12: return L"r12";
  case CV_AMD64_R13: return L"r13";
  case CV_AMD64_R14: return L"r14";
  case CV_AMD64_R15: return L"r15";

  case CV_AMD64_R8B:  return L"r8b";
  case CV_AMD64_R9B:  return L"r9b";
  case CV_AMD64_R10B: return L"r10b";
  case CV_AMD64_R11B: return L"r11b";
  case CV_AMD64_R12B: return L"r12b";
  case CV_AMD64_R13B: return L"r13b";
  case CV_AMD64_R14B: return L"r14b";
  case CV_AMD64_R15B: return L"r15b";

  case CV_AMD64_R8W:  return L"r8w";
  case CV_AMD64_R9W:  return L"r9w";
  case CV_AMD64_R10W: return L"r10w";
  case CV_AMD64_R11W: return L"r11w";
  case CV_AMD64_R12W: return L"r12w";
  case CV_AMD64_R13W: return L"r13w";
  case CV_AMD64_R14W: return L"r14w";
  case CV_AMD64_R15W: return L"r15w";

  case CV_AMD64_R8D:  return L"r8d";
  case CV_AMD64_R9D:  return L"r9d";
  case CV_AMD64_R10D: return L"r10d";
  case CV_AMD64_R11D: return L"r11d";
  case CV_AMD64_R12D: return L"r12d";
  case CV_AMD64_R13D: return L"r13d";
  case CV_AMD64_R14D: return L"r14d";
  case CV_AMD64_R15D: return L"r15d";

  default:
    throw runtime_error("Unexpected register");
  }
}


void render_IDA_type(PdbType* type, struct class_member *cm)
{
  PdbTypeBasic* basicType;
  switch(type->getPdbTypeId())
  {
    case DIAID_BASIC: {
     basicType = dynamic_cast<PdbTypeBasic*>(type);
     switch(basicType->getBasicTypeCode()) {
      case btWChar: 
        cm->type = IDA_WORD;
       break;
      case btInt:
       switch(basicType->getSizeBytes()) {

        case 1:
         cm->type = IDA_BYTE;
         break;

        case 2:
         cm->type = IDA_WORD;
        break;

        case 4:
         cm->type = IDA_DWORD;
        break;

        case 8:
         cm->type = IDA_QWORD;
        break;
       }
       break;

      case btUInt:
       switch(basicType->getSizeBytes()) {

        case 1:
         cm->type = IDA_BYTE;
         break;

        case 2:
         cm->type = IDA_WORD;
        break;

        case 4:
         cm->type = IDA_DWORD;
        break;

        case 8:
         cm->type = IDA_QWORD;
        break;
      }
      break;

     case btFloat:
      switch(basicType->getSizeBytes()) {
      case 4:
         cm->type = IDA_FLOAT;
        break;

      case 8:
        cm->type = IDA_DOUBLE;
        break;

      }
      break;
     case btLong: 
       cm->type = IDA_DWORD;
      break;

     case btULong: 
       cm->type = IDA_DWORD;
      break;
     }
    }
    break;

   case DIAID_POINTER:
     cm->type = IDA_PTR;
    break;
  }
}

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
/// <returns>Rendered string</returns>
///
/// <exception cref="runtime_error">Thrown if an internal error occurs</exception>
/// 
wstring renderTypeShort(PdbType* type, bool withName, wstring dataName,
                        vector<PdbItemData*>* functionParameters,
                        wstring functionCC, bool for_rpd) 
{
  if ( NULL == type )
   return L"ZERO TYPE";
  PdbTypeBasic* basicType;
  PdbType* pointeeType;
  PdbTypeArray* arrayType;
  PdbTypeFunction* functionType;
  PdbTypeReference* referenceType;
  PdbTypePointer* pointerType;
  vector<PdbType*> functionArgs;
  wchar_t buf[256];
  
  
  // deal with the variety of possible types
  unsigned int i;
  wstring result;
  switch(type->getPdbTypeId()) {
  case DIAID_ARRAY: {
    // work out the type of the array
    arrayType = dynamic_cast<PdbTypeArray*>(type);
    result = renderTypeShort(arrayType->getElementType(), false, L"");

    // add on the name if requested
    if (withName) {
      result.append(L" ");
      result.append(dataName);
    }

    // add on the indices
    vector<PdbTypeArrayIndex> indices = arrayType->getArrayIndices();
    for(i=0; i< indices.size(); i++) {
      wsprintfW(buf, L"%i", indices[i].second);
      result.append(L"[");
      result.append(buf);
      result.append(L"]");
    }

    // return NOW, since arrays needed special handling
    return result;
  }

  case DIAID_BASIC: {
    basicType = dynamic_cast<PdbTypeBasic*>(type);
    switch(basicType->getBasicTypeCode()) {
    case btNoType:
      result = L"...";
      break;
    
    case btVoid:
      result = L"void"; 
      break;

    case btChar: 
      result = L"char"; 
      break;

    case btWChar: 
      result = L"wchar_t";
      break;

    case btInt:
      switch(basicType->getSizeBytes()) {
      case 1:
        result = L"char";
        break;

      case 2:
        result = L"short";
        break;

      case 4:
        result = L"int";
        break;

      case 8:
        result = L"__int64";
        break;

      default:
        throw runtime_error("Unknown btInt size");
      }
      break;

    case btUInt:
      switch(basicType->getSizeBytes()) {
      case 1:
        result = L"unsigned char";
        break;

      case 2:
        result = L"unsigned short";
        break;

      case 4:
        result = L"unsigned int";
        break;

      case 8:
        result = L"unsigned __int64";
        break;

      default:
        throw runtime_error("Unknown btUInt size");
      }
      break;

    case btFloat:
      switch(basicType->getSizeBytes()) {
      case 4:
        result = L"float";
        break;

      case 8:
        result = L"double";
        break;

      case 10:
        result = L"long double";
        break;

      default:
        printf("Unknown btFloat size: %d\n", basicType->getSizeBytes() );
        throw runtime_error("Unknown btFloat size");
      }
      break;

    case btBCD: 
      result = L"BCD";
      break;

    case btBool: 
      result = L"bool";
      break;

    case btLong: 
      result = L"long";
      break;

    case btULong: 
      result = L"unsigned long";
      break;

    case btCurrency: 
      result = L"CURRENCY";
      break;

    case btDate: 
      result = L"DATE";
      break;

    case btVariant: 
      result = L"VARIANT";
      break;

    case btComplex:
      result = L"COMPLEX";
      break;

    case btBit:
      result = L"BIT";
      break;

    case btBSTR:
      result = L"BSTR";
      break;

    case btHresult:
      result = L"HRESULT";
      break;

    default:
      throw runtime_error("Unknown basic type");
    }
  }
  break;

  case DIAID_FUNCTION:
    // cast the function type correctly
    functionType = dynamic_cast<PdbTypeFunction*>(type);

    // output start of function
    result.append(renderTypeShort(functionType->getReturnType(), false, L""));
    result.append(L" ");
    result.append(functionCC);
    result.append(L" ");
    if (withName) {
      result.append(dataName);
    }
    result.append(L"(");

    // output args
    functionArgs = functionType->getArguments();
    for(i=0; i< functionArgs.size(); i++) {
      // add on the type
      if ((functionParameters == NULL) || (functionParameters->size() <= i)) {
        result.append(renderTypeShort(functionArgs[i], false, L""));
      } else {
        result.append(renderDataItem(functionParameters->at(i), for_rpd));
      }

      // add on the separating comma
      if (i < (functionArgs.size() - 1)) {
        result.append(L", ");
      }
    }
    result.append(L")");
    return result;

  case DIAID_POINTER:
    pointerType = dynamic_cast<PdbTypePointer*>(type);
    pointeeType = pointerType->getPointeeType();

    // functions need special handling (yuk)
    if (pointeeType->getPdbTypeId() == DIAID_FUNCTION) {
      // setup initial name
      wstring tmp = L"(";
      if (withName) {
        tmp.append(dataName);
      }

      // finalise the name
      for(int i=0; i< pointerType->getIndirectionDepth(); i++) { 
        tmp.append(L"*");
      }
      tmp.append(L")");

      // render it & return 
      return renderTypeShort(pointeeType, true, tmp);
    } else {
      result = renderTypeShort(pointeeType, false, L"");
      for(int ii=0; ii< pointerType->getIndirectionDepth(); ii++) { 
        result.append(L"*");
      }
    }
    break;

  case DIAID_REFERENCE:
    referenceType = dynamic_cast<PdbTypeReference*>(type);
    result = renderTypeShort(referenceType->getRefereeType(), false, L"");
    result.append(L"&");
    break;

  case DIAID_CLASS:
    result = wstring(L"class ") + dynamic_cast<PdbTypeClass*>(type)->getName();
    break;

  case DIAID_ENUMERATION:
    result = wstring(L"enum ") + dynamic_cast<PdbTypeEnumeration*>(type)->getName();
    break;

  case DIAID_STRUCT:
    result = wstring(L"struct ") + dynamic_cast<PdbTypeStruct*>(type)->getName();
    break;

  case DIAID_UNION:
    result = wstring(L"union ") + dynamic_cast<PdbTypeUnion*>(type)->getName();
    break;

  case DIAID_TYPEDEF:
    result = dynamic_cast<PdbTypeTypedef*>(type)->getName();
    break;

  default:
    throw runtime_error("Unknown PdbType");
  }

  // deal with adding on the name
  if (withName) {
    result.append(L" ");
    result.append(dataName);
  }

  // return results
  return result;
}

