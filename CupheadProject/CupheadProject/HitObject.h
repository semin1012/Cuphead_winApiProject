#pragma once
#include <vector>	
#include "framework.h"
#include "Collider.h"

enum class EHitObjectType
{
	TutorialParry,
	Max
};

class HitObject
{
	std::vector<Image*>		images;
	EHitObjectType			type;
	Collider				collider;
	int						x;
	int						y;
	int						width;
	int						height;
	int						curAnimCnt;
	int						curAnimMax;
	int						camera_x;
	int						camera_y;
	int						hp;
	bool					isHit;
	clock_t					isHitTime;
	clock_t					animLastTime;

public:
	HitObject();
	HitObject(EHitObjectType type, int x, int y);
	~HitObject();
	void SetCollider();
	void SetCamera(int x, int y);
	Collider& GetCollider();
	void CreateImage();
	void Draw(HDC& hdc, Graphics& graphics);
	void Hit();
	void SetHp(int hp)		{ this->hp = hp; }
	int GetHp()				{ return hp; }
	int GetX() { return x; }
	int GetY() { return y; }
};

