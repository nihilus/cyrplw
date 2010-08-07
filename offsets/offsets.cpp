/*
 * This plugin converts all indirect ptrs to struct member to explicit
 * offset inside struct
 * v0.1 24-IV-2001   - initial creating
 * v0.2 07-VIII-2010 - port to ida 5.0 & visual c++ 6.0
 * (C) RedPlait, redplait@gmail.com
 */
#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include "../pic/rp.hpp"
#include <funcs.hpp>
#include <struct.hpp>
#include "ds.hpp"
#include "regs.hpp"

/***** for debugging *****/
#include "rp_debug.h"

/***** CONSTANTS *****/
char Off_comment[] = "Plugin for struct offsets recognizing";
char Off_help[] =
"Struct offset recognizing plugin\n";
char Off_wanted_name[] = "Struct offsets plugin";
char Off_wanted_hotkey[] = "Alt-O";

/***** GLOBALS *****/
RP_mapping *my_config = NULL;

/***** CODE *****/
int
Off_init(void)
{
 /* for x86 only */
 if ( ph.id != PLFM_386 )
  return PLUGIN_SKIP;
 return PLUGIN_OK;
}

/* get start addr, end addr and do all dirty work */
ea_t
work_horse(ea_t start, ea_t end)
{
#ifdef RP_DEBUG
 msg("work_horse(%X, %X)\n", start, end);
#endif
  my_vm vm(my_config);
  ulong size;
  while( start < end )
  {
    size = vm.analize_instr(start);
    if ( size < 1 )
     return BADADDR;
    start += size;
    if ( !vm.actual )
     return start;
  }
  return start;
}

/* processed all structs in current function */
int
Off_current_func()
{
  int res = 0;
  ea_t curr_addr = get_screen_ea();
  func_t *curr_func = get_func(curr_addr);
  if ( NULL == curr_func )
  {
    msg("Cannot operate not on function, address %X\n", curr_addr);
    return 0;
  }
  dict_t *dict = my_config->dict();
  dnode_t *node;
  ea_t from, addr;
  for ( node = dict_first(dict); node != NULL; node = dict_next(dict, node) )
  {
    addr = (ea_t)dnode_getkey(node);
#ifdef RP_DEBUG
 msg("Adr %X\n", addr);
#endif
    for ( from = get_first_dref_to(addr);
          from != BADADDR && from < curr_func->endEA;
          from = get_next_dref_to(addr, from) )
    {
#ifdef RP_DEBUG
 msg("from %X\n", from);
#endif
      if ( from < curr_func->startEA )
       continue;
      work_horse(from, curr_func->endEA);
      res++;
    }
  }
  return res;
}

int
Off_all_funcs()
{
  int res = 0;
  func_t *f;
  ea_t adr, from;
  dnode_t *node;
  dict_t *dict = my_config->dict();
  
  for ( node = dict_first(dict); node != NULL; node = dict_next(dict, node) )
  {
    adr = (ea_t)dnode_getkey(node);
    for ( from = get_first_dref_to(adr); 
          from != BADADDR; 
          from = get_next_dref_to(adr, from) )
    {
      f = get_func(from);
      if ( NULL == f )
      {
        msg("Address %X is not in function\n", from);
        continue;
      }
      work_horse(from, f->endEA);
      res++;
    }
  }
  return res;
}

void
Off_run(int arg)
{
  if ( NULL == my_config )
  {
    char *fn = RP_mapping::find_path("off");
    if ( fn == NULL )
    {
      msg("Cannot find appropriate external file .OFF with your structs data\n");
      return;
    }
#ifdef RP_DEBUG
 msg("Found: %s\n", fn);
#endif
    my_config = new RP_mapping(fn);
    if (!my_config->successfull_creating() )
    {
      msg("Problem with '%s' initialization\n", Off_wanted_name);
      delete my_config;
      my_config = NULL;
      return;
    }
    if ( !my_config->read_config() )
    {
      msg("Problem with reading config file '%s'\n", my_config->config_name());
      delete my_config;
      my_config = NULL;
      return;
    }
  }
  switch(arg)
  {
    case 0:
      Off_current_func();
     break;
    case 1:
      Off_all_funcs();
     break;
    default:
     warning("Illegal parameter %d for %s\n"
"Allowed parameters:\n"
" 0 - process current function\n"
" 1 - process all functions (can take long time)\n",
 arg, Off_wanted_name
);
  }
}

void
Off_term(void)
{
  if ( my_config != NULL )
  {
   delete my_config;
   my_config = NULL; /* well lets be carefull */
  }
}

/***** PLUGIN description *****/
extern "C" plugin_t PLUGIN = {
 IDP_INTERFACE_VERSION,
 PLUGIN_MOD,
 Off_init,
 Off_term,
 Off_run,
 Off_comment,
 Off_help,
 Off_wanted_name,
 Off_wanted_hotkey
};