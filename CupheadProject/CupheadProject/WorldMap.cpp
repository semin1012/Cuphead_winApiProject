#include "WorldMap.h"
#include "GameManager.h"
WorldMap::WorldMap()
{
	x = WORLD_START_POINT_X;
	y = WORLD_START_POINT_Y;
	CreateImage();
	width = leftMapImg.GetWidth() * WORLD_MAP_SCALE + rightMapImg.GetWidth() * WORLD_MAP_SCALE;
	height = leftMapImg.GetHeight() * WORLD_MAP_SCALE;
	tripper = (new Tripper(*rectView, 2000, 750, ETripperType::Basic));
	tutorialTripper = (new Tripper(*rectView, 370, 780, ETripperType::TutorialHouse));
	LoadMapInfo();
}

WorldMap::~WorldMap()
{

}

void WorldMap::Draw(HDC& hdc, Graphics& graphics)
{
	// hMemDc ���� �� ������ ���� 
	// hMemDc�� �迭�� �ؼ� ������ �Ӽ����� �����ϱ�
	leftOcean.Draw(hdc, x, y, leftOcean.GetWidth() * WORLD_MAP_SCALE, leftOcean.GetHeight() * WORLD_MAP_SCALE, 0, 0, leftOcean.GetWidth(), leftOcean.GetHeight());
	rightOcean.Draw(hdc, x + rightOcean.GetWidth() * WORLD_MAP_SCALE, y - 8, rightOcean.GetWidth() * WORLD_MAP_SCALE, rightOcean.GetHeight() * WORLD_MAP_SCALE, 0, 0, rightOcean.GetWidth(), leftMapImg.GetHeight());
	leftMapImg.Draw(hdc, x, y, leftMapImg.GetWidth() * WORLD_MAP_SCALE, leftMapImg.GetHeight() * WORLD_MAP_SCALE, 0, 0, leftMapImg.GetWidth(), leftMapImg.GetHeight());
	rightMapImg.Draw(hdc, x + rightMapImg.GetWidth() * WORLD_MAP_SCALE, y - 8, rightMapImg.GetWidth() * WORLD_MAP_SCALE, rightMapImg.GetHeight() * WORLD_MAP_SCALE, 0, 0, rightMapImg.GetWidth(), rightMapImg.GetHeight());

	DrawTrippers(hdc, graphics);
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

void WorldMap::SaveMapInfo()
{
	std::ofstream ofs("../Resource/Save/Map/WorldMapCollider.txt", std::ios::out);
	if (ofs.fail())
	{
		MessageBox(NULL, _T("WorldMapCollider.txt ���� ���� ����"), _T("����"), MB_OK);
		return;
	}

	ofs << colliders.size() << std::endl;
	for (auto collider : colliders)
	{
		ofs << collider->left << " " << collider->top << " " << collider->right << " " << collider->bottom << std::endl;
	}

	MessageBox(NULL, _T("WorldMapCollider.txt ���Ͽ� ���� ���� ������ �����߽��ϴ�."), _T("����"), MB_OK);
	ofs.close();
}

void WorldMap::LoadMapInfo()
{
	int size;

	std::ifstream ifs("../Resource/Save/Map/WorldMapCollider.txt", std::ios::in);
	if (ifs.fail())
	{
		MessageBox(NULL, _T("WorldMapCollider.txt ���� ���� ����"), _T("����"), MB_OK);
		return;
	}

	if (!ifs.eof())
		ifs >> size;

	while (!ifs.eof())
	{
		Collider* collider = new Collider();
		ifs >> collider->left >> collider->top >> collider->right >> collider->bottom;

		colliders.push_back(collider);
	}

	ifs.close();
}

void WorldMap::ClearMapInfo()
{
	for (auto it = colliders.begin(); it != colliders.end(); it++)
	{
		delete (*it);
	}

	colliders.clear();
}
