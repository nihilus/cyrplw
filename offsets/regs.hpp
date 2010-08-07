#ifndef REGS_HPP
# define REGS_HPP	"Written by Red Plait"

#include "ds.hpp"
#include <ida.hpp>
#include <struct.hpp>

struct one_reg {
 int is_s;     /* is register contains offset to struct */
 tid_t tid;    /* tid of structure */
 ulong offset; /* offset from base to current member */
 void reset()
 {
   offset = 0;
   is_s = 0;
 }
 void set_s(tid_t _tid)
 {
   tid = _tid;
   offset = 0;
   is_s = 1;
 }
};

struct my_vm {
protected:
 one_reg regs[8];
public:
 int actual;

 my_vm(RP_mapping *_m)
  : map(_m)
 {
   reset_regs();
 }
 void reset_regs();
 static int get_hreg(int);
 int analize_instr(ea_t);
protected:
 void xfer_reg(int,int);
 void reset_reg(int);
 void set_reg(int, tid_t);
private:
 RP_mapping *map;
};

#endif /* REGS_HPP */