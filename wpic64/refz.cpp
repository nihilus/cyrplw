#include "rp.hpp"
#include "x86.hpp"
#include <idp.hpp>

void idaapi
pic_add_dref(ea_t from, ea_t to, dref_t dtype, char dtyp, bool make_type)
{
  add_dref(from, to, dtype);
  char cmt[24];
  btoa(cmt, sizeof(cmt), to, 0x10);
  rp_set_comment(from, cmt, false );
  if ( !make_type )
    return;
  if ( dtype == dr_R || dr_W )
  {
   switch(dtyp)
   {
     case dt_byte: doByte(to,1);	break;
     case dt_word: doWord(to,2);	break;
     case dt_dword: doDwrd(to,4);	break;
     case dt_float: 
#if defined(NO_DO_FLOAT)
      RP_doFloat(to);
#else
      doFloat(to, sizeof(float));
#endif
      break;
     case dt_qword: doQwrd(to,8);	break;
     case dt_double: 
#if defined(NO_DO_DOUBLE)
      RP_doDouble(to);
#else
      doDouble(to, sizeof(double));
#endif
      break;
     case dt_tbyte: doTbyt(to, ph.tbyte_size);
   }
  }
}
