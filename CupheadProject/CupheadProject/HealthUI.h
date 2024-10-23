#pragma once
#include "framework.h"

class HealthUI
{
	Image*		image;
	int			x;
	int			y;
	int			health;

public:
	HealthUI();
	HealthUI(int health);
	~HealthUI();
	void	Draw(Graphics& graphics);
	void	SetHealth(int health);
};

