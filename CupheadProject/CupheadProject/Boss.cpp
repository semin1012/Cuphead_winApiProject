#include "Boss.h"
#include <string>
#include <random>

Boss::Boss()
{
	x = 1000;
	y = 700;
	camera_x = 0;
	camera_y = 0;
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
	moveLastTime = clock();
	deltaPosY = 0;
	isCameraShake = false;
	CreateImage();
	Turn();
	Turn();
}

void Boss::CreateImage()
{
	images.resize((int)EBossStateSprite::Max);

#pragma region Load Image

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
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Move/Left/slime_tomb_lt_move_00");
	ParsingToImagePath(EBossStateSprite::Ph3MoveLeft, 4, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Move/Right/slime_tomb_rt_move_00");
	ParsingToImagePath(EBossStateSprite::Ph3MoveRight, 4, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Death/slime_tomb_death_00");
	ParsingToImagePath(EBossStateSprite::Ph3Death, 6, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Smash/slime_tomb_smash_00");
	ParsingToImagePath(EBossStateSprite::Ph3Smash, 14, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Move/Left/Trans/slime_tomb_lt_trans_00");
	ParsingToImagePath(EBossStateSprite::TransLeft, 3, temp, 1);
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Move/Right/Trans/slime_tomb_rt_trans_00");
	ParsingToImagePath(EBossStateSprite::TransRight, 3, temp, 1);


	// transitionImage
	_tcscpy(temp, L"../Resource/Image/Boss/Goopy/Phase3/Intro/Transition/slime_tomb_trans_00");
	ParsingToImagePath(1, temp, 1);

	// effect
	effects.resize((int)EBossEffect::Max);
	effects[(int)EBossEffect::MoveDust] = new EffectObject(EEffectType::BossPh3MoveDust, x, y, true, false, false);
	effects[(int)EBossEffect::MoveDirt] = new EffectObject(EEffectType::BossPh3MoveDirt, x, y, true, false, false);
	effects[(int)EBossEffect::IntroDust] = new EffectObject(EEffectType::BossPh3Intro, x, y, false, false, false);
	effects[(int)EBossEffect::IntroDustBack] = new EffectObject(EEffectType::BossPh3IntroBack, x, y, false, true, false);
	effects[(int)EBossEffect::SmashDust] = new EffectObject(EEffectType::BossPh3SmashDust, x, y, false, false, false);
	effects[(int)EBossEffect::Ph2JumpDust] = new EffectObject(EEffectType::BossPh2JumpDust, x, y, false, false, false);
	effects[(int)EBossEffect::DeathLightning] = new EffectObject(EEffectType::BossDeathLightning, x, y, true, false, false);
	effects[(int)EBossEffect::DeathStarA] = new EffectObject(EEffectType::BossDeathStarA, x, y, true, false, false);
	effects[(int)EBossEffect::DeathStarB] = new EffectObject(EEffectType::BossDeathStarB, x, y, true, false, false);
	effects[(int)EBossEffect::DeathCloud] = new EffectObject(EEffectType::AttackSFX, x, y, true, false, false);
#pragma endregion
	 
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

	for (auto it = transitionImages.begin(); it != transitionImages.end(); it++)
		delete* it;
	transitionImages.begin();
	for (auto it = effects.begin(); it != effects.end(); it++)
		delete* it;
	effects.begin();
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
	else if (state == EBossState::Smash)
	{
		drawCollider.left = x - width / 2;
		drawCollider.right = x + width / 2;
		drawCollider.top = y - height + 230;
		drawCollider.bottom = y + 230;
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
		deltaPosY += 50;
		if (deltaPosY >= 700)
		{
			deltaPosY = 700;
			phase = 3;
			ChangeState(EBossState::Intro);
			startChangeStateTime = clock();
			SetEffectImagesIn3Phase();
			if (dirX == -1)
				Turn();
		}
		int tWidth = transitionImages[0]->GetWidth();
		int tHeight = transitionImages[0]->GetHeight();
		graphics.DrawImage(transitionImages[0], x - tWidth / 2, -tHeight + deltaPosY, tWidth, tHeight);
	}

	if (!effects.empty())
	{
		for (auto effect : effects)
		{
			if (effect->GetIsBack() && effect->GetisActive())
				effect->Draw(hdc, graphics);
		}
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
	if (!effects.empty())
	{
		for (auto effect : effects)
		{
			if (!effect->GetIsBack() && effect->GetisActive())
				effect->Draw(hdc, graphics);
		}
	}
}

void Boss::Update()
{
	CheckAnimState();
	CheckAnimCount();

	clock_t curTime = clock();

	if (isHit)
	{
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
		if (curTime - startChangeStateTime >= CHANGE_STATE_MOVE)
		{
			ChangeState(EBossState::Move);
			moveLastTime = clock();
			startChangeStateTime = clock();
			if (dirX == 1)
			{
				effects[(int)EBossEffect::MoveDust]->InverseImage();
				effects[(int)EBossEffect::MoveDirt]->InverseImage();
			}
		}
	}

	if (state == EBossState::Move)
	{
		Move();
		if (curTime - startChangeStateTime >= PATTERN_2_TIME)
			Smash();
	}

	if (!effects.empty())
	{
		if (effects[(int)EBossEffect::MoveDust]->GetisActive())
		{
			effects[(int)EBossEffect::MoveDust]->SetPosition(x, y - 35);
			effects[(int)EBossEffect::MoveDirt]->SetPosition(x, y - 35);
		}
	}
	CheckHp();

	if (!bAttackCollider)
		SetCollider();
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
		else if (state == EBossState::TransitionToPh && phase == 1)
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
		else if (state == EBossState::Smash && curAnimCnt == 9)
		{
			isCameraShake = true;
			effects[(int)EBossEffect::SmashDust]->SetIsActive(true);
			effects[(int)EBossEffect::SmashDust]->SetPosition(x, y - 35);
			curAnimCnt++;
			animLastTime = clock();
		}
		else 
		{
			if (state == EBossState::TransitionToPh)
			{
				if (phase != 3)
				{
					if (curTime - startChangeStateTime >= 3000)
					{
						ChangeState(EBossState::Slime);
						isPossibleCollision = true;
					}
				}
			}
			curAnimCnt++;
			animLastTime = clock();
		}

		if (curAnimCnt >= curAnimMax)
		{
			switch (state)
			{
			case EBossState::Jump:
				targetX = player->GetXPos();
				isJumping = true;
				ChangeState(EBossState::AirUp);
				break;
			case EBossState::AirUpTurn:
				ChangeState(EBossState::Jump);
				SetJumpState();
				break;
			case EBossState::Punch:
				startChangeStateTime = clock();
				curAnimCnt = 0;
				bAttackCollider = false;
				SetCollider();
				SetJumpDirection();
				break;
			case EBossState::TransitionToPh:
				if (phase == 1)
				{
					isPossibleCollision = true;
					phase = 2;
					ChangeState(EBossState::Jump);
				}
				break;
			case EBossState::Intro:
				if ( phase == 3)
					ChangeState(EBossState::TransitionToPh);
				break;
			case EBossState::Smash:
				startChangeStateTime = clock();
				ChangeState(EBossState::Move);
				break;
			case EBossState::Trans:
				ChangeState(EBossState::Move);
				break;
			}
			curAnimCnt = 0;
		}
	}
}

void Boss::CheckHp()
{
	if (hp <= 0 && state != EBossState::Death)
	{
		ChangeState(EBossState::Death);
		isPossibleCollision = false;
		hp = 0;
		effects[(int)EBossEffect::DeathLightning]->SetIsActive(true);
		effects[(int)EBossEffect::DeathStarA]->SetIsActive(true);
		effects[(int)EBossEffect::DeathStarB]->SetIsActive(true);
		effects[(int)EBossEffect::DeathCloud]->SetIsActive(true);
		effects[(int)EBossEffect::DeathLightning]->SetPosition(x + 10, y - 200);
		effects[(int)EBossEffect::DeathStarA]->SetPosition(x - 40, y - 240);
		effects[(int)EBossEffect::DeathStarB]->SetPosition(x + 30, y - 180);
		effects[(int)EBossEffect::DeathCloud]->SetPosition(x + 20, y - 210);
	}
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

void Boss::SetEffectImagesIn3Phase()
{
	for (auto effect : effects)
	{
		if (effect->GetIsLoop())
			continue;
		effect->SetPosition(x, y - 35);
		effect->SetIsActive(true);
	}
	isCameraShake = true;
}

void Boss::Jump()
{
	clock_t curTime = clock();
	x = Lerp(x, targetX, 0.05f);
	y -= curJumpPower;
	curJumpPower -= 3;

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
			SetJumpState();
		if (phase == 2)
		{
			isCameraShake = true;
			effects[(int)EBossEffect::Ph2JumpDust]->SetIsActive(true);
			effects[(int)EBossEffect::Ph2JumpDust]->SetPosition(x, y);
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

void Boss::Move()
{
	clock_t curTime = clock();

	float distance = (curTime - moveLastTime) * 1.2f;

	if (dirX == 1)
		x += (int)distance;
	else x -= (int)distance;

	if (x <= 0 + images[(int)EBossStateSprite::Ph3MoveLeft][0]->GetWidth() / 2)
	{
		x = images[(int)EBossStateSprite::Ph3MoveLeft][0]->GetWidth() / 2 + 10;
		ChangeState(EBossState::Trans);
		dirX = 1;
	}
	else if (x >= WINDOWS_WIDTH - images[(int)EBossStateSprite::Ph3MoveLeft][0]->GetWidth() / 2)
	{
		x = WINDOWS_WIDTH - images[(int)EBossStateSprite::Ph3MoveLeft][0]->GetWidth() / 2 - 10;
		ChangeState(EBossState::Trans);
		dirX = -1;
	}

	moveLastTime = clock();
}

void Boss::Smash()
{
	if (state != EBossState::Smash)
	{
		ChangeState(EBossState::Smash);
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

void Boss::SetCameraPos(int x, int y)
{
	int deltaX = (camera_x - x);
	this->x -= deltaX;
	camera_x = x;
	int deltaY = (camera_y - y);
	this->y -= deltaY;
	camera_y = y;
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
	if (state == EBossState::Move)
	{
		if (!effects.empty())
		{
			effects[(int)EBossEffect::MoveDust]->SetIsActive(true);
			effects[(int)EBossEffect::MoveDirt]->SetIsActive(true);
			moveLastTime = clock();
		}
	}
	else
	{
		if (!effects.empty())
		{
			effects[(int)EBossEffect::MoveDust]->SetIsActive(false);
			effects[(int)EBossEffect::MoveDirt]->SetIsActive(false);
		}
	}

	if (state == EBossState::Trans)
	{
		effects[(int)EBossEffect::MoveDust]->InverseImage();
		effects[(int)EBossEffect::MoveDirt]->InverseImage();
	}
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
			animState = EBossStateSprite::Ph2AirUpTurn;
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
	case EBossState::Move:
		if (dirX == 1)
			animState = EBossStateSprite::Ph3MoveRight;
		else animState = EBossStateSprite::Ph3MoveLeft;
		break;
	case EBossState::Death:
		animState = EBossStateSprite::Ph3Death;
		break;
	case EBossState::Smash:
		animState = EBossStateSprite::Ph3Smash;
		break;
	case EBossState::Trans:
		if (dirX == 1)
			animState = EBossStateSprite::TransRight;
		else animState = EBossStateSprite::TransLeft;
		break;
	}
}

void Boss::SetJumpState()
{
	curAnimCnt = 0;

	targetX = player->GetXPos();
	curJumpPower = JumpMaxPower * (abs(targetX - x) * 0.0018);
	printf("CurJumpPower: %d\n", curJumpPower);
	if (curJumpPower <= 45)
		curJumpPower = 45;
	if (curJumpPower >= 60)
		curJumpPower = 60;
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
	if (phase == 3)
	{
		if (state == EBossState::Smash)
		{
			collider.left = x - images[(int)EBossStateSprite::Ph3Smash][0]->GetWidth() / 2;
			collider.right = x + images[(int)EBossStateSprite::Ph3Smash][0]->GetWidth() / 2;
			collider.top = y - images[(int)EBossStateSprite::Ph3MoveLeft][0]->GetHeight() + 230;
			collider.bottom = y;
		}
		else
		{
			collider.left = x - 100;
			collider.right = x + 100;
			collider.top = y - images[(int)EBossStateSprite::Ph3MoveLeft][0]->GetHeight() + 100;
			collider.bottom = collider.top + 200;
		}
	}
	else
	{
		int temp = phase * 100;
		collider.left = x - temp;
		collider.right = x + temp;
		collider.top = y - temp * 2;
		collider.bottom = y;
	}
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