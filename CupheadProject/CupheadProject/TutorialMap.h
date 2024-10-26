#pragma once
#include "framework.h"
#include "Background.h"

class TutorialMap : public Background
{
	Image* backgroundBackImage;
	Image* backgroundFrontImage;

public:
	TutorialMap();
	~TutorialMap();
	void		Draw(HDC& hdc, Graphics& graphics);
	void		CreateImage();

	void	SaveMapInfo();
	void	LoadMapInfo();
	void	ClearMapInfo();
};

