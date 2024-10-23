#include "EffectObject.h"
#include <string>

EffectObject::EffectObject()
{
	curAnimCnt = 0;
	curAnimMax = 0;
	isActive = true;
	isLoop = false;
	isBack = false;
	collider = { 0, 0, 0, 0 };
	type = EEffectType::Max;
	animLastTime = clock();
	createTime = clock();
	x = 0;
	y = 0;
	camera_x = 0;
	camera_y = 0;
}

EffectObject::EffectObject(EEffectType type, int x, int y, bool isLoop, bool isBack, bool isActive) : EffectObject()
{
	this->x = x;
	this->y = y;
	SetEffect(type);
	if (x == 0 && y == 0)
	{
		int unitX = images[0]->GetWidth() / 3;
		int unitY = images[0]->GetHeight() / 7;
		this->x = WINDOWS_WIDTH / 2 - unitX / 2;
		this->y = WINDOWS_HEIGHT / 2 - unitY / 2;
	}
	this->isLoop = isLoop;
	this->isBack = isBack;
	this->isActive = isActive;
}

EffectObject::~EffectObject()
{
	for (auto it = images.begin(); it != images.end(); it++)
		delete *it;
	images.clear();
}

void EffectObject::SetCameraPos(int x, int y)
{
	int deltaX = (camera_x - x);
	this->x -= deltaX;
	camera_x = x;
	int deltaY = (camera_y - y);
	this->y -= deltaY;
	camera_y = y;
}

void EffectObject::Draw(HDC& hdc, Graphics& graphics)
{
	if (!isActive)
		return;

	graphics.ResetTransform();
	clock_t curTime = clock();
	if (type != EEffectType::Died)
		curAnimMax = images.size();

	if (curTime - animLastTime > 33)
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

	if (type == EEffectType::Died)
	{
		int unitX = images[0]->GetWidth() / 3;
		int unitY = images[0]->GetHeight() / 7;
		Rect rect = { x, y, unitX, unitY };
		int animX = unitX * curAnimCnt % 3;
		int animY = unitY * (int)(curAnimCnt / 3);
		graphics.DrawImage(images[0], rect, animX, animY, unitX, unitY, Gdiplus::Unit::UnitPixel);	
	}
	else if (type == EEffectType::RunDust)
	{
		int unitX = images[0]->GetWidth() / 19;
		int unitY = images[0]->GetHeight();
		Rect rect = { x, y, unitX, unitY };
		int animX = unitX * curAnimCnt;
		int animY = 0;
		graphics.DrawImage(images[0], rect, animX, animY, unitX, unitY, Gdiplus::Unit::UnitPixel);
	}
	else
	{
		int width = images[curAnimCnt]->GetWidth();
		int height = images[curAnimCnt]->GetHeight();
		collider.left = x - width / 2;
		collider.top = y - height / 2;
		collider.right = x + width / 2;
		collider.bottom = y + height / 2;
		graphics.DrawImage(images[curAnimCnt], collider.left, collider.top, width, height);
	}
}

void EffectObject::SetEffect(EEffectType type)
{
	if (type != this->type)
		CreateImage(type);
	isActive = true;
	curAnimCnt = 0;
}

void EffectObject::CreateImage(EEffectType type)
{
	TCHAR temp[128];
	Image* pImg;
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
	case EEffectType::BossPh3MoveDirt:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Move/GroundFX/Dirt/slime_tomb_groundfx_dirt_00");
		ParsingToImagePath(type, 12, temp, 1);
		break;
	case EEffectType::BossPh3MoveDust:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Move/GroundFX/Dust/slime_tomb_groundfx_00");
		ParsingToImagePath(type, 4, temp, 1);
		break;
	case EEffectType::BossPh3IntroBack:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Dust(Intro)/slime_tomb_dust_bk_00");
		ParsingToImagePath(type, 18, temp, 1);
		break;
	case EEffectType::BossPh2JumpDust:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase2/Dust/A/lg_slime_dust_a_00");
		ParsingToImagePath(type, 16, temp, 1);
		break;
	case EEffectType::BossDeathLightning:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Generic/Lightning/lg_generic_lightning_00");
		ParsingToImagePath(type, 10, temp, 1);
		break;
	case EEffectType::BossDeathStarA:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Generic/Star/A/lg_generic_star_a_00");
		ParsingToImagePath(type, 15, temp, 1);
		break;
	case EEffectType::BossDeathStarB:
		_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Generic/Star/B/lg_generic_star_b_00");
		ParsingToImagePath(type, 14, temp, 1);
		break;
	case EEffectType::AttackSFX:
		_tcscpy(temp, L"../Resource/Image/SFX/cuphead_explode_fx_00");
		ParsingToImagePath(type, 16, temp, 1);
		break;
	case EEffectType::Died:
		images.resize(1);
		_tcscpy(temp, L"../Resource/Image/UI/Died/died.png");
		pImg = new Image(temp);
		images[0] = pImg;
		curAnimMax = 20;
		break;
	case EEffectType::RunDust:
		images.resize(1);
		_tcscpy(temp, L"../Resource/Image/SFX/RunDust.png");
		pImg = new Image(temp);
		images[0] = pImg;
		curAnimMax = 19;
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
	curAnimCnt = 0;
}

bool EffectObject::GetisActive()
{
	return isActive;
}
