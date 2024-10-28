#pragma once
#include <vector>
#include "framework.h"
#include "Bullet.h"
#include "Collider.h"
#include "EffectObject.h"

class Boss;

#define PLAYER_IDEL_SIZE 5
#define PLAYER_IDEL_SIZE 5

#define WORLD_SPRITE_SIZE_X 16
#define WORLD_SPRITE_SIZE_Y 8

#define GROUND_POSITION_Y 700
#define DASH_SPEED (4.0)

#define BULLET_MAX_COUNT 50
#define GRACE_PERIOD 2000

enum class EPlayerState
{
	World = 0,
	Intro,
	Idle,
	RightRun,
	RightJump,
	RightDash,
	RightAirDash,
	DownStartRight,
	DownIdleRight,
	DownShootingRight,
	ShootingRunRight,
	ShootingRunRightUp,
	ShootingRight,
	ShootingRightUp,
	ShootingRightDown,
	ShootingUp,
	ShootingDown,
	AimRight,
	AimRightUp,
	AimRightDown,
	AimUp,
	AimDown,
	SCAttackRight,
	SCAttackRightUp,
	SCAttackRightDown,
	SCAttackUp,
	SCAttackDown,
	AirSCAttackRight,
	AirSCAttackRightUp,
	AirSCAttackRightDown,
	AirSCAttackUp,
	AirSCAttackDown,
	HitRight,
	ParryRight,
	ParryPinkRight,
	Ghost,
	Max
};

enum class EPlayerWorldState
{
	Idle = 9,
	RightWalk = 13,
	BackRightWalk = 14,
	FrontRightWalk = 15,
	BackWalk = 15,
	FrontWalk = 12,
	LeftWalk = 13,
	BackLeftWalk = 14,
	FrontLeftWalk = 15,
};

enum class EWorldSpriteY
{
	BackWalk = 0,
	BackRightWalk,
	RightWalk,
	RightWalkFast,
	FrontRightWalk,
	FrontIdle,
	FrontWalk,
	Action
};

class Player
{
private:
	std::vector<Bullet*>	bullets;
	std::vector<EffectObject*> effects;

	int						x;
	int						y;
	int						health;

	int						camera_x;
	int						camera_y;
	int						curAnimMax;
	int						curAnimCnt;
	int						specialAttackCount;

	clock_t					lastTime;
	bool					inWorld;
	bool					inTutorial;

	bool					isDown;
	bool					isJumping;
	bool					isDashing;
	bool					isDashAndJump;
	bool					isShooting;
	bool					isLockin;
	bool					isSpecialAttack;
	bool					isSpecialAttackAndJump;
	bool					isParry;
	bool					isDoubleParry;
	bool					lastForward;
	bool					setJumpDust;
	bool					bInput;
	bool					startStage;
	bool					isDeath;

	const int				JumpMaxPower = 55;
	int						curJumpPower;

	float					speed;
	clock_t					startChangeStateTime;
	clock_t					lastShootingTime;
	clock_t					createRunDustTime;

	EPlayerState			state;
	EPlayerState			prevState;
	EPlayerWorldState		worldState;
	EWorldSpriteY			worldSpriteY;
	std::vector<std::vector<Image*>>	playerImg;

	Collider				collider;
	bool					isHit;
	bool					isGrace;
	clock_t					isHitTime;

public:
	POINT					dir = { 0, 0 };
	POINT					forwardDir = { 0, 0 };

private:
	void		CreateImage();
	void		ParsingToImagePath(EPlayerState state, int spriteSize, TCHAR* path, int startNum);

public:
	Player();
	Player(int x, int y);
	~Player();

	void		Draw(HDC& hdc, Graphics& grapichs);
	void		Update();
	Collider*	GetCollider()								{ return &collider; }	
	bool		Collided(Boss* boss);

	void		Shooting();
	void		SetCameraPos(int x, int y);
	void		SetCameraPosX(int x);
	void		SetCameraPosY(int y);
	int			GetCameraPosX()								{ return camera_x; }
	void		UpdateCameraPosX(int x);

	void		SetState(EPlayerWorldState state, EWorldSpriteY spriteY);
	void		SetState(EPlayerState state);
	void		SetStateOnce(EPlayerState state);
	void		SetInWorld(bool isWorld);
	void		SetInTutorial(bool isTutorial)				{ inTutorial = isTutorial; }
	bool		GetInTutorial()								{ return inTutorial; }

	void		Move(int x, int y);
	float		GetSpeed()									{ return speed; }
	void		SetSpeed(float speed);
	void		Turn();
	void		SetDirection(int x, int y);
	void		SetDirection(int forwardX);

	int			GetXPos()									{ return x; }
	int			GetYPos()									{ return y; }
	void		SetXPos(int x);
	void		SetYPos(int y);
	void		Parry();
	void		SetRunDustEffect();

	bool		GetIsJumping()								{ return isJumping; }
	void		SetIsJumping(bool isJumping);
	int			GetJumpPower()								{ return curJumpPower; }
	void		SetJumpPower(int jumpPower)					{ curJumpPower = jumpPower; }
	void		SetJumpDown();
	bool		GetIsDashing()								{ return isDashing; }
	void		SetIsDashing(bool isDashing);
	bool		GetIsDown()									{ return isDown; }
	void		SetIsDown(bool isDown);
	bool		GetIsShooting()								{ return isShooting; }
	void		SetIsShooting(bool isShooting);
	bool		GetIsLockin()								{ return isLockin; }
	void		SetIsLockin(bool isLockin);
	bool		GetIsSpecialAttack()						{ return isSpecialAttack; }
	void		SetIsSpecialAttack(bool isSpecialAttack);
	bool		GetLastForward()							{ return lastForward; }
	void		SetLastForward(bool lastForward);
	bool		GetJumpDust()								{ return setJumpDust; }
	void		SetJumpDust(bool jumpDust)					{ setJumpDust = jumpDust; }
	bool		GetCanInput()								{ return bInput; }
	void		SetCanInput(bool bInput)					{ this->bInput = bInput; }
	bool		GetIsHit()									{ return isHit; }
	bool		GetIsGraceTime()							{ return isGrace; }
	void		DecreaseHealth();
	int			GetHealth()									{ return health; }
	int			GetSpecailAttackCount()						{ return specialAttackCount; }

	bool		ReadyToSetState();

	void		SetStage();
	bool		CanMoveDirX();
	
	EPlayerWorldState	GetWorldState()						{ return worldState; }
	EPlayerState		GetPlayerState()					{ return state; }

	std::vector<Bullet*>		GetBullets()						{ return bullets; }
};