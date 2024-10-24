#pragma once
#include <vector>
#include "framework.h"
#include "Background.h"
#include "Tripper.h"
#define WORLD_MAP_SCALE (1.1)

class WorldMap : public Background
{

private:
	CImage				leftMapImg;
	CImage				rightMapImg;
	CImage				leftOcean;
	CImage				rightOcean;

public:
	WorldMap();
	~WorldMap();
	void		Draw(HDC& hdc, Graphics& graphics);
	void		CreateImage();

	CImage*		GetLeftMapImg();
	CImage*		GetRightMapImg();

	void	SaveMapInfo();
	void	LoadMapInfo();
	void	ClearMapInfo();
};

