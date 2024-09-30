﻿// CupheadProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <vector>
#include <queue>
#include "Collider.h"
#include "WorldMap.h"
#include "framework.h"
#include "CupheadProject.h"
#include "commdlg.h"
#pragma comment(lib, "Msimg32.lib")

using namespace std;
#define MAX_LOADSTRING 100
#define WINDOWS_WIDTH 1280
#define WINDOWS_HEIGHT 800
#define TILE_SIZE 30

#pragma region WinMain
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);



    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CUPHEADPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);


    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CUPHEADPROJECT));

    MSG msg;


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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CUPHEADPROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CUPHEADPROJECT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;
    RECT rt = { 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

    int captionY = GetSystemMetrics(SM_CYCAPTION) - 3;

    HWND hWnd = CreateWindowW(szWindowClass, _T("Cup Head"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, rt.right - rt.left, rt.bottom - rt.top + captionY, nullptr, nullptr, hInst, nullptr);

    //HWND hWnd = CreateWindowW(szWindowClass, _T("Cup Head"), WS_OVERLAPPEDWINDOW,
    //    CW_USEDEFAULT, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}



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

#pragma endregion


RECT                rectView;

HDC                 hdc, MemDC, tmpDC;
HBITMAP             BackBit, oldBackBit;
RECT                bufferRT;
PAINTSTRUCT         ps;
vector<Collider*>   worldMapCollisions;
WorldMap*           worldMap;

//void SetRectangle(RECT* rect, int left, int top, int right, int bottom);
void Init(HWND hWnd);
void AddTile(HWND& hWnd, LPPOINT& mousePos);
void CreateDoubbleBuffering(HWND hWnd);
void EndDoubleBuffering(HWND hWnd);
void ShowDebugCollider(HDC& hdc);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static LPPOINT mousePos;

    switch (message)
    {
    case WM_CREATE:
    {
        mousePos = new POINT;
        Init(hWnd);
        GetWindowRect(hWnd, &rectView);
        break;
#pragma region COMMAND
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

#pragma endregion
    case WM_LBUTTONDOWN:
    {
        AddTile(hWnd, mousePos);
        InvalidateRect(hWnd, NULL, true);
    }
        break;

    case WM_PAINT:
    {
        CreateDoubbleBuffering(hWnd);
        
        worldMap->Draw(hdc);
        ShowDebugCollider(hdc);

        EndDoubleBuffering(hWnd);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
    }
}

void SetRectangle(RECT* rect, int left, int top, int right, int bottom)
{
    rect->left = left;
    rect->top = top;
    rect->right = right;
    rect->bottom = bottom;
}

void Init(HWND hWnd)
{
    GetClientRect(hWnd, &rectView);

    worldMap = new WorldMap();
    worldMap->SetRectView(rectView);

    worldMap->CreateBitmap();
}

void AddTile(HWND& hWnd, LPPOINT& mousePos)
{
    GetCursorPos(mousePos);
    ScreenToClient(hWnd, mousePos);

    mousePos->x = mousePos->x / TILE_SIZE;
    mousePos->y = mousePos->y / TILE_SIZE;

    Collider* collider = new Collider(mousePos->x * TILE_SIZE, mousePos->y * TILE_SIZE, mousePos->x * TILE_SIZE + TILE_SIZE, mousePos->y * TILE_SIZE + TILE_SIZE);
    
    for (int i = 0; i < worldMapCollisions.size(); i++)
    {
        if (worldMapCollisions[i]->Compare(*collider))
        {
            worldMapCollisions.erase(worldMapCollisions.begin() + i);
            return;
        }
    }
   
    worldMapCollisions.push_back(collider);
    worldMapCollisions.erase(unique(worldMapCollisions.begin(), worldMapCollisions.end()), worldMapCollisions.end());

}

#pragma region Double Buffering
void CreateDoubbleBuffering(HWND hWnd)
{
    hdc = BeginPaint(hWnd, &ps);

    GetClientRect(hWnd, &bufferRT);
    MemDC = CreateCompatibleDC(hdc);
    BackBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
    oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
    PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, BLACKNESS);
    tmpDC = hdc;
    hdc = MemDC;
    MemDC = tmpDC;
}

void EndDoubleBuffering(HWND hWnd)
{
    tmpDC = hdc;
    hdc = MemDC;
    MemDC = tmpDC;
    GetClientRect(hWnd, &bufferRT);
    BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
    SelectObject(MemDC, oldBackBit);
    DeleteObject(BackBit);
    DeleteDC(MemDC);
    EndPaint(hWnd, &ps);
}
#pragma endregion

void ShowDebugCollider(HDC& hdc)
{
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);

    HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

    for (auto obstacle : worldMapCollisions)
    {
        Rectangle(hdc, obstacle->left, obstacle->top, obstacle->right, obstacle->bottom);
    }

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(myBrush);
    DeleteObject(hPen);
}