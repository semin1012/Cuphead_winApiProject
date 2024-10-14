#pragma once
#include "framework.h"
#include "Collider.h"
#include <vector>

enum class EEffectType
{
	JumpUpDust,
	JumpDownDust,
	Max
};

class EffectObject
{
	std::vector<Image*> images;
	int					curAnimCnt;
	int					curAnimMax;
	int					x;
	int					y;
	bool				isActive;
	Collider			collider;
	EEffectType			type;
	clock_t				createTime;
	clock_t				animLastTime;

public:
	EffectObject();
	EffectObject(EEffectType type, int x, int y);
	~EffectObject();
	
	void	Draw(HDC& hdc, Graphics& graphics);
	void	SetEffect(EEffectType type);
	void	CreateImage(EEffectType type);
	void	ParsingToImagePath(EEffectType state, int spriteSize, TCHAR* path, int startNum);

	bool	GetisActive() { return isActive; }
};