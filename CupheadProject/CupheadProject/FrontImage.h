#pragma once
#include "framework.h"
#include <vector>

enum class EFrontImage
{
	Ready,
	FX,
	MAX
};

class FrontImage
{
	std::vector<Image*> images;
	EFrontImage			type;
	int					curAnimCnt;
	int					curAnimMax;
	clock_t				animLastTime;
	bool				isActive;

public:
	FrontImage(EFrontImage type);
	~FrontImage();

	void CreateImage();
	void Draw(HDC& hdc, Graphics& graphics);
	void ParsingToImagePath(int spriteSize, TCHAR* path, int startNum);
	bool GetIsActive()				{ return isActive; }
};

