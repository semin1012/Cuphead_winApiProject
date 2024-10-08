#pragma once
#include "framework.h"
#include "Background.h"

class StageMap : public Background
{
	CImage				groundImg;
	CImage				treeImg;
	CImage				woodImg;
	CImage				backgroundImg;
	std::vector<CImage>	waveLinesImg;

	int					curAnimCnt;
	int					maxAnimCnt;
	clock_t				lastTime;

public:
	StageMap();
	~StageMap();
	
	void		Draw(HDC& hdc);
	void		CreateImage();
	void		ParsingToImagePath(int spriteSize, TCHAR* path, int startNum);
};

