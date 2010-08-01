#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <bytes.hpp>
#include <name.hpp>
#include <offset.hpp>

//#include <rp/rp.hpp>
#include "iid.h"
#include "classtree.hpp"
#include "imp_dlls.h"
#include "mfc_cfg.h"
#include "tlb_buben.h"

extern void idaapi rp_set_comment(ea_t, const char *, bool, bool = false);
bool idaapi check_for_available_space(ea_t, ulong);

/******************** CONSTANTS *******************/
char MFC_comment[] = "Plugin for MFC support";
char MFC_help[] =
 "MFC support plugin\n"
 "\n"
 "Shows some info about various MFC structures\n"
 "Written by RedPlait (redplait@gmail.com)"
;
char MFC_wanted_name[] = "MFC support plugin";
char MFC_wanted_hotkey[] = "Alt-M";

/* some Winblows messages */
#ifndef WM_COMMAND
# define WM_COMMAND	0x111
#endif

#ifndef WM_NOTIFY
# define WM_NOTIFY	0x4E
#endif

#ifndef WM_REFLECT_BASE
# define WM_REFLECT_BASE 0xBC00
#endif

char *OLECMDID_name(ulong id)
{
  static char *cmdid_names[] = {
/*  0 */ NULL,
/*  1 */ "OLECMDID_OPEN",
/*  2 */ "OLECMDID_NEW",
/*  3 */ "OLECMDID_SAVE",
/*  4 */ "OLECMDID_SAVEAS",
/*  5 */ "OLECMDID_SAVECOPYAS",
/*  6 */ "OLECMDID_PRINT",
/*  7 */ "OLECMDID_PRINTPREVIEW",
/*  8 */ "OLECMDID_PAGESETUP",
/*  9 */ "OLECMDID_SPELL",
/* 10 */ "OLECMDID_PROPERTIES",
/* 11 */ "OLECMDID_CUT",
/* 12 */ "OLECMDID_COPY",
/* 13 */ "OLECMDID_PASTE",
/* 14 */ "OLECMDID_PASTESPECIAL",
/* 15 */ "OLECMDID_UNDO",
/* 16 */ "OLECMDID_REDO",
/* 17 */ "OLECMDID_SELECTALL",
/* 18 */ "OLECMDID_CLEARSELECTION",
/* 19 */ "OLECMDID_ZOOM",
/* 20 */ "OLECMDID_GETZOOMRANGE",
/* 21 */ "OLECMDID_UPDATECOMMANDS",
/* 22 */ "OLECMDID_REFRESH",
/* 23 */ "OLECMDID_STOP",
/* 24 */ "OLECMDID_HIDETOOLBARS",
/* 25 */ "OLECMDID_SETPROGRESSMAX",
/* 26 */ "OLECMDID_SETPROGRESSPOS",
/* 27 */ "OLECMDID_SETPROGRESSTEXT",
/* 28 */ "OLECMDID_SETTITLE",
/* 29 */ "OLECMDID_SETDOWNLOADSTATE",
/* 30 */ "OLECMDID_STOPDOWNLOAD",
/* 31 */ "OLECMDID_ONTOOLBARACTIVATED",
/* 32 */ "OLECMDID_FIND",
/* 33 */ "OLECMDID_DELETE",
/* 34 */ "OLECMDID_HTTPEQUIV",
/* 35 */ "OLECMDID_HTTPEQUIV_DONE",
/* 36 */ "OLECMDID_ENABLE_INTERACTION",
/* 37 */ "OLECMDID_ONUNLOAD",
/* 38 */ "OLECMDID_PROPERTYBAG2",
/* 39 */ "OLECMDID_PREREFRESH",
/* 40 */ "OLECMDID_SHOWSCRIPTERROR",
/* 41 */ "OLECMDID_SHOWMESSAGE",
/* 42 */ "OLECMDID_SHOWFIND",
/* 43 */ "OLECMDID_SHOWPAGESETUP",
/* 44 */ "OLECMDID_SHOWPRINT",
/* 45 */ "OLECMDID_CLOSE",
/* 46 */ "OLECMDID_ALLOWUILESSSAVEAS",
/* 47 */ "OLECMDID_DONTDOWNLOADCSS",
/* 48 */ "OLECMDID_UPDATEPAGESTATUS",
/* 49 */ "OLECMDID_PRINT2",
/* 50 */ "OLECMDID_PRINTPREVIEW2",
/* 51 */ "OLECMDID_SETPRINTTEMPLATE",
/* 52 */ "OLECMDID_GETPRINTTEMPLATE",
/* 53 */ NULL,
/* 54 */ NULL,
/* 55 */ "OLECMDID_PAGEACTIONBLOCKED",
/* 56 */ "OLECMDID_PAGEACTIONUIQUERY",
/* 57 */ "OLECMDID_FOCUSVIEWCONTROLS",
/* 58 */ "OLECMDID_FOCUSVIEWCONTROLSQUERY",
/* 59 */ "OLECMDID_SHOWPAGEACTIONMENU",
 };
 if ( id < sizeof(cmdid_names) / sizeof(cmdid_names[0]) )
  return cmdid_names[id];
 return NULL;
}

ulong
process_WM(ea_t adr)
{
  ulong res = get_long(adr);
  char *name = NULL;
  doDwrd(adr,4);
  switch(res)
  {
    case 0x0: name = "WM_NULL";
     break;
    case 0x1: name = "WM_CREATE";
     break;
    case 0x2: name = "WM_DESTROY";
     break;
    case 0x3: name = "WM_MOVE";
     break;
    case 0x5: name = "WM_SIZE";
     break;
    case 0x6: name = "WM_ACTIVATE";
     break;
    case 0x7: name = "WM_SETFOCUS";
     break;
    case 0x8: name = "WM_KILLFOCUS";
     break;
    case 0xA: name = "WM_ENABLE";
     break;
    case 0xB: name = "WM_SETREDRAW";
     break;
    case 0xC: name = "WM_SETTEXT";
     break;
    case 0xD: name = "WM_GETTEXT";
     break;
    case 0xE: name = "WM_GETTEXTLENGTH";
     break;
    case 0xF: name = "WM_PAINT";
     break;
    case 0x10: name = "WM_CLOSE";
     break;
    case 0x11: name = "WM_QUERYENDSESSION";
     break;
    case 0x12: name = "WM_QUIT";
     break;
    case 0x13: name = "WM_QUERYOPEN";
     break;
    case 0x14: name = "WM_ERASEBKGND";
     break;
    case 0x15: name = "WM_SYSCOLORCHANGE";
     break;
    case 0x16: name = "WM_ENDSESSION";
     break;
    case 0x18: name = "WM_SHOWWINDOW";
     break;
    case 0x19: name = "WM_CTLCOLOR"; /* undocumented ? */
     break;
    case WM_REFLECT_BASE+0x19: name = "WM_CTLCOLOR_REFLECT";
     break;
    case 0x1A: name = "WM_WININICHANGE";
     break;
    case 0x1B: name = "WM_DEVMODECHANGE";
     break;
    case 0x1C: name = "WM_ACTIVATEAPP";
     break;
    case 0x1D: name = "WM_FONTCHANGE";
     break;
    case 0x1E: name = "WM_TIMECHANGE";
     break;
    case 0x1F: name = "WM_CANCELMODE";
     break;
    case 0x20: name = "WM_SETCURSOR";
     break;
    case 0x21: name = "WM_MOUSEACTIVATE";
     break;
    case 0x22: name = "WM_CHILDACTIVATE";
     break;
    case 0x23: name = "WM_QUEUESYNC";
     break;
    case 0x24: name = "WM_GETMINMAXINFO";
     break;
    case 0x26: name = "WM_PAINTICON";
     break;
    case 0x27: name = "WM_ICONERASEBKGND";
     break;
    case 0x28: name = "WM_NEXTDLGCTL";
     break;
    case 0x2A: name = "WM_SPOOLERSTATUS";
     break;
    case 0x2B: name = "WM_DRAWITEM";
     break;
    case WM_REFLECT_BASE + 0x2B: name = "WM_DRAWITEM_REFLECT";
     break;
    case 0x2C: name = "WM_MEASUREITEM";
     break;
    case WM_REFLECT_BASE + 0x2C: name = "WM_MEASUREITEM_REFLECT";
     break;
    case 0x2D: name = "WM_DELETEITEM";
     break;
    case WM_REFLECT_BASE + 0x2D: name = "WM_DELETEITEM_REFLECT";
     break;
    case 0x2E: name = "WM_VKEYTOITEM";
     break;
    case WM_REFLECT_BASE + 0x2E: name = "WM_VKEYTOITEM_REFLECT";
     break;
    case 0x2F: name = "WM_CHARTOITEM";
     break;
    case WM_REFLECT_BASE + 0x2F: name = "WM_CHARTOITEM_REFLECT";
     break;
    case 0x30: name = "WM_SETFONT";
     break;
    case 0x31: name = "WM_GETFONT";
     break;
    case 0x32: name = "WM_SETHOTKEY";
     break;
    case 0x33: name = "WM_GETHOTKEY";
     break;
    case 0x37: name = "WM_QUERYDRAGICON";
     break;
    case 0x39: name = "WM_COMPAREITEM";
     break;
    case WM_REFLECT_BASE + 0x39: name = "WM_COMPAREITEM_REFLECT";
     break;
    case 0x3D: name = "WM_GETOBJECT"; /* if WINVER >= 0x0500 */
     break;
    case 0x41: name = "WM_COMPACTING";
     break;
    case 0x44: name = "WM_COMMNOTIFY (not supported)";
     break;
    case 0x46: name = "WM_WINDOWPOSCHANGING";
     break;
    case 0x47: name = "WM_WINDOWPOSCHANGED";
     break;
    case 0x48: name = "WM_POWER";
     break;
    case 0x4A: name = "WM_COPYDATA";
     break;
    case 0x4B: name = "WM_CANCELJOURNAL";
     break;
/* will be processed more complex way 
 *  case 0x4E: name = "WM_NOTIFY";
 *   break;
 */
    case 0x50: name = "WM_INPUTLANGCHANGEREQUEST";
     break;
    case 0x51: name = "WM_INPUTLANGCHANGE";
     break;
    case 0x52: name = "WM_TCARD";
     break;
    case 0x53: name = "WM_HELP";
     break;
    case 0x54: name = "WM_USERCHANGED";
     break;
    case 0x55: name = "WM_NOTIFYFORMAT";
     break;
    case 0x7B: name = "WM_CONTEXTMENU";
     break;
    case 0x7C: name = "WM_STYLECHANGING";
     break;
    case 0x7D: name = "WM_STYLECHANGED";
     break;
    case 0x7E: name = "WM_DISPLAYCHANGE";
     break;
    case 0x7F: name = "WM_GETICON";
     break;
    case 0x80: name = "WM_SETICON";
     break;
    case 0x81: name = "WM_NCCREATE";
     break;
    case 0x82: name = "WM_NCDESTROY";
     break;
    case 0x83: name = "WM_NCCALCSIZE";
     break;
    case 0x84: name = "WM_NCHITTEST";
     break;
    case 0x85: name = "WM_NCPAINT";
     break;
    case 0x86: name = "WM_NCACTIVATE";
     break;
    case 0x87: name = "WM_GETDLGCODE";
     break;
    case 0x88: name = "WM_SYNCPAINT";
     break;
    case 0xA0: name = "WM_NCMOUSEMOVE";
     break;
    case 0xA1: name = "WM_NCLBUTTONDOWN";
     break;
    case 0xA2: name = "WM_NCLBUTTONUP";
     break;
    case 0xA3: name = "WM_NCLBUTTONDBLCLK";
     break;
    case 0xA4: name = "WM_NCRBUTTONDOWN";
     break;
    case 0xA5: name = "WM_NCRBUTTONUP";
     break;
    case 0xA6: name = "WM_NCRBUTTONDBLCLK";
     break;
    case 0xA7: name = "WM_NCMBUTTONDOWN";
     break;
    case 0xA8: name = "WM_NCMBUTTONUP";
     break;
    case 0xA9: name = "WM_NCMBUTTONDBLCLK";
     break;
    case 0x100: name = "WM_KEYDOWN";
     break;
    case 0x101: name = "WM_KEYUP";
     break;
    case 0x102: name = "WM_CHAR";
     break;
    case 0x103: name = "WM_DEADCHAR";
     break;
    case 0x104: name = "WM_SYSKEYDOWN";
     break;
    case 0x105: name = "WM_SYSKEYUP";
     break;
    case 0x106: name = "WM_SYSCHAR";
     break;
    case 0x107: name = "WM_SYSDEADCHAR";
     break;
    case 0x10D: name = "WM_IME_STARTCOMPOSITION";
     break;
    case 0x10E: name = "WM_IME_ENDCOMPOSITION";
     break;
    case 0x10F: name = "WM_IME_COMPOSITION";
     break;
    case 0x110: name = "WM_INITDIALOG";
     break;
/* will be processed more complex way 
 *  case 0x111: name = "WM_COMMAND";
 *   break;
 */
    case 0x112: name = "WM_SYSCOMMAND";
     break;
    case 0x113: name = "WM_TIMER";
     break;
    case 0x114: name = "WM_HSCROLL";
     break;
    case WM_REFLECT_BASE + 0x114: name = "WM_HSCROLL_REFLECT";
     break;
    case 0x115: name = "WM_VSCROLL";
     break;
    case WM_REFLECT_BASE + 0x115: name = "WM_VSCROLL_REFLECT";
     break;
    case 0x116: name = "WM_INITMENU";
     break;
    case 0x117: name = "WM_INITMENUPOPUP";
     break;
    case 0x11F: name = "WM_MENUSELECT";
     break;
    case 0x120: name = "WM_MENUCHAR";
     break;
    case 0x121: name = "WM_ENTERIDLE";
     break;
/* Start WINVER >= 0x0500 */
    case 0x122: name = "WM_MENURBUTTONUP";
     break;
    case 0x123: name = "WM_MENUDRAG";
     break;
    case 0x124: name = "WM_MENUGETOBJECT";
     break;
    case 0x125: name = "WM_UNINITMENUPOPUP";
     break;
    case 0x126: name = "WM_MENUCOMMAND";
     break;
/* End WINVER >= 0x0500 */    
    case 0x132: name = "WM_CTLCOLORMSGBOX";
     break;
    case 0x133: name = "WM_CTLCOLOREDIT";
     break;
    case 0x134: name = "WM_CTLCOLORLISTBOX";
     break;
    case 0x135: name = "WM_CTLCOLORBTN";
     break;
    case 0x136: name = "WM_CTLCOLORDLG";
     break;
    case 0x137: name = "WM_CTLCOLORSCROLLBAR";
     break;
    case 0x138: name = "WM_CTLCOLORSTATIC";
     break;
    case 0x200: name = "WM_MOUSEMOVE";
     break;
    case 0x201: name = "WM_LBUTTONDOWN";
     break;
    case 0x202: name = "WM_LBUTTONUP";
     break;
    case 0x203: name = "WM_LBUTTONDBLCLK";
     break;
    case 0x204: name = "WM_RBUTTONDOWN";
     break;
    case 0x205: name = "WM_RBUTTONUP";
     break;
    case 0x206: name = "WM_RBUTTONDBLCLK";
     break;
    case 0x207: name = "WM_MBUTTONDOWN";
     break;
    case 0x208: name = "WM_MBUTTONUP";
     break;
    case 0x209: name = "WM_MBUTTONDBLCLK";
     break;
    case 0x20A: name = "WM_MOUSEWHEEL";
     break;
    case 0x210: name = "WM_PARENTNOTIFY";
     break;
    case WM_REFLECT_BASE + 0x210: name = "WM_PARENTNOTIFY_REFLECT";
     break;
    case 0x211: name = "WM_ENTERMENULOOP";
     break;
    case 0x212: name = "WM_EXITMENULOOP";
     break;
    case 0x213: name = "WM_NEXTMENU";
     break;
    case 0x214: name = "WM_SIZING";
     break;
    case 0x215: name = "WM_CAPTURECHANGED";
     break;
    case 0x216: name = "WM_MOVING";
     break;
    case 0x218: name = "WM_POWERBROADCAST";
     break;
    case 0x219: name = "WM_DEVICECHANGE";
     break;
    case 0x220: name = "WM_MDICREATE";
     break;
    case 0x221: name = "WM_MDIDESTROY";
     break;
    case 0x222: name = "WM_MDIACTIVATE";
     break;
    case 0x223: name = "WM_MDIRESTORE";
     break;
    case 0x224: name = "WM_MDINEXT";
     break;
    case 0x225: name = "WM_MDIMAXIMIZE";
     break;
    case 0x226: name = "WM_MDITILE";
     break;
    case 0x227: name = "WM_MDICASCADE";
     break;
    case 0x228: name = "WM_MDIICONARRANGE";
     break;
    case 0x229: name = "WM_MDIGETACTIVE";
     break;
    case 0x230: name = "WM_MDISETMENU";
     break;
    case 0x231: name = "WM_ENTERSIZEMOVE";
     break;
    case 0x232: name = "WM_EXITSIZEMOVE";
     break;
    case 0x233: name = "WM_DROPFILES";
     break;
    case 0x234: name = "WM_MDIREFRESHMENU";
     break;
    case 0x281: name = "WM_IME_SETCONTEXT";
     break;
    case 0x282: name = "WM_IME_NOTIFY";
     break;
    case 0x283: name = "WM_IME_CONTROL";
     break;
    case 0x284: name = "WM_IME_COMPOSITIONFULL";
     break;
    case 0x285: name = "WM_IME_SELECT";
     break;
    case 0x286: name = "WM_IME_CHAR";
     break;
    case 0x288: name = "WM_IME_REQUEST"; /* if WINVER >= 0x0500 */
     break;
    case 0x290: name = "WM_IME_KEYDOWN";
     break;
    case 0x291: name = "WM_IME_KEYUP";
     break;
    case 0x2A1: name = "WM_MOUSEHOVER";
     break;
    case 0x2A3: name = "WM_MOUSELEAVE";
     break;
    case 0x300: name = "WM_CUT";
     break;
    case 0x301: name = "WM_COPY";
     break;
    case 0x302: name = "WM_PASTE";
     break;
    case 0x303: name = "WM_CLEAR";
     break;
    case 0x304: name = "WM_UNDO";
     break;
    case 0x305: name = "WM_RENDERFORMAT";
     break;
    case 0x306: name = "WM_RENDERALLFORMATS";
     break;
    case 0x307: name = "WM_DESTROYCLIPBOARD";
     break;
    case 0x308: name = "WM_DRAWCLIPBOARD";
     break;
    case 0x309: name = "WM_PAINTCLIPBOARD";
     break;
    case 0x30A: name = "WM_VSCROLLCLIPBOARD";
     break;
    case 0x30B: name = "WM_SIZECLIPBOARD";
     break;
    case 0x30C: name = "WM_ASKCBFORMATNAME";
     break;
    case 0x30D: name = "WM_CHANGECBCHAIN";
     break;
    case 0x30E: name = "WM_HSCROLLCLIPBOARD";
     break;
    case 0x30F: name = "WM_QUERYNEWPALETTE";
     break;
    case 0x310: name = "WM_PALETTEISCHANGING";
     break;
    case 0x311: name = "WM_PALETTECHANGED";
     break;
    case 0x312: name = "WM_HOTKEY";
     break;
    case 0x317: name = "WM_PRINT";
     break;
    case 0x318: name = "WM_PRINTCLIENT";
     break;
    // 30 Apr 2003 - ripped from VC++7
    case 0x319: name = "WM_APPCOMMAND";
     break;
    case 0x31A: name = "WM_THEMECHANGED";
     break;
    // 22 Apr 2003 - ripped from AfxPriv.h (Internal AFX Windows messages)
    case 0x360: name = "WM_QUERYAFXWNDPROC";
     break;
    case 0x361: name = "WM_SIZEPARENT";
     break;
    case 0x362: name = "WM_SETMESSAGESTRING";
     break;
    case 0x363: name = "WM_IDLEUPDATECMDUI";
     break;
    case 0x364: name = "WM_INITIALUPDATE";
     break;
    case 0x365: name = "WM_COMMANDHELP";
     break;
    case 0x366: name = "WM_HELPHITTEST";
     break;
    case 0x367: name = "WM_EXITHELPMODE";
     break;
    case 0x368: name = "WM_RECALCPARENT";
     break;
    case 0x369: name = "WM_SIZECHILD";
     break;
    case 0x36A: name = "WM_KICKIDLE";
     break;
    case 0x36B: name = "WM_QUERYCENTERWND";
     break;
    case 0x36C: name = "WM_DISABLEMODAL";
     break;
    case 0x36D: name = "WM_FLOATSTATUS";
     break;
    case 0x36E: name = "WM_ACTIVATETOPLEVEL";
     break;
    case 0x36F: name = "WM_QUERY3DCONTROLS";
     break;
    case 0x373: name = "WM_SOCKET_NOTIFY";
     break;
    case 0x374: name = "WM_SOCKET_DEAD";
     break;
    case 0x375: name = "WM_POPMESSAGESTRING";
     break;
//    case 0x376: name = "WM_HELPPROMPTADDR";
//     break;
    case 0x376: name = "WM_OCC_LOADFROMSTREAM";
     break;
    case 0x377: name = "WM_OCC_LOADFROMSTORAGE";
     break;
    case 0x378: name = "WM_OCC_INITNEW";
     break;
    case 0x379: name = "WM_QUEUE_SENTINEL";
     break;
    case 0x37A: name = "WM_OCC_LOADFROMSTREAM_EX";
     break;
    case 0x37B: name = "WM_OCC_LOADFROMSTORAGE_EX";
     break;
    case 0x37F: name = "WM_FORWARDMSG";
     break;
  }
  if ( NULL != res )
   rp_set_comment(adr, name, false);
  return res;
}

void
process_Sig(ea_t adr, ulong what)
{
  const char *sigs[] = {
/*  1 AfxSig_bD */	"BOOL (CDC*)",
/*  2 AfxSig_bb */	"BOOL (BOOL)",
/*  3 AfxSig_bWww */	"BOOL (CWnd*, UINT, UINT)",
/*  4 AfxSig_hDWw */	"HBRUSH (CDC*, CWnd*, UINT)",
/*  5 AfxSig_hDw */	"HBRUSH (CDC*, UINT)",
/*  6 AfxSig_iwWw */	"int (UINT, CWnd*, UINT)",
/*  7 AfxSig_iww */	"int (UINT, UINT)",
/*  8 AfxSig_iWww */	"int (CWnd*, UINT, UINT)",
/*  9 AfxSig_is */	"int (LPTSTR)",
/* 10 AfxSig_lwl */	"LRESULT (WPARAM, LPARAM)",
/* 11 AfxSig_lwwM */	"LRESULT (UINT, UINT, CMenu*)",
/* 12 AfxSig_vv */	"void (void)",
/* 13 AfxSig_vw */	"void (UINT)",
/* 14 AfxSig_vww */	"void (UINT, UINT)",
/* 15 AfxSig_vvii */	"void (int, int)",
/* 16 AfxSig_vwww */	"void (UINT, UINT, UINT)",
/* 17 AfxSig_vwii */    "void (UINT, int, int)",
/* 18 AfxSig_vwl */	"void (UINT, LPARAM)",
/* 19 AfxSig_vbWW */	"void (BOOL, CWnd*, CWnd*)",
/* 20 AfxSig_vD */	"void (CDC*)",
/* 21 AfxSig_vM */	"void (CMenu*)",
/* 22 AfxSig_vMwb */	"void (CMenu*, UINT, BOOL)",
/* 23 AfxSig_vW */	"void (CWnd*)",
/* 24 AfxSig_vWww */	"void (CWnd*, UINT, UINT)",
/* 25 AfxSig_vWp */	"void (CWnd*, CPoint)",
/* 26 AfxSig_vWh */	"void (CWnd*, HANDLE)",
/* 27 AfxSig_vwW */	"void (UINT, CWnd*)",
/* 28 AfxSig_vwWb */	"void (UINT, CWnd*, BOOL)",
/* 29 AfxSig_vwwW */	"void (UINT, UINT, CWnd*)",
/* 30 AfxSig_vwwx */	"void (UINT, UINT)",
/* 31 AfxSig_vs */	"void (LPTSTR)",
/* 32 AfxSig_vOWNER */	"void (int, LPTSTR)",
/* 33 AfxSig_iis */	"int (int, LPTSTR)",
/* 34 AfxSig_wp */	"UINT (CPoint)",
/* 35 AfxSig_wv */	"UINT (void)",
/* 36 AfxSig_vPOS */	"void (WINDOWPOS*)",
/* 37 AfxSig_vCALC */	"void (BOOL, NCCALCSIZE_PARAMS*)",
/* 38 AfxSig_vNMHDRpl */"void (NMHDR*, LRESULT*)",
/* 39 AfxSig_bNMHDRpl */"BOOL (NMHDR*, LRESULT*)",
/* 40 AfxSig_vwNMHDRpl */ "void (UINT, NMHDR*, LRESULT*)",
/* 41 AfxSig_bwNMHDRpl */ "BOOL (UINT, NMHDR*, LRESULT*)",
/* 42 AfxSig_bHELPINFO */ "BOOL (HELPINFO*)",
/* 43 AfxSig_vwSIZING */"void (UINT, LPRECT)",
/* 44 AfxSig_cmdui */	"void (CCmdUI*)",
/* 45 AfxSig_cmduiw */	"void (CCmdUI*, UINT)",
/* 46 AfxSig_vpv */	"void (void*)",
/* 47 AfxSig_bpv */	"BOOL (void*)",
/* 48 AfxSig_vwwh */	"void (UINT, UINT, HANDLE)",
/* 49 AfxSig_vwp */	"void (UINT, CPoint)",
/* 50 AfxSig_vW2 */	"void (CWnd*) (CWnd* comes from lParam)",
/* 51 AfxSig_bWCDS */	"BOOL (CWnd*, COPYDATASTRUCT*)",
/* 52 AfxSig_bwsp */	"BOOL (UINT, short, CPoint)",
/* 53 AfxSig_vws */	NULL
  };
  const int sigs_size = sizeof(sigs)/sizeof(sigs[0]);

  if ( what < 1 || what >= sigs_size )
   return;
  rp_set_comment(adr, sigs[what-1], false);
}

/* Собственно, идея проста как мычание коровы - предполагаем, что стоим
 * на начале таблицы обработчиков, идём с текущего адреса и пока nSig != 0
 * или пока не вылетим за пределы сегмента
 * Сама структура AFX_MESSAGE_ENTRY выглядит так:
 * (+ 0) UINT nMessage
 * (+ 4) UINT nCode
 * (+ 8) UINT nID
 * (+12) UINT nLastID
 * (+16) UINT nSig
 * (+20) UINT pfn
 * Вообще конечно можно было бы оформить её в виде структуры IDA (add_struc),
 * но я понятия не имею, как должен выглядеть typeinfo_t в вызове
 * add_struc_member. А Ильфак всё-равно не ответит :-)
 */
void
process_AfxMessages(ea_t curr_ea)
{
   const char *first_id = "FirstID",
	      *last_id = "LastID",
	      *ctrl_id = "ControlID",
	      *n_code = "Notify Code";

   segment_t *sg = getseg(curr_ea);
   if ( NULL == sg )
   {
     warning("You are now not in a segment");
     return;
   }
   ulong nMessage, nCode, nID, nLastID, nSig, pfn;
   while( curr_ea < sg->endEA )
   {
     nSig = get_long(curr_ea + 16);
     if (!nSig)
      break;
     doDwrd(curr_ea + 16,4);

     nMessage = process_WM(curr_ea);
     /* for detail description see AfxMsg_.h from MFC includes */
     if ( (ulong)-1 != nMessage && nMessage < 0xC000 )
      process_Sig(curr_ea + 16, nSig);

     nCode = get_long(curr_ea + 4);
     doDwrd(curr_ea + 4,4);

     nID = get_long(curr_ea + 8);
     doDwrd(curr_ea + 8,4);

     nLastID = get_long(curr_ea + 12);
     doDwrd(curr_ea + 12,4);

     if ( 0xC002 == nMessage )
     {
       /* OLE verbs */
       if ( (ulong)-1 != nSig )
       {
         rp_set_comment(curr_ea, "ON_OLEVERB",false);
         add_dref(curr_ea + 16, nSig, dr_O);
         op_offset(curr_ea + 16, OPND_MASK, REF_OFF32, nSig);
       } else {
         char *verb_name = NULL;
         rp_set_comment(curr_ea, "ON_STDOLEVERB",false);
         switch(nID)
         {
           case 0: verb_name = "PRIMARY";
            break;
           case (ulong)-1: verb_name = "SHOW";
            break;
           case (ulong)-2: verb_name = "OPEN";
            break;
           case (ulong)-3: verb_name = "HIDE";
	    break;
	   case (ulong)-4: verb_name = "UIACTIVATE";
	    break;
	   case (ulong)-5: verb_name = "INPLACEACTIVATE";
	    break;
	   case (ulong)-6: verb_name = "DISCARDUNDOSTATE";
	    break;
         }
         if ( NULL != verb_name )
          rp_set_comment(curr_ea + 8, verb_name, false);
         else
          rp_set_comment(curr_ea + 8, "VerbID", false);
       }
     }
     if ( 0xC000 == nMessage )
     {
       /* registered windows message */
       add_dref(curr_ea + 16, nSig, dr_O);
       doDwrd(nSig,4);
       op_offset(curr_ea + 16, OPND_MASK, REF_OFF32, nSig);
     } else if ( (ulong)-1 == nMessage )
     {
       /* Update Command UI */
       rp_set_comment(curr_ea, "Update Command", false);
       if ( nLastID )
       {
	 rp_set_comment(curr_ea + 8,first_id,false);
	 rp_set_comment(curr_ea + 12,last_id,false);
       } else
	 rp_set_comment(curr_ea + 8, ctrl_id,false);
     } else if ( WM_COMMAND == nMessage )
     {
       if ( !nCode ) /* CN_COMMAND */
       {
         if ( nSig == 12 ) /* AfxSig_vv */
         {
           rp_set_comment(curr_ea, "ON_COMMAND",false);
         } else if ( nSig == 13 ) /* AfxSig_vw */
         {
           rp_set_comment(curr_ea, "ON_COMMAND_RANGE",false);
         } else if ( nID != nLastID && nLastID )
         {
           rp_set_comment(curr_ea, "ON_COMMAND_EX_RANGE",false);
         } else {
           rp_set_comment(curr_ea, "ON_COMMAND_EX",false);
         }
       } else if ( nCode == (ulong)-1 ) /* CN_UPDATE_COMMAND_UI */
       {
         if ( nID != nLastID && nLastID )
          rp_set_comment(curr_ea, "ON_UPDATE_COMMAND_UI_RANGE",false);
         else
          rp_set_comment(curr_ea, "ON_UPDATE_COMMAND_UI", false);
       } else {
        rp_set_comment(curr_ea + 4, n_code,false);
        if ( nID != nLastID && nLastID )
          rp_set_comment(curr_ea, "ON_CONTROL_RANGE",false);
        else
          rp_set_comment(curr_ea, "ON_CONTROL",false);
       }
       if ( nID != nLastID && nLastID )
       {
        rp_set_comment(curr_ea + 8,first_id,false);
        rp_set_comment(curr_ea + 12,last_id,false);
       } else
        rp_set_comment(curr_ea + 8, ctrl_id,false);
     } else if ( WM_NOTIFY == nMessage )
     {
       if ( nSig == 38 ) /* AfxSig_vNMHDRpl */
        rp_set_comment(curr_ea, "ON_NOTIFY",false);
       else if ( nSig == 40 ) /* AfxSig_vwNMHDRpl */
        rp_set_comment(curr_ea, "ON_NOTIFY_RANGE",false);
       else if ( nID != nLastID && nLastID )
        rp_set_comment(curr_ea, "ON_NOTIFY_EX_RANGE",false);
       else
        rp_set_comment(curr_ea, "ON_NOTIFY_EX",false);
       rp_set_comment(curr_ea + 4, n_code,false);
       if ( nID != nLastID && nLastID )
       {
        rp_set_comment(curr_ea + 8,first_id,false);
        rp_set_comment(curr_ea + 12,last_id,false);
       } else
        rp_set_comment(curr_ea + 8, ctrl_id,false);
     } else if ( WM_COMMAND+WM_REFLECT_BASE == nMessage )
     {
       if ( nCode == (ulong)-1 ) /* CN_UPDATE_COMMAND_UI */
        rp_set_comment(curr_ea, "ON_UPDATE_COMMAND_UI_REFLECT",false);
       else {
        rp_set_comment(curr_ea + 4, n_code,false);
        if ( nSig == 12 ) /* AfxSig_vv */
         rp_set_comment(curr_ea, "ON_CONTROL_REFLECT",false);
        else
         rp_set_comment(curr_ea, "ON_CONTROL_REFLECT_EX",false);
       }
     } else if ( WM_NOTIFY+WM_REFLECT_BASE == nMessage )
     {
       rp_set_comment(curr_ea + 4, n_code,false);
       if ( nSig == 38 ) /* AfxSig_vNMHDRpl */
        rp_set_comment(curr_ea, "ON_NOTIFY_REFLECT",false);
       else
        rp_set_comment(curr_ea, "ON_NOTIFY_REFLECT_EX",false);
     }
     /* and finally mark function pointer */
     pfn = get_long(curr_ea + 20);
     doDwrd(curr_ea + 20,4);
     if ( pfn != NULL )
     {
       if ( !isData(pfn) )
	do_unknown_range(pfn,4,true);
       add_cref(curr_ea + 20, pfn, fl_CN);
       op_offset(curr_ea + 20, OPND_MASK, REF_OFF32, pfn);
     }
     curr_ea += 24; /* size of AFX_MSGMAP_ENTRY */
   }
}

extern struc_t *add_ole_vtbl(char *name);
extern void add_ole_vtbl_members(struc_t *s, struct buben_methods *methods, int size);

void
processIID(ea_t curr_ea)
{
   const int my_size = sizeof(struct win_IID);

   ea_t iid_start_ea = curr_ea;
   struct win_IID iid;
   int count;

   if ( !check_for_available_space(curr_ea, my_size) )
   {
     warning("No enough room to be IID (at least %d bytes required)", my_size);
     return;
   }
   /* fill IID struct and also form it in IDA */
   do_unknown(curr_ea, my_size);
   iid.l = get_long(curr_ea);
   doDwrd(curr_ea, 4);
   curr_ea += 4;
   iid.w1 = get_word(curr_ea);
   doWord(curr_ea, 2);
   curr_ea += 2;
   iid.w2 = get_word(curr_ea);
   doWord(curr_ea, 2);
   curr_ea += 2;
   for ( count = 0; count < 8; count++ )
   {
     iid.b[count] = get_byte(curr_ea + count);
     doByte(curr_ea + count, 1);
   }
   int setted = 0;
   const struct iid_item *rp_iid = NULL;
   /* 5 Nov 2004 - changed apply logic */
   if ( init_tlb_buben() )
   {
      char *res = find_tlb_buben(&iid);
      if ( res != NULL )
      {
       rp_set_comment(iid_start_ea, res, false);
       setted = 1;
       if ( is_tlb_buben_has_vtbl() )
       {
         struc_t *s = add_ole_vtbl(res);
         if ( s != NULL )
         {
           int size = 0;
           struct buben_methods *m = get_buben_vtlb_methods(size);
           if ( m != NULL )
            add_ole_vtbl_members(s, m, size);
         }
       }
      }
   }
   if ( !setted )
   {
     rp_iid = find_iid(&iid);
     if ( rp_iid != NULL )
     {
       rp_set_comment(iid_start_ea, rp_iid->name, false);
       setted = 1;
     }
   }
   if ( !setted )
     rp_set_comment(iid_start_ea, print_IID(&iid), false);
   return;
}

void idaapi
MFC_run(int arg)
{
///  __asm int 3
  check_cfg();
  switch(arg)
  {
    case 0:
     process_AfxMessages(get_screen_ea());
    break;
   case 1:
     processIID(get_screen_ea());
    break;
   case 2:
     process_RT();
    break;
   case 3:
     jump_to_vtbl_by_name();
    break;
   case 4:
     process_VTBL();
    break;
   case 5:
     load_RPD();
    break;
   case 6:
     process_VTBL2();
    break;
   default:   
      warning("Illegal parameter %d for %s\n"
"Allowed parameters:\n"
" 0 - message map processing\n"
" 1 - IID recognizing\n"
" 2 - create map of RuntimeClasses\n"
" 3 - jump to vtbl by class name\n"
" 4 - typize current VTBL from .RPD file\n"
" 5 - manual load RPD file\n"
" 6 - manual VTBLing from .RPD file\n"
 ,arg, MFC_wanted_name
);
    break;
  }
}

int idaapi
MFC_init(void)
{
 /* for x86 PE files only */
 if ( ph.id != PLFM_386 )
   return PLUGIN_SKIP;
 if ( inf.filetype != f_PE && inf.filetype != f_ELF ) // we also can apply ELF signatures !
  return PLUGIN_SKIP;
 return PLUGIN_OK;
}

void idaapi
MFC_term(void)
{
 classes_deinit();
 pdb_deinit();
 finalize_cfg();
 finit_tlb_buben();
}

/*
 * PLUGIN description
 */
extern "C" plugin_t PLUGIN = {
  IDP_INTERFACE_VERSION,
  0,                   // plugin flags - ???
  MFC_init,            // initialize function
  MFC_term,            // terminate. this pointer may be NULL.
  MFC_run,             // invoke plugin
  MFC_comment,         // long comment about the plugin
  MFC_help,            // multiline help about the plugin
  MFC_wanted_name,     // the preferred short name of the plugin
  MFC_wanted_hotkey    // the preferred hotkey to run the plugin
};
