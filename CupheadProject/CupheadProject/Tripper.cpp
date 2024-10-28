#include "Tripper.h"
#include <string>

Tripper::Tripper()
{
	x = 0;
	y = 0;
	height = 0;
	width = 0;
	rectView = nullptr;
	isCollidedPlayer = false;
	curAnimCnt = 0;
	maxAnimCnt = 3;
	lastTime = clock();
	camera_x = 0;
	camera_y = 0;
	deltaX = 0;
	deltaY = 0;
	stage = 0;
	doorImage = nullptr;
	type = ETripperType::Basic;
}

Tripper::Tripper(RECT& rectView, int x, int y, ETripperType type) : Tripper()
{
	this->x = x;
	this->y = y;
	this->rectView = &rectView;
	this->type = type;
	CreateImage();
}

Tripper::~Tripper()
{
	delete doorImage;
}

void Tripper::Draw(HDC& hdc, Graphics& graphics)
{
	keyCollider.left = x + 45 - 60;
	keyCollider.right = x - 45 + width + 60;
	keyCollider.top = y + 45 - 60;
	keyCollider.bottom = y - 45 + height + 60;

	if (isCollidedPlayer)
		pressKeyImg.Draw(hdc, WINDOWS_WIDTH / 2 - pressKeyImg.GetWidth() / 2, 100, pressKeyImg.GetWidth(), pressKeyImg.GetHeight());

	if (type == ETripperType::Door)
	{
		keyCollider.left += camera_x;
		keyCollider.right += camera_x;
		graphics.DrawImage(doorImage, Rect(x + camera_x, y + camera_y, doorImage->GetWidth(), doorImage->GetHeight()));
		return;
	}
	
	clock_t curTime = clock();
	if (curTime - lastTime > 50)
	{
		curAnimCnt++;
		if (curAnimCnt >= maxAnimCnt)
			curAnimCnt = 0;
		lastTime = clock();
	}
	int unitX = width;
	int unitY = height;	
	int animX = unitX * curAnimCnt;
	image.Draw(hdc, x + camera_x, y + camera_y, unitX, unitY, animX, 0, unitX, unitY);
}

void Tripper::CreateImage()
{
	pressKeyImg.Load(L"../Resource/Image/Ect/press_key_a.png");
	image.Load(L"../Resource/Image/Background/World/botanic_panic.png");
	doorImage = new Image(L"../Resource/Image/Background/Tutorial/door.png");
	switch (type)
	{
	case ETripperType::Basic:
		width = image.GetWidth() / 3;
		maxAnimCnt = 3;
		break;
	case ETripperType::Door:
		width = doorImage->GetWidth();
		maxAnimCnt = 1;
		break;
	}
	height = image.GetHeight();
}

void Tripper::SetRectView(RECT& rectView)
{
	this->rectView = &rectView;
}

bool Tripper::CollidedKey(Collider* collider, int deltaX, int deltaY)
{
	Collider temp = *collider;
	temp.left -= deltaX - 1;
	temp.right -= deltaX + 1;
	temp.top -= deltaY - 1;
	temp.bottom -= deltaY + 1;

	if (temp.IsOverlaps(this->keyCollider))
		return true;

	return false;
}

int Tripper::GetXPos()
{
	return x;
}

int Tripper::GetYPos()
{
	return y;
}

void Tripper::SetXPos(int x)
{
	this->x = x;
}

void Tripper::SetYPos(int y)
{
	this->y = y;
}

int Tripper::GetCameraX()
{
	return camera_x;
}

int Tripper::GetCameraY()
{
	return camera_y;
}

void Tripper::SetCameraX(int x)
{
	camera_x = x;
}

void Tripper::SetCameraY(int y)
{
	camera_y = y;
}

void Tripper::SetDeltaPos(int x, int y)
{
	deltaX = x;
	deltaY = y;
}

int Tripper::GetWidth()
{
	return width;
}

int Tripper::GetHeight()
{
	return height;
}

void Tripper::SetWidth(int width)
{
	this->width = width;	
}

void Tripper::SetHeight(int height)
{
	this->height = height;
}

int Tripper::GetStage()
{
	return stage;
}

void Tripper::SetStage(int stage)
{
	this->stage = stage;
}

Collider* Tripper::GetKeyCollider()
{
	return &keyCollider;
}

void Tripper::SetCollidedPlayer(bool collided)
{
	isCollidedPlayer = collided;
}

bool Tripper::GetCollidedPlayer()
{
	return isCollidedPlayer;
}
