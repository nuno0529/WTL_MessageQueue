// Alpha.cpp : main source file for Alpha.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include <atlmisc.h>

#include "resource.h"

#include "View.h"
#include "aboutdlg.h"
#include "MainFrm.h"

CAppModule _Module;

DWORD WINAPI AnotherWINThread(LPVOID pParam)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame dlgMain1;

	if(dlgMain1.Create(NULL) == NULL)
	{
		ATLTRACE(_T("Main dialog 1 creation failed!\n"));
		return 0;
	}

	dlgMain1.ShowWindow(true);

	int nRet;

	nRet = theLoop.Run();

	return 0;
}

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	DWORD dwThreadId = 0;
	HANDLE hWorkingThread = CreateThread(NULL, 0, AnotherWINThread, NULL, 0, &dwThreadId);
	ATLASSERT(hWorkingThread!=NULL);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hRes));

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
