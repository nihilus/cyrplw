#ifndef RP_RECOGN_HPP
# include "recogn.hpp"
#endif

bool
rp_is_defined(ea_t ptr)
{
  return 0 != ( 0x100 & getFlags(ptr) );
}

bool 
is_contain_ptr(ea_t ptr)
{
  if ( !is_defined_area(ptr, sizeof(ea_t)) )
   return false;
  ea_t ptr2 = 
#ifdef __EA64__
    get_qword(ptr);
#else
    get_long(ptr);
#endif /* __EA64__ */
  return rp_is_defined(ptr2);
}

bool
is_defined_area(ea_t ptr, size_t size)
{
#ifdef NO_CHUNK_BUG
  for ( size_t i = 0; i < size; i++ )
  {
     if ( !rp_is_defined(ptr+i) )
      return false;
  }
  return true;
#else
  ea_t end = rp_get_defined_end(ptr);
  if ( NULL == end )
   return false;
  if ( end >= ptr + size )
   return true;
#endif
}

ea_t
rp_get_defined_end(ea_t ptr)
{
/*** Fuck ! functions chunkstart and chunksize not present in ida.lib ! 
 *** So to work only with defined bytes I must return end of segment
 *** and in each function check result of rp_is_defined. Sux
 *** How many bugs I am already find in IDA SDK ? 
 ***/
#ifndef NO_CHUNK_BUG
  ea_t our_start = chunkstart(ptr);
   if ( BADADDR == our_start )
   return NULL;
  size_t our_len = chunksize(ptr);
  if ( ! our_len )
   return NULL;
  return our_start + our_len;
#else
 segment_t *s = getseg(ptr);
 if (NULL == s)
  return 0;
 return s->endEA;
#endif
}

size_t
rp_is_class_name(ea_t ptr)
{
  size_t res = 0;
  ea_t our_end = rp_get_defined_end(ptr);
  if ( NULL == our_end )
   return NULL;

  /* check for first symbol */
#ifdef NO_CHUNK_BUG
  if ( !rp_is_defined(ptr) )
   return 0;
#endif
  uchar c = get_byte(ptr);
  if (! (c == '_' || ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' )) )
   return 0;
  for( res++; ptr + res <= our_end; res++ )
  {
#ifdef NO_CHUNK_BUG
    if ( !rp_is_defined(ptr) )
     return 0;
#endif
    c = get_byte(ptr + res);
    if ( !c )
    {
      if ( res < 3 ) /* name must be at least 3 symbol */
       return 0;
      return res;
    }
    if ( c == '_' || (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') )
      continue;
    return 0;
  }
  return 0; /* bit strange - we have string with name but no zero symbol in our segment */
}

static bool is_needed_name(char *name, const char *what_we_need, int what_we_need_len)
{
  if ( !name || !*name )
   return false;
  int namelen = strlen(name);
  if ( namelen < what_we_need_len )
   return false;
  if ( strcmp(name + namelen - what_we_need_len, what_we_need) )
   return false;
  return true;
}

static ea_t extract_long(ea_t vtbl_func)
{
  if ( !is_contain_ptr(vtbl_func) )
   return NULL;
#ifdef __EA64__
  ea_t func = get_qword(vtbl_func);
#else
  ea_t func = get_long(vtbl_func);
#endif /* __EA64__ */
  return check_for_cruntimeclass(func);
}

/* Terrible function - get name and ea_t of function and tries
 * to recognize if we have message mapper here.
 * Return: ea_t of AFX_MSGMAP * or NULL if all was bad
 */
ea_t is_message_map_func(ea_t vtbl_func, char *name)
{
  static const char *what_we_need = "GetMessageMap()";
  static const int what_we_need_len = 15;
  if ( !is_needed_name(name, what_we_need, what_we_need_len) )
    return NULL;
  // O`k, we really have GetMessageMap function here
  return extract_long(vtbl_func);
}

ea_t is_command_map_func(ea_t vtbl_func, char *name)
{
  static const char *what_we_need = "GetCommandMap()";
  static const int what_we_need_len = 15;
  if ( !is_needed_name(name, what_we_need, what_we_need_len) )
    return NULL;
  // O`k, we really have GetCommandMap function here
  return extract_long(vtbl_func);  
}

ea_t is_dispatch_map_func(ea_t vtbl_func, char *name)
{
  static const char *nname = "GetDispatchMap()";
  static const int n_len = 16;
  if ( !is_needed_name(name, nname, n_len) )
    return NULL;
  // O`k, we really have GetDispatchMap function here
  return extract_long(vtbl_func);  
}

ea_t is_connection_map(ea_t vtbl_func, char *name)
{
  static const char *nname = "GetConnectionMap()";
  static const int n_len = 18;
  if ( !is_needed_name(name, nname, n_len) )
    return NULL;
  // O`k, we really have GetConnectionMap function here
  return extract_long(vtbl_func);  
}

ea_t is_interface_map(ea_t vtbl_func, char *name)
{
  static const char *nname = "GetInterfaceMap()";
  static const int n_len = 17;
  if ( !is_needed_name(name, nname, n_len) )
    return NULL;
  // O`k, we really have GetInterfaceMap function here
  return extract_long(vtbl_func);  
}

ea_t is_eventsink_map(ea_t vtbl_func, char *name)
{
  static const char *nname = "GetEventSinkMap()";
  static const int n_len = 17;
  if ( !is_needed_name(name, nname, n_len) )
    return NULL;
  // O`k, we really have GetEventSinkMap function here
  return extract_long(vtbl_func);    
}