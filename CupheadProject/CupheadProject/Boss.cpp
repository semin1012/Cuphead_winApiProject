#include "Boss.h"
#include <string>
#include <random>

Boss::Boss()
{
	x = 1000;
	y = 700;
	phase = 1;
	curAnimMax = 0;
	curAnimCnt = 0;
	animLastTime = clock();
	state = EBossState::Intro;
	animState = EBossStateSprite::Intro;
	dirX = 1;
	drawCollider = { 0, 0, 0, 0 };
	isHit = false;
	isJumping = false;
	startChangeStateTime = clock();
	targetX = 0;
	bAttackCollider = false;
	isPossibleCollision = true;
	isShowParry = false;
	hp = HEALTH;
	deltaPosY = 0;
	CreateImage();	
}

void Boss::CreateImage()
{
	images.resize((int)EBossStateSprite::Max);

	TCHAR temp[128] = L"../Resource/Image/Boss/Goopy/Intro/slime_intro_00";
	ParsingToImagePath(EBossStateSprite::Intro, 27, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase1/Jump/slime_jump_00");
	ParsingToImagePath(EBossStateSprite::Jump, 9, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase1/Air Up/slime_air_up_00");
	ParsingToImagePath(EBossStateSprite::AirUp, 3, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase1/Air Down/slime_air_down_00");
	ParsingToImagePath(EBossStateSprite::AirDown, 3, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase1/Air Up Turn/slime_air_up_turn_00");
	ParsingToImagePath(EBossStateSprite::AirUpTurn, 3, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase1/Punch/slime_punch_00");
	ParsingToImagePath(EBossStateSprite::Punch, 16, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase1/Transition To Ph2/slime_morph_00");
	ParsingToImagePath(EBossStateSprite::TransitionToPh2, 48, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase2/Jump/lg_slime_jump_00");
	ParsingToImagePath(EBossStateSprite::Ph2Jump, 8, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase2/Air Up/lg_slime_air_up_00");
	ParsingToImagePath(EBossStateSprite::Ph2AirUp, 4, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase2/Air Down/lg_slime_air_down_00");
	ParsingToImagePath(EBossStateSprite::Ph2AirDown, 5, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase2/Punch/lg_slime_punch_00");
	ParsingToImagePath(EBossStateSprite::Ph2Punch, 19, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase2/Air Up Turn/lg_slime_air_up_turn_00");
	ParsingToImagePath(EBossStateSprite::Ph2AirUpTurn, 3, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase2/Death/lg_slime_death_00");
	ParsingToImagePath(EBossStateSprite::TransitionToPh3, 20, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase2/Death/Slime/lg_slime_explode_00");
	ParsingToImagePath(EBossStateSprite::Slime, 16, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Intro/slime_tomb_slam_00");
	ParsingToImagePath(EBossStateSprite::Ph3Intro, 4, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Intro/Transition/slime_tomb_trans_00");
	ParsingToImagePath(EBossStateSprite::Ph3Transition, 3, temp, 1);
	

	// transitionImage
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Intro/Transition/slime_tomb_trans_00");
	ParsingToImagePath(1, temp, 1);

	curAnimMax = images[(int)animState].size();
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

	int width = images[(int)animState][curAnimCnt]->GetWidth();
	int height = images[(int)animState][curAnimCnt]->GetHeight();

	if (state == EBossState::Intro && phase != 3)
	{
		drawCollider.top = y - height;
		drawCollider.bottom = y;
		if (dirX == -1)
		{
			drawCollider.left = x;
			drawCollider.right = x + width - 100;
		}
		else
		{
			drawCollider.left = x - width + 100;
			drawCollider.right = x;
		}
	}
	else 
	{
		drawCollider.top = y - height;
		drawCollider.bottom = y;
		if (state == EBossState::Punch)
		{
			if (dirX == -1)
			{
				drawCollider.left = x - 100 * phase;
				drawCollider.right = x + width - 100 * phase;
			}
			else
			{
				drawCollider.left = x - width + 100 * phase;
				drawCollider.right = x + 100 * phase;
			}
			collider = drawCollider;
		}
		else
		{
			drawCollider.left = x - width / 2;
			drawCollider.right = x + width / 2;
		}
	}

	if (state == EBossState::Slime && phase == 2)
	{
		deltaPosY += 30;
		if (deltaPosY >= 700)
		{
			deltaPosY = 700;
			phase = 3;
			ChangeState(EBossState::Intro);
			startChangeStateTime = clock();
		}
		int tWidth = transitionImages[0]->GetWidth();
		int tHeight = transitionImages[0]->GetHeight();
		graphics.DrawImage(transitionImages[0], x - tWidth / 2, -tHeight + deltaPosY, tWidth, tHeight);
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
		graphics.DrawImage(images[(int)animState][curAnimCnt], Rect(drawCollider.left, drawCollider.top, width, height), 0, 0, width, height, UnitPixel, &imgAttr);
	}
	else graphics.DrawImage(images[(int)animState][curAnimCnt], drawCollider.left, drawCollider.top, width, height);
}

void Boss::Update()
{
	CheckAnimState();
	CheckAnimCount();
	clock_t curTime = clock();

	if (isHit)
	{
		clock_t curTime = clock();
		if (curTime - isHitTime > 150)
			isHit = false;
	}

	if (isJumping && phase != 3)
	{
		SetJumpDirection();
		if (state != EBossState::AirUpTurn)
			Jump();
	}

	if (state == EBossState::Intro && phase != 3)
		ChangeFromStartState();

	if (state == EBossState::TransitionToPh && phase == 3)
	{
	}

	if (!bAttackCollider)
		SetCollider();

	CheckHp();
}

void Boss::Hit(Bullet* bullet)
{
	if (!isPossibleCollision) 
		return;
	isHit = true;
	isHitTime = clock();
	if (bullet->GetIsSpecialAttack())
		hp -= 5;
	else hp -= 1;
}

void Boss::CheckAnimCount()
{
	clock_t curTime = clock();
	curAnimMax = images[(int)animState].size();

	if (curTime - animLastTime > 33)
	{
		if (state == EBossState::Punch)
		{
			if (curAnimCnt == 6 && curTime - animLastTime > 800)
			{
				curAnimCnt++;
				animLastTime = clock();
			}
			else if ( curAnimCnt != 6)
			{
				curAnimCnt++;
				animLastTime = clock();
			}
		}
		else if (phase == 1 && state == EBossState::TransitionToPh)
		{
			if (curAnimCnt == 36)
			{
				if (curTime - startChangeStateTime > TRANSITION_TIME)
				{
					curAnimCnt++;
				}
				else
				{
					curAnimCnt = 34;
					animLastTime = clock();
				}
			}
			else if (curAnimCnt != 36)
			{
				curAnimCnt++;
				animLastTime = clock();
			}
		}
		else 
		{
			if (state == EBossState::TransitionToPh && phase != 3)
			{
				if (curTime - startChangeStateTime >= 3000)
				{
					ChangeState(EBossState::Slime);
					isPossibleCollision = true;
				}
			}
			curAnimCnt++;
			animLastTime = clock();
		}

		if (curAnimCnt >= curAnimMax)
		{
			if (state == EBossState::Jump)
			{
				targetX = player->GetXPos();
				isJumping = true;
				ChangeState(EBossState::AirUp);
			}
			else if (state == EBossState::AirUpTurn)
			{
				ChangeState(EBossState::Jump);
				SetJumpState();
			}
			else if (state == EBossState::Punch)
			{
				startChangeStateTime = clock();
				bAttackCollider = false;
				curAnimCnt = 0;
				SetJumpDirection();
			}
			else if (state == EBossState::TransitionToPh)
			{
				if (phase == 1)
				{
					isPossibleCollision = true;
					phase = 2;
					ChangeState(EBossState::Jump);
				}
			}
			else if (state == EBossState::Intro && phase == 3)
			{
				ChangeState(EBossState::TransitionToPh);
			}
			curAnimCnt = 0;
		}
	}
}

void Boss::CheckHp()
{
	if (hp <= 0)
		hp = 0;
	else if (hp * 3 < HEALTH && phase == 2 && !isJumping)
	{
		if (state != EBossState::Slime && state != EBossState::TransitionToPh && state != EBossState::Intro)
		{
			isPossibleCollision = false;
			ChangeState(EBossState::TransitionToPh);
			bAttackCollider = false;
			startChangeStateTime = clock();

		}
	}
	else if (hp * 3 < HEALTH * 2 && phase == 1 && !isJumping)
	{
		if (phase != 2 && state != EBossState::TransitionToPh)
		{
			isPossibleCollision = false;
			state = EBossState::TransitionToPh;
			bAttackCollider = false;
			startChangeStateTime = clock();
		}
	}
}

void Boss::Jump()
{
	clock_t curTime = clock();
	x = Lerp(x, targetX, 0.07f);
	y -= curJumpPower;
	curJumpPower -= 5;

	if (curJumpPower <= 0)
		ChangeState(EBossState::AirDown);

	if (y >= 700)
	{
		targetX = player->GetXPos();
		state = EBossState::Jump;
		SetJumpDirection();
		if (state != EBossState::TransitionToPh &&  curTime - startChangeStateTime >= PATTERN_1_TIME)
			SetPunchState();
		else
		{
			SetJumpState();
		}
		isJumping = false;
		y = 700;
	}
}

void Boss::Turn()
{
	//ChangeState(EBossState::AirUpTurn);

	for (int i = 0; i < images.size(); i++)
	{
		for (int j = 0; j < images[i].size(); j++)
			images[i][j]->RotateFlip(RotateFlipType::RotateNoneFlipX);
	}
}

void Boss::SetJumpDirection()
{
	prevXPos = x;
	prevDirX = dirX;
	int tempX = Lerp(x, targetX, 0.07f);

	if (prevXPos - tempX >= 0)
		dirX = 1;
	else dirX = -1;

	if (dirX != prevDirX)
	{
		curAnimCnt = 0;
		Turn();
	}
	else if (state != EBossState::Jump && state != EBossState::AirUp && state != EBossState::AirDown)
	{
		SetJumpState();
		ChangeState(EBossState::Jump);
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
	{
		ChangeState(EBossState::Jump);
		SetJumpState();
	}
}

void Boss::ChangeState(EBossState state)
{
	this->state = state;
	curAnimCnt = 0;
}

void Boss::CheckAnimState()
{
	switch (state)
	{
	case EBossState::Intro:
		if (phase == 3) animState = EBossStateSprite::Ph3Intro;
		else animState = EBossStateSprite::Intro;
		break;
	case EBossState::AirDown:
		if (phase == 1)
			animState = EBossStateSprite::AirDown;
		else if (phase == 2)
			animState = EBossStateSprite::Ph2AirDown;
		break;
	case EBossState::AirUp:
		if (phase == 1)
			animState = EBossStateSprite::AirUp;
		else if (phase == 2)
			animState = EBossStateSprite::Ph2AirUp;
		break;
	case EBossState::AirUpTurn:
		if (phase == 1)
			animState = EBossStateSprite::AirUpTurn;
		else if (phase == 2)
			animState == EBossStateSprite::Ph2AirUpTurn;
		break;
	case EBossState::Jump:
		if (phase == 1)
			animState = EBossStateSprite::Jump;
		else if (phase == 2)
			animState = EBossStateSprite::Ph2Jump;
		break;
	case EBossState::Punch:
		if (phase == 1)
			animState = EBossStateSprite::Punch;
		else if (phase == 2)
			animState = EBossStateSprite::Ph2Punch;
		break;
	case EBossState::TransitionToPh:
		if (phase == 1)
			animState = EBossStateSprite::TransitionToPh2;
		else if (phase == 2)
			animState = EBossStateSprite::TransitionToPh3;
		else animState = EBossStateSprite::Ph3Transition;
		break;
	case EBossState::Slime:
		animState = EBossStateSprite::Slime;
		break;
	}
}

void Boss::SetJumpState()
{
	curAnimCnt = 0;

	targetX = player->GetXPos();
	curJumpPower = JumpMaxPower * (abs(targetX - x) * 0.0015);
	if (curJumpPower <= 55)
		curJumpPower = 55;
	if (curJumpPower >= 70)
		curJumpPower = 70;
}

void Boss::SetPunchState()
{
	curAnimCnt = 0;
	state = EBossState::Punch;
	bAttackCollider = true;
}

Collider* Boss::GetCollider()
{
	static Collider temp = { 0, 0, 0, 0 };
	if (isPossibleCollision)
		return &collider;
	return &temp;
}

bool Boss::GetIsTransitionToPhase()
{
	if (state == EBossState::TransitionToPh && !isShowParry)
	{
		isShowParry = true;
		return true;
	}
	return false;
}

void Boss::SetCollider()
{
	int temp = phase * 100;
	collider.left = x - temp;
	collider.right = x + temp;
	collider.top = y - temp * 2;
	collider.bottom = y;
}

void Boss::ParsingToImagePath(EBossStateSprite state, int spriteSize, TCHAR* path, int startNum)
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

void Boss::ParsingToImagePath(int spriteSize, TCHAR* path, int startNum)
{
	transitionImages.resize(spriteSize);

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
		transitionImages[i] = pImg;
	}
}

float Boss::Lerp(float a, float b, float alpha)
{
	return a * (1 - alpha) + b * alpha;
}