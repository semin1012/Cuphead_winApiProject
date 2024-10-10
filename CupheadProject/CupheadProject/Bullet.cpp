#include "Bullet.h"
#include <string>

Bullet::Bullet(int x, int y, POINT dir) : x(x), y(y), dir(dir)
{
	speed = 35.0f;
	curAnimCnt = 0;
	curAnimMax = 0;
	spawnAnimCnt = 0;
	createTime = clock();
	animLastTime = clock();
	state = EBulletState::Loop;
	isActive = true;
	CreateImage();
}

Bullet::~Bullet()
{
	for (auto it = images.begin(); it != images.end(); it++)
	{
		for (auto img : *it)
		{
			delete (img);
		}
	}

	images.clear();
}

void Bullet::Draw(HDC& hdc, Graphics& graphics)
{
	clock_t curTime = clock();
	curAnimMax = images[(int)state].size();

	if (curTime - createTime > 1000)
		isActive = false;

	if (curTime - animLastTime > 33)
	{
		curAnimCnt++;
		if (spawnAnimCnt >= 0)
			spawnAnimCnt++;

		if (curAnimCnt >= curAnimMax)
			curAnimCnt = 0;

		if (spawnAnimCnt >= images[(int)EBulletState::Spawn].size())
			spawnAnimCnt = -1;

		animLastTime = clock();
	}

	if (spawnAnimCnt != -1)
	{
		int spawnWidth = images[(int)EBulletState::Spawn][spawnAnimCnt]->GetWidth();
		int spawnHeight = images[(int)EBulletState::Spawn][spawnAnimCnt]->GetHeight();
		Collider spawnCollider = Collider(x - spawnWidth / 2, y - spawnHeight / 2, x + spawnWidth, y + spawnHeight / 2);
		graphics.DrawImage(images[(int)EBulletState::Spawn][spawnAnimCnt], spawnCollider.left, spawnCollider.top, spawnWidth, spawnHeight);
	}

	int width = images[(int)state][curAnimCnt]->GetWidth();
	int height = images[(int)state][curAnimCnt]->GetHeight();

	collider.left = x - width / 2;
	collider.top = y - height / 2;
	collider.right = x + width / 2;
	collider.bottom = y + height / 2;

	graphics.DrawImage(images[(int)state][curAnimCnt], collider.left, collider.top, width, height);

	x = x + dir.x * speed;
	y = y + dir.y * speed;
}

void Bullet::CreateImage()
{
	images.resize((int)EBulletState::Max);

	TCHAR path[128] = L"../Resource/Image/Bullet/cuphead_bullet_spawn0";
	ParsingToImagePath(EBulletState::Spawn, 4, path, 1);
	_tcscpy(path, L"../Resource/Image/Bullet/cuphead_bullet0");
	ParsingToImagePath(EBulletState::Loop, 8, path, 1);
	_tcscpy(path, L"../Resource/Image/Bullet/cuphead_bullet_death0");
	ParsingToImagePath(EBulletState::Death, 6, path, 1);
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
	}
}
