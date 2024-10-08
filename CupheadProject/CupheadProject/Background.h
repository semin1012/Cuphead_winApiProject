#pragma once
#include "framework.h"
#include "Player.h"
#include "Tripper.h"
#include "Collider.h"	

class Background
{
protected:
	RECT*					rectView;
	Tripper*				tripper;
	int						x;
	int						y;
	int						width;
	int						height;
	bool					debugMode;
	std::vector<Collider*>  colliders;

public:
	Background();
	Background(RECT& rectView, int x, int y);
	virtual ~Background();

	virtual void	Draw(HDC& hdc) = 0;
	virtual void	CreateImage() = 0;
	void			SetRectView(RECT& rectView);

	int			GetXPos();
	int			GetYPos();
	void		SetXPos(int x);
	void		SetYPos(int y);

	void		SetDebugMode(bool debugMode);

	virtual void	SaveMapInfo() = 0;
	virtual void	LoadMapInfo() = 0;
	virtual void	ClearMapInfo() = 0;

	void		SetColliders(std::vector<Collider*> *colliders);
	std::vector<Collider*>* GetColliders();

	int			GetWidth();
	int			GetHeight();
	void		SetWidth(int width);
	void		SetHeight(int height);
	Tripper*	GetTripper();
};

