#include "Player.h"
#include "Boss.h"
#include <string>
using namespace std;

void Player::CreateImage()
{
	playerImg.resize((int)EPlayerState::Max);

	// Image Load
	playerImg[(int)EPlayerState::World].resize(1);
	Image* pImg = new Image(L"../Resource/Image/Cuphead/CupHead_Word01.png");
	playerImg[(int)EPlayerState::World][0] = pImg;

#pragma region Load Image
	// idle
	TCHAR path[128] = L"../Resource/Image/Cuphead/cuphead_idle_000";
	ParsingToImagePath(EPlayerState::Idle, PLAYER_IDEL_SIZE, path, 1);
	// intro
	_tcscpy(path, L"../Resource/Image/Cuphead/Intro/cuphead_intro_a_00");
	ParsingToImagePath(EPlayerState::Intro, 28, path, 1);
	// run
	_tcscpy(path, L"../Resource/Image/Cuphead/Run/cuphead_run_00");
	ParsingToImagePath(EPlayerState::RightRun, 16, path, 1);
	// jump
	_tcscpy(path, L"../Resource/Image/Cuphead/Jump/cuphead_jump_000");
	ParsingToImagePath(EPlayerState::RightJump, 8, path, 1);
	// dash
	_tcscpy(path, L"../Resource/Image/Cuphead/Dash/cuphead_dash_000");
	ParsingToImagePath(EPlayerState::RightDash, 8, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Dash/cuphead_dash_air_000");
	ParsingToImagePath(EPlayerState::RightAirDash, 8, path, 1);
	// down
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/cuphead_duck_000");
	ParsingToImagePath(EPlayerState::DownStartRight, 7, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/cuphead_duck_idle_000");
	ParsingToImagePath(EPlayerState::DownIdleRight, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/R_cuphead_duck_000");
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/cuphead_duck_shoot_000");
	ParsingToImagePath(EPlayerState::DownShootingRight, 6, path, 1);
	// run & shooting
	_tcscpy(path, L"../Resource/Image/Cuphead/RunShooting/cuphead_run_shoot_00");
	ParsingToImagePath(EPlayerState::ShootingRunRight, 16, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/RunShooting/cuphead_run_shoot_diagonal_up_00");
	ParsingToImagePath(EPlayerState::ShootingRunRightUp, 16, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/RunShooting/R_cuphead_run_shoot_00");
	// shooting
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/cuphead_shoot_straight_000");
	ParsingToImagePath(EPlayerState::ShootingRight, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/cuphead_shoot_diagonal_up_000");
	ParsingToImagePath(EPlayerState::ShootingRightUp, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/cuphead_shoot_diagonal_down_000");
	ParsingToImagePath(EPlayerState::ShootingRightDown, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/cuphead_shoot_up_000");
	ParsingToImagePath(EPlayerState::ShootingUp, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/cuphead_shoot_down_000");
	ParsingToImagePath(EPlayerState::ShootingDown, 6, path, 1);
	// lockin
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/cuphead_aim_straight_000");
	ParsingToImagePath(EPlayerState::AimRight, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/cuphead_aim_diagonal_up_000");
	ParsingToImagePath(EPlayerState::AimRightUp, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/cuphead_aim_diagonal_down_000");
	ParsingToImagePath(EPlayerState::AimRightDown, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/cuphead_aim_up_000");
	ParsingToImagePath(EPlayerState::AimUp, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/cuphead_aim_down_000");
	ParsingToImagePath(EPlayerState::AimDown, 5, path, 1);
	// Special Attack 
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_straight_00");
	ParsingToImagePath(EPlayerState::SCAttackRight, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_diagonal_down_00");
	ParsingToImagePath(EPlayerState::SCAttackRightDown, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_diagonal_up_00");
	ParsingToImagePath(EPlayerState::SCAttackRightUp, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_down_00");
	ParsingToImagePath(EPlayerState::SCAttackDown, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_up_00");
	ParsingToImagePath(EPlayerState::SCAttackUp, 13, path, 1);
	// Jump Special Attack
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_straight_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackRight, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_diagonal_down_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackRightDown, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_diagonal_up_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackRightUp, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_down_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackDown, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_up_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackUp, 6, path, 1);
	// Hit
	_tcscpy(path, L"../Resource/Image/Cuphead/Hit/cuphead_hit_000");
	ParsingToImagePath(EPlayerState::HitRight, 6, path, 1);
	// Parry
	_tcscpy(path, L"../Resource/Image/Cuphead/Parry/cuphead_parry_000");
	ParsingToImagePath(EPlayerState::ParryRight, 8, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Parry/cuphead_parry_pink_000");
	ParsingToImagePath(EPlayerState::ParryPinkRight, 8, path, 1);
	// Ghost
	_tcscpy(path, L"../Resource/Image/Cuphead/Ghost/cuphead_ghost_00");
	ParsingToImagePath(EPlayerState::Ghost, 24, path, 1);


#pragma endregion

	curAnimMax = playerImg[(int)EPlayerState::World].size();
	curAnimCnt = 0;
	Turn();
	Turn();
}

// path에 startNum부터 startNum + spriteSize까지의 숫자를 이름으로 해서 Load하는 함수, 기본이 png 파일임
void Player::ParsingToImagePath(EPlayerState state, int spriteSize, TCHAR* path, int startNum)
{
	playerImg[(int)state].resize(spriteSize);

	for (int i = 0, j = startNum; i < spriteSize; i++, j++)
	{
		TCHAR temp[128];
		_tcscpy(temp, path);

		wchar_t num[3];
		_tcscpy(num, to_wstring(j).c_str());
		_tcscat(temp, num);
		_tcscat(temp, L".png");

		Image* pImg = new Image(temp);
		playerImg[(int)state][i] = pImg;

		if (playerImg[(int)state][i] == NULL)
		{
			DWORD dwError = GetLastError();
			_tcscat(temp, L" 파일을 열 수 없습니다.");
			MessageBox(NULL, temp, _T("에러"), MB_OK);
		}
	}
}

Player::Player()
{
	worldState = EPlayerWorldState::Idle;
	state = EPlayerState::World;
	collider.left = 0;
	collider.top = 0;
	collider.right = 0;
	collider.bottom = 0;
	curAnimCnt = 0;
	inWorld = true;
	camera_x = WORLD_START_POINT_X;
	camera_y = WORLD_START_POINT_Y;
	lastTime = clock();
	isJumping = false;
	isDashing = false;
	isDashAndJump = false;
	isDown = false;
	isShooting = false;
	isLockin = false;
	isSpecialAttack = false;
	isSpecialAttackAndJump = false;
	setJumpDust = false;
	lastForward = LAST_FORWARD_IS_RIGHT;
	speed = 1.5f;
	isHit = false;
	isHitTime = clock();
	bInput = true;
	startStage = false;
	isGrace = false;
	isParry = false;
	isDoubleParry = false;
	specialAttackCount = 2;
	isDeath = false;
	health = 3;
	createRunDustTime = clock();
	inTutorial = false;
	for (int i = 0; i < 5; i++)
	{
		EffectObject* effect = new EffectObject(EEffectType::RunDust, x, y);
		effect->SetIsActive(false);
		effects.push_back(effect);
	}
	for (int i = 0; i < BULLET_MAX_COUNT; i++)
	{
		Bullet* bullet = new Bullet();
		bullets.push_back(bullet);
	}
	CreateImage();
}

Player::Player(int x, int y) : Player()
{
	this->x = x; 
	this->y = y;
}

Player::~Player()
{
	for (auto it = playerImg.begin(); it != playerImg.end(); it++)
	{
		for (auto img : *it)
			delete (img);
	}
	playerImg.clear();

	for (auto it = effects.begin(); it != effects.end(); it++)
		delete *it;
	effects.clear();

	for (auto it = bullets.begin(); it != bullets.end(); it++)
		delete* it;
	bullets.clear();
}

void Player::Draw(HDC& hdc, Graphics& grapichs)
{
	int bx, by;
	clock_t curTime = clock();
	grapichs.ResetTransform();

	// 월드가 아니라면
	if (!inWorld)
	{
		if (!effects.empty())
		{
			for (auto effect : effects)
			{
				if (effect->GetisActive())
					effect->Draw(hdc, grapichs);
			}
		}

		curAnimMax = playerImg[(int)state].size();

		if (curTime - lastTime > 33)
		{
			curAnimCnt++;
			lastTime = clock();

			if (state == EPlayerState::HitRight)
			{
				if (curAnimCnt >= curAnimMax)
				{
					if (health <= 0)
						state = EPlayerState::Ghost;
					curAnimCnt = 0;
					isHit = false;
				}
			}
			if (curAnimMax <= curAnimCnt)
			{
				curAnimCnt = 0;
				if (state == EPlayerState::DownStartRight)
					state = EPlayerState::DownIdleRight;
				curAnimMax = playerImg[(int)state].size();
			}
		}

		if (curAnimCnt >= playerImg[(int)state].size())
			curAnimCnt = 0;

		int width = playerImg[(int)state][curAnimCnt]->GetWidth();
		int height = playerImg[(int)state][curAnimCnt]->GetHeight();

		collider.left = x - width / 2;
		collider.top = y - height;
		collider.right = x + width / 2;
		collider.bottom = y;

		if (isGrace && !isDashing)
		{
			ImageAttributes imgAttr;
			ColorMatrix colorMatrix =
			{
				0.7f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.7f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.7f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f, 1.0f
			};
			imgAttr.SetColorMatrix(&colorMatrix);
			grapichs.DrawImage(playerImg[(int)state][curAnimCnt], Rect(collider.left - camera_x, collider.top, width, height), 0, 0, width, height, UnitPixel, &imgAttr);
		}
		else grapichs.DrawImage(playerImg[(int)state][curAnimCnt], collider.left - camera_x, collider.top, width, height);
		if (inTutorial)
			collider = { x - 50, y - 100, x + 50, y };
	}

	// 월드라면
	// 월드라면
	else 
	{
		bx = playerImg[(int)EPlayerState::World][0]->GetWidth();
		by = playerImg[(int)EPlayerState::World][0]->GetHeight();

		const int unitX = bx / (WORLD_SPRITE_SIZE_X);
		const int unitY = by / (WORLD_SPRITE_SIZE_Y * 2);

		// idle인 경우
		if (worldState == EPlayerWorldState::Idle)
		{
			if (curTime - lastTime > 33)
			{
				curAnimMax = (int)EPlayerWorldState::Idle;
				curAnimCnt++;
				if (curAnimCnt >= curAnimMax)
				{
					curAnimCnt = 0;
				}
				lastTime = clock();
			}
		}
		else
		{
			if (curTime - lastTime > 33)
			{
				if (dir.x == 1)
				{
					curAnimMax = (int)worldState;
					curAnimCnt++;
					if (curAnimCnt >= curAnimMax)
						curAnimCnt = 4;
				}
				else if (dir.x == 0)
				{
					curAnimMax = (int)worldState;
					curAnimCnt++;
					if (dir.y == 1)
					{
						if (curAnimCnt >= curAnimMax)
							curAnimCnt = 0;
					}
					if (dir.y == -1)
					{
						if (curAnimCnt >= curAnimMax)
							curAnimCnt = 4;
					}
				}
				else
				{
					curAnimMax = WORLD_SPRITE_SIZE_X - 4;
					curAnimCnt++;
					if (curAnimCnt >= curAnimMax)
					{
						curAnimCnt = (WORLD_SPRITE_SIZE_X - (int)worldState);
					}
				}
				lastTime = clock();
			}
		}

		int animX = unitX * curAnimCnt;
		int animY = unitY * (int)worldSpriteY;
		if (dir.x == -1)
			animY = unitY * ((int)worldSpriteY + WORLD_SPRITE_SIZE_Y);

		collider.left	= x - 103 / 6;
		collider.top	= y - 113 / 5;
		collider.right	= x + 103 / 6;
		collider.bottom = y;
		Rect rect = {x - unitX / 2 - camera_x, y - camera_y - unitY * 6 / 7, unitX, unitY };

		grapichs.DrawImage(playerImg[(int)EPlayerState::World][0], rect, animX, animY, unitX, unitY, Gdiplus::Unit::UnitPixel);
	}
}

void Player::Update()
{
	if (inTutorial)
		collider = { x - 50, y - 100, x + 50, y };

	if (state == EPlayerState::Ghost)
		y -= 1;

	if (state == EPlayerState::RightRun || state == EPlayerState::ShootingRunRight || state == EPlayerState::ShootingRunRightUp)
		SetRunDustEffect();

	if (startStage)
	{
		clock_t curTime = clock();

		if (curTime - startChangeStateTime > STAGE_READY_TIME)
		{
			startStage = false;
			bInput = true;
			state = EPlayerState::Idle;
		}
		return;
	}

	if (!isShooting && isJumping)
	{
		if (!isDashing && !isSpecialAttack)
		{
			y -= curJumpPower;
			curJumpPower -= 5;
		}
		else if (isDashing)
		{
			if (!isDashAndJump)
			{
				curAnimCnt = 0;
				isDashAndJump = true;
			}
		}
		else if (isSpecialAttack)
		{
			if (!isSpecialAttackAndJump)
			{
				curAnimCnt = 0;
				isSpecialAttackAndJump = true;
			}
		}
		if (!isSpecialAttack && !isHit )
		{
			if (isParry)
			{
				switch (dir.x)
				{
				case -1:
					break;
				case 1:
					break;
				case 0:
					break;
				}
			}
			else
			{
				switch (dir.x)
				{
				case -1:
				case 1:
				case 0:
					if (health <= 0)
						SetState(EPlayerState::Ghost);
					else SetState(EPlayerState::RightJump);
					break;
				}
			}
		}
		if (y >= GROUND_POSITION_Y)
		{
			SetJumpDown();
			y = GROUND_POSITION_Y;
			if (!isHit)
			{
				switch (dir.y)
				{
				case 0:
					SetState(EPlayerState::Idle);
					break;
				case -1:
				case 1:
					SetState(EPlayerState::RightRun);
					break;
				}
			}
			if (health <= 0)
				SetState(EPlayerState::Ghost);
		}
	}

	if (!isShooting && isDashing && !isSpecialAttack && !isHit)
	{
		clock_t curTime = clock();
		curJumpPower = 0;
		isGrace = true;
		switch (dir.x)
		{
		case -1:
		case 1:
			if (isDashAndJump)
				state = EPlayerState::RightAirDash;
			else state = EPlayerState::RightDash;
			break;
		}
		if (curTime - startChangeStateTime > 350)
		{
			isGrace = false;
			isDashing = false;
			speed = 1.0f;
			switch (dir.x)
			{
			case 0:
				if (isJumping) state = EPlayerState::RightJump;
				else state = EPlayerState::Idle;
				break;
			case -1:
			case 1:
				if (isJumping) state = EPlayerState::RightJump;
				else state = EPlayerState::RightRun;				
				break;
			}
			curAnimCnt = 0;
		}
	}

	if (isSpecialAttack && !isHit)
	{
		clock_t curTime = clock();
		if (isSpecialAttackAndJump)
		{
			if (curTime - startChangeStateTime > 400)
			{
				state = prevState;
				isSpecialAttack = false;
				curAnimCnt = 0;
			}
		}
		else
		{
			if (curTime - startChangeStateTime > 800)
			{
				state = prevState;
				isSpecialAttack = false;
				curAnimCnt = 0;
			}
		}
	}
	curAnimMax = playerImg[(int)state].size();

	if (isShooting && !isHit)
	{
		clock_t curTime = clock();

		if (curTime - lastShootingTime > 400)
		{
			Shooting();
			lastShootingTime = clock();
		}
	}

	if (isGrace && !isDashing)
	{
		clock_t curTime = clock();
		if (curTime - isHitTime > GRACE_PERIOD)
		{
			isGrace = false;
		}
	}
}

bool Player::Collided(Boss* boss)
{
	if (isDeath)
		return false;
	if (this->collider.IsOverlaps(*boss->GetCollider()))
	{
		if (boss->GetIsPunch())
		{
			if (isDown)
				return false;
		}
		DecreaseHealth();
		return true;
	}
	return false;
}

void Player::Shooting()
{
	if (isDown)
	{
		for (auto bullet : bullets)
		{
			if (!bullet->GetisActive())
			{
				if (dir.x != 0) bullet->SetBullet(x + dir.x * 80, y - 40, { dir.x, 0 });
				else
				{
					if (lastForward == LAST_FORWARD_IS_LEFT) bullet->SetBullet(x - 80, y - 40, { -1, 0 });
					else bullet->SetBullet(x + 80, y - 40, { 1, 0 });
				}
				break;
			}
		}
	}

	else if (isLockin)
	{
		for (auto bullet : bullets)
		{
			if (!bullet->GetisActive())
			{
				if (dir.x == 0)
				{
					if (dir.y == -1) bullet->SetBullet(x + 35, y + 120 * dir.y, { dir.x, dir.y });
					else if (dir.y == 1) bullet->SetBullet(x + 35, y + 10 * dir.y, { dir.x, dir.y });
					else
					{
						if (lastForward == LAST_FORWARD_IS_LEFT) bullet->SetBullet(x - 80, y - 80, { -1, dir.y });
						else bullet->SetBullet(x + 80, y - 80, { 1, dir.y });
					}
				}
				else
				{
					if (dir.y == 0) bullet->SetBullet(x + dir.x * 80, y - 80, dir);
					else if (dir.y == -1) bullet->SetBullet(x + dir.x * 60, y - 110, dir);
					else bullet->SetBullet(x + dir.x * 60, y - 20, dir);
				}
				break;
			}
		}
	}

	else
	{
		for (auto bullet : bullets)
		{
			if (!bullet->GetisActive())
			{
				if (dir.x == 0)
				{
					if (dir.y == -1) bullet->SetBullet(x + 35, y + 120 * dir.y, { dir.x, dir.y });
					else
					{
						if (lastForward == LAST_FORWARD_IS_LEFT) bullet->SetBullet(x - 80, y - 80, { -1, dir.y });
						else bullet->SetBullet(x + 80, y - 80, { 1, dir.y });
					}
				}
				else
				{
					if (dir.y != 0)
						bullet->SetBullet(x + dir.x * 90, y + 100 * dir.y, dir);
					else bullet->SetBullet(x + dir.x * 80, y - 80, dir);
				}
				break;
			}
		}
	}
	lastShootingTime = clock();
}

void Player::SetCameraPos(int x, int y)
{
	int deltaX = (camera_x - x);
	int deltaY = (camera_y - y);
	this->x -= deltaX;
	this->y -= deltaY;
	camera_x = x;
	camera_y = y;

	for (auto effect : effects)
	{
		if (effect->GetisActive())
			effect->SetCameraPos(x, y);
	}
}

void Player::SetCameraPosX(int x)
{
	int deltaX = (camera_x - x);
	this->x -= deltaX;
	camera_x = x;
	for (auto effect : effects)
	{
		if (effect->GetisActive())
			effect->SetCameraPos(-x, 0);
	}
}

void Player::SetCameraPosY(int y)
{
	int deltaY = (camera_y - y);
	this->y -= deltaY;
	camera_y = y;
}

void Player::UpdateCameraPosX(int x)
{
	camera_x = x;
}

void Player::SetState(EPlayerWorldState state, EWorldSpriteY spriteY)
{
	this->worldState = state;
	this->worldSpriteY = spriteY;
}

void Player::SetState(EPlayerState state)
{
	EPlayerState temp = this->state;
	if (!isJumping && !isDashing && !isDown && !isShooting && !isSpecialAttack && !isHit)
	{
		temp = state;
	}

	// 슈팅
	if (isShooting && !isLockin && !isJumping && !isDashing && !isSpecialAttack)
	{
		if (isDown)
		{
			temp = EPlayerState::DownShootingRight;
		}
		else
		{
			switch (dir.y)
			{
			case -1:
				if (dir.x != 0) temp = EPlayerState::ShootingRunRightUp;
				else temp = EPlayerState::ShootingUp;
				break;
			case 0:
				if (dir.x != 0) temp = EPlayerState::ShootingRunRight;
				else temp = EPlayerState::ShootingRight;
				break;
			case 1:
				if (dir.x != 0) temp = EPlayerState::ShootingRunRight;
				else temp = EPlayerState::ShootingRight;
			}
		}
	}

	// 록인
	if (isLockin && !isJumping && !isDashing && !isSpecialAttack)
	{
		switch (dir.y)
		{
		case -1:
			if (isShooting)
			{
				if (dir.x != 0) temp = EPlayerState::ShootingRightUp;
				else temp = EPlayerState::ShootingUp;
			}
			else if (dir.x != 0) temp = EPlayerState::AimRightUp;
			else temp = EPlayerState::AimUp;
			break;
		case 0:
			if (isShooting)
			{
				if (dir.x != 0) temp = EPlayerState::ShootingRight;
				else temp = EPlayerState::ShootingRight;
			}
			else if (dir.x != 0) temp = EPlayerState::AimRight;
			else temp = EPlayerState::AimRight;
			break;
		case 1:
			if (isShooting)
			{
				if (dir.x != 0) temp = EPlayerState::ShootingRightDown;
				else temp = EPlayerState::ShootingDown;
			}
			else if (dir.x != 0) temp = EPlayerState::AimRightDown;
			else temp = EPlayerState::AimDown;
			break;
		}
	}

	if (temp != this->state)
	{
		curAnimCnt = 0;
		this->state = temp;
	}

	curAnimMax = playerImg[(int)state].size();
}

void Player::SetStateOnce(EPlayerState state)
{
	this->state = state;
}

void Player::SetInWorld(bool isWorld)
{
	inWorld = isWorld;
	if (isWorld)
		state = EPlayerState::World;
	else
		state = EPlayerState::Idle;
	curAnimCnt = 0;
}

void Player::Move(int x, int y)
{
	if (!inWorld)
	{
		if (this->x - x < 65)
			return;
		if (this->x - x > 1215)
			return;
	}


	this->x -= x;
	this->y -= y;
}

void Player::SetSpeed(float speed)
{
	this->speed = speed;
}

void Player::Turn()
{
	static int turncount = 0;
	for (int i = 1; i < playerImg.size(); i++)
	{
		for (int j = 0; j < playerImg[i].size(); j++)
			playerImg[i][j]->RotateFlip(RotateFlipType::RotateNoneFlipX);
	}
}

void Player::SetDirection(int forwardX)
{
	this->forwardDir.x = forwardX;
}

void Player::SetDirection(int x, int y)
{
	if (x != 99)
	{
		if (this->dir.x != x)
		{
			if (lastForward == LAST_FORWARD_IS_LEFT)
			{
				if (x == 1)
				{
					Turn();
					lastForward = LAST_FORWARD_IS_RIGHT;
				}
			}
			else
			{
				if (x == -1)
				{
					Turn();
					lastForward = LAST_FORWARD_IS_LEFT;
				}
			}
		}
		this->dir.x = x;
	}
	if (y != 99)
		this->dir.y = y;
}

void Player::SetXPos(int x)
{
	this->x = x;
}

void Player::SetYPos(int y)
{
	this->y = y;
}

void Player::Parry()
{
	SetIsJumping(true);
	if (isParry)
	{
		isDoubleParry = true;
		state = EPlayerState::ParryPinkRight;
	}
	else state = EPlayerState::ParryRight;
	isParry = true;
	if (specialAttackCount < 5)
		specialAttackCount++;
}

void Player::SetRunDustEffect()
{
	clock_t curTime = clock();
	if (curTime - createRunDustTime > 300)
	{
		for (auto effect : effects)
		{
			if (!effect->GetisActive())
			{
				effect->SetEffect(EEffectType::RunDust);
				effect->SetIsActive(true);
				effect->SetPosition(x + 30 * dir.x, y);
				createRunDustTime = clock();
				return;
			}
		}
	}
}

void Player::SetIsJumping(bool isJumping)
{
	ReadyToSetState();
	this->isJumping = isJumping;
	if (isJumping)
		curJumpPower = JumpMaxPower;

	state = EPlayerState::RightJump;
	curAnimCnt = 0;
	curAnimMax = playerImg[(int)state].size();
}

void Player::SetJumpDown()
{
	isParry = false;
	isDoubleParry = false;
	if (isDashAndJump) isDashAndJump = false;
	if (isSpecialAttackAndJump) isSpecialAttackAndJump = false;
	isJumping = false;
	setJumpDust = true;
}

void Player::SetIsDashing(bool isDashing)
{
	if (isDashAndJump) return;
	
	ReadyToSetState();

	this->isDashing = isDashing;
	isGrace = true;
	state = EPlayerState::RightDash;
	speed = DASH_SPEED;
	startChangeStateTime = clock();

	curAnimCnt = 0;
	curAnimMax = playerImg[(int)state].size();
}

void Player::SetIsDown(bool isDown)
{
	if (!ReadyToSetState())
		return;

	this->isDown = isDown;
	if (isDown)
	{
		state = EPlayerState::DownStartRight;
	}

	curAnimCnt = 0;
	curAnimMax = playerImg[(int)state].size();
}

void Player::SetIsShooting(bool isShooting)
{
	if (isJumping) return;
	if (isDashAndJump) return;
	if (isDashing) return;

	if (isDown && isShooting == false)
	{
		state = EPlayerState::DownIdleRight;
	}

	this->isShooting = isShooting;

	if (isShooting)
		Shooting();

	curAnimCnt = 0;
	curAnimMax = playerImg[(int)state].size();
}

void Player::SetIsLockin(bool isLockin)
{
	if (!ReadyToSetState())
		return;
	this->isLockin = isLockin;
	curAnimCnt = 0;
	curAnimMax = playerImg[(int)state].size();
}

void Player::SetIsSpecialAttack(bool isSpecialAttack)
{
	if (isDashing || isSpecialAttackAndJump || this->isSpecialAttack)
		return;

	specialAttackCount -= 1;
	this->isSpecialAttack = isSpecialAttack;
	if (isSpecialAttack)
	{
#pragma region Set Anim State
		startChangeStateTime = clock();
		prevState = state;

		// set state
		if (isJumping)
		{
			switch (dir.y)
			{
			case -1:
				if (dir.x == 0) state = EPlayerState::AirSCAttackUp;
				else state = EPlayerState::AirSCAttackRightUp;
				break;
			case 0:
				state = EPlayerState::AirSCAttackRight;
				break;
			case 1:
				if (dir.x == 0) state = EPlayerState::AirSCAttackDown;
				else state = EPlayerState::AirSCAttackRightDown;
				break;
			}
		}
		else
		{
			switch (dir.y)
			{
			case -1:
				if (dir.x == 0) state = EPlayerState::SCAttackUp;
				else state = EPlayerState::SCAttackRightUp;
				break;
			case 0:
				state = EPlayerState::SCAttackRight;
				break;
			case 1:
				if (dir.x == 0) state = EPlayerState::SCAttackDown;
				else state = EPlayerState::SCAttackRightDown;
				break;
			}
		}
#pragma endregion

#pragma region Set Bullet
		for (auto bullet : bullets)
		{
			if (!bullet->GetisActive())
			{
				if (dir.y == 0)
				{
					switch (dir.x)
					{
					case 0:
						if ( lastForward == LAST_FORWARD_IS_LEFT )
							bullet->SetBullet(x - 60, y - 60, { -1, 0 }, true);
						else bullet->SetBullet(x + 60, y - 60, { 1, 0 }, true);
						break;
					case 1:
					case -1:
						bullet->SetBullet(x + 60 * dir.x, y - 60, { dir.x, 0 }, true);
						break;
					}
				}
				else if (dir.y == -1)
				{
					switch (dir.x)
					{
					case 0:
						bullet->SetBullet(x, y - 130, { dir.x, dir.y }, true);
						break;
					case 1:
					case -1:
						bullet->SetBullet(x + 60 * dir.x, y - 90, { dir.x, dir.y }, true);
						break;
					}
				}
				else
				{
					switch (dir.x)
					{
					case 0:
						bullet->SetBullet(x, y, { 0, dir.y }, true);
						break;
					case 1:
					case -1:
						bullet->SetBullet(x + 60 * dir.x, y, { dir.x, dir.y }, true);
						break;
					}
				}
				break;
			}
		}
#pragma endregion

		curAnimCnt = 0;
		curAnimMax = playerImg[(int)state].size();
	}
}

void Player::SetLastForward(bool lastForward)
{
	this->lastForward = lastForward;
}

void Player::DecreaseHealth()
{
	isHitTime = clock();
	isGrace = true;
	isHit = true;
	state = EPlayerState::HitRight;
	curAnimCnt = 0;
	health -= 1;

	if (health <= 0)
	{
		health = 0;
		isDeath = true;
		bInput = false;
	}
}

bool Player::ReadyToSetState()
{
	if (isJumping || isDashAndJump)
		return false;

	isDown = false;
	isDashing = false;
	isShooting = false;
	isLockin = false;
	return true;
}

void Player::SetStage()
{
	x = WINDOWS_WIDTH / 2 - 300;
	y = GROUND_POSITION_Y;
	SetInWorld(false);
	bInput = false;
	startStage = true;
	startChangeStateTime = clock();
	dir.x = 0;
	camera_x = 0;
	camera_y = 0;
	lastForward = LAST_FORWARD_IS_RIGHT;
	state = EPlayerState::Intro;
}

bool Player::CanMoveDirX()
{
	if (isLockin) return false;
	if (isDown)	return false;
	if (isSpecialAttack) return false;
	return true;
}
