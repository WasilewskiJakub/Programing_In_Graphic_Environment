// SAPERGRA.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SAPERGRA.h"
#include"Function.h"
#include<time.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK ChildJob(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM ChildClass(HINSTANCE hInstance);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SAPERGRA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	ChildClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAPERGRA));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

// single panel:
int Gtoppanel = 30;
int Gfield = 25;
int Gspace = 1;

WindowProperty WND_prop;
GameProps Game_Property;
Board** Board_Game;
HWND DialogResize;
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM ChildClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ChildJob;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAPERGRA));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(96, 96, 96));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"CHILD";
	wcex.hIconSm = NULL;

	return RegisterClassExW(&wcex);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAPERGRA));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SAPERGRA);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	Game_Property.Gncm = nCmdShow;
	WND_prop.Gxcount = 10;
	WND_prop.Gycount = 10;
	WND_prop.hInt = hInstance;
	Game_Property.Gmines_count = 10;
	int width = WND_prop.Gxcount * Gfield + WND_prop.Gxcount - Gspace;
	int height = Gtoppanel + WND_prop.Gycount * Gfield + WND_prop.Gycount - 1;

	RECT rc{ 0,0,width,height };
	AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX, TRUE);
	WND_prop.Gheight = abs(rc.top - rc.bottom);
	WND_prop.Gwidth = abs(rc.right - rc.left);
	

	WND_prop.main = CreateWindowW(szWindowClass, szTitle, (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX,
		0, 0, WND_prop.Gwidth, WND_prop.Gheight, nullptr, nullptr, hInstance, nullptr);
	SetWindowText(WND_prop.main, L"SAPER");
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	MoveWindow(WND_prop.main, (ScreenX - WND_prop.Gwidth) / 2, (ScreenY - WND_prop.Gheight) / 2, WND_prop.Gwidth, WND_prop.Gheight, TRUE);
	if (!WND_prop.main)
	{
		return FALSE;
	}

	ShowWindow(WND_prop.main, nCmdShow);
	UpdateWindow(WND_prop.main);
	PrepareBoard(Board_Game, &Game_Property, &WND_prop);
	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
INT_PTR ResizeFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hWnd, IDC_EDIT1, WND_prop.Gycount, FALSE);
		SetDlgItemInt(hWnd, IDC_EDIT2, WND_prop.Gxcount, FALSE);
		SetDlgItemInt(hWnd, IDC_EDIT3, Game_Property.Gmines_count, FALSE);
		return (INT_PTR)TRUE;
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDCANCEL:
			EndDialog(hWnd, LOWORD(wParam));
			//return (INT_PTR)TRUE;
		break;
		case IDOK:
			ClearBoard(Board_Game, WND_prop);
			EndDialog(hWnd, LOWORD(wParam));
			WND_prop.Gycount = GetDlgItemInt(hWnd, IDC_EDIT1, NULL, FALSE);
			WND_prop.Gxcount = GetDlgItemInt(hWnd, IDC_EDIT2, NULL, FALSE);
			Game_Property.Gmines_count = GetDlgItemInt(hWnd, IDC_EDIT3, NULL, FALSE);
			
			WND_prop.Gycount = WND_prop.Gycount < 10 ? 10 : WND_prop.Gycount;
			WND_prop.Gxcount = WND_prop.Gxcount < 10 ? 10 : WND_prop.Gxcount;
			Game_Property.Gmines_count = Game_Property.Gmines_count < 10 ? 10 : Game_Property.Gmines_count;

			WND_prop.Gycount = WND_prop.Gycount > 30 ? 30 : WND_prop.Gycount;
			WND_prop.Gxcount = WND_prop.Gxcount > 24 ? 24 : WND_prop.Gxcount;

			int areaofsquare = WND_prop.Gycount * WND_prop.Gxcount;
			Game_Property.Gmines_count = Game_Property.Gmines_count > areaofsquare ? areaofsquare : Game_Property.Gmines_count;

			int width = WND_prop.Gxcount * Gfield + WND_prop.Gxcount - Gspace;
			int height = Gtoppanel + WND_prop.Gycount * Gfield + WND_prop.Gycount - 1;

			RECT rc{ 0,0,width,height };
			AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX, TRUE);
			WND_prop.Gheight = abs(rc.top - rc.bottom);
			WND_prop.Gwidth = abs(rc.right - rc.left);

			int ScreenX = GetSystemMetrics(SM_CXSCREEN);
			int ScreenY = GetSystemMetrics(SM_CYSCREEN);

			MoveWindow(WND_prop.main, (ScreenX - WND_prop.Gwidth) / 2, (ScreenY - WND_prop.Gheight) / 2, WND_prop.Gwidth, WND_prop.Gheight, TRUE);
			PrepareBoard(Board_Game, &Game_Property, &WND_prop);
			return (INT_PTR)TRUE;
			break;
		}
	}
	break;
	}
	return (INT_PTR)FALSE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_CUSTSIZE:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)ResizeFunc);
			break;
		}
		case IDM_NEW:
		{
			int ScreenX = GetSystemMetrics(SM_CXSCREEN);
			int ScreenY = GetSystemMetrics(SM_CYSCREEN);
			MoveWindow(WND_prop.main, (ScreenX - WND_prop.Gwidth) / 2, (ScreenY - WND_prop.Gheight) / 2, WND_prop.Gwidth, WND_prop.Gheight, TRUE);
			ClearBoard(Board_Game, WND_prop);
			PrepareBoard(Board_Game, &Game_Property, &WND_prop);
			break;
		}
		case IDM_DEB:
		{
			HMENU parent_menu = GetMenu(WND_prop.main);
			if (WND_prop.Debug == false)
			{
				WND_prop.Debug = true;
				CheckMenuItem(parent_menu, IDM_DEB, MFS_CHECKED);
				DebugColoring(Board_Game, WND_prop);
			}
			else
			{
				WND_prop.Debug = false;
				CheckMenuItem(parent_menu, IDM_DEB, MFS_UNCHECKED);
				CoverDebugColoring(Board_Game, WND_prop);
			}
		}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hWnd, &ps);
	//	// TODO: Add any drawing code that uses hdc here...
	//	Timer(hWnd, Game_Property.Gmillisec, WND_prop);
	//	Flague(hWnd, Game_Property.Gflagues, WND_prop);
	//	if (Game_Property.Gmillisec == 0) {
	//		EndPaint(hWnd, &ps);
	//		break;
	//	}
	//	if (WND_prop.Debug == true)
	//	{
	//		CoverDebugColoring(Board_Game, WND_prop);
	//	}
	//	else
	//	{
	//		DebugColoring(Board_Game, WND_prop);
	//	}
	//	EndPaint(hWnd, &ps);
	//}
	//break;
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		minMaxInfo->ptMaxSize.x = minMaxInfo->ptMaxTrackSize.x = minMaxInfo->ptMinTrackSize.x = WND_prop.Gwidth;
		minMaxInfo->ptMaxSize.y = minMaxInfo->ptMaxTrackSize.y = minMaxInfo->ptMinTrackSize.y = WND_prop.Gheight;
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK ChildJob(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_RBUTTONDOWN:
	{
		if (Game_Property.EndGame == false && GetProp(hWnd, L"shown") == FALSE)
		{
			if (Game_Property.Gtimerstart == false)
			{
				Game_Property.Gtimerstart = true;
				SetTimer(hWnd, 2, 100, NULL);
			}
			bool flag = (bool)GetProp(hWnd, _T("flague"));
			if (flag == true)
			{
				Game_Property.Gflagues++;
				DeleteFlag(hWnd, hInst);
				if((bool)GetProp(hWnd, L"mine"))
					Game_Property.Gmines_found--;
				if (WND_prop.Debug == true)
					ColoringForDebuging(hWnd, WND_prop, Board_Game, (int)GetProp(hWnd, L"i-idx"), (int)GetProp(hWnd, L"j-idx"));
			}
			else
			{
				Game_Property.Gflagues--;
				PutFlague(hWnd, hInst);
				if((bool)GetProp(hWnd, L"mine"))
					Game_Property.Gmines_found++;
			}
			Flague(WND_prop.main,Game_Property.Gflagues, WND_prop);
			if (Game_Property.Gflagues == 0 && Game_Property.Gmines_found == Game_Property.Gmines_count && Game_Property.EndGame == false)
			{
				Game_Property.EndGame = true;
				Game_Property.Gtimerstart = false;
				MessageBox(WND_prop.main, L"WIN", L"Minesweeper", MB_OK);
			}	
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		if (Game_Property.EndGame == false && (bool)GetProp(hWnd, L"flague") == false)
		{
			if (Game_Property.Gtimerstart == false)
			{
				Game_Property.Gtimerstart = true;
				SetTimer(hWnd, 2, 100, NULL);
			}
			LeftButtonCLicked_ColoringBoard(hWnd, WND_prop, Board_Game,Game_Property);
		}
		int uncovered_fields = 0;
		for(int i = 0 ;i<WND_prop.Gycount;i++)
			for (int j = 0; j < WND_prop.Gxcount; j++)
			{
				if ((bool)GetProp(Board_Game[i][j].child_window, L"shown") == true)
					uncovered_fields += 1;
			}
		if (WND_prop.Gxcount * WND_prop.Gycount - Game_Property.Gmines_count == uncovered_fields && Game_Property.EndGame == false)
		{
			Game_Property.EndGame = true;
			Game_Property.Gtimerstart = false;
			MessageBox(WND_prop.main, L"WIN", L"Minesweeper", MB_OK);
		}
	}
	break;
	case WM_TIMER:
	{
		if (wParam == 2)
		{
			if (Game_Property.Gtimerstart == true)
			{
				Game_Property.Gmillisec += 1;
				Timer(WND_prop.main, Game_Property.Gmillisec,WND_prop);
			}
		}
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}