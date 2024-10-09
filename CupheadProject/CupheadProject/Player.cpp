#include "Player.h"
#include <string>
using namespace std;

void Player::CreateImage()
{
	playerImg.resize((int)EPlayerState::Max);

	// Image Load
	playerImg[(int)EPlayerState::World].resize(1);
	playerImg[(int)EPlayerState::World][0].Load(L"../Resource/Image/Cuphead/CupHead_Word01.png");

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
	_tcscpy(path, L"../Resource/Image/Cuphead/Dash/R_cuphead_dash_000");
	ParsingToImagePath(EPlayerState::LeftDash, 8, path, 1);
	// down
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/cuphead_duck_000");
	ParsingToImagePath(EPlayerState::DownStartRight, 7, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/cuphead_duck_idle_000");
	ParsingToImagePath(EPlayerState::DownIdleRight, 5, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/R_cuphead_duck_000");
	ParsingToImagePath(EPlayerState::DownStartLeft, 7, path, 1);
	_tcscpy(path, L"../Resource/Image/Cuphead/Down/R_cuphead_duck_idle_000");
	ParsingToImagePath(EPlayerState::DownIdleLeft, 5, path, 1);
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

	currAnimMax = playerImg[(int)EPlayerState::World].size();
	currAnimCnt = 0;
}

// path�� startNum���� startNum + spriteSize������ ���ڸ� �̸����� �ؼ� Load�ϴ� �Լ�, �⺻�� png ������
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
			_tcscat(temp, L" ������ �� �� �����ϴ�.");
			MessageBox(NULL, temp, _T("����"), MB_OK);
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
	currAnimCnt = 0;
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
	lastForward = true;
	speed = 1;
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
	currAnimCnt = 0;
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
	lastForward = true;
	speed = 1;
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

	// ���尡 �ƴ϶��
	if (!inWorld)
	{
		currAnimMax = playerImg[(int)state].size();

		if (curTime - lastTime > 50)
		{
			currAnimCnt++;
			lastTime = clock();

			if (currAnimMax <= currAnimCnt)
			{
				currAnimCnt = 0;
				if (state == EPlayerState::DownStartRight)
					state = EPlayerState::DownIdleRight;
				else if (state == EPlayerState::DownStartLeft)
					state = EPlayerState::DownIdleLeft;
				currAnimMax = playerImg[(int)state].size();
			}
		}

		collider.left = x - playerImg[(int)state][currAnimCnt].GetWidth() / 2;
		collider.top = y - playerImg[(int)state][currAnimCnt].GetHeight();
		collider.right = x + playerImg[(int)state][currAnimCnt].GetWidth() / 2;
		collider.bottom = y;

		playerImg[(int)state][currAnimCnt].Draw(hdc, collider.left, collider.top);
	}

	// ������
	else 
	{
		bx = playerImg[(int)EPlayerState::World][0].GetWidth();
		by = playerImg[(int)EPlayerState::World][0].GetHeight();

		const int unitX = bx / (WORLD_SPRITE_SIZE_X);
		const int unitY = by / (WORLD_SPRITE_SIZE_Y * 2);

		// idle�� ���
		if (worldState == EPlayerWorldState::Idle)
		{
			if (curTime - lastTime > 50)
			{
				currAnimMax = (int)EPlayerWorldState::Idle;
				currAnimCnt++;
				if (currAnimCnt >= currAnimMax)
				{
					currAnimCnt = 0;
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
					currAnimMax = (int)worldState;
					currAnimCnt++;
					if (currAnimCnt >= currAnimMax)
						currAnimCnt = 4;
				}
				else if (dir.x == 0)
				{
					currAnimMax = (int)worldState;
					currAnimCnt++;
					if (dir.y == 1)
					{
						if (currAnimCnt >= currAnimMax)
							currAnimCnt = 0;
					}
					if (dir.y == -1)
					{
						if (currAnimCnt >= currAnimMax)
							currAnimCnt = 4;
					}
				}
				else
				{
					currAnimMax = WORLD_SPRITE_SIZE_X - 4;
					currAnimCnt++;
					if (currAnimCnt >= currAnimMax)
					{
						currAnimCnt = (WORLD_SPRITE_SIZE_X - (int)worldState);
					}
				}
				lastTime = clock();
			}
			
		}


		int animX = unitX * currAnimCnt;
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
		if (!isDashing)
		{
			y -= curJumpPower;
			curJumpPower -= 5;
		}
		else isDashAndJump = true;
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

		if (y >= GROUND_POSITION_Y)
		{
			if (isDashAndJump) isDashAndJump = false;
			isJumping = false;
			y = GROUND_POSITION_Y;
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

	if (!isShooting && isDashing)
	{
		clock_t curTime = clock();
		curJumpPower = 0;
		switch (dir.x)
		{
		case 1:
			state = EPlayerState::RightDash;
			break;
		case -1:
			state = EPlayerState::LeftDash;
			break;
		}
		if (curTime - startDashTime > 350)
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
		}
	}

	currAnimMax = playerImg[(int)state].size();
}

Collider* Player::GetCollider()
{
	return &collider;
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
	if (!isJumping && !isDashing && !isDown && !isShooting)
	{
		temp = state;
	}

	if (!isLockin && isShooting && !isJumping && !isDashing)
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

	if (isLockin && !isJumping && !isDashing)
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
		currAnimCnt = 0;
		this->state = temp;
	}

	currAnimMax = playerImg[(int)state].size();
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
	currAnimCnt = 0;
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

float Player::GetSpeed()
{
	return speed;
}

void Player::SetSpeed(float speed)
{
	this->speed = speed;
}

int Player::GetXPos()
{
	return x;
}

int Player::GetYPos()
{
	return y;
}

void Player::SetXPos(int x)
{
	this->x = x;
}

void Player::SetYPos(int y)
{
	this->y = y;
}

bool Player::GetIsJumping()
{
	return isJumping;
}

void Player::SetIsJumping(bool isJumping)
{
	ReadyToSetState();
	this->isJumping = isJumping;
	if (isJumping)
		curJumpPower = JumpMaxPower;
	currAnimCnt = 0;
	if (dir.x == -1)
		state = EPlayerState::LeftJump;
	else 
		state = EPlayerState::RightJump;
}

bool Player::GetIsDashing()
{
	return isDashing;
}

void Player::SetIsDashing(bool isDashing)
{
	if (isDashAndJump) return;

	this->isDashing = isDashing;
	currAnimCnt = 0;
	if (dir.x == -1)
		state = EPlayerState::LeftDash;
	else state = EPlayerState::RightDash;
	speed = DASH_SPEED;
	startDashTime = clock();
}

bool Player::GetIsDown()
{
	return isDown;
}

void Player::SetIsDown(bool isDown)
{
	if (!ReadyToSetState())
		return;

	this->isDown = isDown;
	currAnimCnt = 0;
	if (isDown)
	{
		if (dir.x == -1)
			state = EPlayerState::DownStartLeft;
		else state = EPlayerState::DownStartRight;
	}
}

bool Player::GetIsShooting()
{
	return isShooting;
}

void Player::SetIsShooting(bool isShooting)
{
	if (isJumping) return;
	if (isDashAndJump) return;
	if (isDashing) return;

	this->isShooting = isShooting;

	currAnimCnt = 0;
}

bool Player::GetIsLockin()
{
	return isLockin;
}

void Player::SetIsLockin(bool isLockin)
{
	if (!ReadyToSetState())
		return;
	this->isLockin = isLockin;
}

bool Player::GetLastForward()
{
	return lastForward;
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

EPlayerWorldState Player::GetWorldState()
{
	return worldState;
}

EPlayerState Player::GetPlayerState()
{
	return state;
}
