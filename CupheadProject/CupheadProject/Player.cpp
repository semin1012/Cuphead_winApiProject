#include "Player.h"
#include <string>
using namespace std;

void Player::CreateImage()
{
	playerImg.resize((int)EPlayerState::Max);

	// Image Load
	TCHAR path[128] = L"../Resource/Image/Cuphead/cuphead_idle_000";
	ParsingToImagePath(EPlayerState::Idle, PLAYER_IDEL_SIZE, path, 1);

	currAnimCnt = 0;
	currAnimMax = playerImg[(int)EPlayerState::Idle].size();
}

// path�� startNum���� startNum + spriteSize������ ���ڸ� �߰��ؼ� Load�ϴ� �Լ�, �⺻�� png ������
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
			MessageBox(NULL, _T("�÷��̾� �̹��� ������ �� �� �����ϴ�."), _T("����"), MB_OK);
		}
	}
}

Player::Player()
{
	state = EPlayerState::Idle;
	CreateImage();
	collider.left = 0;
	collider.top = 0;
	collider.right = 0;
	collider.bottom = 0;
}

Player::Player(int x, int y)
{
	state = EPlayerState::Idle;
	CreateImage();
	collider.left = 0;
	collider.top = 0;
	collider.right = 0;
	collider.bottom = 0;
	this->x = x; 
	this->y = y;
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

	currAnimMax = playerImg[(int)state].size();
	currAnimCnt++;
	if (currAnimCnt >= currAnimMax)
	{
		currAnimCnt = 0;
	}
	
	// x, y�� �ǹ����� �θ� �ٴ� ����� �ؾ� ��
	collider.left = x - playerImg[(int)state][currAnimCnt].GetWidth() / 2;
	collider.top = y - playerImg[(int)state][currAnimCnt].GetHeight();
	collider.right = x + playerImg[(int)state][currAnimCnt].GetWidth() / 2;
	collider.bottom = y;

	int pos_y = collider.top + 200;

	playerImg[(int)state][currAnimCnt].Draw(hdc, collider.left, collider.top);
}

RECT* Player::GetCollider()
{
	return &collider;
}
