#include "HealthUI.h"

HealthUI::HealthUI()
{
	Image* pImg = new Image(L"../Resource/Image/UI/Health/Health.png");
	image = pImg;
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
	delete image;
}

void HealthUI::Draw(Graphics& graphics)
{
	graphics.ResetTransform();

	int unitX = image->GetWidth() / 6;
	int unitY = image->GetHeight() / 2;
	Rect rect = { x, y, unitX, unitY };

	int animX;
	if (health > 1)
		animX = unitX * (health + 2);
	else
		animX = unitX * health;

	graphics.DrawImage(image, rect, animX, 0, unitX, unitY, Gdiplus::Unit::UnitPixel);
}

void HealthUI::SetHealth(int health)
{
	this->health = health;
}
