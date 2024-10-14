#include "Player.h"
#include <string>
using namespace std;

void Player::CreateImage()
{
	playerImg.resize((int)EPlayerState::Max);

	// Image Load
	playerImg[(int)EPlayerState::World].resize(1);
	playerImg[(int)EPlayerState::World][0].Load(L"../Resource/Image/Cuphead/CupHead_Word01.png");

#pragma region Load Image
	// idle
	TCHAR path[128] = L"../Resource/Image/Cuphead/cuphead_idle_000";
	ParsingToImagePath(EPlayerState::Idle, PLAYER_IDEL_SIZE, path, 1);
	// run
	_tcscpy(path, L"../Resource/Image/Cuphead/Run/cuphead_run_00");
	ParsingToImagePath(EPlayerState::RightRun, 16, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Run/R_cuphead_run_00");
	ParsingToImagePath(EPlayerState::LeftRun, 16, path, 1);
	// jump
	_tcscpy(path, L"../Resource/Image/Cuphead/Jump/cuphead_jump_000");
	ParsingToImagePath(EPlayerState::RightJump, 8, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Jump/R_cuphead_jump_000");
	ParsingToImagePath(EPlayerState::LeftJump, 8, path, 1);
	// dash
	_tcscpy(path, L"../Resource/Image/Cuphead/Dash/cuphead_dash_000");
	ParsingToImagePath(EPlayerState::RightDash, 8, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Dash/cuphead_dash_air_000");
	ParsingToImagePath(EPlayerState::RightAirDash, 8, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Dash/R_cuphead_dash_000");
	ParsingToImagePath(EPlayerState::LeftDash, 8, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Dash/R_cuphead_dash_air_000");
	ParsingToImagePath(EPlayerState::LeftAirDash, 8, path, 1);
	// down
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/cuphead_duck_000");
	ParsingToImagePath(EPlayerState::DownStartRight, 7, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/cuphead_duck_idle_000");
	ParsingToImagePath(EPlayerState::DownIdleRight, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/R_cuphead_duck_000");
	ParsingToImagePath(EPlayerState::DownStartLeft, 7, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/R_cuphead_duck_idle_000");
	ParsingToImagePath(EPlayerState::DownIdleLeft, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/cuphead_duck_shoot_000");
	ParsingToImagePath(EPlayerState::DownShootingRight, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/R_cuphead_duck_shoot_000");
	ParsingToImagePath(EPlayerState::DownShootingLeft, 6, path, 1);
	// run & shooting
	_tcscpy(path, L"../Resource/Image/Cuphead/RunShooting/cuphead_run_shoot_00");
	ParsingToImagePath(EPlayerState::ShootingRunRight, 16, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/RunShooting/cuphead_run_shoot_diagonal_up_00");
	ParsingToImagePath(EPlayerState::ShootingRunRightUp, 16, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/RunShooting/R_cuphead_run_shoot_00");
	ParsingToImagePath(EPlayerState::ShootingRunLeft, 16, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/RunShooting/R_cuphead_run_shoot_diagonal_up_00");
	ParsingToImagePath(EPlayerState::ShootingRunLeftUp, 16, path, 1);
	// shooting
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/cuphead_shoot_straight_000");
	ParsingToImagePath(EPlayerState::ShootingRight, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/R_cuphead_shoot_straight_000");
	ParsingToImagePath(EPlayerState::ShootingLeft, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/cuphead_shoot_diagonal_up_000");
	ParsingToImagePath(EPlayerState::ShootingRightUp, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/R_cuphead_shoot_diagonal_up_000");
	ParsingToImagePath(EPlayerState::ShootingLeftUp, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/cuphead_shoot_diagonal_down_000");
	ParsingToImagePath(EPlayerState::ShootingRightDown, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Shooting/R_cuphead_shoot_diagonal_down_000");
	ParsingToImagePath(EPlayerState::ShootingLeftDown, 6, path, 1);
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
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/R_cuphead_aim_straight_000");
	ParsingToImagePath(EPlayerState::AimLeft, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/R_cuphead_aim_diagonal_up_000");
	ParsingToImagePath(EPlayerState::AimLeftUp, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/R_cuphead_aim_diagonal_down_000");
	ParsingToImagePath(EPlayerState::AimLeftDown, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/cuphead_aim_up_000");
	ParsingToImagePath(EPlayerState::AimUp, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Aim/cuphead_aim_down_000");
	ParsingToImagePath(EPlayerState::AimDown, 5, path, 1);
	// Special Attack 
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_straight_00");
	ParsingToImagePath(EPlayerState::SCAttackRight, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/R_cuphead_ex_straight_00");
	ParsingToImagePath(EPlayerState::SCAttackLeft, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_diagonal_down_00");
	ParsingToImagePath(EPlayerState::SCAttackRightDown, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/R_cuphead_ex_diagonal_down_00");
	ParsingToImagePath(EPlayerState::SCAttackLeftDown, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_diagonal_up_00");
	ParsingToImagePath(EPlayerState::SCAttackRightUp, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/R_cuphead_ex_diagonal_up_00");
	ParsingToImagePath(EPlayerState::SCAttackLeftUp, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_down_00");
	ParsingToImagePath(EPlayerState::SCAttackDown, 13, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/cuphead_ex_up_00");
	ParsingToImagePath(EPlayerState::SCAttackUp, 13, path, 1);
	// Jump Special Attack
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_straight_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackRight, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/R_cuphead_ex_straight_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackLeft, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_diagonal_down_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackRightDown, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/R_cuphead_ex_diagonal_down_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackLeftDown, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_diagonal_up_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackRightUp, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/R_cuphead_ex_diagonal_up_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackLeftUp, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_down_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackDown, 6, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/SCAttack/Air/cuphead_ex_up_air_000");
	ParsingToImagePath(EPlayerState::AirSCAttackUp, 6, path, 1);

#pragma endregion

	curAnimMax = playerImg[(int)EPlayerState::World].size();
	curAnimCnt = 0;
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

		playerImg[(int)state][i].Load(temp);

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
	speed = 1;

	for (int i = 0; i < BULLET_MAX_COUNT; i++)
	{
		Bullet* bullet = new Bullet();
		bullets.push_back(bullet);
	}
	CreateImage();
}

Player::Player(int x, int y)
{
	worldState = EPlayerWorldState::Idle;
	state = EPlayerState::World;
	collider.left = 0;
	collider.top = 0;
	collider.right = 0;
	collider.bottom = 0;
	curAnimCnt = 0;
	this->x = x; 
	this->y = y;
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
	lastForward = LAST_FORWARD_IS_RIGHT;
	setJumpDust = false;
	speed = 1;

	for (int i = 0; i < BULLET_MAX_COUNT; i++)
	{
		Bullet* bullet = new Bullet();
		bullets.push_back(bullet);
	}
	CreateImage();
}

Player::~Player()
{
	for (auto it = playerImg.begin(); it != playerImg.end(); it++)
	{
		for (auto img : *it)
		{
			delete (img);
		}
	}

	playerImg.clear();
}

void Player::Draw(HDC& hdc)
{
	int bx, by;
	clock_t curTime = clock();

	// 월드가 아니라면
	if (!inWorld)
	{
		curAnimMax = playerImg[(int)state].size();

		if (curTime - lastTime > 50)
		{
			curAnimCnt++;
			lastTime = clock();

			if (curAnimMax <= curAnimCnt)
			{
				curAnimCnt = 0;
				if (state == EPlayerState::DownStartRight)
					state = EPlayerState::DownIdleRight;
				else if (state == EPlayerState::DownStartLeft)
					state = EPlayerState::DownIdleLeft;
				curAnimMax = playerImg[(int)state].size();
			}
		}

		if (curAnimCnt >= playerImg[(int)state].size())
			curAnimCnt = 0;

		collider.left = x - playerImg[(int)state][curAnimCnt].GetWidth() / 2;
		collider.top = y - playerImg[(int)state][curAnimCnt].GetHeight();
		collider.right = x + playerImg[(int)state][curAnimCnt].GetWidth() / 2;
		collider.bottom = y;

		playerImg[(int)state][curAnimCnt].Draw(hdc, collider.left, collider.top);
	}

	// 월드라면
	else 
	{
		bx = playerImg[(int)EPlayerState::World][0].GetWidth();
		by = playerImg[(int)EPlayerState::World][0].GetHeight();

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

		playerImg[(int)EPlayerState::World][0].Draw(hdc, collider.left - unitX / 3 - camera_x, collider.top - unitY * 5 / 7 - camera_y, unitX, unitY, animX, animY, unitX, unitY);
	}

	Update();
}

void Player::Update()
{
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
		if (!isSpecialAttack)
		{
			switch (dir.x)
			{
			case -1:
				state = EPlayerState::LeftJump;
				break;
			case 1:
			case 0:
				state = EPlayerState::RightJump;
				break;
			}
		}

		if (y >= GROUND_POSITION_Y)
		{
			if (isDashAndJump) isDashAndJump = false;
			if (isSpecialAttackAndJump) isSpecialAttackAndJump = false;
			isJumping = false;
			y = GROUND_POSITION_Y;
			setJumpDust = true;
			switch (dir.y)
			{
			case 0:
				state = EPlayerState::Idle;
				break;
			case -1:
				state = EPlayerState::LeftRun;
				break;
			case 1:
				state = EPlayerState::RightRun;
				break;
			}
		}
	}

	if (!isShooting && isDashing && !isSpecialAttack)
	{
		clock_t curTime = clock();
		curJumpPower = 0;
		switch (dir.x)
		{
		case 1:
			if (isDashAndJump)
				state = EPlayerState::RightAirDash;
			else state = EPlayerState::RightDash;
			break;
		case -1:
			if (isDashAndJump)
				state = EPlayerState::LeftAirDash;
			else state = EPlayerState::LeftDash;
			break;
		}
		if (curTime - startChangeStateTime > 350)
		{
			isDashing = false;
			speed = 1.0f;
			switch (dir.x)
			{
			case 0:
				state = EPlayerState::Idle;
				break;
			case 1:
				state = EPlayerState::RightRun;
				break;
			case -1:
				state = EPlayerState::LeftRun;
				break;
			}
			curAnimCnt = 0;
		}
	}

	if (isSpecialAttack)
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
}

void Player::SetCameraPos(int x, int y)
{
	int deltaX = (camera_x - x);
	int deltaY = (camera_y - y);
	this->x -= deltaX;
	this->y -= deltaY;
	camera_x = x;
	camera_y = y;
}

void Player::SetCameraPosX(int x)
{
	int deltaX = (camera_x - x);
	this->x -= deltaX;
	camera_x = x;
}

void Player::SetCameraPosY(int y)
{
	int deltaY = (camera_y - y);
	this->y -= deltaY;
	camera_y = y;
}

void Player::SetState(EPlayerWorldState state, EWorldSpriteY spriteY)
{
	this->worldState = state;
	this->worldSpriteY = spriteY;
}

void Player::SetState(EPlayerState state)
{
	EPlayerState temp = this->state;
	if (!isJumping && !isDashing && !isDown && !isShooting && !isSpecialAttack)
	{
		temp = state;
	}

	// 슈팅
	if (isShooting && !isLockin && !isJumping && !isDashing && !isSpecialAttack)
	{
		if (isDown)
		{
			if (dir.x == 1) temp = EPlayerState::DownShootingRight;
			else if (dir.x == -1) temp = EPlayerState::DownShootingLeft;
			else
			{
				if (lastForward == LAST_FORWARD_IS_LEFT) temp = EPlayerState::DownShootingLeft;
				else temp = EPlayerState::DownShootingRight;
			}
		}
		else
		{
			switch (dir.y)
			{
			case -1:
				if (dir.x == 1) temp = EPlayerState::ShootingRunRightUp;
				else if (dir.x == -1) temp = EPlayerState::ShootingRunLeftUp;
				else temp = EPlayerState::ShootingUp;
				break;
			case 0:
				if (dir.x == 1) temp = EPlayerState::ShootingRunRight;
				else if (dir.x == -1) temp = EPlayerState::ShootingRunLeft;
				else
				{
					if (lastForward == LAST_FORWARD_IS_LEFT) temp = EPlayerState::ShootingLeft;
					else temp = EPlayerState::ShootingRight;
				}
				break;
			case 1:
				if (dir.x == 1) temp = EPlayerState::ShootingRunRight;
				else if (dir.x == -1) temp = EPlayerState::ShootingRunLeft;
				else
				{
					if (lastForward == LAST_FORWARD_IS_LEFT) temp = EPlayerState::ShootingLeft;
					else temp = EPlayerState::ShootingRight;
				}
				break;
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
				if (dir.x == 1) temp = EPlayerState::ShootingRightUp;
				else if (dir.x == -1) temp = EPlayerState::ShootingLeftUp;
				else temp = EPlayerState::ShootingUp;
			}
			else if (dir.x == 1) temp = EPlayerState::AimRightUp;
			else if (dir.x == -1) temp = EPlayerState::AimLeftUp;
			else temp = EPlayerState::AimUp;
			break;
		case 0:
			if (isShooting)
			{
				if (dir.x == -1) temp = EPlayerState::ShootingLeft;
				else if (dir.x == 1) temp = EPlayerState::ShootingRight;
				else
				{
					if (lastForward == LAST_FORWARD_IS_LEFT) temp = EPlayerState::ShootingLeft;
					else temp = EPlayerState::ShootingRight;
				}
			}
			else if (dir.x == -1) temp = EPlayerState::AimLeft;
			else if (dir.x == 1) temp = EPlayerState::AimRight;
			else
			{
				if (lastForward == LAST_FORWARD_IS_LEFT) temp = EPlayerState::AimLeft;
				else temp = EPlayerState::AimRight;
			}
			break;
		case 1:
			if (isShooting)
			{
				if (dir.x == 1) temp = EPlayerState::ShootingRightDown;
				else if (dir.x == -1) temp = EPlayerState::ShootingLeftDown;
				else temp = EPlayerState::ShootingDown;
			}
			else if (dir.x == 1) temp = EPlayerState::AimRightDown;
			else if (dir.x == -1) temp = EPlayerState::AimLeftDown;
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

void Player::SetXPos(int x)
{
	this->x = x;
}

void Player::SetYPos(int y)
{
	this->y = y;
}

void Player::SetIsJumping(bool isJumping)
{
	ReadyToSetState();
	this->isJumping = isJumping;
	if (isJumping)
		curJumpPower = JumpMaxPower;

	if (dir.x == -1)
		state = EPlayerState::LeftJump;
	else 
		state = EPlayerState::RightJump;
	curAnimCnt = 0;
	curAnimMax = playerImg[(int)state].size();
}

void Player::SetIsDashing(bool isDashing)
{
	if (isDashAndJump) return;
	
	ReadyToSetState();

	this->isDashing = isDashing;
	if (dir.x == -1)
		state = EPlayerState::LeftDash;
	else state = EPlayerState::RightDash;
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
		if (dir.x == -1)
			state = EPlayerState::DownStartLeft;
		else if (dir.x == 1) state = EPlayerState::DownStartRight;
		else
		{
			if (lastForward == LAST_FORWARD_IS_LEFT) state = EPlayerState::DownStartLeft;
			else state = EPlayerState::DownStartRight;
		}
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
		if (dir.x == -1)
			state = EPlayerState::DownIdleLeft;
		else if (dir.x == 1) state = EPlayerState::DownIdleRight;
		else
		{
			if (lastForward == LAST_FORWARD_IS_LEFT) state = EPlayerState::DownIdleLeft;
			else state = EPlayerState::DownIdleRight;
		}
	}

	this->isShooting = isShooting;

	if (isShooting)
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
						if ( dir.y != 0)
							bullet->SetBullet(x + dir.x * 90, y + 100 * dir.y, dir);
						else bullet->SetBullet(x + dir.x * 80, y - 80, dir);
					}
					break;
				}
			}
		}

	}

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
				else if (dir.x == 1) state = EPlayerState::AirSCAttackRightUp;
				else state = EPlayerState::AirSCAttackLeftUp;
				break;
			case 0:
				if (dir.x == 0)
				{
					if (lastForward == LAST_FORWARD_IS_LEFT) state = EPlayerState::AirSCAttackLeft;
					else state = EPlayerState::AirSCAttackRight;
				}
				else if (dir.x == 1) state = EPlayerState::AirSCAttackRight;
				else state = EPlayerState::AirSCAttackLeft;
				break;
			case 1:
				if (dir.x == 0) state = EPlayerState::AirSCAttackDown;
				else if (dir.x == 1) state = EPlayerState::AirSCAttackRightDown;
				else state = EPlayerState::AirSCAttackLeftDown;
				break;
			}
		}
		else
		{
			switch (dir.y)
			{
			case -1:
				if (dir.x == 0) state = EPlayerState::SCAttackUp;
				else if (dir.x == 1) state = EPlayerState::SCAttackRightUp;
				else state = EPlayerState::SCAttackLeftUp;
				break;
			case 0:
				if (dir.x == 0)
				{
					if (lastForward == LAST_FORWARD_IS_LEFT) state = EPlayerState::SCAttackLeft;
					else state = EPlayerState::SCAttackRight;
				}
				else if (dir.x == 1) state = EPlayerState::SCAttackRight;
				else state = EPlayerState::SCAttackLeft;
				break;
			case 1:
				if (dir.x == 0) state = EPlayerState::SCAttackDown;
				else if (dir.x == 1) state = EPlayerState::SCAttackRightDown;
				else state = EPlayerState::SCAttackLeftDown;
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
}

bool Player::CanMoveDirX()
{
	if (isLockin) return false;
	if (isDown)	return false;
	if (isSpecialAttack) return false;
	return true;
}
