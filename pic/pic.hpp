#define USE_STANDARD_FILE_FUNCTIONS
#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <bytes.hpp>

extern const char *log_filename;
extern FILE *rp_log_fp;

#define RP_TRACE(str)	if ( NULL != rp_log_fp ) \
 {\
  fprintf(rp_log_fp, str );\
  fflush(rp_log_fp);\
 } else\
  msg( str );

#define RP_TRACE1(str, args)	if ( NULL != rp_log_fp ) \
 {\
  fprintf(rp_log_fp, str, (args) );\
  fflush(rp_log_fp);\
 } else\
  msg( str, (args) );

#define RP_TRACE2(str, arg1, arg2)	if ( NULL != rp_log_fp ) \
 {\
  fprintf(rp_log_fp, str, arg1, arg2 );\
  fflush(rp_log_fp);\
 } else\
  msg( str, arg1, arg2 );

#define RP_TRACE3(str, arg1, arg2, arg3)	if ( NULL != rp_log_fp ) \
 {\
  fprintf(rp_log_fp, str, arg1, arg2, arg3 );\
  fflush(rp_log_fp);\
 } else\
  msg( str, arg1, arg2, arg3 );

#define RP_TRACE4(str, arg1, arg2, arg3, arg4)	if ( NULL != rp_log_fp ) \
 {\
  fprintf(rp_log_fp, str, arg1, arg2, arg3, arg4 );\
  fflush(rp_log_fp);\
 } else\
  msg( str, arg1, arg2, arg3, arg4 );

#define RP_TRACE5(str, arg1, arg2, arg3, arg4, arg5)	if ( NULL != rp_log_fp ) \
 {\
  fprintf(rp_log_fp, str, arg1, arg2, arg3, arg4, arg5 );\
  fflush(rp_log_fp);\
 } else\
  msg( str, arg1, arg2, arg3, arg4, arg5 );
