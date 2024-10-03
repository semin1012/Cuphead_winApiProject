#include "WorldMap.h"
#include "GameManager.h"
WorldMap::WorldMap()
{
	x = WORLD_START_POINT_X;
	y = WORLD_START_POINT_Y;
	CreateBitmap();
	CreateImage();
}

WorldMap::~WorldMap()
{
}

void WorldMap::Draw(HDC& hdc)
{
	// hMemDc ���� �� ������ ���� 
	// hMemDc�� �迭�� �ؼ� ������ �Ӽ����� �����ϱ�
	//HDC hMemDC;
	//HBITMAP hOldBitmap;
	int bx, by;
	//hMemDC = CreateCompatibleDC(hdc);
	
	// hdc, ��ġ x, y, �̹��� �ʺ�, ����, hMemDC, �̹����� ���� ���� x, y, �߶� �̹����� x, y, ���� ����
	// left
	//hOldBitmap = (HBITMAP)SelectObject(hMemDC, hLeftOcean);
	//bx = bitLeftOcean.bmWidth;
	//by = bitLeftOcean.bmHeight;
	//TransparentBlt(hdc, x, y, bx * WORLD_MAP_SCALE, by * WORLD_MAP_SCALE, hMemDC, 0, 0, bx, by, RGB(104, 156, 199));

	//hOldBitmap = (HBITMAP)SelectObject(hMemDC, hLeftMapImg);
	//bx = bitLeftMap.bmWidth;
	//by = bitLeftMap.bmHeight;
	//TransparentBlt(hdc, x, y, bx * WORLD_MAP_SCALE, by * WORLD_MAP_SCALE, hMemDC, 0, 0, bx, by, RGB(104, 156, 199));

	//// right
	//hOldBitmap = (HBITMAP)SelectObject(hMemDC, hRightOcean);
	//bx = bitRightMap.bmWidth;
	//by = bitRightMap.bmHeight;
	//TransparentBlt(hdc, bitLeftOcean.bmWidth * WORLD_MAP_SCALE + x, y, 
	// bx * WORLD_MAP_SCALE, by * WORLD_MAP_SCALE, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));

	//// ��Ʈ�� �ٲܰ�
	//hOldBitmap = (HBITMAP)SelectObject(hMemDC, hRightMapImg);
	//bx = bitRightMap.bmWidth;
	//by = bitRightMap.bmHeight;
	//TransparentBlt(hdc, bitLeftMap.bmWidth * WORLD_MAP_SCALE+ x, y - 7, bx * WORLD_MAP_SCALE, by * WORLD_MAP_SCALE, hMemDC, 0, 0, bx, by, RGB(104, 156, 199));


	//DeleteDC(hMemDC);
	//SelectObject(hMemDC, hOldBitmap);
	leftOcean.Draw(hdc, x, y, leftOcean.GetWidth() * WORLD_MAP_SCALE, leftOcean.GetHeight() * WORLD_MAP_SCALE, 0, 0, leftOcean.GetWidth(), leftOcean.GetHeight());
	rightOcean.Draw(hdc, x + rightOcean.GetWidth() * WORLD_MAP_SCALE, y, rightOcean.GetWidth() * WORLD_MAP_SCALE, rightOcean.GetHeight() * WORLD_MAP_SCALE, 0, 0, rightOcean.GetWidth(), leftMapImg.GetHeight());
	rightMapImg.Draw(hdc, x + rightMapImg.GetWidth() * WORLD_MAP_SCALE, y - 7, rightMapImg.GetWidth() * WORLD_MAP_SCALE, rightMapImg.GetHeight() * WORLD_MAP_SCALE, 0, 0, rightMapImg.GetWidth(), leftMapImg.GetHeight());
	leftMapImg.Draw(hdc, x, y, leftMapImg.GetWidth() * WORLD_MAP_SCALE, leftMapImg.GetHeight() * WORLD_MAP_SCALE, 0, 0, leftMapImg.GetWidth(), leftMapImg.GetHeight());
}

void WorldMap::CreateBitmap()
{
	hLeftMapImg = (HBITMAP)LoadImage(NULL, TEXT("../Resource/Image/Background/World/Large011.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hLeftMapImg == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("�� �̹���1 ������ �� �� �����ϴ�."), _T("����"), MB_OK);
	}
	else
		GetObject(hLeftMapImg, sizeof(BITMAP), &bitLeftMap);

	hRightMapImg = (HBITMAP)LoadImage(NULL, TEXT("../Resource/Image/Background/World/Large022.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hRightMapImg == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("�� �̹���1 ������ �� �� �����ϴ�."), _T("����"), MB_OK);
	}
	else
		GetObject(hRightMapImg, sizeof(BITMAP), &bitRightMap);

	hLeftOcean = (HBITMAP)LoadImage(NULL, TEXT("../Resource/Image/Background/World/Ocean01.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hLeftOcean == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("���� 01 ������ �� �� �����ϴ�."), _T("����"), MB_OK);
	}
	else
		GetObject(hLeftOcean, sizeof(BITMAP), &bitRightOcean);

	hRightOcean = (HBITMAP)LoadImage(NULL, TEXT("../Resource/Image/Background/World/Ocean02.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hRightOcean == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("���� 02 ������ �� �� �����ϴ�."), _T("����"), MB_OK);
	}
	else
		GetObject(hRightOcean, sizeof(BITMAP), &bitLeftOcean);
}

void WorldMap::CreateImage()
{
	// Image Load
	rightMapImg.Load(L"../Resource/Image/Background/World/Large02.png");
	leftMapImg.Load(L"../Resource/Image/Background/World/Large01.png");
	leftOcean.Load(L"../Resource/Image/Background/World/Ocean01.png");
	rightOcean.Load(L"../Resource/Image/Background/World/Ocean02.png");
}

void WorldMap::SetRectView(RECT& rectView)
{
	this->rectView = &rectView;
	CreateBitmap();
}
