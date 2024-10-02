#include "GameManager.h"

GameManager::GameManager()
{
	debugMode = true;
	camera_x = WORLD_START_POINT_X;
	camera_y = WORLD_START_POINT_Y;
	SetCameraView();

	mouseDelta = new POINT;
	player = new Player();
}

GameManager::~GameManager()
{
	for (auto it = worldMapCollisions.begin(); it != worldMapCollisions.end(); it++)
	{
		delete (*it);
	}

	worldMapCollisions.clear();
	delete worldMap;
	delete mouseDelta;
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

void GameManager::SaveWorldMapInfo()
{
	std::ofstream ofs("../Resource/Save/Map/WorldMapCollider.txt", std::ios::out);
	if (ofs.fail())
	{
		MessageBox(NULL, _T("WorldMapCollider.txt 파일 열기 실패"), _T("에러"), MB_OK);
		return;
	}

	ofs << worldMapCollisions.size() << std::endl;
	for (auto collider : worldMapCollisions)
	{
		ofs << collider->left << " " << collider->top << " " << collider->right << " " << collider->bottom << std::endl;
	}

	MessageBox(NULL, _T("WorldMapCollider.txt 파일에 월드 맵의 정보를 저장했습니다."), _T("성공"), MB_OK);
	ofs.close();
}

void GameManager::LoadWorldMapInfo()
{
	int size;

	std::ifstream ifs("../Resource/Save/Map/WorldMapCollider.txt", std::ios::in);
	if (ifs.fail())
	{
		MessageBox(NULL, _T("WorldMapCollider.txt 파일 열기 실패"), _T("에러"), MB_OK);
		return;
	}

	if ( !ifs.eof() )
		ifs >> size;

	while (!ifs.eof())
	{
		Collider* collider = new Collider();
		ifs >> collider->left >> collider->top >> collider->right >> collider->bottom;

		worldMapCollisions.push_back(collider);
	}

	// MessageBox(NULL, _T("WorldMapCollider.txt 파일에 월드 맵의 정보를 가지고 왔습니다."), _T("성공"), MB_OK);
	ifs.close();
}

void GameManager::ClearWorldMapInfo()
{
	for (auto it = worldMapCollisions.begin(); it != worldMapCollisions.end(); it++)
	{
		delete (*it);
	}

	worldMapCollisions.clear();	
}

void GameManager::SetWorldMap(WorldMap* worldMap)
{
	this->worldMap = worldMap;
}

int GameManager::GetCameraXPos()
{
	return camera_x;
}

int GameManager::GetCameraYPos()
{
	return camera_y;
}

void GameManager::SetMouseDeltaPos(HWND& hWnd)
{
	GetCursorPos(mouseDelta);
	ScreenToClient(hWnd, mouseDelta);
}

void GameManager::DragAndMoveWorldMap(HWND& hWnd)
{
	int x, y;
	POINT temp;
	GetCursorPos(&temp);
	ScreenToClient(hWnd, &temp);
	x = mouseDelta->x - temp.x;
	y = mouseDelta->y - temp.y;
	SetCameraPos(camera_x + x, camera_y + y);
	mouseDelta->x = temp.x;
	mouseDelta->y = temp.y;
}
