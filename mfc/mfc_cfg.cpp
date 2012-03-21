#include "mfc_cfg.h"
#include <stdlib.h>
#include <string.h>
#include <kernwin.hpp>

MFC_Cfg::MFC_Cfg(char *name)
 : Cfg(name)
{
  m_tlb_dir = NULL;
  m_rpd_dir = NULL;
}

MFC_Cfg::~MFC_Cfg()
{
  if ( m_tlb_dir )
   free(m_tlb_dir);
  if ( m_rpd_dir )
   free(m_rpd_dir);
}

void MFC_Cfg::parse(char *key, char *value)
{
#ifdef __EA64__
  if ( !stricmp(key, "RPD64_DIR") )
#else
  if ( !stricmp(key, "RPD_DIR") )
#endif /* __EA64__ */
  {
    if ( m_rpd_dir )
    {
      free(m_rpd_dir);
      m_rpd_dir = NULL;
    }
    if ( value )
      m_rpd_dir = _strdup(value);
  } else if ( !stricmp(key, "TLB_DIR") )
  {
    if ( m_tlb_dir )
    {
      free(m_tlb_dir);
      m_tlb_dir = NULL;
    }
    if ( value )
      m_tlb_dir = _strdup(value);
  }
}

char *MFC_Cfg::tlb_data_dir()
{
  if ( m_tlb_dir )
  {
    return m_tlb_dir;
  }
  /* default value */
  return "c:\\work\\tlb";
}

char *MFC_Cfg::rpd_data_dir()
{
  if ( m_rpd_dir )
   return m_rpd_dir;
  /* default value */
#ifdef __EA64__
  return "c:\\work\\rpd64";
#else
  return "c:\\work\\rpd";
#endif /* __EA64__ */
}

/* some interface functions */
MFC_Cfg *mfc_cfg = NULL;

void finalize_cfg()
{
  if ( mfc_cfg )
  {
    delete mfc_cfg;
    mfc_cfg = NULL;
  }
}

void check_cfg()
{
  if ( mfc_cfg )
    return;
  mfc_cfg = new MFC_Cfg("mfc.cfg");
  mfc_cfg->read();
}