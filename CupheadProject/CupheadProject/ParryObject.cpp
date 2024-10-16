#include "ParryObject.h"
#include <string>

ParryObject::ParryObject()
{
	player = nullptr;
	x = 0;
	y = 0;
	curAnimMax = 0;
	curAnimCnt = 0;
	isActive = true;
	createTime = clock();
	animLastTime = clock();
	collider = { 0, 0, 0, 0 };
	CreateImage();
}

ParryObject::ParryObject(int x, int y, Player* player) : ParryObject()
{
	this->x = x;
	this->y = y;
	this->player = player;
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

void ParryObject::Draw(HDC& hdc, Graphics& graphics)
{
	graphics.ResetTransform();
	clock_t curTime = clock();
	curAnimMax = images.size();

	if (curTime - animLastTime > 20)
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

	collider.left = x - width / 2;
	collider.top = y - height / 2;
	collider.right = x + width / 2;
	collider.bottom = y + height / 2;

	graphics.DrawImage(images[(int)state][curAnimCnt], collider.left, collider.top, width, height);
}

void ParryObject::CreateImage()
{
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
