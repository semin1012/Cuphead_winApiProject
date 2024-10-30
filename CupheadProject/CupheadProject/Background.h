#pragma once
#include "framework.h"
#include "Player.h"
#include "Tripper.h"
#include "Collider.h"	
#include "HitObject.h"
#include "ParryObject.h"

class Background
{
protected:
	RECT*					rectView;
	Tripper*				tripper;
	Tripper*				tutorialTripper;
	int						camera_x;
	int						camera_y;
	int						x;
	int						y;
	int						width;
	int						height;
	bool					debugMode;
	std::vector<Collider*>  colliders;
	HitObject*				hitObject;
	std::vector<ParryObject*> parryObjects;

public:
	Background();
	Background(RECT& rectView, int x, int y);
	virtual ~Background();

	virtual void	Draw(HDC& hdc, Graphics& graphics) = 0;
	virtual void	DrawTrippers(HDC& hdc, Graphics& graphics);
	virtual void	CreateImage() = 0;
	void			SetRectView(RECT& rectView);
	void			SetCameraPos(int x, int y);

	int				GetXPos();
	int				GetYPos();
	void			SetXPos(int x);
	void			SetYPos(int y);

	void			SetDebugMode(bool debugMode);

	virtual void	SaveMapInfo() = 0;
	virtual void	LoadMapInfo() = 0;
	virtual void	ClearMapInfo() = 0;

	int				GetWidth();
	int				GetHeight();
	void			SetWidth(int width);
	void			SetHeight(int height);
	HitObject*		GetHitObject()				{ return hitObject; }
	void			RemoveHitObject();

	bool			CheckCollidedHitObject(Player* player, int deltaX, int deltaY);

	void			SetColliders(std::vector<Collider*>* colliders);
	Tripper*		GetTripper()				{ return tripper; }
	Tripper*		GetTutorialTripper()		{ return tutorialTripper; }
	std::vector<Collider*>* GetColliders();
	std::vector<ParryObject*>* GetParryObjects() { return &parryObjects; }
};

