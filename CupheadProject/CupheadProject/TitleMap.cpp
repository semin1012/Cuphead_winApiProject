#include "TitleMap.h"
#include <string>

TitleMap::TitleMap()
{
	x = 0;
	y = 0;
	curAnimCnt = 0;
	maxAnimCnt = 34;
	CreateImage();
	width = backgroundImg.GetWidth();
	height = backgroundImg.GetHeight();
	lastTime = clock();
	LoadMapInfo();
}

TitleMap::~TitleMap()
{
	characterImgs.clear();
}

void TitleMap::Draw(HDC& hdc)
{
	clock_t curTime = clock();
	
	if (curTime - lastTime > 30)
	{
		curAnimCnt++;

		if (curAnimCnt >= maxAnimCnt)
			curAnimCnt = 0;

		lastTime = clock();
	}

	backgroundImg.Draw(hdc, x, y, WINDOWS_WIDTH, WINDOWS_HEIGHT, 0, 0, backgroundImg.GetWidth(), backgroundImg.GetHeight());
	characterImgs[curAnimCnt].Draw(hdc, WINDOWS_WIDTH / 2 - characterImgs[curAnimCnt].GetWidth() / 2, WINDOWS_HEIGHT - characterImgs[curAnimCnt].GetHeight()
		, characterImgs[curAnimCnt].GetWidth(), characterImgs[curAnimCnt].GetHeight(), 0, 0, characterImgs[curAnimCnt].GetWidth(), characterImgs[curAnimCnt].GetHeight());
	pressKeyImg.Draw(hdc, x, y, WINDOWS_WIDTH, WINDOWS_HEIGHT, 0, 0, pressKeyImg.GetWidth(), pressKeyImg.GetHeight());
}

void TitleMap::CreateImage()
{
	TCHAR path[128] = L"../Resource/Image/Background/Title/cuphead_title_screen_00";
	ParsingToImagePath(34, path, 1); 

	backgroundImg.Load(L"../Resource/Image/Background/Title/background.png");
	pressKeyImg.Load(L"../Resource/Image/Background/Title/press_key.png");
}

// path�� startNum���� startNum + spriteSize������ ���ڸ� �̸����� �ؼ� Load�ϴ� �Լ�, �⺻�� png ������
void TitleMap::ParsingToImagePath(int spriteSize, TCHAR* path, int startNum)
{
	characterImgs.resize(spriteSize);

	for (int i = 0, j = startNum; i < spriteSize; i++, j++)
	{
		TCHAR temp[128];
		_tcscpy(temp, path);

		wchar_t num[3];
		_tcscpy(num, to_wstring(j).c_str());
		_tcscat(temp, num);
		_tcscat(temp, L".png");

		characterImgs[i].Load(temp);

		if (characterImgs[i] == NULL)
		{
			DWORD dwError = GetLastError();
			_tcscat(temp, L" ������ �� �� �����ϴ�.");
			MessageBox(NULL, temp, _T("����"), MB_OK);
		}
	}
}

void TitleMap::SaveMapInfo()
{
}

void TitleMap::LoadMapInfo()
{
}

void TitleMap::ClearMapInfo()
{
}
