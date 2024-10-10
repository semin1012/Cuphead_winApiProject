#pragma once
#include "framework.h"

class FireBall
{
	const float		lifeTime = 2.0f;
	int				x;
	int				y;
	int				speed;
	POINT			dir;
	clock_t			createTime;
	clock_t			curTime;

public:
	FireBall(int x, int y, POINT dir);
	~FireBall();

	void		Draw(HDC& hdc);
	void		CreateImage();
};

