#include <math.h>
#include <ida.hpp>
#include <ua.hpp>
#include <intel.hpp>

extern "C" {
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
};

/* Perl helper function */
#define null_arg(sv)	(  SvROK(sv)  &&  SVt_PVAV == SvTYPE(SvRV(sv))	\
			   &&  -1 == av_len((AV*)SvRV(sv))  )

extern "C"
XS(myxs_ua_ana)
{
  dXSARGS;
  if (items != 1)
   Perl_croak(aTHX_ "Usage: IDA::ua_ana(addr)");
  unsigned long addr = null_arg(ST(0)) ? 0 : (int) SvUV(ST(0));
  ST(0) = sv_newmortal();
  int res = ua_ana0(addr);
  if ( !res )
   sv_setsv(ST(0), &PL_sv_undef);
  else {
    HV *hv = (HV*) sv_2mortal((SV*) newHV());
#define HV_STORE(name, name_len, field)	hv_store(hv, name, name_len, newSVuv((UV)cmd.field ), 0);

    HV_STORE("cs", 2, cs);
    HV_STORE("ip", 2, ip);
    HV_STORE("ea", 2, ea);
    HV_STORE("itype", 5, itype);
    HV_STORE("size", 4, size);
    HV_STORE("auxpref", 7, auxpref);
    HV_STORE("flags", 5, flags);
    sv_setsv(ST(0), (SV*) newRV((SV*) hv));
#undef HV_STORE
  }
  XSRETURN(1);
}

extern "C"
XS(myxs_get_op)
{
  dXSARGS;
  if (items != 1)
   Perl_croak(aTHX_ "Usage: IDA::get_op(N)");
  unsigned long n = null_arg(ST(0)) ? 0 : (int) SvUV(ST(0));
  ST(0) = sv_newmortal();
  if ( n >= UA_MAXOP )
    sv_setsv(ST(0), &PL_sv_undef);
  else if ( cmd.Operands[n].type == o_void )
    sv_setsv(ST(0), &PL_sv_undef);
  else { // number of operand is valid and this operand exists
    HV *hv = (HV*) sv_2mortal((SV*) newHV());
#define HV_STORE(name, name_len, field)	hv_store(hv, name, name_len, newSVuv((UV)cmd.Operands[n].field ), 0);
    HV_STORE("type", 4, type)
    HV_STORE("offb", 4, offb)
    HV_STORE("offo", 4, offo)
    HV_STORE("flags", 5, flags)
    HV_STORE("dtyp", 4, dtyp)
    HV_STORE("specflag1", 9, specflag1)
    HV_STORE("specflag2", 9, specflag2)
    HV_STORE("specflag3", 9, specflag3)
    HV_STORE("specflag4", 9, specflag4)
    switch(cmd.Operands[n].type)
    {
      case o_reg:
        HV_STORE("reg", 3, reg)
       break;
      case o_far:
      case o_near:
      case o_mem:
        HV_STORE("addr", 4, addr)
       break;
      case o_imm:
        if ( cmd.Operands[n].dtyp == dt_byte )
          HV_STORE("value", 5, value)
        else if ( cmd.Operands[n].dtyp == dt_word )
          HV_STORE("value", 5, value)
        else if ( cmd.Operands[n].dtyp == dt_dword )
          HV_STORE("value", 5, value)
       break;
      case o_displ:
      case o_phrase:
        HV_STORE("phrase", 6, phrase)
        if ( cmd.Operands[n].hasSIB )
        {
          hv_store(hv, "sib_base",  8, newSVuv((UV)sib_base(cmd.Operands[n])), 0);
          hv_store(hv, "sib_index", 9, newSVuv((UV)sib_index(cmd.Operands[n])), 0);
        }
        if ( cmd.Operands[n].type == o_displ )
          HV_STORE("addr", 4, addr)
       break;
    }
    sv_setsv(ST(0), (SV*) newRV((SV*) hv));
  }
  XSRETURN(1);
}