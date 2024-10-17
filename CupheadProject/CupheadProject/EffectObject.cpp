#include "EffectObject.h"
#include <string>

EffectObject::EffectObject()
{
	curAnimCnt = 0;
	curAnimMax = 0;
	isActive = true;
	isLoop = false;
	isBack = false;
	isStart = true;
	collider = { 0, 0, 0, 0 };
	type = EEffectType::Max;
	animLastTime = clock();
	createTime = clock();
	x = 0;
	y = 0;
}

EffectObject::EffectObject(EEffectType type, int x, int y, bool isLoop, bool isBack, bool isStart) : EffectObject()
{
	this->x = x;
	this->y = y;
	this->isLoop = isLoop;
	this->isBack = isBack;
	this->isStart = isStart;
	SetEffect(type);
}

EffectObject::~EffectObject()
{
	for (auto it = images.begin(); it != images.end(); it++)
		delete *it;
	images.clear();
}

void EffectObject::Draw(HDC& hdc, Graphics& graphics)
{
	if (!isStart || !isActive)
		return;

	graphics.ResetTransform();
	clock_t curTime = clock();
	curAnimMax = images.size();

	if (curTime - animLastTime > 20)
	{
		curAnimCnt++;
		if (curAnimCnt >= curAnimMax)
		{
			curAnimCnt = 0;
			if (!isLoop)
				isActive = false;
		}
		animLastTime = clock();
	}

	if (!isActive)
		return;

	int width = images[curAnimCnt]->GetWidth();
	int height = images[curAnimCnt]->GetHeight();

	collider.left = x - width / 2;
	collider.top = y - height / 2;
	collider.right = x + width / 2;
	collider.bottom = y + height / 2;

	graphics.DrawImage(images[curAnimCnt], collider.left, collider.top, width, height);
}

void EffectObject::SetEffect(EEffectType type)
{
	if ( type != this->type)
		CreateImage(type);
	isActive = true;
}

void EffectObject::CreateImage(EEffectType type)
{
	TCHAR temp[128];
	this->type = type;
	switch (type)
	{
	case EEffectType::JumpUpDust:
		_tcscpy(temp, L"../Resource/Image/Cuphead/Jump/Dust/cuphead_jump_dust_a_00");
		ParsingToImagePath(type, 14, temp, 1);
		break;
	case EEffectType::JumpDownDust:
		_tcscpy(temp, L"../Resource/Image/Cuphead/Jump/Dust/cuphead_jump_dust_b_00");
		ParsingToImagePath(type, 14, temp, 1);
		break;
	case EEffectType::BossPh3SmashDust:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Smash/Dust/slime_tomb_smash_dust_00");
		ParsingToImagePath(type, 17, temp, 1);
		break;
	case EEffectType::BossPh3Intro:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Dust(Intro)/slime_tomb_dust_00");
		ParsingToImagePath(type, 19, temp, 1);
		break;
	case EEffectType::BossPh3MoveDust:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Move/GroundFX/Dust/slime_tomb_groundfx_00");
		ParsingToImagePath(type, 4, temp, 1);
		break;
	case EEffectType::BossPh3IntroBack:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Dust(Intro)/slime_tomb_dust_bk_00");
		ParsingToImagePath(type, 18, temp, 1);
		break;
	}
}

void EffectObject::ParsingToImagePath(EEffectType state, int spriteSize, TCHAR* path, int startNum)
{
	if (!images.empty())
	{
		for (auto it = images.begin(); it != images.end(); it++)
			delete* it;
		images.clear();
	}
	
	images.resize(spriteSize);
	curAnimMax = spriteSize;

	for (int i = 0, j = startNum; i < spriteSize; i++, j++)
	{
		TCHAR temp[128];
		_tcscpy(temp, path);

		wchar_t num[3];
		if (j < 10)
		{
			_tcscpy(num, std::to_wstring(0).c_str());
			_tcscat(num, std::to_wstring(j).c_str());
		}
		else _tcscpy(num, std::to_wstring(j).c_str());
		_tcscat(temp, num);
		_tcscat(temp, L".png");

		Image* pImg = new Image(temp);
		images[i] = pImg;
	}
}

void EffectObject::InverseImage()
{
	for (int j = 0; j < images.size(); j++)
		images[j]->RotateFlip(RotateFlipType::RotateNoneFlipX);
}

void EffectObject::SetPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void EffectObject::SetIsActive(bool isActive)
{
	this->isActive = isActive;
}

bool EffectObject::GetisActive()
{
	return isActive;
}
