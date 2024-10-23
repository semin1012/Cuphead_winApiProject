#pragma once
#include "framework.h"
class CardUI
{
	CImage	image;
	int		x;
	int		maxYPos;
	int		curYPos;
	bool	isActive;

public:
	CardUI(int xPos);
	~CardUI();
	void	Draw(HDC& hdc);

	void	FillPositionY();
	void	SetIsActive(bool isActive)	{ this->isActive = isActive; }
	bool	GetIsActive()				{ return isActive; }
};

