#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include "framework.h"
#include "WorldMap.h"
#include "Collider.h"
#include "Player.h"

#define WINDOWS_WIDTH 1280
#define WINDOWS_HEIGHT 800
#define TILE_SIZE 30

class GameManager
{
private:
	std::vector<Collider*>  worldMapCollisions;
	WorldMap*				worldMap;
	Player*					player;
	bool					debugMode;
	RECT					cameraView;
	int						camera_x;
	int						camera_y;
	LPPOINT					mouseDelta;
	bool					bMouseDrag;
	RECT*					rectView;


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


	// mouse event
	void		SetMouseDeltaPos(HWND& hWnd);
	void		DragAndMoveWorldMap(HWND& hWnd);
};

