#include "ClearMap.h"
#include <string>

ClearMap::ClearMap()
{
	curCupheadAnimCnt = 0;
	curClearTextAnimCnt = 0;
	lastTime = clock();
	CreateImage();
}

ClearMap::~ClearMap()
{
	for (auto it = cuphead.begin(); it != cuphead.end(); it++)
		delete (*it);
	cuphead.clear();

	for (auto it = clearText.begin(); it != clearText.end(); it++)
		delete (*it);
	clearText.clear();
}

void ClearMap::Draw(HDC& hdc, Graphics& graphics)
{
	clock_t curTime = clock();
	if (curTime - lastTime > 50)
	{
		curCupheadAnimCnt++;
		curClearTextAnimCnt++;

		if (curCupheadAnimCnt >= cuphead.size())
			curCupheadAnimCnt = 0;
		if (curClearTextAnimCnt >= clearText.size())
			curClearTextAnimCnt = 0;
		
		lastTime = clock();
	}

	background.Draw(hdc, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT);

	Rect cupHeadRect;
	cupHeadRect.Width = cuphead[curCupheadAnimCnt]->GetWidth() * 1.7f;
	cupHeadRect.X = 300 - cupHeadRect.Width / 2;
	cupHeadRect.Height = cuphead[curCupheadAnimCnt]->GetHeight() * 1.7f;
	cupHeadRect.Y = 850 - cupHeadRect.Height;
	graphics.DrawImage(cuphead[curCupheadAnimCnt], cupHeadRect);
	
	Rect textRect;
	textRect.Width = clearText[curClearTextAnimCnt]->GetWidth();
	textRect.X = WINDOWS_WIDTH / 2 - textRect.Width / 2;
	textRect.Height = clearText[curClearTextAnimCnt]->GetHeight();
	textRect.Y = 200 - textRect.Height;
	graphics.DrawImage(clearText[curClearTextAnimCnt], textRect);
}

void ClearMap::CreateImage()
{
	TCHAR temp[128];
	background.Load(L"../Resource/Image/Clear/BG/clear.png");

	_tcscpy(temp, L"../Resource/Image/Clear/Cuphead/winscreen_ch_0");
	ParsingToImagePath(cuphead, 7, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Clear/Text/winscreen_results_title_korean_0");
	ParsingToImagePath(clearText, 3, temp, 1);
}

void ClearMap::ParsingToImagePath(std::vector<Image*>& image, int spriteSize, TCHAR* path, int startNum)
{
	image.resize(spriteSize);

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
		image[i] = pImg;
	}
}

void ClearMap::SaveMapInfo()
{
}

void ClearMap::LoadMapInfo()
{
}

void ClearMap::ClearMapInfo()
{
}
