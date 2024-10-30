#include "HitObject.h"

HitObject::HitObject()
{
	x = 0;
	y = 0;
	type = EHitObjectType::TutorialParry;
	CreateImage();
	curAnimCnt = 0;
	animLastTime = clock();
	collider.left = 0;
	collider.right = 0;
	collider.top = 0;
	collider.bottom = 0;
	isHit = false;
	hp = 5;
}

HitObject::HitObject(EHitObjectType type, int x, int y) : HitObject()
{
	this->x = x;
	this->y = y;
	this->type = type;
	CreateImage();
	SetCollider();
}

HitObject::~HitObject()
{
	for (auto it = images.begin(); it != images.end(); it++)
		delete (*it);
	images.clear();
}

void HitObject::SetCollider()
{
	collider.left = x + camera_x;
	collider.top = y - camera_y;
	collider.right = x + width + camera_x;
	collider.bottom = y + height - camera_y;
}

void HitObject::SetCamera(int x, int y)
{
	camera_x = x;
	camera_y = y;
}

Collider& HitObject::GetCollider()
{
	return collider;
}

void HitObject::CreateImage()
{
	switch (type)
	{
	case EHitObjectType::TutorialParry:
		images.push_back(new Image(L"../Resource/Image/Background/Tutorial/lock1.png"));
		images.push_back(new Image(L"../Resource/Image/Background/Tutorial/lock2.png"));
		images.push_back(new Image(L"../Resource/Image/Background/Tutorial/lock3.png"));
		break;
	}
	curAnimMax = images.size();
	width = images[0]->GetWidth();
	height = images[0]->GetHeight();
}

void HitObject::Draw(HDC& hdc, Graphics& graphics)
{
	clock_t curTime = clock();
	if (curTime - animLastTime > 33)
	{
		curAnimCnt++;
		if (curAnimCnt >= curAnimMax)
			curAnimCnt = 0;
	}
	if (isHit)
	{
		if (curTime - isHitTime > 150)
			isHit = false;
	}
	Rect rect = { x + camera_x, y + camera_y, width, height };

	if (isHit)
	{
		ImageAttributes imgAttr;
		ColorMatrix colorMatrix =
		{
			0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.7f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.7f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.2f, 0.3f, 0.3f, 0.0f, 1.0f
		};
		imgAttr.SetColorMatrix(&colorMatrix);
		graphics.DrawImage(images[curAnimCnt], rect, 0, 0, width, height, UnitPixel, &imgAttr);
	}
	else graphics.DrawImage(images[curAnimCnt], rect);
}

void HitObject::Hit()
{
	isHit = true;
	isHitTime = clock();
}
