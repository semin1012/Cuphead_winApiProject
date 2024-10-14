#pragma once
#include "framework.h"
#include "Collider.h"
#include <vector>

enum class EBossState
{
	Intro,
	Max
};

class Boss
{
	std::vector<std::vector<Image*>> images;
	int						x;
	int						y;
	int						phase;
	int						curAnimMax;
	int						curAnimCnt;
	int						dirX;
	clock_t					animLastTime;
	EBossState				state;
	Collider				drawCollider;
	Collider				collider;
	bool					beAttacked;
	clock_t					beAttackedTime;
	
public:
	Boss();
	~Boss();

	void		Draw(HDC& hdc, Graphics& graphics);
	void		Update();
	void		CreateImage();
	void		ParsingToImagePath(EBossState state, int spriteSize, TCHAR* path, int startNum);
	void		BeAttacked();

	Collider*	GetCollider()		{ return &collider; }
};

