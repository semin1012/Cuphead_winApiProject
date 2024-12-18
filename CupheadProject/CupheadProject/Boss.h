#pragma once
#include <vector>
#include "Collider.h"
#include "Player.h"
#include "Bullet.h"
#include "EffectObject.h"
#include "framework.h"
#include "Sound.h"

#define PATTERN_1_TIME 4000
#define HEALTH 100
#define TRANSITION_TIME 4000
#define CHANGE_STATE_MOVE 2000
#define PATTERN_2_TIME 3000

enum class EBossState
{
	Intro,
	Jump,
	AirUp,
	AirDown,
	Punch,
	AirUpTurn,
	TransitionToPh,
	Slime,
	Move,
	Death,
	Smash,
	Trans,
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
	TransitionToPh3,
	Slime,
	Ph3Intro,
	Ph3Transition,
	Ph3MoveRight,
	Ph3MoveLeft,
	Ph3Death,
	Ph3Smash,
	TransLeft,
	TransRight,
	Max
};

enum class EBossEffect
{
	MoveDust,
	MoveDirt,
	IntroDust,
	IntroDustBack,
	SmashDust,
	Ph2JumpDust,
	DeathLightning,
	DeathStarA,
	DeathStarB,
	DeathCloud,
	Max
};

enum class EBossSoundType
{
	SmallIntro,
	SmallJump,
	SmallLand,
	SmallPunch,
	SmallTransition,
	BigJump,
	BigLand,
	BigPunch,
	BigDeath,
	Hit,
	StonDeath,
	StonDrop,
	StonSlide,
	StonSmash,
	StonSplat,
	Max
};

class Boss
{
	std::vector<std::vector<Image*>> images;
	std::vector<Image*>				 transitionImages;
	std::vector<EffectObject*> 		 effects;

	float					hp;
	Player*					player;
	Sound*					sound;
	int						x;
	int						targetX;
	int						y;
	int						phase;
	int						curAnimMax;
	int						curAnimCnt;
	int						dirX;
	int						deltaPosY;
	int						prevXPos;
	int						prevDirX;

	int						camera_x;
	int						camera_y;

	clock_t					animLastTime;
	EBossState				state;
	EBossStateSprite		animState;
	Collider				drawCollider;
	Collider				collider;
	bool					bAttackCollider;
	bool					isPossibleCollision;
	bool					isHit;
	clock_t					isHitTime;
	clock_t					startChangeStateTime;
	bool					isShowParry;
	clock_t					moveLastTime;

	bool					isCameraShake;
	
	bool					isJumping;
	const int				JumpMaxPower = 45;
	int						curJumpPower;
	EBossSoundType			curSoundType;
	
public:
	Boss();
	~Boss();
	float		Lerp(float a, float b, float alpha);

	void		SetPlayer(Player* player);
	void		CreateImage();
	void		ParsingToImagePath(EBossStateSprite state, int spriteSize, TCHAR* path, int startNum);
	void		ParsingToImagePath(int spriteSize, TCHAR* path, int startNum);
	void		ChangeFromStartState();
	void		ChangeState(EBossState state);
	void		CheckAnimState();
	void		CheckAnimCount();
	void		CheckHp();
	void		SetEffectImagesIn3Phase();

	void		Draw(HDC& hdc, Graphics& graphics);
	void		Update();
	void		Hit(Bullet* bullet);
	void		Jump();
	void		Turn();
	void		Move();
	void		Smash();
	void		SetJumpDirection();
	bool		GetIsPunch()				{ return state == EBossState::Punch; }
	bool		GetIsDeath()				{ return hp <= 0; }
	void		SetCameraPos(int x, int y);
	void		SetStage();

	bool		GetIsCameraShake()			{ return isCameraShake; }
	void		SetIsCameraShake(bool shake) { isCameraShake = shake; }
	void		SetCollider();
	void		SetJumpState();
	void		SetPunchState();
	void		SetIsShowParry(bool parry)	{ this->isShowParry = parry; }
	bool		GetIsJumping()				{ return isJumping; }
	Collider*	GetCollider();
	int			GetXPosition()				{ return x; };
	bool		GetIsTransitionToPhase();
	int			GetXDirection()				{ return dirX; }

	void		PlaySound(EBossSoundType type);
};

