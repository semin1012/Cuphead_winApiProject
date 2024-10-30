#pragma once
#include "framework.h"
#include "Collider.h"
#define TRIPPER_X_POS 270
#define TRIPPER_Y_POS 970

enum class ETripperType
{
	Basic,
	Door,
	TutorialHouse,
	Max
};
class Tripper
{
	CImage				image;
	CImage				pressKeyImg;
	Collider			keyCollider;
	RECT*				rectView;
	ETripperType		type;

	int					x;
	int					y;
	int					camera_x;
	int					camera_y;
	int					deltaX;
	int					deltaY;

	int					width;
	int					height;
	bool				isCollidedPlayer;

	int					curAnimCnt;
	int					maxAnimCnt;
	clock_t				lastTime;

	int					stage;


public:
	Tripper();
	Tripper(RECT& rectView, int x, int y, ETripperType type = ETripperType::Basic);
	~Tripper();

	void		Draw(HDC& hdc, Graphics& graphics);
	void		CreateImage();
	void		SetRectView(RECT& rectView);

	bool		CollidedKey(Collider* collider, int deltaX, int deltaY);

	int			GetXPos();
	int			GetYPos();
	void		SetXPos(int x);
	void		SetYPos(int y);
	int			GetCameraX();
	int			GetCameraY();
	void		SetCameraX(int x);
	void		SetCameraY(int y);
	void		SetDeltaPos(int x, int y);

	int			GetWidth();
	int			GetHeight();
	void		SetWidth(int width);
	void		SetHeight(int height);
	ETripperType GetTripperType()				{ return type; }

	int			GetStage();
	void		SetStage(int stage);

	Collider*	GetKeyCollider();
	void		SetCollidedPlayer(bool collided);
	bool		GetCollidedPlayer();
};

