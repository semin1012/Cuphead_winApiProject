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
	bool				isLoop;
	bool				isHide;
	clock_t				createTime;
	clock_t				animLastTime;
	clock_t				hideTime;
	EParryType			state;

public:
	ParryObject();
	ParryObject(int x, int y, bool isLoop = false);
	~ParryObject();
	void		SetCameraPos(int x, int y);

	void		Draw(HDC& hdc, Graphics& graphics);
	bool		Collided(Player* player);

	void		CreateImage();
	void		ParsingToImagePath(EParryType state, int spriteSize, TCHAR* path, int startNum);
	bool		StartAnimation();
	void		SetCollider();
	void		SetHide();
	void		SetCamera(int x, int y);
	bool		IsHide()			{ return isHide; }
	bool		GetIsActive()		{ return isActive; }
	Collider*	GetCollider()		{ return &collider; }
};