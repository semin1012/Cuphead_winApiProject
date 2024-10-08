#pragma once
#include <vector>
#include "framework.h"
#include "Collider.h"
using namespace std;
#define PLAYER_IDEL_SIZE 5
#define PLAYER_IDEL_SIZE 5

#define WORLD_SPRITE_SIZE_X 16
#define WORLD_SPRITE_SIZE_Y 8

#define GROUND_POSITION_Y 700

enum class EPlayerState
{
	World = 0,
	Idle,
	RightRun,
	LeftRun,
	RightJump,
	LeftJump,
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
	int						x;
	int						y;
	int						camera_x;
	int						camera_y;
	int						currAnimMax;
	int						currAnimCnt;
	clock_t					lastTime;
	bool					inWorld;

	bool					isJumping;
	const int				JumpMaxPower = 45;
	int						curJumpPower;

	EPlayerState			state;
	EPlayerWorldState		worldState;
	EWorldSpriteY			worldSpriteY;
	vector<vector<CImage>>	playerImg;

	Collider				collider;

public:
	POINT					dir = { 0, 0 };

private:
	void		CreateImage();
	void		ParsingToImagePath(EPlayerState state, int spriteSize, TCHAR* path, int startNum);

public:
	Player();
	Player(int x, int y);
	~Player();

	void		Draw(HDC& hdc);
	void		Update();
	Collider*	GetCollider();

	void		SetCameraPos(int x, int y);
	void		SetCameraPosX(int x);
	void		SetCameraPosY(int y);
	void		SetState(EPlayerWorldState state, EWorldSpriteY spriteY);
	void		SetState(EPlayerState state);
	void		SetInWorld(bool isWorld);
	void		Move(int x, int y);
	int			GetXPos();
	int			GetYPos();
	void		SetXPos(int x);
	void		SetYPos(int y);

	bool		GetIsJumping();
	void		SetIsJumping(bool isJumping);

	void		SetStage();
	
	EPlayerWorldState	GetWorldState();
	EPlayerState		GetPlayerState();
};

