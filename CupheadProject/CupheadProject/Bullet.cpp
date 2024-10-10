#include "Bullet.h"
#include <string>

Bullet::Bullet(int x, int y, POINT dir) : x(x), y(y), dir(dir)
{
	speed = 1.0f;
	curAnimCnt = 0;
	curAnimMax = 0;
	createTime = clock();
	animLastTime = clock();
	state = EBulletState::Spawn;
	CreateImage();
}

Bullet::~Bullet()
{
}

void Bullet::Draw(HDC& hdc, Graphics& graphics)
{
	clock_t curTime = clock();
	curAnimMax = images[(int)state].size();

	if (curTime - animLastTime > 33)
	{
		curAnimCnt++;

		if (curAnimCnt >= curAnimMax)
			curAnimCnt = 0;

		animLastTime = clock();
	}

	int width = images[(int)state][curAnimCnt]->GetWidth();
	int height = images[(int)state][curAnimCnt]->GetHeight();

	collider.left = x - width / 2;
	collider.top = y - height / 2;
	collider.right = x + width / 2;
	collider.bottom = y + height / 2;

	graphics.DrawImage(images[(int)state][curAnimCnt], collider.left, collider.top, width, height);
	/*images[(int)state][curAnimCnt]->DrawImage();

	images[(int)state][curAnimCnt].TransparentBlt(hdc, collider.left, collider.top, width, height, RGB(255,255,255));
	images[(int)state][curAnimCnt].Draw(hdc, collider.left, collider.top);*/
}

void Bullet::CreateImage()
{
	images.resize((int)EBulletState::Max);

	TCHAR path[128] = L"../Resource/Image/Bullet/cuphead_bullet_spawn0";
	ParsingToImagePath(EBulletState::Spawn, 4, path, 1);
}

void Bullet::ParsingToImagePath(EBulletState state, int spriteSize, TCHAR* path, int startNum)
{
	images[(int)state].resize(spriteSize);

	for (int i = 0, j = startNum; i < spriteSize; i++, j++)
	{
		TCHAR temp[128];
		_tcscpy(temp, path);

		wchar_t num[3];
		_tcscpy(num, std::to_wstring(j).c_str());
		_tcscat(temp, num);
		_tcscat(temp, L".png");

		Image* pImg = new Image(temp);
		images[(int)state][i] = pImg;

		/*if (images[(int)state][i] == NULL)
		{
			DWORD dwError = GetLastError();
			_tcscat(temp, L" 파일을 열 수 없습니다.");
			MessageBox(NULL, temp, _T("에러"), MB_OK);
		}*/
	}
}
