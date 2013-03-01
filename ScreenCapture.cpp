#include "RopWindow.h"
CAppModule _Module;
//#pragma comment( lib, "gdiplus.lib" )
int WINAPI WinMain( IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nShowCmd )
{

	_Module.Init(0,hInstance);
	HRESULT hRes = ::CoInitialize(NULL);
	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES); 
	//ULONG_PTR m_gdiplusToken;
	//Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	//Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	MSG uMsg;

	RopWindow wnd;
	wnd.Create(NULL,CWindow::rcDefault,"Rop",WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW);

	wnd.ShowWindow(TRUE);
	wnd.UpdateWindow();


	while(GetMessage(&uMsg,0,0,0))
	{
		TranslateMessage(&uMsg);
		DispatchMessage(&uMsg);
	}


	_Module.Term();
	//Gdiplus::GdiplusShutdown(m_gdiplusToken);
	return 0;
}