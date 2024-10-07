#pragma once
#include <vector>
#include "framework.h"
#define WORLD_MAP_SCALE (1.1)

class WorldMap
{

private:
	RECT*				rectView;
	CImage				leftMapImg;
	CImage				rightMapImg;
	CImage				leftOcean;
	CImage				rightOcean;

	int					x;
	int					y;


public:
	WorldMap();
	~WorldMap();
	void		Draw(HDC& hdc);
	void		CreateImage();
	void		SetRectView(RECT& rectView);

	int			GetXPos();
	int			GetYPos();
	void		SetXPos(int x);
	void		SetYPos(int y);

	CImage*		GetLeftMapImg();
	CImage*		GetRightMapImg();
};

