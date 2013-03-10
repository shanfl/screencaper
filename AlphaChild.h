#ifndef _ALPHA_CHILD_H_
#define _ALPHA_CHILD_H_

typedef CWinTraits<WS_POPUPWINDOW, WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW> CListViewMarqueeTraits;

class AlphaChild : public CWindowImpl<AlphaChild ,CWindow, CListViewMarqueeTraits>
{
	// 截屏状态
	// 1.选择区域（选择状态）				----- 在不是编辑状态下，鼠标左键按下
	// 2.选择完毕，编辑区域（编辑状态）	----- 鼠标右键
	// 3.确定
	enum eSTATUS
	{
		SELECT_STATUS,		// 
		EDIT_STATSUS,		// 
		DRAG_STATUS,		// 拖拽选区，不改变选区的大小
		DRAG_EDIT_STATUS,	// 拖拽边缘，调整选区的大小
	};

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
		MESSAGE_HANDLER(WM_RBUTTONDOWN,OnRMouseBtnDown)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK,OnDoubleClick)
		REFLECT_NOTIFICATIONS();
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg,WPARAM wParam, LPARAM lParam,BOOL &bHandled)
	{

		//CenterWindow();
		ModifyStyle(WS_VISIBLE | WS_BORDER | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
		//LONG lWindowLong = ::GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_NOACTIVATE;
		//::SetWindowLong(m_hWnd, GWL_EXSTYLE, lWindowLong); 
		/*Set alpha layer*/
		const BYTE AlphaPercent = 200;

		::SetLayeredWindowAttributes(m_hWnd, RGB(255,255,255), AlphaPercent, LWA_COLORKEY | LWA_ALPHA);

		ShowWindow(TRUE);
		FillBackGnd();
		//----------mouse status---------
		mbLMouseDown = false;
		mPtBeg.x = 0;
		mPtBeg.y = 0;
		mPtEnd.x = 0;
		mPtEnd.y  = 0;
		//-------------------

		//--------------------------
		CRect rcScreen;
		GetClientRect(&rcScreen);		
		RECT rc;
		rc.left = rcScreen.right - 400;
		rc.top = rcScreen.bottom - 20;
		rc.right = rcScreen.right - 80;
		rc.bottom = rcScreen.bottom;
		mSavePath.Create(m_hWnd,rc,"",ES_LEFT /*| WS_OVERLAPPED*/ | WS_VISIBLE | WS_POPUP,WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR);
		mSavePath.ShowWindow(FALSE);
		mSavePath.SetWindowText("d:/shot.bmp");
		
		//mSaveBtn.Create(m_hWnd,)

		meStatus = SELECT_STATUS;

		return false;
	}

	LRESULT OnPaint(UINT uMsg,WPARAM wParam, LPARAM lParam,BOOL &bHandled)
	{

#if 1
		RECT rc,rcTxt = {0,0,100,100};
		CPaintDC dc = m_hWnd;
		dc.SetBkMode(TRANSPARENT);
		//dc.SetROP2(R2_NOT);
		//dc.DrawText("Hello World!",strlen("Hello World!"),&rcTxt,0);

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


		COLORREF backgndcolor = RGB(0,0,0);
		CBrush brush;
		brush.CreateSolidBrush(backgndcolor);
		GetClientRect(&rc);
		dc.FillRect(&rc,brush);
	}

	LRESULT OnMouseMove(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		
		if(mbLMouseDown && meStatus == SELECT_STATUS)
		{
			GetCursorPos(&mPtEnd);
			DrawRec();
		}
		return 1 ;
	}

	LRESULT OnLMouseBtnDwn(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		mbLMouseDown = true;
		if(meStatus == SELECT_STATUS)
		{
			GetCursorPos(&mPtBeg);
			mPtEnd.x = mPtBeg.x;
			mPtEnd.y = mPtBeg.y;
		}
		return 1 ;
	}

	//OnDoubleClick
	LRESULT OnDoubleClick(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		if(meStatus != SELECT_STATUS )
		{
			RECT rc = Convert(mPtBeg,mPtEnd);
			if(HasSelected())
			{
				int x = rc.left;
				int y = rc.top;
				int w = rc.right - rc.left;
				int h = rc.bottom - rc.top;
				DWORD dw = MAKEWORD(y,x);
				DWORD dl = MAKEWORD(h,w);
				CRect rc(x,y,w,h);
				char buff[1024];
				memset(buff,0,1024);
				::GetWindowTextA(mSavePath.m_hWnd,buff,1024);
				::SendMessage(GetParent(),MSG_USER_SCREEN,(WPARAM)&rc,(LPARAM)buff);
				meStatus = SELECT_STATUS;
				mPtBeg.x = mPtEnd.x = 0;
				mPtBeg.y = mPtEnd.y = 0;
				DrawRec();
				UpateControls();
				//RedrawWindow();
			}
		}
		return 1 ;
	}

	LRESULT OnLMouseBtnUp(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		mbLMouseDown = FALSE;
		if(HasSelected())
		{
			meStatus = EDIT_STATSUS;
			mSavePath.ShowWindow(TRUE);
			UpateControls();
		}
		else
		{
			//GetCursorPos(&mPtEnd);
			meStatus = SELECT_STATUS;
		}
			
        return 1 ;
	}

	//OnRMouseBtnDown
	LRESULT OnRMouseBtnDown(UINT umsg,WPARAM wParam, LPARAM lParam,BOOL&bHandled)
	{
		meStatus = SELECT_STATUS;
		mPtEnd.x = mPtBeg.x = 0;
		mPtEnd.y = mPtBeg.y = 0;		
		DrawRec();
		mSavePath.ShowWindow(FALSE);
		return 1 ;
	}

	void DrawRec()
	{
		CRect rc;
		CClientDC dc = m_hWnd;
		dc.SetBkMode(TRANSPARENT);
		COLORREF backgndcolor = RGB(0,0,0);
		CBrush brush;
		brush.CreateSolidBrush(backgndcolor);
		GetClientRect(&rc);
		dc.FillRect(&rc,brush);
		RECT rcGet = Convert(mPtBeg,mPtEnd);
		dc.Rectangle(&rcGet);
		RedrawWindow();
	}


	RECT Convert(POINT ptBeg,POINT ptEnd)
	{
		/*
			1--------
			|        |
			|		 |
			---------2
		*/
		if(ptEnd.x >= ptBeg.x && ptEnd.y >= ptBeg.y)
		{
			RECT rc = {ptBeg.x,ptBeg.y,ptEnd.x,ptEnd.y};
			return rc;
		}

		/*
			---------1
			|        |
			|		 |
			2---------
		*/
		else if(ptEnd.x <= ptBeg.x && ptEnd.y >= ptBeg.y)
		{
			RECT rc = {ptEnd.x,ptBeg.y,ptBeg.x,ptEnd.y};
			return rc;
		}

		/*
			2---------
			|        |
			|		 |
			---------1
		*/
		else if(ptEnd.x <= ptBeg.x && ptEnd.y <= ptBeg.y)
		{
			RECT rc = {ptEnd.x,ptEnd.y,ptBeg.x,ptBeg.y};
			return rc;
		}

		/*
			---------2
			|        |
			|		 |
			1---------
		*/			
		else if(ptEnd.x >= ptBeg.x && ptEnd.y <= ptBeg.y)
		{
			RECT rc = {ptBeg.x,ptEnd.y,ptEnd.x,ptBeg.y};
			return rc;
		}			
	}

	bool HasSelected()
	{
		if(mPtEnd.y - mPtBeg.y != 0 && mPtEnd.x - mPtBeg.x != 0 )
			return true;
		else 
			return false;
	}

	void UpateControls()
	{
		CRect rc;
		GetClientRect(&rc);
		if(meStatus != SELECT_STATUS)
		{
			CRect rcS = Convert(mPtEnd,mPtBeg);
			if(rcS.bottom + 20 <= rc.bottom)
			{
				mSavePath.SetWindowPos(HWND_TOP,rcS.left,rcS.bottom,0,0,SWP_NOSIZE);
			}
		}

		if(meStatus == SELECT_STATUS)
		{
			mSavePath.ShowWindow(false);
		}
	}
private:
	bool mbLMouseDown;
	POINT mPtBeg;
	POINT mPtEnd;

	eSTATUS meStatus;

private:
	CEdit mSavePath;
	CButton mSaveBtn;
};



#endif