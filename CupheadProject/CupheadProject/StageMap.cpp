#include "StageMap.h"
#include <string>

StageMap::StageMap()
{
	x = 0;
	y = 0;
	curAnimCnt = 0;
	maxAnimCnt = 12;
	CreateImage();
	lastTime = clock();
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

	backgroundImg.Draw(hdc, 0, 0, backgroundImg.GetWidth(), backgroundImg.GetHeight(), 0, 0, backgroundImg.GetWidth(), backgroundImg.GetHeight());
	treeImg.Draw(hdc, 0, 50, treeImg.GetWidth(), treeImg.GetHeight(), 0, 0, treeImg.GetWidth(), treeImg.GetHeight());
	woodImg.Draw(hdc, -200, 0, woodImg.GetWidth(), woodImg.GetHeight(), 0, 0, woodImg.GetWidth(), woodImg.GetHeight());
	waveLinesImg[curAnimCnt].Draw(hdc, 525, 420, waveLinesImg[curAnimCnt].GetWidth(), waveLinesImg[curAnimCnt].GetHeight(), 0, 0, waveLinesImg[curAnimCnt].GetWidth(), waveLinesImg[curAnimCnt].GetHeight());
	groundImg.Draw(hdc, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, 0, 0, groundImg.GetWidth(), groundImg.GetHeight());
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
