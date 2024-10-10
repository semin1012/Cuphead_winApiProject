#include "FireBall.h"

FireBall::FireBall(int x, int y, POINT dir) : x(x), y(y), dir(dir)
{
	speed = 1.0f;
	createTime = clock();
	curTime = clock();
}

FireBall::~FireBall()
{
}

void FireBall::Draw(HDC& hdc)
{

}

void FireBall::CreateImage()
{

}
