#include "Bullet.h"
#include <string>

Bullet::Bullet()
{
	speed = 35.0f;
	curAnimCnt = 0;
	curAnimMax = 0;
	camera_x = 0;
	camera_y = 0;
	spawnAnimCnt = 0;
	createTime = clock();
	animLastTime = clock();
	state = EBulletState::Loop;
	createPos = { 0, 0 };
	isActive = false;
	isCollided = false;
	CreateImage();
}

Bullet::Bullet(int x, int y, POINT dir) : x(x), y(y), dir(dir)
{
	speed = 35.0f;
	curAnimCnt = 0;
	curAnimMax = 0;
	spawnAnimCnt = 0;
	createTime = clock();
	animLastTime = clock();
	state = EBulletState::Loop;
	createPos = { 0, 0 };
	isActive = false;
	isSpecialAttack = false;
	isCollided = false;
	CreateImage();
}

Bullet::~Bullet()
{
	for (auto it = images.begin(); it != images.end(); it++)
	{
		for (auto img : *it)
			delete (img);
	}
	images.clear();
}

void Bullet::SetBullet(int x, int y, POINT dir, bool isSpecialAttack)
{
	this->x = x;
	this->y = y;
	this->dir = dir;
	createTime = clock();
	animLastTime = clock();
	createPos = { x, y };
	curAnimCnt = 0;
	state = EBulletState::Spawn;
	isActive = true;
	this->isSpecialAttack = isSpecialAttack;
}

void Bullet::Draw(HDC& hdc, Graphics& graphics)
{
	graphics.ResetTransform();

	clock_t curTime = clock();
	curAnimMax = images[(int)state].size();

	if (curTime - createTime > 1000)
	{
		curAnimCnt = 0;
		isActive = false;
		x = -10000;
		y = -10000;
		isCollided = false;
	}

	if (curTime - animLastTime > 33)
	{
		curAnimCnt++;

		if (state == EBulletState::Death || state == EBulletState::EX_Death)
		{
			if (curAnimCnt >= curAnimMax)
			{
				curAnimCnt = 0;
				isActive = false;
				x = -10000;
				y = -10000;
				isCollided = false;
			}
		}

		if (curAnimCnt >= images[(int)EBulletState::Spawn].size() && state == EBulletState::Spawn)
		{
			if (isSpecialAttack)
				state = EBulletState::EX_Loop;
			else state = EBulletState::Loop;
			curAnimCnt = 0;
			curAnimMax = images[(int)state].size();
		}

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

	Gdiplus::Matrix mat;
	static int rot = 0;
	switch (dir.y)
	{
	case -1:
		if (dir.x == 1) rot = -45;
		else if (dir.x == 0) rot = -90;
		else rot = 225;
		break;
	case 0:
		if (dir.x == 1) rot = 0;
		else if (dir.x == -1) rot = 180;
		break;
	case 1:
		if (dir.x == 1) rot = 45;
		else if (dir.x == 0) rot = 90;
		else rot = 135;
		
		break;
	}
	mat.RotateAt((rot % 360), Gdiplus::PointF(x, y));
	graphics.SetTransform(&mat);

	graphics.DrawImage(images[(int)state][curAnimCnt], collider.left, collider.top, width, height);

	if (state == EBulletState::Spawn)
	{
		if (isSpecialAttack)
			return;
		x = x + dir.x * 15;
		y = y + dir.y * 15;
	}
	else
	{
		x = x + dir.x * speed;
		y = y + dir.y * speed;
	}
}

bool Bullet::Collided(Collider* collider)
{
	if (this->collider.IsOverlaps(*collider))
	{
		if (isSpecialAttack)
			state = EBulletState::EX_Death;
		else state = EBulletState::Death;
		curAnimCnt = 0;
		dir.x = 0;
		dir.y = 0;
		isCollided = true;
		return true;
	}
	return false;
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
	_tcscpy(path, L"../Resource/Image/Bullet/EX_bullet_loop0");
	ParsingToImagePath(EBulletState::EX_Loop, 8, path, 1);
	_tcscpy(path, L"../Resource/Image/Bullet/EX_bullet_death0");
	ParsingToImagePath(EBulletState::EX_Death, 9, path, 1);
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

void Bullet::SetCameraPos(int x, int y)
{
	int deltaX = (camera_x - x);
	this->x -= deltaX;
	camera_x = x;
	int deltaY = (camera_y - y);
	this->y -= deltaY;
	camera_y = y;
}

Collider* Bullet::GetCollider()
{
	return &collider;
}
