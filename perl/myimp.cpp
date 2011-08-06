#include <ida.hpp>
#include <idp.hpp>
#include <bytes.hpp>
#include <kernwin.hpp>
#include <auto.hpp>
#include <entry.hpp>
#include <struct.hpp>
#include <loader.hpp>
#include <name.hpp>
#include "ida.h"

/* I implemented this functions by myself to skip one marshaller level for calling
 * IDC function from IDCFuncs array and such make boost for some functions
 */
int
 MakeByte(long ea)
{
  return doByte(ea,1);
}

int 
 MakeWord(long ea)
{
  return doWord(ea, 2);
}

int
 MakeDword(long ea)
{
  return doDwrd(ea, 4);
}

int
 MakeQword(long ea)
{
  return doQwrd(ea, 8);
}

int
 MakeOword(long ea)
{
  return doOwrd(ea, 16);
}

int
 MakeFloat(long ea)
{
  return doFloat(ea, 4);
}

int
 MakeDouble(long ea)
{
  return doDouble(ea, 8);
}

int
 MakePackReal(long ea)
{
  return doPackReal(ea, 1);
}

int
 MakeTbyte(long ea)
{
  return doTbyt(ea, 1);
}

void
 MakeUnkn(long ea, long expand)
{
  do_unknown(ea, (bool)expand);
}

int
 OpBinary(long ea, long n)
{
  return op_bin(ea, n);
}

int
 OpOctal(long ea, long n)
{
  return op_oct(ea, n);
}

int
 OpDecimal(long ea, long n)
{
  return op_dec(ea, n);
}

int
 OpHex(long ea, long n)
{
  return op_hex(ea, n);
}

int
 OpChr(long ea, long n)
{
  return op_chr(ea,n);
}

int
 OpNumber(long ea, long n)
{
  return op_num(ea, n);
}

int
 PatchByte(long ea, long value)
{
  return patch_byte(ea, value);
}

int
 PatchWord(long ea, long value)
{
  return patch_word(ea, value);
}

int
 PatchDword(long ea, long value)
{
  return patch_long(ea, value);
}

static char ifp[1024];
char *
 GetIdbPath()
{
  get_input_file_path(ifp, 1024);
  return ifp;
}

unsigned long
 GetFlags(long ea)
{
  return getFlags(ea);
}

unsigned long
 Byte(long ea)
{
  return get_byte(ea);
}

unsigned long
 Word(long ea)
{
  return get_word(ea);
}

unsigned long
 Dword(long ea)
{
  return get_long(ea);
}

int
 Jump(long ea)
{
  return jumpto(ea);
}

int
 RunPlugin(char *name ,long arg)
{
  return load_and_run_plugin(name, arg);
}

int
 MakeComm(long ea, char *comment)
{
  return set_cmt(ea, comment, 0);
}

int
 MakeRptCmt(long ea, char *comment)
{
  return set_cmt(ea, comment, 1);
}

char *
 GetInputFile()
{
  static char gif[1024];
  get_root_filename(gif, 1024);
  return gif;
}

char *
 GetInputFilePath()
{
  static char gifp[1024];
  get_input_file_path(gifp, 1024);
  return gifp;
}


unsigned long
 ScreenEA()
{
  return get_screen_ea();
}

unsigned long
 SetStatus(long status)
{
  return setStat(status);
}

unsigned long
 GetEntryPointQty()
{
  return get_entry_qty();
}

unsigned long
 GetEntryPoint(long ordinal)
{
  return get_entry(ordinal);
}

unsigned long
 GetStrucQty()
{
  return get_struc_qty();
}

char *
 loader_name()
{
  static char ln[1024];
  get_loader_name(ln, 1024);
  return ln;
}

int
 load_ids(char *name)
{
  return load_ids_module(name);
}

void
 save_idb(void)
{
  // save_database();
  flush_buffers();
}

int
 is_debugged()
{
  return (int)is_debugger_on();
}

unsigned long 
 GetOriginalByte(long ea)
{
  return get_original_byte(ea);
}

long 
 GetOriginalWord(long ea)
{
  return (long)get_original_word(ea);
}

long 
 GetOriginalDword(long ea)
{
  return (long)get_original_long(ea);
}

void 
 MakeUnknRange(long ea_from, long size, int expand)
{
  do_unknown_range(ea_from, size, (bool)expand);
}

int IsPublicName(long ea)
{
  return is_public_name(ea);
}

void MakeNamePublic(long ea)
{
  make_name_public(ea);
}

void MakeNameNonPublic(long ea)
{
  make_name_non_public(ea);
}

void HideName(long ea)
{
  hide_name(ea);
}

void ShowName(long ea)
{
  show_name(ea);
}

char *IdpName()
{
  static char buffer[17];
  buffer[0] = 0;
  return get_idp_name(buffer, 16);
}