#include "TutorialMap.h"
#include <fstream>

TutorialMap::TutorialMap()
{
	CreateImage();
	width = 3000;
	height = 800;
	LoadMapInfo();
}

TutorialMap::~TutorialMap()
{
	delete backgroundBackImage;
	delete backgroundFrontImage;
	delete tutorialText;
	delete downText;
	delete jump;
	delete dash;
}

void TutorialMap::Draw(HDC& hdc, Graphics& graphics)
{
	Rect rect = { 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT };
	graphics.DrawImage(backgroundBackImage, rect);
	rect = { 0 + camera_x, 0 + camera_y, (int)tutorialText->GetWidth(), (int)tutorialText->GetHeight() };
	graphics.DrawImage(tutorialText, rect);
	rect = { 500 + camera_x, 0 + camera_y, (int)downText->GetWidth(), (int)downText->GetHeight() };
	graphics.DrawImage(downText, rect);
	rect = { 1200 + camera_x, 0 + camera_y, (int)jump->GetWidth(), (int)jump->GetHeight() };
	graphics.DrawImage(jump, rect);
	rect = { 1700 + camera_x, 0 + camera_y, (int)dash->GetWidth(), (int)dash->GetHeight() };
	graphics.DrawImage(dash, rect);
	rect = { 2200 + camera_x, 0 + camera_y, (int)shoot->GetWidth(), (int)shoot->GetHeight() };
	graphics.DrawImage(shoot, rect);
	// front
	rect = { 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT };
	graphics.DrawImage(backgroundFrontImage, rect);
}

void TutorialMap::CreateImage()
{
	backgroundBackImage = new Image(L"../Resource/Image/Background/Tutorial/back_image.png");
	backgroundFrontImage = new Image(L"../Resource/Image/Background/Tutorial/front_image.png");
	tutorialText = new Image(L"../Resource/Image/Background/Tutorial/Tutorial.png");
	downText = new Image(L"../Resource/Image/Background/Tutorial/down.png");
	jump = new Image(L"../Resource/Image/Background/Tutorial/jump.png");
	dash = new Image(L"../Resource/Image/Background/Tutorial/dash.png");
	shoot = new Image(L"../Resource/Image/Background/Tutorial/shoot.png");
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
