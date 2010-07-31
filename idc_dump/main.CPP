#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <expr.hpp>
#include <kernwin.hpp>

void idaapi
IDC_run(int arg)
{
  FILE *fp = fopen("idc.out", "w");
  if ( fp == NULL )
  {
    warning("Cannot open idc.out");
    return;
  }
  const char *ptr;
  for ( int i = 0; i < IDCFuncs.qnty; i++ )
  {
    fprintf(fp, "%s", IDCFuncs.f[i].name);
    for ( ptr = IDCFuncs.f[i].args; *ptr; ptr++ )
     fprintf(fp, " %d", *ptr);
    fprintf(fp, "\n");
  }
  fclose(fp);
}

int idaapi
IDC_init(void)
{
  return PLUGIN_OK;
}

/******************** CONSTANTS *******************/
char IDC_comment[] = "Plugin for dumping IDCFuncs table";
char IDC_help[] =
 "Plugin for dumping IDCFuncs table\n";
char IDC_wanted_name[] = "IDCFuncs dumper";
char IDC_wanted_hotkey[] = "Alt-D";

/*
 * PLUGIN description
 */
extern "C" plugin_t PLUGIN = {
  IDP_INTERFACE_VERSION,
  PLUGIN_UNL,    	// plugin flags
  IDC_init,             // initialize function
  NULL,	                // terminate. this pointer may be NULL.
  IDC_run,              // invoke plugin
  IDC_comment,          // long comment about the plugin
  IDC_help,             // multiline help about the plugin
  IDC_wanted_name,      // the preferred short name of the plugin
  IDC_wanted_hotkey     // the preferred hotkey to run the plugin
};
