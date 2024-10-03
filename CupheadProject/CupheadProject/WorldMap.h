#pragma once
#include <vector>
#include "framework.h"
#define WORLD_MAP_SCALE (1.1)

class WorldMap
{
	RECT*				rectView;

public:
	CImage				leftMapImg;
	CImage				rightMapImg;
	CImage				leftOcean;
	CImage				rightOcean;


public:
	WorldMap();
	~WorldMap();
	void		Draw(HDC& hdc);
	void		CreateImage();
	void		SetRectView(RECT& rectView);

	int					x;
	int					y;
};

