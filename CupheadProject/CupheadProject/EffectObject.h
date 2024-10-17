#pragma once
#include "framework.h"
#include "Collider.h"
#include <vector>

enum class EEffectType
{
	JumpUpDust,
	JumpDownDust,
	BossPh3Intro,
	BossPh3IntroBack,
	BossPh3MoveDust,
	BossPh3SmashDust,
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
	bool				isLoop;
	bool				isBack;
	bool				isStart;
	Collider			collider;
	EEffectType			type;
	clock_t				createTime;
	clock_t				animLastTime;

public:
	EffectObject();
	EffectObject(EEffectType type, int x, int y, bool isLoop = false, bool isBack = false, bool isStart = true);
	~EffectObject();
	
	void	Draw(HDC& hdc, Graphics& graphics);
	void	SetEffect(EEffectType type);
	void	CreateImage(EEffectType type);
	void	ParsingToImagePath(EEffectType state, int spriteSize, TCHAR* path, int startNum);
	void	InverseImage();
	void	SetPosition(int x, int y);
	void	SetIsActive(bool isActive);
	void	SetIsStart(bool isStart) { this->isStart = isStart; }
	bool	GetIsStart()			 { return isStart; }
	bool	GetisActive();
	bool	GetIsLoop()				 { return isLoop; }
	bool	GetIsBack()				 { return isBack; }
	std::vector<Image*>& GetImages() { return images; }
};