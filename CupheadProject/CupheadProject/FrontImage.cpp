#include "FrontImage.h"
#include <string>

FrontImage::FrontImage(EFrontImage type)
{
	curAnimCnt = 0;
	curAnimMax = 0;
	isActive = true;
	animLastTime = clock();
	this->type = type;
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
	TCHAR temp[128];
	switch (type)
	{
	case EFrontImage::Ready:
		_tcscpy(temp, L"../Resource/Image/Ready/FightText_GetReady_00");
		ParsingToImagePath(51, temp, 2);
		break;
	case EFrontImage::FX:
		_tcscpy(temp, L"../Resource/Image/UI/FX/cuphead_screen_fx_0");
		ParsingToImagePath(30, temp, 1);
		break;
	}
}

void FrontImage::Draw(HDC& hdc, Graphics& graphics)
{
	if (!isActive)
		return;

	graphics.ResetTransform();
	clock_t curTime = clock();
	curAnimMax = images.size();

	if (curTime - animLastTime > 100)
	{
		curAnimCnt++;

		if (curAnimCnt >= curAnimMax)
		{
			curAnimCnt = 0;
			if (type == EFrontImage::Ready)
				isActive = false;
		}

		animLastTime = clock();
	}

	if (!isActive)
		return;
	if (type == EFrontImage::FX)
	{
		ImageAttributes imgAttr;
		ColorMatrix colorMatrix =
		{
			0.2f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.2f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.3f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		imgAttr.SetColorMatrix(&colorMatrix);
		graphics.DrawImage(images[curAnimCnt], Rect(0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT), 0, 0, images[curAnimCnt]->GetWidth(), images[curAnimCnt]->GetHeight(), UnitPixel, &imgAttr);
	}
	else graphics.DrawImage(images[curAnimCnt], 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT);
}

void FrontImage::ParsingToImagePath(int spriteSize, TCHAR* path, int startNum)
{
	images.resize(spriteSize);
	curAnimMax = spriteSize;

	for (int i = 0, j = startNum; i <= spriteSize - startNum; i++, j++)
	{
		TCHAR temp[128];
		_tcscpy(temp, path);

		wchar_t num[4];
		if (j < 10)
		{
			_tcscpy(num, std::to_wstring(0).c_str());
			_tcscat(num, std::to_wstring(0).c_str());
			_tcscat(num, std::to_wstring(j).c_str());
		}
		else if (j < 100)
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
