#include "EffectObject.h"
#include <string>

EffectObject::EffectObject()
{
	curAnimCnt = 0;
	curAnimMax = 0;
	isActive = false;
	collider = { 0, 0, 0, 0 };
	type = EEffectType::Max;
	animLastTime = clock();
	createTime = clock();
	x = 0;
	y = 0;
}

EffectObject::EffectObject(EEffectType type, int x, int y)
{
	curAnimCnt = 0;
	curAnimMax = 0;
	isActive = true;
	collider = { 0, 0, 0, 0 };
	this->type = EEffectType::Max;
	this->x = x;
	this->y = y;
	animLastTime = clock();
	createTime = clock();
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
	clock_t curTime = clock();
	curAnimMax = images.size();

	if (curTime - animLastTime > 1000 / 60)
	{
		curAnimCnt++;

		if (curAnimCnt >= curAnimMax)
		{
			curAnimCnt = 0;
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
	switch (type)
	{
	case EEffectType::JumpUpDust:
		_tcscpy(temp, L"../Resource/Image/Cuphead/Jump/Dust/cuphead_jump_dust_a_000");
		ParsingToImagePath(type, 14, temp, 1);
		break;
	case EEffectType::JumpDownDust:
		_tcscpy(temp, L"../Resource/Image/Cuphead/Jump/Dust/cuphead_jump_dust_b_000");
		ParsingToImagePath(type, 14, temp, 1);
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
			_tcscpy(num, std::to_wstring(0).c_str());
		_tcscpy(num, std::to_wstring(j).c_str());
		_tcscat(temp, num);
		_tcscat(temp, L".png");

		Image* pImg = new Image(temp);
		images[i] = pImg;
	}
}
