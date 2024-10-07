#pragma once
#include "framework.h"

class FadeEffect
{
	CImage		image;
	clock_t		lastTime;
	int			alpha;
	bool		isOut;
	bool		bEnd;

public:
	FadeEffect();
	~FadeEffect();

	void	Draw(HDC& hdc);
	bool	GetIsFadeIn();
	bool	GetIsEnd();
};

