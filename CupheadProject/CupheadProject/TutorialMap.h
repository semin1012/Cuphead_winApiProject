#pragma once
#include "framework.h"
#include "Background.h"
#include "HitObject.h"
#include <vector>

class TutorialMap : public Background
{
	CImage backgroundBackImage;
	Image* backgroundFrontImage;
	Image* tutorialText;
	Image* downText;
	Image* jump;
	Image* dash;
	Image* shoot;
	Image* lock;
	Image* parry;
	Image* parry2;
	Image* supperAttack;
	int	curAnimCnt;
	int curAnimMax;
	clock_t animLastTime;

public:
	TutorialMap();
	~TutorialMap();
	void		Draw(HDC& hdc, Graphics& graphics);
	void		CreateImage();

	void		CurlingToPosition(Image* image, Graphics& graphics, int x, int y);
	void		SaveMapInfo();
	void		LoadMapInfo();
	void		ClearMapInfo();
};

