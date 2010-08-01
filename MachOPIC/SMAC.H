#ifndef SMAC_H
# define SMAC_H	"String referrer for RealBasic executables in MachO format"

#include <ida.hpp>
#include <segment.hpp>

class smac_reffer
{
 public:
  smac_reffer();
  ea_t add(ea_t, ea_t);
 protected:
  inline int is_ba_segm(ea_t a)
  {
    if ( m_start == BADADDR )
     return 0;
    if ( a >= m_start && a < m_end )
     return 1;
    return 0;
  }
  ea_t m_start;
  ea_t m_end;
};
#endif /* SMAC_H */