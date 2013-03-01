#ifndef _ROPWINDOW_H_
#define _ROPWINDOW_H_
#include "stdafx.h"
#include "AlphaChild.h"
class RopWindow : public CWindowImpl<RopWindow>
{
public:
	//using namespace Gdiplus;
	DECLARE_WND_CLASS("rop widnow")

	BEGIN_MSG_MAP(theClass)
		MESSAGE_HANDLER(WM_PAINT,OnPaint)
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
		MESSAGE_HANDLER(WM_DESTROY,OnDes)
		MESSAGE_HANDLER(WM_ERASEBKGND,OnErs)
		MESSAGE_HANDLER(WM_KEYDOWN,OnChar)
		CHAIN_MSG_MAP_ALT_MEMBER( mAlpha, 1 )
		 REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	/*
	void CaptureImg()
	{
		HDC hdcScreen;
		HDC hdcWindow;
		HDC hdcMemDC = NULL;
		HBITMAP hbmScreen = NULL;
		BITMAP bmpScreen;

		// Retrieve the handle to a display device context for the client 
		// area of the window. 
		hdcScreen = ::GetDC(NULL);
		//hdcScreen = ::CreateDC("DISPLAY", NULL, NULL, NULL);
		hdcWindow = ::GetDC(m_hWnd);

		// Create a compatible DC which is used in a BitBlt from the window DC
		hdcMemDC = CreateCompatibleDC(hdcWindow); 

		if(!hdcMemDC)
		{
			::MessageBox(m_hWnd, "CreateCompatibleDC has failed","Failed", MB_OK);
			goto done;
		}

		// Get the client area for size calculation
		RECT rcClient;
		::GetClientRect(m_hWnd, &rcClient);

		//This is the best stretch mode
		::SetStretchBltMode(hdcWindow,HALFTONE);

		//The source DC is the entire screen and the destination DC is the current window (HWND)
		if(!StretchBlt(hdcWindow, 
			0,0, 
			rcClient.right, rcClient.bottom, 
			hdcScreen, 
			0,0,
			GetSystemMetrics (SM_CXSCREEN),
			GetSystemMetrics (SM_CYSCREEN),
			SRCCOPY))
		{
			::MessageBox(m_hWnd, "StretchBlt has failed","Failed", MB_OK);
			goto done;
		}

		// Create a compatible bitmap from the Window DC
		hbmScreen = CreateCompatibleBitmap(hdcWindow, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top);

		if(!hbmScreen)
		{
			::MessageBox(m_hWnd, "CreateCompatibleBitmap Failed","Failed", MB_OK);
			goto done;
		}

		// Select the compatible bitmap into the compatible memory DC.
		SelectObject(hdcMemDC,hbmScreen);

		// Bit block transfer into our compatible memory DC.
		if(!BitBlt(hdcMemDC, 
			0,0, 
			rcClient.right-rcClient.left, rcClient.bottom-rcClient.top, 
			hdcWindow, 
			0,0,
			SRCCOPY))
		{
			::MessageBox(m_hWnd, "BitBlt has failed", "Failed", MB_OK);
			goto done;
		}

		// Get the BITMAP from the HBITMAP
		GetObject(hbmScreen,sizeof(BITMAP),&bmpScreen);

		BITMAPFILEHEADER   bmfHeader;    
		BITMAPINFOHEADER   bi;

		bi.biSize = sizeof(BITMAPINFOHEADER);    
		bi.biWidth = bmpScreen.bmWidth;    
		bi.biHeight = bmpScreen.bmHeight;  
		bi.biPlanes = 1;    
		bi.biBitCount = 32;    
		bi.biCompression = BI_RGB;    
		bi.biSizeImage = 0;  
		bi.biXPelsPerMeter = 0;    
		bi.biYPelsPerMeter = 0;    
		bi.biClrUsed = 0;    
		bi.biClrImportant = 0;

		DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

		// Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
		// call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
		// have greater overhead than HeapAlloc.
		HANDLE hDIB = GlobalAlloc(GHND,dwBmpSize); 
		char *lpbitmap = (char *)GlobalLock(hDIB);    

		// Gets the "bits" from the bitmap and copies them into a buffer 
		// which is pointed to by lpbitmap.
		GetDIBits(hdcWindow, hbmScreen, 0,
			(UINT)bmpScreen.bmHeight,
			lpbitmap,
			(BITMAPINFO *)&bi, DIB_RGB_COLORS);

		// A file is created, this is where we will save the screen capture.
		HANDLE hFile = CreateFileW(L"d:\\captureqwsx.bmp",
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);   

		// Add the size of the headers to the size of the bitmap to get the total file size
		DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		//Offset to where the actual bitmap bits start.
		bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER); 

		//Size of the file
		bmfHeader.bfSize = dwSizeofDIB; 

		//bfType must always be BM for Bitmaps
		bmfHeader.bfType = 0x4D42; //BM   

		DWORD dwBytesWritten = 0;
		WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
		WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
		WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

		//Unlock and Free the DIB from the heap
		GlobalUnlock(hDIB);    
		GlobalFree(hDIB);

		//Close the handle for the file that was created
		CloseHandle(hFile);

		//Clean up
done:
		::DeleteObject(hbmScreen);
		::DeleteObject(hdcMemDC);
		::ReleaseDC(NULL,hdcScreen);
		::ReleaseDC(m_hWnd,hdcWindow);
	}

*/

	LRESULT OnCreate(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		CenterWindow();
		//CaptureImg();
		//DisplayII();
		//获取屏幕分辩率
		int cx = GetSystemMetrics(SM_CXSCREEN);
		int cy = GetSystemMetrics(SM_CYSCREEN);

		//SetWindowPos(HWND_TOPMOST,0,0,cx,cy,SWP_NOREDRAW);
		MoveWindow(CRect(0,0,cx,cy));
		ModifyStyle(WS_VISIBLE |~WS_CAPTION | ~WS_BORDER/* WS_BORDER| WS_CAPTION*/ /*| WS_CLIPSIBLINGS*/ /*| WS_CLIPCHILDREN*/, 0);

		//SetWindowPos( 0, 0,0, cx,cy, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
		CRect rc;
		GetClientRect(&rc);
		CPaintDC dc(m_hWnd);

		//LONG lWindowLong = ::GetWindowLong(m_hWnd, GWL_STYLE) | ~WS_CAPTION;//| WS_EX_NOACTIVATE;
		//::SetWindowLong(m_hWnd, GWL_STYLE, lWindowLong); 

		mMemDC.CreateCompatibleDC(dc);
		mBmp.CreateCompatibleBitmap(dc,rc.Width(),rc.Height());
		HBITMAP b = mMemDC.SelectBitmap(mBmp);



		HDC hScreenDC = ::GetDC(NULL);
#if 0
		::SetStretchBltMode(mMemDC.m_hDC,HALFTONE);

		mMemDC.StretchBlt(
			0,0, 
			rc.Width(),rc.Height(), 
			hScreenDC, 
			0,0,
			cx,cy,
			SRCCOPY | CAPTUREBLT);
#endif
		mMemDC.BitBlt(0,0,rc.Width(),rc.Height(),hScreenDC,0,0,SRCCOPY | CAPTUREBLT);

		mAlpha.Create(m_hWnd,CRect(0,0,cx,cy),"",WS_VISIBLE | WS_POPUP);
		//SetWindowPos(HWND_TOPMOST, 0,0, cx,cy, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
		return false;
	}


	LRESULT OnPaint(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		CRect rc;
		GetClientRect(&rc);
		CPaintDC dc(m_hWnd);
		dc.BitBlt(0,0,rc.Width(),rc.Height(),mMemDC,0,0,SRCCOPY |CAPTUREBLT );
		return false;
	}



	LRESULT OnDes(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		PostQuitMessage(0);
		return false;
	}

	LRESULT OnHit(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		return HTCAPTION ;
	}

	//OnChar

	LRESULT OnChar(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		switch(wParam)
		{
		case VK_ESCAPE:
			PostMessage(WM_CLOSE,0,0);
			break;
		}
		return false ;
	}

	LRESULT OnMouseMove(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		//Display();
		return false ;
	}

	//OnErs
	LRESULT OnErs(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		return 1 ;
	}

	LRESULT OnActive(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		return false ;
	}
private:

	CDC mMemDC;
	CBitmap mBmp;

	AlphaChild mAlpha;

};
#endif