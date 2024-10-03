#pragma once
#include <vector>
#include "framework.h"
#define WORLD_MAP_SCALE (1.1)

class WorldMap
{
	HBITMAP				hLeftMapImg;
	HBITMAP				hRightMapImg;
	HBITMAP				hLeftOcean;
	HBITMAP				hRightOcean;
	BITMAP				bitLeftMap;
	BITMAP				bitRightMap;
	BITMAP				bitLeftOcean;
	BITMAP				bitRightOcean;


	CImage				leftMapImg;
	CImage				rightMapImg;
	CImage				leftOcean;
	CImage				rightOcean;

	RECT*				rectView;

public:
	WorldMap();
	~WorldMap();
	void		Draw(HDC& hdc);
	void		CreateBitmap();
	void		CreateImage();
	void		SetRectView(RECT& rectView);

	int					x;
	int					y;
};

