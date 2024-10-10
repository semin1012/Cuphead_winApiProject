// CupheadProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <queue>
#include <string>
#include "framework.h"

#include "Collider.h"
#include "Background.h"
#include "TitleMap.h"
#include "WorldMap.h"
#include "GameManager.h"
#include "FadeEffect.h"
#include "CupheadProject.h"
#include "commdlg.h"
#pragma comment(lib, "Msimg32.lib")

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

using namespace std;
#define MAX_LOADSTRING 100
#define TIMER_KEYSTATE 0

#pragma region WinMain
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


RECT                rectView;
GameManager* gameMgr;
void Init(HWND hWnd);


/* -------- Double Buffering -------- */
HDC                 hdc, MemDC, tmpDC;
HBITMAP             BackBit, oldBackBit;
RECT                bufferRT;
PAINTSTRUCT         ps;

void CreateDoubbleBuffering(HWND hWnd);
void EndDoubleBuffering(HWND hWnd);
/* ---------------------------------- */


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

    gameMgr->Gdi_End();

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


// timer
VOID CALLBACK KeyStateProc(HWND, UINT, UINT_PTR, DWORD);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static LPPOINT mousePos;
    gameMgr->WndProc(hWnd, message, wParam, lParam);

    switch (message)
    {
    case WM_CREATE:
    {
        SetTimer(hWnd, TIMER_KEYSTATE, 20, KeyStateProc);
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
        case ID_WORLD_SAVE:
            gameMgr->GetBackground()->SaveMapInfo();
            break;
        case ID_WORLD_LOAD:
            gameMgr->GetBackground()->LoadMapInfo();
            break;
        case ID_WORLD_CLEAR:
            gameMgr->GetBackground()->ClearMapInfo();
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_KEYUP:
        if (gameMgr->GetPlayer() == nullptr)
            break;
        if (!gameMgr->GetIsTitle())
        {
            switch (wParam)
            {
            case VK_UP:
                if (gameMgr->GetPlayer()->dir.y == -1)
                    gameMgr->GetPlayer()->dir.y = 0;
                break;
            case VK_DOWN:
                if (gameMgr->GetPlayer()->dir.y == 1)
                    gameMgr->GetPlayer()->dir.y = 0;
                break;
            }
        }
        break;
    case WM_RBUTTONDOWN:
        gameMgr->SetMouseDrageState(true);
        gameMgr->SetMouseDeltaPos(hWnd);
        break;
    case WM_RBUTTONUP:
        gameMgr->SetMouseDrageState(false);
        break;
    case WM_CHAR:
        switch (wParam)
        {
        case 'D':
        case 'd':
            gameMgr->SetDebugMode();
            break;
        }
        break;
#pragma endregion
    case WM_LBUTTONDOWN:
        gameMgr->AddTile(hWnd, mousePos);
        break;
    case WM_TIMER:
        break;
    case WM_PAINT:
        CreateDoubbleBuffering(hWnd);

        gameMgr->Draw(hdc);

        gameMgr->Gdi_Draw(hdc);

        EndDoubleBuffering(hWnd);
        break;
    case WM_DESTROY:
        KillTimer(hWnd, TIMER_KEYSTATE);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
    }
}

void Init(HWND hWnd)
{
    GetClientRect(hWnd, &rectView);
    gameMgr = new GameManager(&rectView);
    gameMgr->Gdi_Init();
}

#pragma region Double Buffering
void CreateDoubbleBuffering(HWND hWnd)
{
    hdc = BeginPaint(hWnd, &ps);

    GetClientRect(hWnd, &bufferRT);
    MemDC = CreateCompatibleDC(hdc);
    SetStretchBltMode(MemDC, COLORONCOLOR);
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

VOID KeyStateProc(HWND hWnd, UINT message, UINT_PTR iTimerID, DWORD dwTime)
{
    InvalidateRect(hWnd, NULL, false);

    if (gameMgr->GetPlayer() == nullptr)
        return;

    if (gameMgr->GetMouseDragState())
        gameMgr->DragAndMoveWorldMap(hWnd);

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        gameMgr->GetPlayer()->dir.x = -1;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        gameMgr->GetPlayer()->dir.x = 1;

    if (GetAsyncKeyState(VK_UP) & 0x8000)
        gameMgr->GetPlayer()->dir.y = -1;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        gameMgr->GetPlayer()->dir.y = 1;

    if (gameMgr->GetIsWorld())
    {

        switch (gameMgr->GetPlayer()->dir.y)
        {
        // 아래로 이동
        case 1:
            if (gameMgr->GetPlayer()->dir.x == 0)
                gameMgr->GetPlayer()->SetState(EPlayerWorldState::FrontWalk, EWorldSpriteY::FrontWalk);
            else if (gameMgr->GetPlayer()->dir.x == 1)
                gameMgr->GetPlayer()->SetState(EPlayerWorldState::FrontRightWalk, EWorldSpriteY::FrontRightWalk);
            else 
                gameMgr->GetPlayer()->SetState(EPlayerWorldState::FrontLeftWalk, EWorldSpriteY::FrontRightWalk);
            break;
        // 위로 이동
        case -1:
            if (gameMgr->GetPlayer()->dir.x == 0)
                gameMgr->GetPlayer()->SetState(EPlayerWorldState::BackWalk, EWorldSpriteY::BackWalk);
            else if (gameMgr->GetPlayer()->dir.x == 1)
                gameMgr->GetPlayer()->SetState(EPlayerWorldState::BackRightWalk, EWorldSpriteY::BackRightWalk);
            else
                gameMgr->GetPlayer()->SetState(EPlayerWorldState::BackLeftWalk, EWorldSpriteY::BackRightWalk);
            break;
        // y축 제자리
        case 0:
            if (gameMgr->GetPlayer()->dir.x == 0)
                gameMgr->GetPlayer()->SetState(EPlayerWorldState::Idle, EWorldSpriteY::FrontIdle);
            else if (gameMgr->GetPlayer()->dir.x == 1)
                gameMgr->GetPlayer()->SetState(EPlayerWorldState::RightWalk, EWorldSpriteY::RightWalkFast);
            else if (gameMgr->GetPlayer()->dir.x == -1)
                gameMgr->GetPlayer()->SetState(EPlayerWorldState::LeftWalk, EWorldSpriteY::RightWalkFast);
            break;
        }
    }
    else
    {
        switch (gameMgr->GetPlayer()->dir.x)
        {
        case 0:
            gameMgr->GetPlayer()->SetState(EPlayerState::Idle);
            break;
        case -1:
            gameMgr->GetPlayer()->SetState(EPlayerState::LeftRun);
            break;
        case 1:
            gameMgr->GetPlayer()->SetState(EPlayerState::RightRun);
            break;
        }
    }

    int moveDistance = MOVE_DISTANCE;
    if (gameMgr->GetIsWorld())
        moveDistance /= 2;

    gameMgr->SetCameraPos((gameMgr->GetCameraXPos() + gameMgr->GetPlayer()->dir.x * moveDistance) * gameMgr->GetPlayer()->CanMoveDirX(),
        (gameMgr->GetCameraYPos() + gameMgr->GetPlayer()->dir.y * moveDistance) * gameMgr->GetIsWorld());
}


void Gdi_Draw(HDC hdc)
{
   

    // : png 출력
    // : 컬러 키값 빼고 png 출력
    //Image img2((WCHAR*)L"../images/zero_run.png");
    //w = img2.GetWidth() / SPRITE_COUNT;
    //h = img2.GetHeight() / SPRITE_DIRECTION;
    //int xStart = curFrame * w;
    //int yStart = 0; // 한쪽 방향

    //ImageAttributes imgAttr0;
    //imgAttr0.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));  // 블렌드를 해서 색깔 빼줄 수 있음
    //graphics.DrawImage(&img2, Rect(200, 100, w, h), xStart, yStart, w, h, UnitPixel, &imgAttr0);

    //// :
    //brush.SetColor(Color(64, 255, 0, 0));
    //graphics.FillRectangle(&brush, 100, 100, 200, 300);

    //// :
    //Image* pImg = nullptr;
    //pImg = Image::FromFile((WCHAR*)L"../images/sigong.png");
    //int xPos = 300;
    //int yPos = 200;
    //if (pImg)
    //{
    //    w = pImg->GetWidth();
    //    h = pImg->GetHeight();

    //    Gdiplus::Matrix mat;
    //    static int rot = 0;
    //    mat.RotateAt((rot % 360), Gdiplus::PointF(xPos + ((float)w / 2), yPos + ((float)h / 2)));
    //    graphics.SetTransform(&mat);
    //    graphics.DrawImage(pImg, xPos, yPos, w, h);
    //    rot += 10;

    //    mat.Reset();
    //    graphics.SetTransform(&mat);
    //}

    //// : 
    //ImageAttributes imgAttr;
    //imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));  // 블렌드를 해서 색깔 빼줄 수 있음
    //yPos = 300;

    //graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);

    //// : 반투명 이미지
    //if (pImg)
    //{
    //    REAL transparency = 0.5f;
    //    ColorMatrix colorMatrix =
    //    {
    //        1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    //        0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    //        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //        0.0f, 0.0f, 0.0f, transparency, 0.0f,
    //        0.0f, 0.0f, transparency, 0.0f, 1.0f
    //    };
    //    imgAttr.SetColorMatrix(&colorMatrix);
    //    xPos = 400;

    //    graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);


    //    // : 흑백 이미지
    //    ColorMatrix colorMatrix2 =
    //    { // R     G     B      
    //        0.3f, 0.3f, 0.3f, 0.0f, 0.0f,   // R
    //        0.6f, 0.6f, 0.6f, 0.0f, 0.0f,   // G
    //        0.1f, 0.1f, 0.1f, 0.0f, 0.0f,   // B
    //        0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //        0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    //    };
    //    imgAttr.SetColorMatrix(&colorMatrix2);
    //    xPos = 500;

    //    graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);

    //    // : x축 반전
    //    xPos = 600;
    //    pImg->RotateFlip(RotateNoneFlipX);
    //    graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);
    //}

    //if (pImg) delete pImg;
}