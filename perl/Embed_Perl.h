#ifndef EMBED_PERL_H
# define EMBED_PERL_H	"Embedded Perl class"

#include "Embed_Lang.h"
/* Perl specific includes */
#include <EXTERN.h>
#define PERL_IMPLICIT_SYS	// dirty hack for STDOUT/STDERR redirection
#include <perl.h>
#include <string.h>
#define NO_XSLOCKS
#include <XSUB.h>
#include <win32iop.h>

void my_init_sys_perl();
void my_term_sys_perl();

class Embed_Perl: public Embed_Language
{
  public:
    Embed_Perl();
    virtual ~Embed_Perl();
    virtual int Init();
    virtual int ParseScript(char *);
    virtual int RunScript(char *);
    virtual void *get_true_interpretor()
    {
      return (void *)m_perl;
    }
  protected:
    PerlInterpreter *m_perl;
    IPerlStdIOInfo m_mystdio;
};

#endif /* EMBED_PERL_H */