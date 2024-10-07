#include "Background.h"

Background::Background()
{
    rectView = nullptr;
    x = 0;
    y = 0;
    width = 0;
    height = 0;
}

Background::Background(RECT& rectView, int x, int y)
{
    this->rectView = &rectView;
    this->x = x;
    this->y = y;
    width = 0;
    height = 0;
}

Background::~Background()
{
}

void Background::SetRectView(RECT& rectView)
{
    this->rectView = &rectView;
}

int Background::GetXPos()
{
    return x;
}

int Background::GetYPos()
{
    return y;
}

void Background::SetXPos(int x)
{
    this->x = x;
}

void Background::SetYPos(int y)
{
    this->y = y;
}

int Background::GetWidth()
{
    return width;
}

int Background::GetHeight()
{
    return height;
}

void Background::SetWidth(int width)
{
    this->width = width;
}

void Background::SetHeight(int height)
{
    this->height = height;
}
