#include "HealthUI.h"

HealthUI::HealthUI()
{
	image.Load(L"../Resource/Image/UI/Health/Health.png");
	x = 35;
	y = 750;
	health = 3;
}

HealthUI::HealthUI(int health) : HealthUI()
{
	this->health = health;
}

HealthUI::~HealthUI()
{

}

void HealthUI::Draw(HDC& hdc)
{
	int unitX = image.GetWidth() / 6;
	int unitY = image.GetHeight() / 2;
	Rect rect = { x, y, unitX, unitY };

	int animX;
	if (health > 1)
		animX = unitX * (health + 2);
	else
		animX = unitX * health;

	image.Draw(hdc, x, y, unitX, unitY, animX, 0, unitX, unitY);
}

void HealthUI::SetHealth(int health)
{
	this->health = health;
}
