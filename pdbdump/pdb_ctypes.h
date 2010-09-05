#ifndef PDB_CTYPES_H
# define PDB_CTYPES_H

/*
 * Enumeration of types of PdbType structures
 */
enum PdbTypeIds {
  DIAID_BASIC = 0,
  DIAID_POINTER,
  DIAID_REFERENCE,
  DIAID_ARRAY,
  DIAID_MANAGED,
  DIAID_CUSTOM,
  DIAID_ENUMERATION,
  DIAID_STRUCT,
  DIAID_CLASS,
  DIAID_UNION,
  DIAID_TYPEDEF,
  DIAID_FUNCTION,
};

/*
 * Enum for IDA struct converting
 */
enum IDA_typez {
  IDA_BYTE = 0,
  IDA_WORD,
  IDA_DWORD,
  IDA_QWORD,
  IDA_FLOAT,
  IDA_DOUBLE,
  IDA_PTR,	 // added 28 Aug 2006 for support AMD64
};
#endif /* PDB_CTYPES_H */