#include "smac.h"
#include <bytes.hpp>
#include <xref.hpp>
#include <offset.hpp>

smac_reffer::smac_reffer()
{
  m_start = m_end = BADADDR;
  segment_t *s = get_segm_by_name("__basicstring");
  if ( NULL == s )
   return;
  m_start = s->startEA;
  m_end   = s->endEA;
}

ea_t smac_reffer::add(ea_t addr, ea_t value)
{
  ea_t real_value = value;
  if ( is_ba_segm(value) )
  {
    doDwrd(value, 4);
    doDwrd(value + 4, 4);
    real_value = get_long(value + 4);
    doDwrd(value + 8, 4);
    doDwrd(value + 12, 4);
    doDwrd(value + 16, 4);
    add_dref(value + 4, real_value, dr_O);
    op_offset(value + 4, OPND_MASK, REF_OFF32, real_value);
    make_ascii_string(real_value, 0, ASCSTR_PASCAL);
  }
  // lets make cross-ref from addr to real_value
  add_dref(addr, real_value, dr_O);
  return real_value;
}