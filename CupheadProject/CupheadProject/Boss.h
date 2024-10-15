#pragma once
#include "framework.h"
#include "Collider.h"
#include "Player.h"
#include <vector>

enum class EBossState
{
	Intro,
	Jump,
	AirUp,
	AirDown,
	Max
};

class Boss
{
	std::vector<std::vector<Image*>> images;
	Player*					player;
	int						x;
	int						targetX;
	int						y;
	int						phase;
	int						curAnimMax;
	int						curAnimCnt;
	int						dirX;
	clock_t					animLastTime;
	EBossState				state;
	Collider				drawCollider;
	Collider				collider;
	bool					isHit;
	clock_t					isHitTime;
	clock_t					startChangeStateTime;
	
	bool					isJumping;
	const int				JumpMaxPower = 65;
	int						curJumpPower;
	
public:
	Boss();
	~Boss();
	float		Lerp(float a, float b, float alpha);

	void		SetPlayer(Player* player);
	void		CreateImage();
	void		ParsingToImagePath(EBossState state, int spriteSize, TCHAR* path, int startNum);
	void		ChangeFromStartState();
	void		CheckAnimCount();

	void		Draw(HDC& hdc, Graphics& graphics);
	void		Update();
	void		Hit();
	void		Jump();

	void		SetCollider();
	void		SetJumpState();
	bool		GetIsJumping()		{ return isJumping; }
	Collider*	GetCollider()		{ return &collider; }
};

