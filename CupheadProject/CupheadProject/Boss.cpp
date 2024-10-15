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
	dirX = 1;
	drawCollider = { 0, 0,0, 0 };
	isHit = false;
	isJumping = false;
	startChangeStateTime = clock();
	targetX = 0;
	CreateImage();	
}

void Boss::CreateImage()
{
	images.resize((int)EBossState::Max);

	TCHAR temp[128] = L"../Resource/Image/Boss/Goopy/Intro/slime_intro_00";
	ParsingToImagePath(EBossState::Intro, 27, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase1/Jump/slime_jump_00");
	ParsingToImagePath(EBossState::Jump, 9, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase1/Air Up/slime_air_up_00");
	ParsingToImagePath(EBossState::AirUp, 3, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase1/Air Down/slime_air_down_00");
	ParsingToImagePath(EBossState::AirDown, 3, temp, 1);

	curAnimMax = images[(int)state].size();
}

Boss::~Boss()
{
	for (auto it = images.begin(); it != images.end(); it++)
	{
		for (auto img : *it)
			delete (img);
	}

	images.clear();
}

void Boss::Draw(HDC& hdc, Graphics& graphics)
{
	graphics.ResetTransform();

	int width = images[(int)state][curAnimCnt]->GetWidth();
	int height = images[(int)state][curAnimCnt]->GetHeight();

	if (state == EBossState::Intro)
	{
		drawCollider.left = x - width + 100;
		drawCollider.top = y - height;
		drawCollider.right = x;
		drawCollider.bottom = y;
	}
	else 
	{
		drawCollider.left = x - width / 2;
		drawCollider.right = x + width / 2;
		drawCollider.top = y - height;
		drawCollider.bottom = y;
	}

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
	CheckAnimCount();

	if (isHit)
	{
		clock_t curTime = clock();
		if (curTime - isHitTime > 150)
			isHit = false;
	}

	if (isJumping)
		Jump();

	if (state == EBossState::Intro)
		ChangeFromStartState();

	SetCollider();
}

void Boss::Hit()
{
	isHit = true;
	isHitTime = clock();
}

void Boss::CheckAnimCount()
{
	clock_t curTime = clock();
	curAnimMax = images[(int)state].size();

	if (curTime - animLastTime > 50)
	{
		curAnimCnt++;

		if (curAnimCnt >= curAnimMax)
		{
			if (state == EBossState::Jump)
			{
				state = EBossState::AirUp;
				targetX = player->GetXPos();
				isJumping = true;
			}
			curAnimCnt = 0;
		}

		animLastTime = clock();
	}
}

void Boss::Jump()
{
	int prevXPos = x;
	int prevDirX = dirX;
	y -= curJumpPower;
	curJumpPower -= 5;
	x = Lerp(x, targetX, 0.07f);

	if (prevXPos - x >= 0)
		dirX = 1;
	else dirX = -1;

	if (dirX != prevDirX)
	{
		for (int i = 0; i < images.size(); i++)
		{
			for (int j = 0; j < images[i].size(); j++)
			{
				images[i][j]->RotateFlip(RotateFlipType::RotateNoneFlipX);
			}
		}
	}

	if (curJumpPower <= 0)
		state = EBossState::AirDown;

	if (y >= 700)
	{
		SetJumpState();
		isJumping = false;
		y = 700;
	}
}

void Boss::SetPlayer(Player* player)
{
	this->player = player;
}

void Boss::ChangeFromStartState()
{
	clock_t curTime = clock();

	if (curTime - startChangeStateTime > STAGE_READY_TIME)
		SetJumpState();
}

void Boss::SetJumpState()
{
	state = EBossState::Jump;
	curAnimCnt = 0;
	curJumpPower = JumpMaxPower;
}

void Boss::SetCollider()
{
	collider.left = x - 100;
	collider.right = x + 100;
	collider.top = y - 200;
	collider.bottom = y;
}

void Boss::ParsingToImagePath(EBossState state, int spriteSize, TCHAR* path, int startNum)
{
	images[(int)state].resize(spriteSize);

	for (int i = 0, j = startNum; i <= spriteSize - startNum; i++, j++)
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

float Boss::Lerp(float a, float b, float alpha)
{
	return a * (1 - alpha) + b * alpha;
}