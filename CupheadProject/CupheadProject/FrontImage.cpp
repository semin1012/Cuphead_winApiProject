#include "FrontImage.h"
#include <string>

FrontImage::FrontImage()
{
	curAnimCnt = 0;
	curAnimMax = 0;
	isActive = true;
	animLastTime = clock();
	CreateImage();
}

FrontImage::~FrontImage()
{
	for (auto it = images.begin(); it != images.end(); it++)
		delete* it;

	images.clear();
}

void FrontImage::CreateImage()
{
	TCHAR temp[128] = L"../Resource/Image/Ready/FightText_GetReady_00";
	ParsingToImagePath(51, temp, 2);
}

void FrontImage::Draw(HDC& hdc, Graphics& graphics)
{
	if (!isActive)
		return;

	graphics.ResetTransform();
	clock_t curTime = clock();
	curAnimMax = images.size();

	if (curTime - animLastTime > 35)
	{
		curAnimCnt++;

		if (curAnimCnt >= curAnimMax)
		{
			curAnimCnt = 0;
			isActive = false;
		}

		animLastTime = clock();
	}

	if (!isActive)
		return;

	graphics.DrawImage(images[curAnimCnt], 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT);
}

void FrontImage::ParsingToImagePath(int spriteSize, TCHAR* path, int startNum)
{
	images.resize(spriteSize);
	curAnimMax = spriteSize;

	for (int i = 0, j = startNum; i <= spriteSize - startNum; i++, j++)
	{
		TCHAR temp[128];
		_tcscpy(temp, path);

		wchar_t num[3];
		if (j < 10)
		{
			_tcscpy(num, std::to_wstring(0).c_str());
			_tcscat(num, std::to_wstring(j).c_str());
		}
		else _tcscpy(num, std::to_wstring(j).c_str());
		_tcscat(temp, num);
		_tcscat(temp, L".png");

		Image* pImg = new Image(temp);
		images[i] = pImg;
	}
}
