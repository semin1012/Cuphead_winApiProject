#pragma once
#include "framework.h"
#include "Background.h"
#include "HitObject.h"
#include <vector>

class TutorialMap : public Background
{
	CImage backgroundBackImage;
	Image* backgroundFrontImage;
	CImage tutorialText;
	CImage downText;
	CImage jump;
	CImage dash;
	CImage shoot;
	CImage lock;
	CImage parry;
	CImage parry2;
	CImage supperAttack;
	int	curAnimCnt;
	int curAnimMax;
	clock_t animLastTime;

public:
	TutorialMap();
	~TutorialMap();
	void		Draw(HDC& hdc, Graphics& graphics);
	void		CreateImage();

	void		CurlingToPosition(Image* image, Graphics& graphics, int x, int y);
	void		CurlingToPosition(CImage* image, HDC& hdc, int x, int y, int r, int g, int b);
	void		SaveMapInfo();
	void		LoadMapInfo();
	void		ClearMapInfo();
};

