#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>	
#include "framework.h"
#include "TitleMap.h"
#include "WorldMap.h"
#include "Collider.h"
#include "Player.h"
#include "StageMap.h"
#include "FadeEffect.h"
#include "Bullet.h"
#include "Boss.h"
#include "EffectObject.h"
#include "FrontImage.h"
#include "ParryObject.h"
#define TILE_SIZE 30

class GameManager
{
private:
	std::vector<EffectObject*>	effects;
	std::vector<ParryObject*>	parryObjects;
	std::vector<int>		xInputs;
	Background*				background;
	Player*					player;
	Boss*					boss;
	FrontImage*				frontImage;
	bool					debugMode;
	RECT					cameraView;
	int						camera_x;
	int						camera_y;
	LPPOINT					mouseDelta;
	bool					bMouseDrag;
	RECT*					rectView;
	bool					isWorld;
	bool					isTitle;
	bool					isStage;
	int						stage;


	FadeEffect*				fadeEffect;

	ULONG_PTR				g_GdipPlusToken;


public:
	GameManager(RECT* rectView);
	~GameManager();

	void		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void		Draw(HDC& hdc);
	void		Update();
	void		SetCameraView();
	void		SetCameraPos(int x, int y);
	void		AddTile(HWND& hWnd, LPPOINT& mousePos);
	bool		CompairTilePos(Collider& collide);
	
	void		SetDebugMode();

	void		SetMouseDrageState(bool state);

	int			GetCameraXPos();
	int			GetCameraYPos();
	bool		GetMouseDragState();
	Player*		GetPlayer();
	Background* GetBackground();

	bool		GetIsWorld();
	void		SetIsWorld(bool isWorld);
	bool		GetIsTitle();
	void		SetIsTitle(bool isTitle);
	bool		GetIsStage();
	void		SetIsStage(bool isStage);

	void		SetStage(int stage);

	// mouse event
	void		SetMouseDeltaPos(HWND& hWnd);
	void		DragAndMoveWorldMap(HWND& hWnd);

	// World Map
	bool		CollidedPlayerWithWorldCollisions(int deltaX, int deltaY);
	bool		CollidedPlayer(Collider* collider, int deltaX, int deltaY);

	// gdi+
	void Gdi_Init();
	void Gdi_Draw(HDC hdc);
	void Gdi_End();
};

