#include "WorldMap.h"
#include "GameManager.h"
WorldMap::WorldMap()
{
	x = WORLD_START_POINT_X;
	y = WORLD_START_POINT_Y;
	CreateImage();
	width = leftMapImg.GetWidth() * WORLD_MAP_SCALE + rightMapImg.GetWidth() * WORLD_MAP_SCALE;
	height = leftMapImg.GetHeight() * WORLD_MAP_SCALE;
	tripper = new Tripper();
}

WorldMap::~WorldMap()
{
	delete tripper;
}

void WorldMap::Draw(HDC& hdc)
{
	// hMemDc ���� �� ������ ���� 
	// hMemDc�� �迭�� �ؼ� ������ �Ӽ����� �����ϱ�
	leftOcean.Draw(hdc, x, y, leftOcean.GetWidth() * WORLD_MAP_SCALE, leftOcean.GetHeight() * WORLD_MAP_SCALE, 0, 0, leftOcean.GetWidth(), leftOcean.GetHeight());
	rightOcean.Draw(hdc, x + rightOcean.GetWidth() * WORLD_MAP_SCALE, y - 8, rightOcean.GetWidth() * WORLD_MAP_SCALE, rightOcean.GetHeight() * WORLD_MAP_SCALE, 0, 0, rightOcean.GetWidth(), leftMapImg.GetHeight());
	leftMapImg.Draw(hdc, x, y, leftMapImg.GetWidth() * WORLD_MAP_SCALE, leftMapImg.GetHeight() * WORLD_MAP_SCALE, 0, 0, leftMapImg.GetWidth(), leftMapImg.GetHeight());
	rightMapImg.Draw(hdc, x + rightMapImg.GetWidth() * WORLD_MAP_SCALE, y - 8, rightMapImg.GetWidth() * WORLD_MAP_SCALE, rightMapImg.GetHeight() * WORLD_MAP_SCALE, 0, 0, rightMapImg.GetWidth(), rightMapImg.GetHeight());

	tripper->SetCameraX(x);
	tripper->SetCameraY(y);

	if (tripper != nullptr)
		tripper->Draw(hdc);
}

void WorldMap::CreateImage()
{
	// Image Load
	rightMapImg.Load(L"../Resource/Image/Background/World/Large02.png");
	if (rightMapImg == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("Large02.png ������ �� �� �����ϴ�."), _T("����"), MB_OK);
	}
	leftMapImg.Load(L"../Resource/Image/Background/World/Large01.png");
	if (rightMapImg == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("Large01.png ������ �� �� �����ϴ�."), _T("����"), MB_OK);
	}
	leftOcean.Load(L"../Resource/Image/Background/World/Ocean01.png");
	if (rightMapImg == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("Ocean01.png ������ �� �� �����ϴ�."), _T("����"), MB_OK);
	}
	rightOcean.Load(L"../Resource/Image/Background/World/Ocean02.png");
	if (rightMapImg == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("Ocean02.png ������ �� �� �����ϴ�."), _T("����"), MB_OK);
	}
}

CImage* WorldMap::GetLeftMapImg()
{
	return &leftMapImg;
}

CImage* WorldMap::GetRightMapImg()
{
	return &rightMapImg;
}
