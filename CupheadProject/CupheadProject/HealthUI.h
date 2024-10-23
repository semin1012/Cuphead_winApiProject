#pragma once
#include "framework.h"

class HealthUI
{
	CImage		image;
	int			x;
	int			y;
	int			health;

public:
	HealthUI();
	HealthUI(int health);
	~HealthUI();
	void	Draw(HDC& hdc);
	void	SetHealth(int health);
};

