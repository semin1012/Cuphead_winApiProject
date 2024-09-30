#pragma once
#include <vector>
#include "framework.h"

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
	RECT*				rectView;

public:
	void		Draw(HDC hdc);
	void		CreateBitmap();
	void		SetRectView(RECT& rectView);
};

