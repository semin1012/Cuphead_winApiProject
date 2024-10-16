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
	Player*				player;
	Collider			collider;
	int					x;
	int					y;
	int					curAnimMax;
	int					curAnimCnt;
	bool				isActive;
	clock_t				createTime;
	clock_t				animLastTime;
	EParryType			state;

public:
	ParryObject();
	ParryObject(int x, int y, Player* player);
	~ParryObject();

	void		Draw(HDC& hdc, Graphics& graphics);

	void		CreateImage();
	void		ParsingToImagePath(EParryType state, int spriteSize, TCHAR* path, int startNum);
	bool		GetIsActive()		{ return isActive; }
};