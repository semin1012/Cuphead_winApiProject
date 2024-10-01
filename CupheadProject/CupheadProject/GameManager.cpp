#include "GameManager.h"

GameManager::GameManager()
{
	debugMode = true;
	camera_x = WORLD_START_POINT_X;
	camera_y = WORLD_START_POINT_Y;
	SetCameraView();
}

GameManager::~GameManager()
{

	for (auto it = worldMapCollisions.begin(); it != worldMapCollisions.end(); it++)
	{
		delete (*it);
	}

	worldMapCollisions.clear();
	delete worldMap;
}

void GameManager::Draw(HDC& hdc)
{
	if (worldMap != nullptr)
		worldMap->Draw(hdc);

	if (debugMode == true)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HGDIOBJ hOldPen = SelectObject(hdc, hPen);

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		for (auto collider : worldMapCollisions)
		{
			if ( CompairTilePos(*collider))
				Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
		}

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(myBrush);
		DeleteObject(hPen);
	}
}

void GameManager::SetCameraView()
{
	cameraView.left = camera_x;
	cameraView.top = camera_y;
	cameraView.right = camera_x + WINDOWS_WIDTH;
	cameraView.bottom = camera_y + WINDOWS_HEIGHT;
}

void GameManager::SetCameraPos(int x, int y)
{
	camera_x = x;
	camera_y = y;

	if (worldMap != nullptr)
	{
		worldMap->x = -camera_x;
		worldMap->y = -camera_y;
	}

	SetCameraView();
}

void GameManager::AddTile(HWND& hWnd, LPPOINT& mousePos)
{
	GetCursorPos(mousePos);
	ScreenToClient(hWnd, mousePos);

	mousePos->x = (mousePos->x + camera_x ) / TILE_SIZE;
	mousePos->y = (mousePos->y + camera_y )/ TILE_SIZE;

	Collider* collider = new Collider( mousePos->x * TILE_SIZE, mousePos->y * TILE_SIZE, mousePos->x * TILE_SIZE + TILE_SIZE, mousePos->y * TILE_SIZE + TILE_SIZE);

	for (int i = 0; i < worldMapCollisions.size(); i++)
	{
		if (worldMapCollisions[i]->Compare(*collider))
		{
			worldMapCollisions.erase(worldMapCollisions.begin() + i);
			return;
		}
	}

	worldMapCollisions.push_back(collider);
	worldMapCollisions.erase(std::unique(worldMapCollisions.begin(), worldMapCollisions.end()), worldMapCollisions.end());
}

bool GameManager::CompairTilePos(Collider& collider)
{
	if (collider.left >= cameraView.right - TILE_SIZE) return false;
	if (collider.right <= cameraView.left + TILE_SIZE) return false;
	if (collider.top >= cameraView.bottom - TILE_SIZE) return false;
	if (collider.bottom <= cameraView.top + TILE_SIZE) return false;
	return true;
}

void GameManager::SetDebugMode()
{
	debugMode = !debugMode;
}

void GameManager::SaveWorldMapCollider()
{

}
