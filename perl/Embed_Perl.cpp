#include "Embed_Perl.h"
#include "perliol.h"
/* IDA specific includes */
#include "pro.h"
#include "kernwin.hpp"

char *staticlinkmodules[] = {
 "DynaLoader",
 "IDA",
#ifdef IDADBG_PERL
 "IDADbg",
#endif
 NULL,
};

extern int init_IDC();
/* boot functions */
EXTERN_C void boot_DynaLoader(pTHXo_ CV* cv);
EXTERN_C void boot_IDA(pTHXo_ CV* cv);

#ifdef IDADBG_PERL
EXTERN_C void boot_IDADbg(pTHXo_ CV* cv);
#endif

static void
xs_init(pTHX)
{
  char *file = __FILE__;
  dXSUB_SYS;
  newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
  newXS("IDA::boot_IDA", boot_IDA, file);
#ifdef IDADBG_PERL
  newXS("IDADbg::boot_IDADbg", boot_IDADbg, file);
#endif
}

static int is_stdout(IPerlStdIO *io, FILE *p)
{
  if ( p == io->pStdout(io) )
   return 1;
  return 0;
}

static int is_stderr(IPerlStdIO *io, FILE *p)
{
  if ( p == io->pStderr(io) )
   return 1;
  return 0;
}

/*** ** * stdout/stderr redirectors * ** ***/
SSize_t PerlIOidamsg_write(pTHX_ PerlIO *f, const void *vbuf, Size_t count)
{
    SSize_t total= 0;
    Size_t ofs= 0;
    while (ofs<count) {
        Size_t printed= msg("%.*s", count-ofs, (const char*)vbuf+ofs);
        ofs += printed;
        if (printed==0)
            break;
    }
    return total;
}

static PerlIO_funcs PerlIO_idamsg = {
    sizeof(PerlIO_funcs),        
    "idamsg",                    
    sizeof(_PerlIO),
    PERLIO_K_MULTIARG | PERLIO_K_RAW,
    PerlIOBase_pushed,         
    NULL,                       /* PerlIOBase_popped */
    NULL,                       /* PerlIOidamsg_open */
    NULL,                       /* PerlIOBase_binmode */
    NULL,                       /* no getarg needed */
    NULL,                       /* PerlIOidamsg_fileno */
    NULL,                       /* PerlIOidamsg_dup */
    NULL,                       /* PerlIOidamsg_read */
    NULL,                       /* PerlIOBase_unread */
    PerlIOidamsg_write,         /* PerlIOidamsg_write */
    NULL,                       /* PerlIOidamsg_seek */
    NULL,                       /* PerlIOidamsg_tell */
    NULL,                       /* PerlIOidamsg_close */
    NULL,                       /* PerlIOidamsg_flush */
    NULL,                       /* PerlIOidamsg_noop_fail - fill */
    NULL,                       /* PerlIOidamsg_eof */
    NULL,                       /* PerlIOBase_error */
    NULL,                       /* PerlIOBase_clearerr */
    NULL,                       /* PerlIOBase_setlinebuf */
    NULL,                       /* get_base */
    NULL,                       /* get_bufsiz */
    NULL,                       /* get_ptr */
    NULL,                       /* get_cnt */
    NULL,                       /* set_ptrcnt */
};

void init_idamsg_io(pTHX)
{
    PerlIO_define_layer(aTHX_ &PerlIO_idamsg);

//binmode ":idamsg", stdout;
    PerlIO_push(aTHX_ PerlIO_stdout(), &PerlIO_idamsg, "a", NULL);
//binmode ":idamsg", stderr;
    PerlIO_push(aTHX_ PerlIO_stderr(), &PerlIO_idamsg, "a", NULL);
}

static SSize_t __cdecl
my_write(struct IPerlStdIO* piPerl, const void *buffer, Size_t size, Size_t count, FILE *fp)
{
  if ( is_stdout(piPerl, fp) )
  {
    msg("%s", buffer);
    return size;
  }
  if ( is_stderr(piPerl, fp) )
  {
    warning("%s", buffer);
    return size;
  }
  return win32_fwrite(buffer, size, count, fp);
}

static int __cdecl
my_vprintf(struct IPerlStdIO* piPerl, FILE *fp, const char *format, va_list va)
{
  if ( is_stdout(piPerl, fp) )
  {
    return vmsg(format, va);
  }
  if ( is_stderr(piPerl, fp) )
  {
    vwarning(format, va);
    return 1; // ??
  }
  return win32_vfprintf(fp, format, va);
}

static int __cdecl
my_printf(struct IPerlStdIO* piPerl, FILE *fp, const char *format, ... )
{
  va_list marker;
  va_start(marker, format);

  if ( is_stdout(piPerl, fp) )
  {
    return vmsg(format, marker);
  }
  if ( is_stderr(piPerl, fp) )
  {
    vwarning(format, marker);
    return 1; // ??
  }
  return win32_vfprintf(fp, format, marker);
}

/*** my Embedded Perl class implementation ***/
void my_init_sys_perl()
{
  int argc = 0;
  char *args = NULL;
  char **argv = &args;
  PERL_SYS_INIT(&argc, &argv);
}

// return code or exception from constructor IMHO is bad practice so all
// important code for initialization located in Init method
Embed_Perl::Embed_Perl()
{
  m_perl = NULL;
}

Embed_Perl::~Embed_Perl()
{
  if ( NULL != m_perl )
  {
    perl_destruct(m_perl);
    perl_free(m_perl);
  }
}

int Embed_Perl::Init()
{
  if ( !init_IDC() )
  {
    warning("Cannot initialize IDC func set");
    return 0;
  }
  m_perl = perl_alloc();
  if ( NULL == m_perl )
  {
    warning("Cannot alloc perl");
    return 0;
  }
  perl_construct(m_perl);
  /* redirect of input/output */
  init_idamsg_io(m_perl);
  IPerlStdIO *io = m_perl->IStdIO;
  if ( io != NULL )
  {
    io->pWrite   = my_write;
    io->pPrintf  = my_printf;
    io->pVprintf = my_vprintf;
  }
  return 1;
}

int Embed_Perl::ParseScript(char *fname)
{
  char *argv[] = { "IDAPerl", NULL, NULL };
  argv[1] = fname;
  if ( perl_parse(m_perl, xs_init, 2, argv, NULL) )
	  return 0;
  return 1;
}

int Embed_Perl::RunScript(char *fname)
{
  if ( !ParseScript(fname) )
   return 0;
  perl_run(m_perl);
  return 1;
}