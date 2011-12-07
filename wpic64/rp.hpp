#ifndef RP_HPP

# define RP_HPP	"Some usefull functions for IDA Pro plugins"

#include <ida.hpp>
#include <bytes.hpp>

#define RP_HEX(c)	btoa((c), 0x10)

/* function declaration */
void idaapi rp_set_comment(ea_t ea, const char *comment, bool is_before, bool rptbl = false);

#if (IDP_INTERFACE_VERSION < 58)
# define NO_DO_FLOAT	true
# define NO_DO_DOUBLE	true
#else
# undef NO_DO_FLOAT
# undef NO_DO_DOUBLE
#endif

#ifdef NO_DO_FLOAT
inline bool idaapi
RP_doFloat(ea_t ea)
{
#define FF_FLOAT    0x80000000L         // float
  return do_data_ex(ea, floatflag(), sizeof(float), BADNODE);
#undef FF_FLOAT
}
#endif

#ifdef NO_DO_DOUBLE
inline bool idaapi
RP_doDouble(ea_t ea)
{
#define FF_DOUBLE   0x90000000L         // double
  return do_data_ex(ea, doubleflag(), sizeof(double), BADNODE);
#undef FF_DOUBLE
}
#endif

#endif /* RP_HPP */