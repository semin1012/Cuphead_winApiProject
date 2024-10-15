#include "Boss.h"
#include <string>

Boss::Boss()
{
	x = 1000;
	y = 700;
	phase = 1;
	curAnimMax = 0;
	curAnimCnt = 0;
	animLastTime = clock();
	state = EBossState::Intro;
	dirX = 0;
	drawCollider = { 0, 0,0, 0 };
	isHit = false;
	CreateImage();	
}

Boss::~Boss()
{
	for (auto it = images.begin(); it != images.end(); it++)
	{
		for (auto img : *it)
		{
			delete (img);
		}
	}

	images.clear();
}

void Boss::Draw(HDC& hdc, Graphics& graphics)
{
	graphics.ResetTransform();

	clock_t curTime = clock();
	curAnimMax = images[(int)state].size();

	if (curTime - animLastTime > 50)
	{
		curAnimCnt++;

		if (curAnimCnt >= curAnimMax)
		{
			curAnimCnt = 0;
		}

		animLastTime = clock();
	}

	int width = images[(int)state][curAnimCnt]->GetWidth();
	int height = images[(int)state][curAnimCnt]->GetHeight();

	if (state == EBossState::Intro)
	{
		drawCollider.left = x - width;
		drawCollider.top = y - height;
		drawCollider.right = x;
		drawCollider.bottom = y;
	}

	collider.left	= x - 200;
	collider.right	= x;
	collider.top	= y - 200;
	collider.bottom = y;

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

		graphics.DrawImage(images[(int)state][curAnimCnt], Rect(drawCollider.left, drawCollider.top, width, height), 0, 0, width, height, UnitPixel, &imgAttr);
	}
	else graphics.DrawImage(images[(int)state][curAnimCnt], drawCollider.left, drawCollider.top, width, height);
}

void Boss::Update()
{
	if (isHit)
	{
		clock_t curTime = clock();
		if (curTime - isHitTime > 150)
			isHit = false;
	}
}

void Boss::CreateImage()
{
	images.resize((int)EBossState::Max);
	
	TCHAR temp[128] = L"../Resource/Image/Boss/Goopy/Intro/slime_intro_00";
	ParsingToImagePath(EBossState::Intro, 27, temp, 1);
	curAnimMax = images[(int)state].size();
}

void Boss::ParsingToImagePath(EBossState state, int spriteSize, TCHAR* path, int startNum)
{
	images[(int)state].resize(spriteSize);

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
		images[(int)state][i] = pImg;
	}

}

void Boss::Hit()
{
	isHit = true;
	isHitTime = clock();
}
