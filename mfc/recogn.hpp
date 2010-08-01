#ifndef RP_RECOGN_HPP
#define RP_RECOGN_HPP	"Written by Red Plait, 15-IV-2000"

#include <ida.hpp>
#include <bytes.hpp>
#include <segment.hpp>

#define NO_CHUNK_BUG	"Ilfack bugs work around"

ea_t check_for_cruntimeclass(ea_t ptr);
ea_t check_for_cruntimeclass2(ea_t ptr);
ea_t rp_get_defined_end(ea_t ptr);
size_t rp_is_class_name(ea_t ptr);
bool is_defined_area(ea_t ptr, size_t size);
bool is_contain_ptr(ea_t ptr);
// all MFC mapper methods
ea_t is_message_map_func(ea_t func, char *name);
ea_t is_command_map_func(ea_t func, char *name);
ea_t is_dispatch_map_func(ea_t func, char *name);
ea_t is_connection_map(ea_t func, char *name);
ea_t is_interface_map(ea_t func, char *name);
ea_t is_eventsink_map(ea_t func, char *name);

#endif /* RP_RECOGN_HPP */