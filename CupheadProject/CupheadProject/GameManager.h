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
#define TILE_SIZE 30

class GameManager
{
private:
	std::vector<Collider*>  worldMapCollisions;
	Background*				background;
	Player*					player;
	bool					debugMode;
	RECT					cameraView;
	int						camera_x;
	int						camera_y;
	LPPOINT					mouseDelta;
	bool					bMouseDrag;
	RECT*					rectView;
	bool					inWorld;
	bool					isTitle;
	int						stage;


public:
	GameManager(RECT* rectView);
	~GameManager();

	void		Draw(HDC& hdc);
	void		SetCameraView();
	void		SetCameraPos(int x, int y);
	void		AddTile(HWND& hWnd, LPPOINT& mousePos);
	bool		CompairTilePos(Collider& collide);
	
	void		SetDebugMode();

	void		SaveWorldMapInfo();
	void		LoadWorldMapInfo();
	void		ClearWorldMapInfo();

	void		SetMouseDrageState(bool state);

	int			GetCameraXPos();
	int			GetCameraYPos();
	bool		GetMouseDragState();
	Player*		GetPlayer();
	Background* GetBackground();

	bool		GetIsWorld();
	void		SetInWorld(bool isWorld);
	bool		GetIsTitle();
	void		SetIsTitle(bool isTitle);

	void		SetStage(int stage);

	// mouse event
	void		SetMouseDeltaPos(HWND& hWnd);
	void		DragAndMoveWorldMap(HWND& hWnd);

	// World Map
	bool		CollidedPlayerWithWorldCollisions(int deltaX, int deltaY);
	bool		CollidedPlayer(Collider* collider, int deltaX, int deltaY);
};

