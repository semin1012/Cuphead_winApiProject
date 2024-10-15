#pragma once
#include "framework.h"
#include <vector>

class FrontImage
{
	std::vector<Image*> images;
	int					curAnimCnt;
	int					curAnimMax;
	clock_t				animLastTime;
	bool				isActive;

public:
	FrontImage();
	~FrontImage();

	void CreateImage();
	void Draw(HDC& hdc, Graphics& graphics);
	void ParsingToImagePath(int spriteSize, TCHAR* path, int startNum);
	bool GetIsActive()				{ return isActive; }
};

