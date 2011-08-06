#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <expr.hpp>

#include "Embed_Perl.h"

void idaapi run(int arg)
{
  char *res = askfile_c(0, "*.pl", "Perl script", NULL);
  if ( NULL == res )
   return;
  Embed_Perl perl;
  if ( !perl.Init() )
   return;
  perl.RunScript(res);
}

int idaapi init(void)
{
  my_init_sys_perl();
  return PLUGIN_KEEP;
}

char comment[] = "This is embedded Perl replacement for IDC.";
char help[] =
        "Embedded Perl plugin\n"
        "\n"
        "This module allows you run Perl scripts instead nasty and poor IDC\n"
        "\n"
        "If you have questions or suggestions - mail me to redp@mail.ru\n"
;
char wanted_name[] = "Embedded Perl";
char wanted_hotkey[] = "Alt-P";

extern "C" plugin_t PLUGIN = {
  IDP_INTERFACE_VERSION,
  0,                    // plugin flags
  init,                 // initialize

  NULL,                 // terminate. this pointer may be NULL.

  run,                  // invoke plugin

  comment,              // long comment about the plugin
                        // it could appear in the status line
                        // or as a hint

  help,                 // multiline help about the plugin

  wanted_name,          // the preferred short name of the plugin
  wanted_hotkey         // the preferred hotkey to run the plugin
};
