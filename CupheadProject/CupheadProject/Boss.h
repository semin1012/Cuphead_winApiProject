#pragma once
#include <vector>
#include "Collider.h"
#include "Player.h"
#include "Bullet.h"
#include "framework.h"

#define PATTERN_1_TIME 4000
#define HEALTH 10

enum class EBossState
{
	Intro,
	Jump,
	AirUp,
	AirDown,
	Punch,
	AirUpTurn,
	TransitionToPh,
	Max
};

enum class EBossStateSprite
{
	Intro,
	Jump,
	AirUp,
	AirDown,
	Punch,
	AirUpTurn,
	TransitionToPh2,
	Ph2Jump,
	Ph2AirUp,
	Ph2AirDown,
	Ph2Punch,
	Ph2AirUpTurn,
	Max
};

class Boss
{
	std::vector<std::vector<Image*>> images;

	float					hp;

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
	EBossStateSprite		animState;
	Collider				drawCollider;
	Collider				collider;
	bool					isHit;
	bool					bAttackCollider;
	clock_t					isHitTime;
	clock_t					startChangeStateTime;
	bool					isShowParry;
	
	bool					isJumping;
	const int				JumpMaxPower = 65;
	int						curJumpPower;
	
public:
	Boss();
	~Boss();
	float		Lerp(float a, float b, float alpha);

	void		SetPlayer(Player* player);
	void		CreateImage();
	void		ParsingToImagePath(EBossStateSprite state, int spriteSize, TCHAR* path, int startNum);
	void		ChangeFromStartState();
	void		ChangeState(EBossState state);
	void		CheckAnimState();
	void		CheckAnimCount();
	void		CheckHp();

	void		Draw(HDC& hdc, Graphics& graphics);
	void		Update();
	void		Hit(Bullet* bullet);
	void		Jump();
	void		Turn();
	void		SetJumpDirection();
	bool		GetIsPunch()				{ return state == EBossState::Punch; }

	void		SetCollider();
	void		SetJumpState();
	void		SetPunchState();
	void		SetIsShowParry(bool parry)		{ this->isShowParry = parry; }
	bool		GetIsJumping()				{ return isJumping; }
	Collider*	GetCollider()				{ return &collider; }
	int			GetXPosition()				{ return x; };
	bool		GetIsTransitionToPhase();
	int			GetXDirection()				{ return dirX; }
};

