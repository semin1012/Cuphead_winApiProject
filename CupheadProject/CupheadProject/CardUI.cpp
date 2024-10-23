#include "CardUI.h"

CardUI::CardUI(int xPos)
{
	image.Load(L"../Resource/Image/UI/card.png");
	x = 125 + xPos * image.GetWidth() + xPos * 5;
	isActive = true;
	curYPos = 800;
	maxYPos = 748;
}

CardUI::~CardUI()
{

}

void CardUI::Draw(HDC& hdc)
{
	int dist = maxYPos - curYPos;
	image.Draw(hdc, x, maxYPos, image.GetWidth(), image.GetHeight());
}

void CardUI::FillPositionY()
{

}
