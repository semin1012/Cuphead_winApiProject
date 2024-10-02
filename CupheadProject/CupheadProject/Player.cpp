#include "Player.h"
#include <string>
void Player::CreateImage()
{
	playerImg.resize((int)EPlayerState::Max);

	// Image Load
	TCHAR path[128] = L"../Resource/Image/Cuphead/cuphead_idle_000";
	ParsingToImagePath(EPlayerState::Idle, PLAYER_IDEL_SIZE, path, 1);

}

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
	CreateImage();
}

Player::Player(int x, int y)
{
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
