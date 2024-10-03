#include "Player.h"
#include <string>
using namespace std;

void Player::CreateImage()
{
	playerImg.resize((int)EPlayerState::Max);

	// Image Load
	playerImg[(int)EPlayerState::World].resize(1);
	playerImg[(int)EPlayerState::World][0].Load(L"../Resource/Image/Cuphead/CupHead_Word01.png");

	TCHAR path[128] = L"../Resource/Image/Cuphead/cuphead_idle_000";
	ParsingToImagePath(EPlayerState::Idle, PLAYER_IDEL_SIZE, path, 1);

	currAnimMax = playerImg[(int)EPlayerState::World].size();
	currAnimCnt = 0;
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
			MessageBox(NULL, _T("플레이어 이미지 파일을 열 수 없습니다."), _T("에러"), MB_OK);
		}
	}
}

Player::Player()
{
	worldState = EPlayerWorldState::Idle;
	state = EPlayerState::World;
	CreateImage();
	collider.left = 0;
	collider.top = 0;
	collider.right = 0;
	collider.bottom = 0;
	inWorld = true;
	camera_x = WORLD_START_POINT_X;
	camera_y = WORLD_START_POINT_Y;
}

Player::Player(int x, int y)
{
	worldState = EPlayerWorldState::Idle;
	state = EPlayerState::World;
	CreateImage();
	collider.left = 0;
	collider.top = 0;
	collider.right = 0;
	collider.bottom = 0;
	this->x = x; 
	this->y = y;
	inWorld = true;
	camera_x = WORLD_START_POINT_X;
	camera_y = WORLD_START_POINT_Y;
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
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	// 월드가 아니라면
	if (!inWorld)
	{
		currAnimMax = playerImg[(int)state].size();
		currAnimCnt++;
		if (currAnimCnt >= currAnimMax)
		{
			currAnimCnt = 0;
		}

		// x, y를 피벗으로 두면 바닥 가운데로 해야 함
		collider.left = x - playerImg[(int)state][currAnimCnt].GetWidth() / 2;
		collider.top = y - playerImg[(int)state][currAnimCnt].GetHeight();
		collider.right = x + playerImg[(int)state][currAnimCnt].GetWidth() / 2;
		collider.bottom = y;

		playerImg[(int)state][currAnimCnt].Draw(hdc, collider.left, collider.top);
	}


	// 월드라면
	{
		bx = playerImg[(int)EPlayerState::World][0].GetWidth();
		by = playerImg[(int)EPlayerState::World][0].GetHeight();

		const int unitX = bx / (WORLD_SPRITE_SIZE_X);
		const int unitY = by / (WORLD_SPRITE_SIZE_Y * 2);

		// idle인 경우
		if (worldState == EPlayerWorldState::Idle)
		{
			currAnimMax = (int)EPlayerWorldState::Idle;
			currAnimCnt++;
			if (currAnimCnt >= currAnimMax)
			{
				currAnimCnt = 0;
			}
		}

		else
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
		}


		int animX = unitX * currAnimCnt;
		int animY = unitY * (int)worldSpriteY;
		if (dir.x == -1)
			animY = unitY * ((int)worldSpriteY + WORLD_SPRITE_SIZE_Y);

		collider.left	= x - unitX / 4;
		collider.top	= y - unitY / 5;
		collider.right	= x + unitX / 4;
		collider.bottom = y;

		playerImg[(int)EPlayerState::World][0].Draw(hdc, collider.left - unitX / 4 - camera_x, collider.top - unitY * 3 / 5 - camera_y, unitX, unitY, animX, animY, unitX, unitY);
	}
}

RECT* Player::GetCollider()
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

void Player::SetState(EPlayerWorldState state, EWorldSpriteY spriteY)
{
	this->worldState = state;
	this->worldSpriteY = spriteY;
}

void Player::SetState(EPlayerState state)
{
	this->state = state;
}

void Player::SetInWorld(bool isWorld)
{
	inWorld = isWorld;
}
