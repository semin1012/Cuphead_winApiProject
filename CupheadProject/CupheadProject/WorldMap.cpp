#include "WorldMap.h"

void WorldMap::Draw(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;
	hMemDC = CreateCompatibleDC(hdc);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hLeftOcean);
	bx = bitLeftOcean.bmWidth;
	by = bitLeftOcean.bmHeight;
	TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 255, 255));

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hLeftMapImg);
	bx = bitLeftMap.bmWidth;
	by = bitLeftMap.bmHeight;
	TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 255, 255));
	

	//hOldBitmap = (HBITMAP)SelectObject(hMemDC, hRightMapImg);
	//bx = bitRightMap.bmWidth;
	//by = bitRightMap.bmHeight;
	//TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 255, 255));


	//hOldBitmap = (HBITMAP)SelectObject(hMemDC, hRightMapImg);
	//bx = bitRightMap.bmWidth;
	//by = bitRightMap.bmHeight;
	//TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 255, 255));


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
}
