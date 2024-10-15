#pragma once
#include "framework.h"
#include "Collider.h"
#include "Player.h"
#include <vector>

#define PATTERN_1_TIME 3000

enum class EBossState
{
	Intro,
	Jump,
	AirUp,
	AirDown,
	Punch,
	AirUpTurn,
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
	int						prevXPos;
	int						prevDirX;
	clock_t					animLastTime;
	EBossState				state;
	Collider				drawCollider;
	Collider				collider;
	bool					isHit;
	bool					bAttackCollider;
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
	void		ChangeState(EBossState state);
	void		CheckAnimCount();

	void		Draw(HDC& hdc, Graphics& graphics);
	void		Update();
	void		Hit();
	void		Jump();
	void		Turn();
	void		SetJumpDirection();

	void		SetCollider();
	void		SetJumpState();
	void		SetPunchState();
	bool		GetIsJumping()		{ return isJumping; }
	Collider*	GetCollider()		{ return &collider; }
};

