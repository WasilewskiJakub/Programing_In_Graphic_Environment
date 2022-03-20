#pragma once
#include"struct.h"
#include"framework.h"
#include<tuple>

void FillBehind(HWND& hWnd);
void Timer(HWND hWnd, int time, WindowProperty ww)
{
    RECT rc;
    HDC hdc = GetDC(hWnd);
    GetClientRect(hWnd, &rc);
    TCHAR s[7];
    _stprintf_s(s, 7, _T("%04d.%d"), time / 10,time % 10);
    HFONT hFont, oldhFont;
    rc.right /= 2;
    rc.bottom = 30;
    hFont = (HFONT)CreateFont( 25, // Height
         0, // Width
         0, // Escapement
         0, // Orientation
         FW_BOLD, // Weight
         FALSE, // Italic
         FALSE, // Underline
         0, // StrikeOut
         EASTEUROPE_CHARSET, // CharSet
        OUT_DEFAULT_PRECIS, // OutPrecision
        CLIP_DEFAULT_PRECIS, // ClipPrecision
         DEFAULT_QUALITY, // Quality
         DEFAULT_PITCH | FF_SWISS, // PitchAndFamily
         _T("Arial"));
    oldhFont = (HFONT)SelectObject(hdc, hFont);
    SetTextColor((HDC)hdc, RGB(194, 0, 0));
    DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ReleaseDC(hWnd, hdc);
    SelectObject(hdc, oldhFont);
    DeleteObject(hFont);
}

void Flague(HWND hWnd, int flague_yet, WindowProperty ww)
{
    RECT rc;
    HDC hdc = GetDC(hWnd);
    GetClientRect(hWnd, &rc);
    TCHAR s[5];
    rc.left = rc.right / 2;
    rc.bottom = 30;
    _stprintf_s(s, 5, _T("%04d"), flague_yet);
    HFONT hFont, oldhFont;
    hFont = (HFONT)CreateFont(25, // Height
        0, // Width
        0, // Escapement
        0, // Orientation
        FW_BOLD, // Weight
        FALSE, // Italic
        FALSE, // Underline
        0, // StrikeOut
        EASTEUROPE_CHARSET, // CharSet
        OUT_DEFAULT_PRECIS, // OutPrecision
        CLIP_DEFAULT_PRECIS, // ClipPrecision
        DEFAULT_QUALITY, // Quality
        DEFAULT_PITCH | FF_SWISS, // PitchAndFamily
        _T("Arial"));
    oldhFont = (HFONT)SelectObject(hdc, hFont);
    SetTextColor((HDC)hdc, RGB(194, 0, 0));
    DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ReleaseDC(hWnd, hdc);
    SelectObject(hdc, oldhFont);
    DeleteObject(hFont);
}

void FillNumberMatrix(Board** &tab, WindowProperty wndprop, int minesCount);
void PrepareBoard(Board** &board, GameProps* Gprops, WindowProperty* wndprop)
{
    Gprops->Gmines_found = 0;
    Gprops->Gflagues = Gprops->Gmines_count;
    Gprops->Gmillisec = 0;
    Gprops->Gtimerstart = false;
    Gprops->Gdebug_on = false;
    Gprops->EndGame = false;
    wndprop->Debug = false;
    HMENU parent_menu = GetMenu(wndprop->main);
    CheckMenuItem(parent_menu, IDM_DEB, MFS_UNCHECKED);
    board = (Board**)malloc(sizeof(Board*) * wndprop->Gycount);
    for (int i = 0; i < wndprop->Gycount; i++)
        board[i] = (Board*)malloc(sizeof(Board) * wndprop->Gxcount);

    int yposition = 30;
    for (int i = 0; i < wndprop->Gycount; i++)
    {
        int xposition = 0;
        for (int j = 0; j < wndprop->Gxcount; j++)
        {
            board[i][j].child_window = CreateWindowW(L"CHILD", (LPCWSTR)NULL, WS_CHILD,
                xposition, yposition, 25, 25,
                wndprop->main, NULL, wndprop->hInt, NULL, NULL);
            xposition += 26;
            ShowWindow(board[i][j].child_window, Gprops->Gncm);
        }
        yposition += 26;
    }
    Timer(wndprop->main, Gprops->Gmillisec,*wndprop);
    Flague(wndprop->main, Gprops->Gflagues, *wndprop);

    FillNumberMatrix(board, *wndprop, Gprops->Gmines_count);
    for(int i = 0 ; i <wndprop->Gycount;i++)
        for (int j = 0; j < wndprop->Gxcount; j++)
        {
            SetProp(board[i][j].child_window, L"i-idx", (HANDLE)i);
            SetProp(board[i][j].child_window, L"j-idx", (HANDLE)j);
            SetProp(board[i][j].child_window, L"flague", (HANDLE)false);
            SetProp(board[i][j].child_window, L"shown", (HANDLE)false);
            bool xx = board[i][j].number_of_nearest_mines == INT_MIN ? true : false;
            SetProp(board[i][j].child_window, L"mine", (HANDLE)xx);
        }

}
void FillNumberMatrix(Board ** &tab, WindowProperty wndprop, int minesCount)
{
    srand(time(NULL));
    for (int i = 0; i < wndprop.Gycount; i++)
        for (int j = 0; j < wndprop.Gxcount; j++)
            tab[i][j].number_of_nearest_mines = 0;
    
    for (int i = 0; i < minesCount; i++)
    {
        int x, y;
        do
        {
            x = rand() % wndprop.Gxcount;
            y = rand() % wndprop.Gycount;
        } while (tab[y][x].number_of_nearest_mines == INT_MIN);
        tab[y][x].number_of_nearest_mines = INT_MIN;
    }

    for (int i = 0; i < wndprop.Gycount; i++)
    {
        for (int j = 0; j < wndprop.Gxcount; j++)
        {
            if (tab[i][j].number_of_nearest_mines == INT_MIN) continue;
            int number = 0;
            // Above element:
            if ((i != 0 && j!= 0) && tab[i - 1][j - 1].number_of_nearest_mines == INT_MIN)
                number++;
            if (i != 0 && tab[i - 1][j].number_of_nearest_mines == INT_MIN)
                number++;
            if ((i != 0 && j != (wndprop.Gxcount - 1)) && tab[i - 1][j + 1].number_of_nearest_mines == INT_MIN)
                number++;
            
            // element row:
            if (j != 0 && tab[i][j - 1].number_of_nearest_mines == INT_MIN)
                number++;
            if (j != (wndprop.Gxcount - 1) && tab[i][j + 1].number_of_nearest_mines == INT_MIN)
                number++;
            
            // under element:
            if ((j != 0 && i != (wndprop.Gycount - 1)) && tab[i + 1][j - 1].number_of_nearest_mines == INT_MIN)
                number++;
            if (i != (wndprop.Gycount - 1) && tab[i + 1][j].number_of_nearest_mines == INT_MIN)
                number++;
            if ((j != wndprop.Gxcount && i != (wndprop.Gycount - 1)) && tab[i + 1][j + 1].number_of_nearest_mines == INT_MIN)
                number++;
            tab[i][j].number_of_nearest_mines = number;
        }
    }

}
void ClearBoard(Board** &tab, WindowProperty wndprop)
{
    for (int i = 0; i < wndprop.Gycount; i++)
        for (int j = 0; j < wndprop.Gxcount; j++)
        {
            tab[i][j].number_of_nearest_mines = 0;
            DestroyWindow(tab[i][j].child_window);
        }        
    for (int i = 0; i < wndprop.Gycount; i++)
        free(tab[i]);
    free(tab);
}
void PutFlague(HWND &hWnd,HINSTANCE hInst)
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    HDC hdc = GetDC(hWnd);
    HBITMAP Flaga = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    HDC CompDC = CreateCompatibleDC(hdc);
    HBITMAP OBitmap = (HBITMAP)SelectObject(CompDC, Flaga);
    BITMAP bmInfo;
    GetObject(Flaga, sizeof(bmInfo), &bmInfo);
    BitBlt(hdc, 0, 0, rc.right, rc.bottom, CompDC, 0, 0, SRCCOPY);
    StretchBlt(hdc, 0, 0, 25, 25, CompDC, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY);
    SetProp(hWnd, _T("flague"), (HANDLE)true);
    SelectObject(CompDC, OBitmap);
    DeleteObject(Flaga);
    DeleteDC(CompDC);
}
void DeleteFlag(HWND& hWnd, HINSTANCE hInst)
{
    SetProp(hWnd, _T("flague"), (HANDLE)false);
    HDC hdc = GetDC(hWnd);
    RECT rc;
    GetClientRect(hWnd, &rc);
    HBRUSH brush = CreateSolidBrush(RGB(96, 96, 96)); // background light silver
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, -1, -1, rc.right - rc.left+1, rc.bottom - rc.top+1);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}
void Boom(HWND &hWnd, WindowProperty &wnd,GameProps & gg)
{
    FillBehind(hWnd);
	HDC hdc = GetDC(hWnd);
	//HDC COMPDC = CreateCompatibleDC(hdc);
    HBRUSH PedzelZiel, Pudelko;
    PedzelZiel = CreateSolidBrush(RGB(0,0,0));
    Pudelko = (HBRUSH)SelectObject(hdc, PedzelZiel);
    Ellipse(hdc, 4, 4, 21, 21);
    SelectObject(hdc, Pudelko);
    DeleteObject(PedzelZiel);
    ReleaseDC(hWnd, hdc);
    
    if (wnd.Debug == false || wnd.Debug == true)
    {
        gg.EndGame = true;
        gg.Gtimerstart = false;
        MessageBox(wnd.main, _T("BOOM!"), _T("Mine"), MB_ICONERROR | MB_APPLMODAL);
        MessageBox(wnd.main, L"Lose!", L"Minesweeper", MB_OK);
    }
}

void FillBehind(HWND& hWnd)
{
    HDC hdc = GetDC(hWnd);
    RECT rc;
    GetClientRect(hWnd, &rc);
    HBRUSH brush = CreateSolidBrush(RGB(211, 211, 211)); // background light silver
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, -1, -1, rc.right - rc.left+1 , rc.bottom - rc.top+1);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}
// Filing colour of text writen when Open Field.
void TempToColour(HWND& hWnd, WindowProperty& wnd, Board**& tab, int i, int j)
{
    int ColorTab[] = { 0,0,220, 0,190,20, 210,0,0, 0,0,110, 165, 8, 145, 193, 163, 64, 169, 159, 246, 255, 178, 32 };
    FillBehind(hWnd);
    HDC hdc = GetDC(hWnd);
    RECT rc;
    GetClientRect(hWnd, &rc);
    TCHAR s[2];
    bool printnr = tab[i][j].number_of_nearest_mines == 0 ? false : true;
    _itow_s(tab[i][j].number_of_nearest_mines, s, 16);
    int val = tab[i][j].number_of_nearest_mines == 0? tab[i][j].number_of_nearest_mines : tab[i][j].number_of_nearest_mines-1;
    SetTextColor(hdc, RGB(ColorTab[val*3], ColorTab[val * 3+1], ColorTab[val * 3+2]));
    SetBkColor(hdc, RGB(211, 211, 211)); // text background light silver
    if(printnr) DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    SetProp(hWnd, L"shown", (HANDLE)true);
    ReleaseDC(hWnd, hdc);
}
void RecurrColoringBoard(HWND hWnd, WindowProperty& wnd, Board**& tab)
{
    if ((bool)GetProp(hWnd, L"shown") == true || (bool)GetProp(hWnd, L"flague") == true || (bool)GetProp(hWnd, L"mine") == true)
        return;
    int i = (int)GetProp(hWnd, L"i-idx");
    int j = (int)GetProp(hWnd, L"j-idx");
    bool gofar = tab[i][j].number_of_nearest_mines == 0 ? true : false;
    TempToColour(hWnd, wnd, tab, i, j);

    // Above element:
    if (i != 0 && j != 0 && gofar)
        RecurrColoringBoard(tab[i - 1][j - 1].child_window, wnd, tab);
    if (i != 0 && gofar)
        RecurrColoringBoard(tab[i - 1][j].child_window, wnd, tab);
    if (i != 0 && j != wnd.Gxcount-1 && gofar)
        RecurrColoringBoard(tab[i - 1][j + 1].child_window, wnd, tab);
    
    // Same Row:
    if (j != 0 && gofar)
        RecurrColoringBoard(tab[i][j - 1].child_window, wnd, tab);
    if (j != wnd.Gxcount - 1 && gofar)
        RecurrColoringBoard(tab[i][j+1].child_window, wnd, tab);
    // Under:

    if (i != wnd.Gycount-1 && j != 0 && gofar)
        RecurrColoringBoard(tab[i + 1][j - 1].child_window, wnd, tab);
    if (i != wnd.Gycount - 1 && gofar)
        RecurrColoringBoard(tab[i + 1][j].child_window, wnd, tab);
    if (i != wnd.Gycount - 1 && j != wnd.Gxcount - 1 && gofar)
        RecurrColoringBoard(tab[i + 1][j + 1].child_window, wnd, tab);
}
void LeftButtonCLicked_ColoringBoard(HWND &hWnd, WindowProperty &wnd, Board ** &tab, GameProps & gg)
{
    int i = (int)GetProp(hWnd, L"i-idx");
    int j = (int)GetProp(hWnd, L"j-idx");
    bool BOOM = (bool)GetProp(hWnd, L"mine");
    //SetProp(hWnd, L"shown", (HANDLE)true);
    if (BOOM) // tutaj zrob ¿e kaput!
        Boom(hWnd, wnd, gg);
    else
    {
        RecurrColoringBoard(hWnd, wnd, tab);
        //TempToColour(hWnd, wnd, tab, i, j);
    }        
}
void FillBehindDebug(HWND& hWnd)
{
    HDC hdc = GetDC(hWnd);
    RECT rc;
    GetClientRect(hWnd, &rc);
    HBRUSH brush = CreateSolidBrush(RGB(169, 169, 169)); // background light silver
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, -1, -1, rc.right - rc.left + 1, rc.bottom - rc.top + 1);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}
void ColoringForDebuging(HWND& hWnd, WindowProperty& wnd, Board**& tab, int i, int j)
{
    int ColorTab[] = { 0,0,220, 0,190,20, 210,0,0, 0,0,110, 165, 8, 145, 193, 163, 64, 169, 159, 246, 255, 178, 32 };
    FillBehindDebug(hWnd);
    HDC hdc = GetDC(hWnd);
    RECT rc;
    GetClientRect(hWnd, &rc);
    TCHAR s[2];
    bool printnr = tab[i][j].number_of_nearest_mines == 0 ? false : true;
    if (tab[i][j].number_of_nearest_mines == INT_MIN)
    {
        //FillBehindDebug(hWnd);
        HDC hdc = GetDC(hWnd);
        //HDC COMPDC = CreateCompatibleDC(hdc);
        HBRUSH PedzelZiel, Pudelko;
        PedzelZiel = CreateSolidBrush(RGB(0, 0, 0));
        Pudelko = (HBRUSH)SelectObject(hdc, PedzelZiel);
        Ellipse(hdc, 4, 4, 21, 21);
        SelectObject(hdc, Pudelko);
        DeleteObject(PedzelZiel);
        ReleaseDC(hWnd, hdc);
    }
    else
    {
        int val = tab[i][j].number_of_nearest_mines == 0 ? tab[i][j].number_of_nearest_mines : tab[i][j].number_of_nearest_mines - 1;
        _itow_s(tab[i][j].number_of_nearest_mines, s, 16);
        SetTextColor(hdc, RGB(ColorTab[val * 3], ColorTab[val * 3 + 1], ColorTab[val * 3 + 2]));
        SetBkColor(hdc, RGB(169, 169, 169)); // text background light silver
        if (printnr) DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        //SetProp(hWnd, L"shown", (HANDLE)true);
        ReleaseDC(hWnd, hdc);
    }

}
void FillToCover(HWND& hWnd)
{
    HDC hdc = GetDC(hWnd);
    RECT rc;
    GetClientRect(hWnd, &rc);
    HBRUSH brush = CreateSolidBrush(RGB(96, 96, 96)); // background light silver
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, -1, -1, rc.right - rc.left + 1, rc.bottom - rc.top + 1);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}
void DebugColoring(Board**& tab, WindowProperty& wnd)
{
    for (int i = 0; i < wnd.Gycount; i++)
    {
        for (int j = 0; j < wnd.Gxcount; j++)
        {
            if ((bool)GetProp(tab[i][j].child_window, L"shown") == false && (bool)GetProp(tab[i][j].child_window, L"flague") == false)
            {
                ColoringForDebuging(tab[i][j].child_window, wnd, tab, i, j);
            }
        }
    }
}
void CoverDebugColoring(Board**& tab, WindowProperty& wnd)
{
    for (int i = 0; i < wnd.Gycount; i++)
    {
        for (int j = 0; j < wnd.Gxcount; j++)
        {
            if ((bool)GetProp(tab[i][j].child_window, L"shown") == false && (bool)GetProp(tab[i][j].child_window, L"flague") == false)
            {
                FillToCover(tab[i][j].child_window);
            }
        }
    }
}
