#ifndef _ROPWINDOW_H_
#define _ROPWINDOW_H_
#include "stdafx.h"
#include "AlphaChild.h"


class RopWindow : public CWindowImpl<RopWindow>
{
public:
	//using namespace Gdiplus;
	DECLARE_WND_CLASS("ScreenCapture")

	BEGIN_MSG_MAP(theClass)
		MESSAGE_HANDLER(WM_PAINT,OnPaint)
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
		MESSAGE_HANDLER(WM_DESTROY,OnDes)
		MESSAGE_HANDLER(WM_ERASEBKGND,OnErs)
		MESSAGE_HANDLER(WM_KEYDOWN,OnChar)
		MESSAGE_HANDLER(MSG_USER_SCREEN,OnCMDScreenCapture)
		CHAIN_MSG_MAP_ALT_MEMBER( mAlpha, 1 )
	END_MSG_MAP()

	LRESULT OnCMDScreenCapture(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL&bHandled)
	{	

		strcpy(mSavePath,(char*)lParam);
		CRect *rc = (CRect*)wParam;
		int x = rc->left;
		int y = rc->top;
		int w = rc->right;
		int h = rc->bottom;
		if(w > 0 && h > 0)
		{
			OnScreenCapture(x,y,w,h,(char*)lParam);
		}
		return false;
	}


	LRESULT OnCreate(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		CenterWindow();
		//获取屏幕分辩率
		int cx = GetSystemMetrics(SM_CXSCREEN);
		int cy = GetSystemMetrics(SM_CYSCREEN);

		MoveWindow(CRect(0,0,cx,cy));
		ModifyStyle(WS_VISIBLE |~WS_CAPTION | ~WS_BORDER, 0);

		CRect rc;
		GetClientRect(&rc);
		CPaintDC dc(m_hWnd);

		mMemDC.CreateCompatibleDC(dc);
		mBmp.CreateCompatibleBitmap(dc,rc.Width(),rc.Height());
		HBITMAP b = mMemDC.SelectBitmap(mBmp);



		HDC hScreenDC = ::GetDC(NULL);
#if 0
		// NOT A GOOD METHOD.
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
		mAlpha.SetWindowPos(m_hWnd,0,0,0,0,SWP_NOSIZE);
		SetFocus();
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

	
	void OnScreenCapture(int x,int y,int w,int h,char*path)
	{
		CClientDC dc(m_hWnd);
		CDC dcMem;
		dcMem.CreateCompatibleDC(dc);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(dc,w,h);
		HBITMAP oldBit = dcMem.SelectBitmap(bitmap);
		dcMem.BitBlt(0,0,w,h,dc,x,y,SRCCOPY);
		dcMem.SelectBitmap(oldBit);
		
		CImage Image ; 
		Image.Attach(bitmap.m_hBitmap);                         
		Image.Save(mSavePath);
	}

private:

	CDC mMemDC;
	CBitmap mBmp;

	AlphaChild mAlpha;
	char mSavePath[1024];

};
#endif