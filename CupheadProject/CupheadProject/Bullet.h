#pragma once
#include "framework.h"
#include "Collider.h"
#include <vector>

enum class EBulletState
{
	Spawn,
	Loop,
	Death,
	EX_Loop,
	EX_Death,
	Max
};

class Bullet
{
	std::vector<std::vector<Image*>> images;
	const float				lifeTime = 2.0f;
	int						x;
	int						y;
	int						speed;
	int						curAnimCnt;
	int						curAnimMax;
	int						spawnAnimCnt;
	bool					isActive;
	POINT					dir;
	clock_t					createTime;
	clock_t					animLastTime;
	EBulletState			state;
	Collider				collider;

public:
	Bullet(int x, int y, POINT dir);
	~Bullet();

	void		Draw(HDC& hdc, Graphics& graphics);
	void		CreateImage();
	void		ParsingToImagePath(EBulletState fireBall, int spriteSize, TCHAR* path, int startNum);

	bool		GetisActive()		{ return isActive; }
};

