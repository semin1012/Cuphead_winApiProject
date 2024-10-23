#include "StageMap.h"
#include <string>
#include <fstream>

StageMap::StageMap()
{
	x = 0;
	y = 0;
	curAnimCnt = 0;
	maxAnimCnt = 12;
	CreateImage();
	lastTime = clock();
	width = groundImg.GetWidth();
	height = groundImg.GetHeight();
	LoadMapInfo();
}

StageMap::~StageMap()
{
}

void StageMap::Draw(HDC& hdc)
{
	clock_t curTime = clock();

	if (curTime - lastTime > 30)
	{
		curAnimCnt++;

		if (curAnimCnt >= maxAnimCnt)
			curAnimCnt = 0;

		lastTime = clock();
	}

	backgroundImg.Draw(hdc, x, y, backgroundImg.GetWidth(), backgroundImg.GetHeight(), 0, 0, backgroundImg.GetWidth(), backgroundImg.GetHeight());
	treeImg.Draw(hdc, x, 50 + y, treeImg.GetWidth(), treeImg.GetHeight(), 0, 0, treeImg.GetWidth(), treeImg.GetHeight());
	woodImg.Draw(hdc, -200 + x, 0 + y, woodImg.GetWidth(), woodImg.GetHeight(), 0, 0, woodImg.GetWidth(), woodImg.GetHeight());
	waveLinesImg[curAnimCnt].Draw(hdc, 525 + x, 420 + y, waveLinesImg[curAnimCnt].GetWidth(), waveLinesImg[curAnimCnt].GetHeight(), 0, 0, waveLinesImg[curAnimCnt].GetWidth(), waveLinesImg[curAnimCnt].GetHeight());
	groundImg.Draw(hdc, x, y, groundImg.GetWidth(), WINDOWS_HEIGHT, 0, 0, groundImg.GetWidth(), groundImg.GetHeight());
}

void StageMap::CreateImage()
{
	TCHAR path[128] = L"../Resource/Image/Background/Stage/slime_bg_stream_00";
	ParsingToImagePath(12, path, 1);

	groundImg.Load(L"../Resource/Image/Background/Stage/slime_bg_mg_main_ground.png");
	treeImg.Load(L"../Resource/Image/Background/Stage/slime_bg_bg_evergreens.png");
	woodImg.Load(L"../Resource/Image/Background/Stage/slime_bg_bg_forest.png");
	backgroundImg.Load(L"../Resource/Image/Background/Stage/slime_bg_bg_far_forest.png");
	// ../Resource/Image/Background/Stage/slime_bg_stream_00
}

void StageMap::ParsingToImagePath(int spriteSize, TCHAR* path, int startNum)
{
	waveLinesImg.resize(spriteSize);

	for (int i = 0, j = startNum; i < spriteSize; i++, j++)
	{
		TCHAR temp[128];
		_tcscpy(temp, path);

		wchar_t num[3];
		_tcscpy(num, std::to_wstring(j).c_str());
		_tcscat(temp, num);
		_tcscat(temp, L".png");

		waveLinesImg[i].Load(temp);

		if (waveLinesImg[i] == NULL)
		{
			DWORD dwError = GetLastError();
			_tcscat(temp, L" 파일을 열 수 없습니다.");
			MessageBox(NULL, temp, _T("에러"), MB_OK);
		}
	}

}

void StageMap::SaveMapInfo()
{
	std::ofstream ofs("../Resource/Save/Map/Stage1MapCollider.txt", std::ios::out);
	if (ofs.fail())
	{
		MessageBox(NULL, _T("Stage1MapCollider.txt 파일 열기 실패"), _T("에러"), MB_OK);
		return;
	}

	ofs << colliders.size() << std::endl;
	for (auto collider : colliders)
	{
		ofs << collider->left << " " << collider->top << " " << collider->right << " " << collider->bottom << std::endl;
	}

	MessageBox(NULL, _T("Stage1MapCollider.txt 파일에 월드 맵의 정보를 저장했습니다."), _T("성공"), MB_OK);
	ofs.close();
}

void StageMap::LoadMapInfo()
{
	int size;

	std::ifstream ifs("../Resource/Save/Map/Stage1MapCollider.txt", std::ios::in);
	if (ifs.fail())
	{
		MessageBox(NULL, _T("Stage1MapCollider.txt 파일 열기 실패"), _T("에러"), MB_OK);
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

void StageMap::ClearMapInfo()
{
	for (auto it = colliders.begin(); it != colliders.end(); it++)
	{
		delete (*it);
	}

	colliders.clear();
}
