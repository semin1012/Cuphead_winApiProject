#pragma once
#include "framework.h"
#include "Player.h"
#include "Collider.h"
#include <vector>

enum class EParryType
{
	QuestionMark,
	Pop,
	Max
};

class ParryObject
{
	std::vector<std::vector<Image*>> images;
	Collider			collider;
	int					x;
	int					y;
	int						camera_x;
	int						camera_y;
	int					curAnimMax;
	int					curAnimCnt;
	bool				isActive;
	clock_t				createTime;
	clock_t				animLastTime;
	EParryType			state;

public:
	ParryObject();
	ParryObject(int x, int y);
	~ParryObject();
	void		SetCameraPos(int x, int y);

	void		Draw(HDC& hdc, Graphics& graphics);
	bool		Collided(Player* player);

	void		CreateImage();
	void		ParsingToImagePath(EParryType state, int spriteSize, TCHAR* path, int startNum);
	bool		StartAnimation();
	bool		GetIsActive()		{ return isActive; }
	Collider*	GetCollider()		{ return &collider; }
};