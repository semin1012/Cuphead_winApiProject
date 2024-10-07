#pragma once
#include <vector>
#include "framework.h"
#include "Background.h"
using namespace std;


class TitleMap : public Background
{
	CImage				backgroundImg;
	CImage				pressKeyImg;
	std::vector<CImage> characterImgs;

	int					curAnimCnt;
	int					maxAnimCnt;
	clock_t				lastTime;

public:

	TitleMap();
	~TitleMap();
	void		Draw(HDC& hdc);
	void		CreateImage();
	void		ParsingToImagePath(int spriteSize, TCHAR* path, int startNum);
};

