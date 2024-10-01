#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include "framework.h"
#include "WorldMap.h"
#include "Collider.h"

#define WINDOWS_WIDTH 1280
#define WINDOWS_HEIGHT 800
#define WORLD_START_POINT_X 0
#define WORLD_START_POINT_Y 0
#define TILE_SIZE 30

class GameManager
{
private:
	std::vector<Collider*>  worldMapCollisions;
	WorldMap*				worldMap;
	bool					debugMode;
	RECT					cameraView;
	int						camera_x;
	int						camera_y;
	LPPOINT					mouseDelta;


public:
	GameManager();
	~GameManager();

	void			Draw(HDC& hdc);
	void			SetCameraView();
	void			SetCameraPos(int x, int y);
	void			AddTile(HWND& hWnd, LPPOINT& mousePos);
	bool			CompairTilePos(Collider& collide);
	void			SetDebugMode();
	void			SaveWorldMapInfo();
	void			LoadWorldMapInfo();
	void			ClearWorldMapInfo();

	void			SetWorldMap(WorldMap* worldMap);

	int				GetCameraXPos();
	int				GetCameraYPos();

	// mouse event
	void			SetMouseDeltaPos(HWND& hWnd);
	void			DragAndMoveWorldMap(HWND& hWnd);
};

