#include "GameManager.h"
#include <iostream>

GameManager::GameManager(RECT* rectView)
{
	debugMode = false;
	camera_x = WORLD_START_POINT_X;
	camera_y = WORLD_START_POINT_Y;
	
	SetCameraView();
	mouseDelta = new POINT;
	bMouseDrag = false;

	player = nullptr;

	background = new TitleMap();
	background->SetRectView(*rectView);
	isTitle = true;

	LoadWorldMapInfo();
	SetCameraPos(camera_x, camera_y);
}

GameManager::~GameManager()
{
	for (auto it = worldMapCollisions.begin(); it != worldMapCollisions.end(); it++)
	{
		delete (*it);
	}

	worldMapCollisions.clear();
	delete background;
	delete mouseDelta;
}

void GameManager::Draw(HDC& hdc)
{
	if (background != nullptr)
		background->Draw(hdc);

#pragma region Debug Mode
	if (debugMode == true)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HGDIOBJ hOldPen = SelectObject(hdc, hPen);

		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		for (auto collider : worldMapCollisions)
		{
			if (CompairTilePos(*collider))
				Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
		}

		if (player != nullptr)
		{
			Collider* collider = player->GetCollider();
			Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
		}

		if (background->GetTripper() != nullptr)
		{
			Collider* collider = background->GetTripper()->GetCollider();
			Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
			collider = background->GetTripper()->GetKeyCollider();
			Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
		}

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(myBrush);
		DeleteObject(hPen);
	}
#pragma endregion

 	if (player != nullptr)
		player->Draw(hdc);
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
	if (isTitle)
		return;

	static bool isMoveCameraY = true;
	static bool isMoveCameraX = true;

	int deltaX = (camera_x - x);
	int deltaY = (camera_y - y);

	if (background != nullptr)
	{
		if (isMoveCameraX)
			background->SetXPos(-camera_x);
		if (isMoveCameraY)
			background->SetYPos(-camera_y);
	}

	if (CollidedPlayerWithWorldCollisions(deltaX, deltaY))
		return;

	if (background->GetTripper() != nullptr)
	{
		if (CollidedPlayer(background->GetTripper()->GetKeyCollider(), deltaX, deltaY))
			background->GetTripper()->SetCollidedPlayer(true);
		else 
			background->GetTripper()->SetCollidedPlayer(false);
		if (CollidedPlayer(background->GetTripper()->GetCollider(), deltaX, deltaY))
			return;
	}

	int mapSizeWidth = background->GetWidth();
	int mapSizeHeight = background->GetHeight();

	// check player camera 
	// x
	if (isMoveCameraX && camera_x < MOVE_DISTANCE)
	{
		isMoveCameraX = false;
		camera_x = 0;
	}
	if (isMoveCameraX && camera_x + WINDOWS_WIDTH >= mapSizeWidth)
	{
		isMoveCameraX = false;
		camera_x = mapSizeWidth - WINDOWS_WIDTH;
	}
	if (!isMoveCameraX && player->GetXPos() > WINDOWS_WIDTH / 2 + MOVE_DISTANCE && camera_x <= 100 )
	{
		camera_x = 0;
		isMoveCameraX = true;
		player->SetXPos(WINDOWS_WIDTH / 2 + MOVE_DISTANCE);
	}
	if (!isMoveCameraX && player->GetXPos() < mapSizeWidth - WINDOWS_WIDTH / 2 && camera_x >= 1000)
	{
		camera_x = mapSizeWidth - WINDOWS_WIDTH / 2;
		isMoveCameraX = true;
		player->SetXPos(mapSizeWidth - WINDOWS_WIDTH / 2);
	}
	// y
	if (isMoveCameraY && camera_y < MOVE_DISTANCE * 2)
	{
		isMoveCameraY = false;
		camera_y = MOVE_DISTANCE * 2;
	}
	if (isMoveCameraY && camera_y + WINDOWS_HEIGHT >= mapSizeHeight)
	{
		isMoveCameraY = false;
		camera_y = mapSizeHeight - WINDOWS_HEIGHT;
	}
	if (!isMoveCameraY && player->GetYPos() > 405&& camera_y <= 50)
	{
		camera_y = 0;
		isMoveCameraY = true;
		player->SetYPos(405);
	}
	if (!isMoveCameraY && player->GetYPos() < mapSizeHeight - WINDOWS_HEIGHT / 2 && camera_y >= 800)
	{
		camera_y = 1275;
		isMoveCameraY = true;
		player->SetYPos(1670);
	}

	if (isMoveCameraX)
		camera_x = x;
	if (isMoveCameraY)
		camera_y = y;

	SetCameraView();
	if (player != nullptr)
	{
		if (isMoveCameraX && isMoveCameraY)
		{
			player->SetCameraPosY(camera_y + deltaY);
			player->SetCameraPosX(camera_x + deltaY);
			return;
		}
		if (!isMoveCameraX && !isMoveCameraY)
		{
			player->Move(deltaX, deltaY);
			player->SetCameraPos(camera_x + deltaY, camera_y + deltaY);
			return;
		}
		if (isMoveCameraX)
		{
			player->Move(0, deltaY);
			player->SetCameraPosX(camera_x + deltaY);
		}
		if (isMoveCameraY)
		{
			player->Move(deltaX, 0);
			player->SetCameraPosY(camera_y + deltaY);
		}
	}
}

void GameManager::AddTile(HWND& hWnd, LPPOINT& mousePos)
{
	if (debugMode)
	{
		GetCursorPos(mousePos);
		ScreenToClient(hWnd, mousePos);

		mousePos->x = (mousePos->x + camera_x) / TILE_SIZE;
		mousePos->y = (mousePos->y + camera_y) / TILE_SIZE;

		Collider* collider = new Collider(mousePos->x * TILE_SIZE, mousePos->y * TILE_SIZE, mousePos->x * TILE_SIZE + TILE_SIZE, mousePos->y * TILE_SIZE + TILE_SIZE);

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
	background->SetDebugMode(debugMode);
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

void GameManager::SetMouseDrageState(bool state)
{
	bMouseDrag = state;
}

int GameManager::GetCameraXPos()
{
	return camera_x;
}

int GameManager::GetCameraYPos()
{
	return camera_y;
}

bool GameManager::GetMouseDragState()
{
	return bMouseDrag;
}

Player* GameManager::GetPlayer()
{
	return player;
}

bool GameManager::GetIsWorld()
{
	return inWorld;
}

void GameManager::SetInWorld(bool isWorld)
{
	inWorld = isWorld;
	player->SetInWorld(isWorld);
}

bool GameManager::GetIsTitle()
{
	return isTitle;
}

void GameManager::SetIsTitle(bool isTitle)
{
	this->isTitle = isTitle;
	if (isTitle == false)
	{
		inWorld = true;
		delete background;

		background = new WorldMap();
		background->SetRectView(*rectView);
		player = new Player(WORLD_START_POINT_X + WINDOWS_WIDTH / 2, WORLD_START_POINT_Y + WINDOWS_HEIGHT / 2);
	}
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

bool GameManager::CollidedPlayerWithWorldCollisions(int deltaX, int deltaY)
{
	Collider temp = *player->GetCollider();
	temp.left -= deltaX - 1;
	temp.right -= deltaX + 1;
	temp.top -= deltaY - 1;
	temp.bottom -= deltaY + 1;

	for (auto collider : worldMapCollisions)
	{
		if (temp.IsOverlaps(*collider))
			return true;
	}
	return false;
}

bool GameManager::CollidedPlayer(Collider* collider, int deltaX, int deltaY)
{
	Collider temp = *player->GetCollider();
	temp.left	-= deltaX - 1;
	temp.right	-= deltaX + 1;
	temp.top	-= deltaY - 1;
	temp.bottom -= deltaY + 1;

	if (temp.IsOverlaps(*collider))
		return true;

	return false;
}
