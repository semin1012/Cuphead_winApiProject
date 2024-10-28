#include "ParryObject.h"
#include <string>

ParryObject::ParryObject()
{
	x = 0;
	y = 0;
	camera_x = 0;
	camera_y = 0;
	curAnimMax = 0;
	curAnimCnt = 0;
	isActive = true;
	createTime = clock();
	animLastTime = clock();
	collider = { 0, 0, 0, 0 };
	isLoop = false;
	isHide = false;
	CreateImage();
}

ParryObject::ParryObject(int x, int y, bool isLoop) : ParryObject()
{
	this->x = x;
	this->y = y;
	this->isLoop = isLoop;
}

ParryObject::~ParryObject()
{
	for (auto it = images.begin(); it < images.end(); it++)
	{
		for (auto image : *it)
			delete image;
	}
	images.clear();
}

void ParryObject::SetCameraPos(int x, int y)
{
	int deltaX = (camera_x - x);
	this->x -= deltaX;
	camera_x = x;
	int deltaY = (camera_y - y);
	this->y -= deltaY;
	camera_y = y;
}

void ParryObject::Draw(HDC& hdc, Graphics& graphics)
{
	graphics.ResetTransform();
	clock_t curTime = clock();
	curAnimMax = images[(int)state].size();

	if (isHide)
	{
		if (curTime - hideTime > 3000)
			isHide = false;
		return;
	}

	if (!isLoop)
	{
		if (curTime - createTime > 4000)
			isActive = false;
	}

	if (curTime - animLastTime > 50)
	{
		curAnimCnt++;
		if (curAnimCnt >= curAnimMax)
		{
			curAnimCnt = 3;
			//isActive = false;
		}
		animLastTime = clock();
	}

	if (!isActive)
		return;

	int width = images[(int)state][curAnimCnt]->GetWidth();
	int height = images[(int)state][curAnimCnt]->GetHeight();
	collider.left = x - width / 2 + 10 + camera_x;
	collider.top = y - height / 2 + 30 + camera_y;
	collider.right = x + width / 2 - 10 + camera_x;
	collider.bottom = y + height / 2 - 30 + camera_y;
	graphics.DrawImage(images[(int)state][curAnimCnt], collider.left - 10, collider.top - 30, width, height);
}

bool ParryObject::Collided(Player* player)
{
	if (!isLoop)
	{
		if (collider.IsOverlaps(*player->GetCollider()))
			return true;
		return false;
	}
	Collider temp = collider;
	temp.left -= camera_x;
	temp.right -= camera_x;
	if (temp.IsOverlaps(*player->GetCollider()))
		return true;
	return false;
}

void ParryObject::CreateImage()
{
	images.resize(2);

	TCHAR path[128] = L"../Resource/Image/Parry/c_slime_question_mark_00";
	ParsingToImagePath(EParryType::QuestionMark, 7, path, 1);
	_tcscpy(path, L"../Resource/Image/Parry/cuphead_slap_spark_00");
	ParsingToImagePath(EParryType::Pop, 9, path, 1);

	state = EParryType::QuestionMark;
}

void ParryObject::ParsingToImagePath(EParryType state, int spriteSize, TCHAR* path, int startNum)
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

bool ParryObject::StartAnimation()
{
	clock_t curTime = clock();
	if (curTime - createTime > 700)
		return true;
	return false;
}

void ParryObject::SetCollider()
{
	collider.left = x + camera_x;
	collider.top = y - camera_y;
	collider.right = x + images[(int)state][curAnimCnt]->GetWidth() + camera_x;
	collider.bottom = y + images[(int)state][curAnimCnt]->GetHeight() - camera_y;
}

void ParryObject::SetHide()
{
	isHide = true;
	hideTime = clock();
}

void ParryObject::SetCamera(int x, int y)
{
	camera_x = x;
	camera_y = y;
}
