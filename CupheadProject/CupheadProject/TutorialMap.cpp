#include "TutorialMap.h"
#include <fstream>

TutorialMap::TutorialMap()
{
	CreateImage();
	width = 2000;
	height = 800;
	LoadMapInfo();
}

TutorialMap::~TutorialMap()
{
	delete backgroundBackImage;
	delete backgroundFrontImage;
}

void TutorialMap::Draw(HDC& hdc, Graphics& graphics)
{
	Rect rect = { 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT };
	graphics.DrawImage(backgroundBackImage, rect);
	graphics.DrawImage(backgroundFrontImage, rect);
}

void TutorialMap::CreateImage()
{
	backgroundBackImage = new Image(L"../Resource/Image/Background/Tutorial/back_image.png");
	backgroundFrontImage = new Image(L"../Resource/Image/Background/Tutorial/front_image.png");
}

void TutorialMap::SaveMapInfo()
{
	std::ofstream ofs("../Resource/Save/Map/TutorialMapSave.txt", std::ios::out);
	if (ofs.fail())
	{
		MessageBox(NULL, _T("TutorialMapSave.txt 파일 열기 실패"), _T("에러"), MB_OK);
		return;
	}

	ofs << colliders.size() << std::endl;
	for (auto collider : colliders)
	{
		ofs << collider->left << " " << collider->top << " " << collider->right << " " << collider->bottom << std::endl;
	}

	MessageBox(NULL, _T("TutorialMapSave.txt 파일에 월드 맵의 정보를 저장했습니다."), _T("성공"), MB_OK);
	ofs.close();
}

void TutorialMap::LoadMapInfo()
{
	int size;

	std::ifstream ifs("../Resource/Save/Map/TutorialMapSave.txt", std::ios::in);
	if (ifs.fail())
	{
		MessageBox(NULL, _T("TutorialMapSave.txt 파일 열기 실패"), _T("에러"), MB_OK);
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

void TutorialMap::ClearMapInfo()
{
	for (auto it = colliders.begin(); it != colliders.end(); it++)
	{
		delete (*it);
	}

	colliders.clear();
}
