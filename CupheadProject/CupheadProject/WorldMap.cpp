#include "WorldMap.h"
#include "GameManager.h"
WorldMap::WorldMap()
{
	x = WORLD_START_POINT_X;
	y = WORLD_START_POINT_Y;
}

WorldMap::~WorldMap()
{
}

void WorldMap::Draw(HDC& hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;
	hMemDC = CreateCompatibleDC(hdc);
	
	// hdc, 위치 x, y, 이미지 너비, 높이, hMemDC, 이미지의 시작 지점 x, y, 잘라낼 이미지의 x, y, 투명 색상
	

	// left
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hLeftOcean);
	bx = bitLeftOcean.bmWidth;
	by = bitLeftOcean.bmHeight;
	TransparentBlt(hdc, x, y, bx * WORLD_MAP_SCALE, by * WORLD_MAP_SCALE, hMemDC, 0, 0, bx, by, RGB(104, 156, 199));

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hLeftMapImg);
	bx = bitLeftMap.bmWidth;
	by = bitLeftMap.bmHeight;
	TransparentBlt(hdc, x, y, bx * WORLD_MAP_SCALE, by * WORLD_MAP_SCALE, hMemDC, 0, 0, bx, by, RGB(104, 156, 199));


	// right
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hRightOcean);
	bx = bitRightMap.bmWidth;
	by = bitRightMap.bmHeight;
	TransparentBlt(hdc, bitLeftOcean.bmWidth * WORLD_MAP_SCALE + x, y, bx * WORLD_MAP_SCALE, by * WORLD_MAP_SCALE, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hRightMapImg);
	bx = bitRightMap.bmWidth;
	by = bitRightMap.bmHeight;
	TransparentBlt(hdc, bitLeftMap.bmWidth * WORLD_MAP_SCALE+ x, y - 7, bx * WORLD_MAP_SCALE, by * WORLD_MAP_SCALE, hMemDC, 0, 0, bx, by, RGB(104, 156, 199));


	DeleteDC(hMemDC);
	SelectObject(hMemDC, hOldBitmap);
}

void WorldMap::CreateBitmap()
{
	hLeftMapImg = (HBITMAP)LoadImage(NULL, TEXT("../Resource/Image/Background/World/Large011.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hLeftMapImg == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("맵 이미지1 파일을 열 수 없습니다."), _T("에러"), MB_OK);
	}
	else
		GetObject(hLeftMapImg, sizeof(BITMAP), &bitLeftMap);

	hRightMapImg = (HBITMAP)LoadImage(NULL, TEXT("../Resource/Image/Background/World/Large022.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hRightMapImg == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("맵 이미지1 파일을 열 수 없습니다."), _T("에러"), MB_OK);
	}
	else
		GetObject(hRightMapImg, sizeof(BITMAP), &bitRightMap);

	hLeftOcean = (HBITMAP)LoadImage(NULL, TEXT("../Resource/Image/Background/World/Ocean01.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hLeftOcean == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("오션 01 파일을 열 수 없습니다."), _T("에러"), MB_OK);
	}
	else
		GetObject(hLeftOcean, sizeof(BITMAP), &bitRightOcean);

	hRightOcean = (HBITMAP)LoadImage(NULL, TEXT("../Resource/Image/Background/World/Ocean02.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hRightOcean == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("오션 02 파일을 열 수 없습니다."), _T("에러"), MB_OK);
	}
	else
		GetObject(hRightOcean, sizeof(BITMAP), &bitLeftOcean);
}

void WorldMap::SetRectView(RECT& rectView)
{
	this->rectView = &rectView;
	CreateBitmap();
}
