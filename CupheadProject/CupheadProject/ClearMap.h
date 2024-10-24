#pragma once
#include "framework.h"
#include "Background.h"

class ClearMap : public Background
{
	CImage background;
	std::vector<Image*> cuphead;
	std::vector<Image*> clearText;

	int					curCupheadAnimCnt;
	int					curClearTextAnimCnt;
	clock_t				lastTime;

public:
	ClearMap();
	~ClearMap();

	void		Draw(HDC& hdc, Graphics& graphics);
	void		CreateImage();
	void		ParsingToImagePath(std::vector<Image*>& image, int spriteSize, TCHAR* path, int startNum);

	void	SaveMapInfo();
	void	LoadMapInfo();
	void	ClearMapInfo();
};

