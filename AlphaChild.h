#ifndef _ALPHA_CHILD_H_
#define _ALPHA_CHILD_H_

typedef CWinTraits<WS_POPUPWINDOW, WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW> CListViewMarqueeTraits;

class AlphaChild : public CWindowImpl<AlphaChild ,CWindow, CListViewMarqueeTraits>
{
public:
	DECLARE_WND_CLASS_EX(_T("AlphaChild"), CS_OWNDC, -1);
	BEGIN_MSG_MAP(D)
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
		//MESSAGE_HANDLER(WM_PAINT,OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND,OnErs)
		ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_MOUSEMOVE,OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONDOWN,OnLMouseBtnDwn)
		MESSAGE_HANDLER(WM_LBUTTONUP,OnLMouseBtnUp)
		// MESSAGE_HANDLER(WM_MOUSEMOVE,)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg,WPARAM wParam, LPARAM lParam,BOOL &bHandled)
	{

		//CenterWindow();
		ModifyStyle(WS_VISIBLE | WS_BORDER /*| WS_CAPTION*/ | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		LONG lWindowLong = ::GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_NOACTIVATE;
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, lWindowLong); 
		/*Set alpha layer*/
		const BYTE AlphaPercent = 200;

		::SetLayeredWindowAttributes(m_hWnd, RGB(255,255,255), AlphaPercent, LWA_COLORKEY | LWA_ALPHA);
		//RedrawWindow( NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN); 
		SetWindowPos( HWND_TOPMOST, 0,0, 500,500, SWP_NOSIZE);

		//SetCapture();
		ShowWindow(TRUE);
		FillBackGnd();
		//----------mouse status---------
		mbLMouseDown = false;
		mPtBeg.x = 0;
		mPtBeg.y = 0;
		mPtEnd.x = 0;
		mPtEnd.y  = 0;
		//-------------------
		return false;
	}

	LRESULT OnPaint(UINT uMsg,WPARAM wParam, LPARAM lParam,BOOL &bHandled)
	{
#if 1
		RECT rc,rcTxt = {0,0,100,100};
		CPaintDC dc = m_hWnd;
		dc.SetBkMode(TRANSPARENT);
		//dc.SetROP2(R2_NOT);
		dc.DrawText("Hello World!",strlen("Hello World!"),&rcTxt,0);

#if 1

		COLORREF backgndcolor = RGB(0,0,0);
		CBrush brush;
		brush.CreateSolidBrush(backgndcolor);
		GetClientRect(&rc);
		dc.FillRect(&rc,brush);

		//RECT rc2 = {100,100,400,400};
		//dc.Rectangle(&rc2);
		dc.Rectangle(mPtBeg.x,mPtBeg.y,mPtEnd.x,mPtEnd.y);
#endif
#endif
		return false;
	}

	LRESULT OnErs(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		return 1 ;
	}

	void FillBackGnd()
	{
		RECT rc,rcTxt = {0,0,100,100};
		CPaintDC dc = m_hWnd;
		//dc.SetBkMode(TRANSPARENT);
		//dc.SetROP2(R2_NOT);
		//dc.DrawText("Hello World!",strlen("Hello World!"),&rcTxt,0);

		COLORREF backgndcolor = RGB(0,0,0);
		CBrush brush;
		brush.CreateSolidBrush(backgndcolor);
		GetClientRect(&rc);
		dc.FillRect(&rc,brush);
	}

	LRESULT OnMouseMove(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		if(mbLMouseDown)
		{
#if 1
			GetCursorPos(&mPtEnd);
			RECT rc,rcTxt = {0,0,100,100};
			CClientDC dc = m_hWnd;
			dc.SetBkMode(TRANSPARENT);
			//dc.SetROP2(R2_NOT);
			dc.DrawText("Hello World!",strlen("Hello World!"),&rcTxt,0);

#if 1

			COLORREF backgndcolor = RGB(0,0,0);
			CBrush brush;
			brush.CreateSolidBrush(backgndcolor);
			GetClientRect(&rc);
			dc.FillRect(&rc,brush);

			RECT rc2 = {100,100,400,400};
			dc.Rectangle(mPtBeg.x,mPtBeg.y,mPtEnd.x,mPtEnd.y);
#endif
#endif
		}
		return 1 ;
	}

	LRESULT OnLMouseBtnDwn(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		//SetFocus();
		mbLMouseDown = true;
		GetCursorPos(&mPtBeg);
		//SetCapture();
		return 1 ;
	}

	LRESULT OnLMouseBtnUp(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		mbLMouseDown = FALSE;
		GetCursorPos(&mPtEnd);
		//ReleaseCapture();
		return 1 ;
	}


	void DrawRec(POINT begin,POINT end)
	{

	}


private:
	bool mbLMouseDown;
	POINT mPtBeg;
	POINT mPtEnd;
};



#endif