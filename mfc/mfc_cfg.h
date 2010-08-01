#ifndef MFC_CFG_H
# define MFC_CFG_H

#include "cfg.h"

extern "C" void check_cfg();
extern "C" void finalize_cfg();

class MFC_Cfg: public Cfg
{
  public:
    MFC_Cfg(char *);
    virtual ~MFC_Cfg();
    virtual void parse(char *, char *);
    /* something usefull */
    char *tlb_data_dir();
    char *rpd_data_dir();
  protected:
    char *m_tlb_dir;
    char *m_rpd_dir;
};

extern MFC_Cfg *mfc_cfg;

#endif /* MFC_CFG_H */