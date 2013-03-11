#ifndef _STDAFX_H_
#define _STDAFX_H_


// Change these values to use different versions
#define WINVER            0x0501
#define _WIN32_WINNT      0x0501
#define _WIN32_IE         0x0600
#define _RICHEDIT_VER     0x0100

#define MSG_USER_SCREEN   (WM_USER + 10001)

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;


#include <atlwin.h>
#include <atlctrls.h>
//#include <atlmisc.h>
#include "atlimage.h"
//#include <atlcrack.h>

//#include <GdiPlus.h>

#endif