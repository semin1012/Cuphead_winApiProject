#pragma once
#include <vector>
#include "framework.h"
using namespace std;
#define PLAYER_IDEL_SIZE 5
#define WORLD_SPRITE_SIZE_X 16
#define WORLD_SPRITE_SIZE_Y 8

enum class EPlayerState
{
	World,
	Idle,
	Jump,
	Max
};

enum class EPlayerWorldState
{
	RightWalk,
	LeftWalk,

};

enum class EWorldSpriteCount
{
	IdleMax = 3,
	BackWalk = 15,
	BackRightWalk = 14,
};

class Player
{
private:
	int		x;
	int		y;
	int		camera_x;
	int		camera_y;
	int		currAnimMax;
	int		currAnimCnt;
	bool	inWorld;

	EPlayerState			state;
	vector<vector<CImage>>	playerImg;

	RECT					collider;

private:
	void		CreateImage();
	void		ParsingToImagePath(EPlayerState state, int spriteSize, TCHAR* path, int startNum);

public:
	Player();
	Player(int x, int y);
	~Player();

	void		Draw(HDC& hdc);
	RECT*		GetCollider();

	void		SetCameraPos(int x, int y);
};

