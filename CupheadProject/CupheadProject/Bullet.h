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
	POINT					createPos;
	int						x;
	int						y;
	int						speed;
	int						curAnimCnt;
	int						curAnimMax;
	int						spawnAnimCnt;
	bool					isActive;
	bool					isSpecialAttack;
	bool					isCollided;
	POINT					dir;
	clock_t					createTime;
	clock_t					animLastTime;
	EBulletState			state;
	Collider				collider;

public:
	Bullet();
	Bullet(int x, int y, POINT dir);
	~Bullet();

	void		SetBullet(int x, int y, POINT dir, bool isSpecialAttack = false);
	void		Draw(HDC& hdc, Graphics& graphics);
	bool		Collided(Collider* collider);
	void		CreateImage();
	void		ParsingToImagePath(EBulletState fireBall, int spriteSize, TCHAR* path, int startNum);

	Collider*	GetCollider();
	bool		GetisActive()			{ return isActive; }
	bool		GetIsCollided()			{ return isCollided; }
	bool		GetIsSpecialAttack()	{ return isSpecialAttack; }
};

