#include "ida.h"

void
DelExtLnA(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[43].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetEnumFlag(long arg0)
{
 void *fp = RP_Funcs->f[320].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
DelExtLnB(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[44].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

int
OpSeg(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[21].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetCharPrm(long arg0)
{
 void *fp = RP_Funcs->f[355].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FindFuncEnd(long arg0)
{
 void *fp = RP_Funcs->f[213].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
OpAlt(long arg0,long arg1,char * arg2)
{
 void *fp = RP_Funcs->f[27].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
OpHigh(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[371].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetLastStrucIdx()
{
 void *fp = RP_Funcs->f[253].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Dnext(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[190].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
AddCodeXref(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[177].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

int
OpFloat(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[34].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetMemberName(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[268].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetCustomDataFormat(char * arg0)
{
 void *fp = RP_Funcs->f[485].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetDisasm(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[125].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
RfirstB0(long arg0)
{
 void *fp = RP_Funcs->f[184].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetEnumSize(long arg0)
{
 void *fp = RP_Funcs->f[318].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
ChooseFunction(char * arg0)
{
 void *fp = RP_Funcs->f[210].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
AskYN(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[75].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetOperandValue(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[129].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
OpEnumEx(long arg0,long arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[30].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetArrayLong(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[295].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
MarkPosition(long arg0,long arg1,long arg2,long arg3,long arg4,char * arg5)
{
 void *fp = RP_Funcs->f[248].fp;
 value_t res;
 value_t args[6];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 args[4].vtype = VT_LONG;
 args[4].num = arg4;
 args[5]._set_string(arg5);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

char *
GetEntryName(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[236].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

char *
GetString(long arg0,long arg1,long arg2)
{
 char *resstr;
 void *fp = RP_Funcs->f[389].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
MakeStructEx(long arg0,long arg1,char * arg2)
{
 void *fp = RP_Funcs->f[36].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFrameSize(long arg0)
{
 void *fp = RP_Funcs->f[214].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
RenameSeg(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[84].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetNextConst(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[332].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetShortPrm(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[357].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetRegEx(long arg0,char * arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[68].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetConstValue(long arg0)
{
 void *fp = RP_Funcs->f[322].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
Del_dref(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[188].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

char *
GetOpnd(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[126].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
DnextB(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[192].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetStrucPrevOff(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[263].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
MakeVar(long arg0)
{
 void *fp = RP_Funcs->f[37].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

int
DelArrayElement(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[298].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
readstr(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[164].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
SelEnd()
{
 void *fp = RP_Funcs->f[114].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 return res.num;
}

char *
GetConstName(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[334].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetLastMember(long arg0)
{
 void *fp = RP_Funcs->f[266].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FindImmediate(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[174].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

long
GenerateFile(long arg0,long arg1,long arg2,long arg3,long arg4)
{
 void *fp = RP_Funcs->f[46].fp;
 value_t res;
 value_t args[5];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 args[4].vtype = VT_LONG;
 args[4].num = arg4;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
RefreshLists()
{
 void *fp = RP_Funcs->f[385].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
}

unsigned long
NextFuncFchunk(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[233].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
EndTypeUpdating(long arg0)
{
 void *fp = RP_Funcs->f[487].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetFchunkAttr(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[225].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
readlong(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[161].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
SetManualInsn(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[374].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

int
SetColor(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[401].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetBmaskName(long arg0,long arg1,char * arg2)
{
 void *fp = RP_Funcs->f[349].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
AddEntryPoint(long arg0,long arg1,char * arg2,long arg3)
{
 void *fp = RP_Funcs->f[235].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
RnextB0(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[186].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetNextBmask(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[328].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetFunctionName(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[207].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
LocByName(char * arg0)
{
 void *fp = RP_Funcs->f[13].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetSegAddressing(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[86].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
PrevFchunk(long arg0)
{
 void *fp = RP_Funcs->f[228].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
PrevFunction(long arg0)
{
 void *fp = RP_Funcs->f[204].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetEnumBf(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[343].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFixupTgtSel(long arg0)
{
 void *fp = RP_Funcs->f[243].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetFunctionCmt(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[208].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
SetFunctionEnd(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[202].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
NextFunction(long arg0)
{
 void *fp = RP_Funcs->f[203].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFirstIndex(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[299].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FindBinary(long arg0,long arg1,char * arg2)
{
 void *fp = RP_Funcs->f[176].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SaveBase(char * arg0,long arg1)
{
 void *fp = RP_Funcs->f[146].fp;
 value_t res;
 value_t args[2];
 args[0]._set_string(arg0);
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
ItemSize(long arg0)
{
 void *fp = RP_Funcs->f[139].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FindExplored(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[173].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
ExecIDC(char * arg0)
{
 void *fp = RP_Funcs->f[143].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
MakeLocal(long arg0,long arg1,char * arg2,char * arg3)
{
 void *fp = RP_Funcs->f[212].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 args[3]._set_string(arg3);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFixupTgtType(long arg0)
{
 void *fp = RP_Funcs->f[242].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Qword(long arg0)
{
 void *fp = RP_Funcs->f[483].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetEnumWidth(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[342].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetHashLong(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[303].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
AutoUnmark(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[194].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

int
SetEnumName(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[339].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
SetFlags(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[65].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
ord(char * arg0)
{
 void *fp = RP_Funcs->f[108].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
OpSign(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[28].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetFuncOffset(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[211].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

void
DelSelector(long arg0)
{
 void *fp = RP_Funcs->f[199].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
AskSelector(long arg0)
{
 void *fp = RP_Funcs->f[197].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetBmaskCmt(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[352].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
MakeCode(long arg0)
{
 void *fp = RP_Funcs->f[2].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Batch(long arg0)
{
 void *fp = RP_Funcs->f[63].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
DelLineNumber(long arg0)
{
 void *fp = RP_Funcs->f[287].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
AnalyzeArea(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[140].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
HideArea(long arg0,long arg1,char * arg2,char * arg3,char * arg4,long arg5)
{
 void *fp = RP_Funcs->f[392].fp;
 value_t res;
 value_t args[6];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 args[3]._set_string(arg3);
 args[4]._set_string(arg4);
 args[5].vtype = VT_LONG;
 args[5].num = arg5;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
SetMemberComment(long arg0,long arg1,char * arg2,long arg3)
{
 void *fp = RP_Funcs->f[283].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
SetSelector(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[196].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetPrevConst(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[333].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetConstEx(long arg0,long arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[325].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
Wait()
{
 void *fp = RP_Funcs->f[141].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
}

unsigned long
CreateArray(char * arg0)
{
 void *fp = RP_Funcs->f[291].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetEnumCmt(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[340].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
IsBitfield(long arg0)
{
 void *fp = RP_Funcs->f[348].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
OpOff(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[15].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
AddEnum(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[336].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetEnumCmt(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[317].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetMemberFlag(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[271].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
DelEnum(long arg0)
{
 void *fp = RP_Funcs->f[337].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetPrevStrucIdx(long arg0)
{
 void *fp = RP_Funcs->f[255].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetSourceFile(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[289].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
MakeArray(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[5].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetArrayId(char * arg0)
{
 void *fp = RP_Funcs->f[292].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetNextStrucIdx(long arg0)
{
 void *fp = RP_Funcs->f[254].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
NextAddr(long arg0)
{
 void *fp = RP_Funcs->f[131].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFchunkAttr(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[224].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FindVoid(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[169].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
PrevAddr(long arg0)
{
 void *fp = RP_Funcs->f[132].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetManualInsn(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[375].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetPrevBmask(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[329].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetMemberQty(long arg0)
{
 void *fp = RP_Funcs->f[262].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFunctionAttr(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[205].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetIdaDirectory()
{
 char *resstr;
 void *fp = RP_Funcs->f[368].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
NextNotTail(long arg0)
{
 void *fp = RP_Funcs->f[135].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetMemberSize(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[270].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Rnext0(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[185].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetBmaskName(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[350].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetArrayString(long arg0,long arg1,char * arg2)
{
 void *fp = RP_Funcs->f[296].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetEnum(char * arg0)
{
 void *fp = RP_Funcs->f[315].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetMnem(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[127].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetSegmentAttr(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[88].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
DelCodeXref(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[178].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
MakeFunction(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[200].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
AskLong(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[72].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
DelFixup(long arg0)
{
 void *fp = RP_Funcs->f[247].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

void
SetTargetAssembler(long arg0)
{
 void *fp = RP_Funcs->f[62].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
RnextB(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[182].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetSpDiff(long arg0)
{
 void *fp = RP_Funcs->f[217].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
OpStroffEx(long arg0,long arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[31].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
DfirstB(long arg0)
{
 void *fp = RP_Funcs->f[191].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
AskAddr(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[71].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetStrucNextOff(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[264].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
AppendFchunk(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[229].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
XrefType()
{
 void *fp = RP_Funcs->f[193].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 return res.num;
}

void
Refresh()
{
 void *fp = RP_Funcs->f[384].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
}

char *
SegName(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[117].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
AddSourceFile(long arg0,long arg1,char * arg2)
{
 void *fp = RP_Funcs->f[288].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
SetStrucName(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[277].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetLastIndex(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[301].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetSegBounds(long arg0,long arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[83].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Dfirst(long arg0)
{
 void *fp = RP_Funcs->f[189].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
AddSeg(long arg0,long arg1,long arg2,long arg3,long arg4,long arg5)
{
 void *fp = RP_Funcs->f[81].fp;
 value_t res;
 value_t args[6];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 args[4].vtype = VT_LONG;
 args[4].num = arg4;
 args[5].vtype = VT_LONG;
 args[5].num = arg5;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
SetLineNumber(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[285].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

int
SetFunctionAttr(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[206].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
CommentEx(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[123].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetEnumWidth(long arg0)
{
 void *fp = RP_Funcs->f[319].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
DelStrucMember(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[280].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FindData(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[171].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FirstSeg()
{
 void *fp = RP_Funcs->f[115].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
AddHotkey(char * arg0,char * arg1)
{
 void *fp = RP_Funcs->f[360].fp;
 value_t res;
 value_t args[2];
 args[0]._set_string(arg0);
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetStrucComment(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[260].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

char *
GetConstCmt(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[335].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

void
SetFixup(long arg0,long arg1,long arg2,long arg3,long arg4)
{
 void *fp = RP_Funcs->f[246].fp;
 value_t res;
 value_t args[5];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 args[4].vtype = VT_LONG;
 args[4].num = arg4;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
ParseTypes(char * arg0,long arg1)
{
 void *fp = RP_Funcs->f[398].fp;
 value_t res;
 value_t args[2];
 args[0]._set_string(arg0);
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
LoadTil(char * arg0)
{
 void *fp = RP_Funcs->f[377].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
LocByNameEx(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[110].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
writestr(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[165].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFixupTgtOff(long arg0)
{
 void *fp = RP_Funcs->f[244].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
AutoMark2(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[195].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetStrucIdx(long arg0)
{
 void *fp = RP_Funcs->f[256].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
RenameArray(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[293].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
Demangle(char * arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[373].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0]._set_string(arg0);
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetOpType(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[128].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetEnumQty()
{
 void *fp = RP_Funcs->f[312].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 return res.num;
}

void
SetInputFilePath(char * arg0)
{
 void *fp = RP_Funcs->f[364].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetStrucId(long arg0)
{
 void *fp = RP_Funcs->f[257].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
SegByBase(long arg0)
{
 void *fp = RP_Funcs->f[111].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetEnumFlag(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[341].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
DelFunction(long arg0)
{
 void *fp = RP_Funcs->f[201].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
RemoveFchunk(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[230].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
readshort(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[160].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
AltOp(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[124].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
PrevNotTail(long arg0)
{
 void *fp = RP_Funcs->f[136].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
ProcessUiAction(char * arg0,long arg1)
{
 void *fp = RP_Funcs->f[366].fp;
 value_t res;
 value_t args[2];
 args[0]._set_string(arg0);
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Exec(char * arg0)
{
 void *fp = RP_Funcs->f[365].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
IdbByte(long arg0)
{
 void *fp = RP_Funcs->f[49].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
BeginTypeUpdating(long arg0)
{
 void *fp = RP_Funcs->f[486].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetMarkedPos(long arg0)
{
 void *fp = RP_Funcs->f[249].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
DelHiddenArea(long arg0)
{
 void *fp = RP_Funcs->f[394].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
ItemHead(long arg0)
{
 void *fp = RP_Funcs->f[137].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetNextHashKey(long arg0,char * arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[309].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
SetStrucComment(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[278].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
GenFuncGdl(char * arg0,char * arg1,long arg2,long arg3,long arg4)
{
 void *fp = RP_Funcs->f[47].fp;
 value_t res;
 value_t args[5];
 args[0]._set_string(arg0);
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 args[4].vtype = VT_LONG;
 args[4].num = arg4;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
AskIdent(char * arg0,char * arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[74].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0]._set_string(arg0);
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

char *
LineA(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[121].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

char *
LineB(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[122].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
savefile(long arg0,long arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[156].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetNextFixupEA(long arg0)
{
 void *fp = RP_Funcs->f[240].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetShortPrm(long arg0)
{
 void *fp = RP_Funcs->f[354].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
RebaseProgram(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[91].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetFirstHashKey(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[308].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
SetXML(char * arg0,char * arg1,char * arg2)
{
 void *fp = RP_Funcs->f[402].fp;
 value_t res;
 value_t args[3];
 args[0]._set_string(arg0);
 args[1]._set_string(arg1);
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetSpDiff(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[218].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetLongPrm(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[356].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
MakeNameEx(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[3].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetLongPrm(long arg0)
{
 void *fp = RP_Funcs->f[353].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetSpd(long arg0)
{
 void *fp = RP_Funcs->f[216].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetStrucIdByName(char * arg0)
{
 void *fp = RP_Funcs->f[258].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFirstConst(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[330].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetStrucName(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[259].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
ItemEnd(long arg0)
{
 void *fp = RP_Funcs->f[138].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetLineNumber(long arg0)
{
 void *fp = RP_Funcs->f[286].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
DelHotkey(char * arg0)
{
 void *fp = RP_Funcs->f[361].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
AskSeg(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[73].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
MakeAlign(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[372].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetProcessorType(char * arg0,long arg1)
{
 void *fp = RP_Funcs->f[61].fp;
 value_t res;
 value_t args[2];
 args[0]._set_string(arg0);
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetNextIndex(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[300].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
DelConstEx(long arg0,long arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[345].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FindText(long arg0,long arg1,long arg2,long arg3,char * arg4)
{
 void *fp = RP_Funcs->f[175].fp;
 value_t res;
 value_t args[5];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 args[4]._set_string(arg4);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetMarkComment(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[250].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
DelStruc(long arg0)
{
 void *fp = RP_Funcs->f[275].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
AskStr(char * arg0,char * arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[69].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0]._set_string(arg0);
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetFchunkReferer(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[226].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
MoveSegm(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[90].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFirstMember(long arg0)
{
 void *fp = RP_Funcs->f[265].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
SegByName(char * arg0)
{
 void *fp = RP_Funcs->f[0].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetLocalType(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[380].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
SelStart()
{
 void *fp = RP_Funcs->f[113].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFirstBmask(long arg0)
{
 void *fp = RP_Funcs->f[326].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetReg(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[67].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetLocalTypeName(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[382].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

char *
NameEx(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[119].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetEntryOrdinal(long arg0)
{
 void *fp = RP_Funcs->f[237].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Rfirst(long arg0)
{
 void *fp = RP_Funcs->f[179].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FindCode(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[170].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetHashLong(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[305].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
OpNot(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[29].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
AddUserStkPnt(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[219].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetEnumName(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[316].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetConstEnum(long arg0)
{
 void *fp = RP_Funcs->f[324].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
DelHashElement(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[307].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetHiddenArea(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[393].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetHashString(long arg0,char * arg1,char * arg2)
{
 void *fp = RP_Funcs->f[304].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
RenameEntryPoint(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[239].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Til2Idb(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[378].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetMinSpd(long arg0)
{
 void *fp = RP_Funcs->f[223].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetConstBmask(long arg0)
{
 void *fp = RP_Funcs->f[323].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetPrevHashKey(long arg0,char * arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[311].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
writeshort(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[162].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
AddStrucEx(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[273].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
ApplySig(char * arg0)
{
 void *fp = RP_Funcs->f[387].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
ChangeConfig(char * arg0)
{
 void *fp = RP_Funcs->f[359].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetPrevFixupEA(long arg0)
{
 void *fp = RP_Funcs->f[241].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
strfill(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[102].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
SetBmaskCmt(long arg0,long arg1,char * arg2,long arg3)
{
 void *fp = RP_Funcs->f[351].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
AddConstEx(long arg0,char * arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[344].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetCurrentLine()
{
 char *resstr;
 void *fp = RP_Funcs->f[112].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

void
SetFunctionCmt(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[209].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetFixupTgtDispl(long arg0)
{
 void *fp = RP_Funcs->f[245].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
GenCallGdl(char * arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[48].fp;
 value_t res;
 value_t args[3];
 args[0]._set_string(arg0);
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
MK_FP(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[1].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetArrayFormat(long arg0,long arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[376].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
AskFile(long arg0,char * arg1,char * arg2)
{
 char *resstr;
 void *fp = RP_Funcs->f[70].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
MakeStr(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[40].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetType(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[397].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
RecalcSpd(long arg0)
{
 void *fp = RP_Funcs->f[222].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
MakeUnknown(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[39].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
FindUnexplored(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[172].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetFchunkOwner(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[231].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FirstFuncFchunk(long arg0)
{
 void *fp = RP_Funcs->f[232].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetTrueNameEx(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[120].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
SetMemberName(long arg0,long arg1,char * arg2)
{
 void *fp = RP_Funcs->f[281].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
Exit(long arg0)
{
 void *fp = RP_Funcs->f[145].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetPrevIndex(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[302].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetStringType(long arg0)
{
 void *fp = RP_Funcs->f[388].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
OpOffEx(long arg0,long arg1,long arg2,long arg3,long arg4,long arg5)
{
 void *fp = RP_Funcs->f[33].fp;
 value_t res;
 value_t args[6];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 args[4].vtype = VT_LONG;
 args[4].num = arg4;
 args[5].vtype = VT_LONG;
 args[5].num = arg5;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetLastConst(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[331].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetEnumIdx(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[338].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetSegDefReg(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[66].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
DeleteArray(long arg0)
{
 void *fp = RP_Funcs->f[294].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetEnumIdx(long arg0)
{
 void *fp = RP_Funcs->f[314].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
SetStorageType(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[89].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

void
Add_dref(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[187].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
NextSeg(long arg0)
{
 void *fp = RP_Funcs->f[116].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetType(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[395].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

char *
Atoa(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[106].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
SetConstName(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[346].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetMemberStrId(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[272].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetMemberComment(long arg0,long arg1,long arg2)
{
 char *resstr;
 void *fp = RP_Funcs->f[269].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

unsigned long
GetCustomDataType(char * arg0)
{
 void *fp = RP_Funcs->f[484].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetLocalType(long arg0,long arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[381].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

void
ExtLinA(long arg0,long arg1,char * arg2)
{
 void *fp = RP_Funcs->f[41].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

void
ExtLinB(long arg0,long arg1,char * arg2)
{
 void *fp = RP_Funcs->f[42].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2]._set_string(arg2);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
}

unsigned long
GetMemberOffset(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[267].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Rnext(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[181].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetFirstStrucIdx()
{
 void *fp = RP_Funcs->f[252].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 return res.num;
}

char *
GuessType(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[396].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

void
DeleteAll()
{
 void *fp = RP_Funcs->f[80].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
}

int
OpStkvar(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[32].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetConstByName(char * arg0)
{
 void *fp = RP_Funcs->f[321].fp;
 value_t res;
 value_t args[1];
 args[0]._set_string(arg0);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetLastBmask(long arg0)
{
 void *fp = RP_Funcs->f[327].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
Rfirst0(long arg0)
{
 void *fp = RP_Funcs->f[183].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
NextFchunk(long arg0)
{
 void *fp = RP_Funcs->f[227].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetHashString(long arg0,char * arg1)
{
 char *resstr;
 void *fp = RP_Funcs->f[306].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
DelSourceFile(long arg0)
{
 void *fp = RP_Funcs->f[290].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
SetSegmentAttr(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[87].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetnEnum(long arg0)
{
 void *fp = RP_Funcs->f[313].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetColor(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[400].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
MakeFrame(long arg0,long arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[215].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
writelong(long arg0,long arg1,long arg2)
{
 void *fp = RP_Funcs->f[163].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
IsUnion(long arg0)
{
 void *fp = RP_Funcs->f[274].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetStrucSize(long arg0)
{
 void *fp = RP_Funcs->f[261].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
RfirstB(long arg0)
{
 void *fp = RP_Funcs->f[180].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
GetMaxLocalType()
{
 void *fp = RP_Funcs->f[379].fp;
 value_t res;
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 return res.num;
}

int
SetConstCmt(long arg0,char * arg1,long arg2)
{
 void *fp = RP_Funcs->f[347].fp;
 value_t res;
 value_t args[3];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
NextHead(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[133].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
FindSelector(long arg0)
{
 void *fp = RP_Funcs->f[198].fp;
 value_t res;
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
PrevHead(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[134].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

char *
GetLastHashKey(long arg0)
{
 char *resstr;
 void *fp = RP_Funcs->f[310].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 value_t args[1];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

char *
GetInputMD5()
{
 char *resstr;
 void *fp = RP_Funcs->f[370].fp;
 value_t res;
	memset(&res, 0, sizeof(res));
 __asm {
   lea eax, res
   push eax
   xor eax, eax
   push eax
   call [fp]
}
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
}

int
SetSegClass(long arg0,char * arg1)
{
 void *fp = RP_Funcs->f[85].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1]._set_string(arg1);
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

unsigned long
SetStrucIdx(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[276].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
SetCharPrm(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[358].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
DelSeg(long arg0,long arg1)
{
 void *fp = RP_Funcs->f[82].fp;
 value_t res;
 value_t args[2];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

int
MakeData(long arg0,long arg1,long arg2,long arg3)
{
 void *fp = RP_Funcs->f[7].fp;
 value_t res;
 value_t args[4];
 args[0].vtype = VT_LONG;
 args[0].num = arg0;
 args[1].vtype = VT_LONG;
 args[1].num = arg1;
 args[2].vtype = VT_LONG;
 args[2].num = arg2;
 args[3].vtype = VT_LONG;
 args[3].num = arg3;
 __asm {
   lea eax, res
   push eax
   lea eax, args
   push eax
   call [fp]
}
 return res.num;
}

