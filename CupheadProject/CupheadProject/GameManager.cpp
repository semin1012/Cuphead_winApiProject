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
	boss = nullptr;

	background = new TitleMap();
	background->SetRectView(*rectView);
	isTitle = true;
	isWorld = false;
	isStage = false;
	fadeEffect = nullptr;
	frontImage = nullptr;

	SetCameraPos(camera_x, camera_y);
}

GameManager::~GameManager()
{
	delete background;
	delete mouseDelta;
}

void GameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (GetIsTitle())
		{
			if (wParam == VK_SPACE && fadeEffect == nullptr)
				fadeEffect = new FadeEffect();
			break;
		}
		if (!player->GetCanInput() || player->GetIsHit())
			break;
		if (!GetIsWorld() && !GetIsTitle())
		{
			switch (wParam)
			{
			case 'Z':
			case 'z':
				if (!player->GetIsJumping() && !player->GetIsDashing() && !player->GetIsSpecialAttack())
					player->SetIsJumping(true);
				break;
			case VK_SHIFT:
				if (!player->GetIsDashing() && player->dir.x != 0 && !player->GetIsSpecialAttack())
					player->SetIsDashing(true);
				break;
			case VK_DOWN:
				if (!player->GetIsDown() && !player->GetIsLockin() && !player->GetIsSpecialAttack())
				{
					if (player->GetIsShooting())
						player->SetIsShooting(false);
					player->SetIsDown(true);
				}
				break;
			case 'X':
			case 'x':
				if (!player->GetIsShooting() && !player->GetIsJumping() && !player->GetIsDashing() && !player->GetIsSpecialAttack())
				{
					player->SetIsShooting(true);
				}
				break;
			case 'C':
			case 'c':
				if (!player->GetIsLockin() && !player->GetIsSpecialAttack())
					player->SetIsLockin(true);
				break;
			case 'v':
			case 'V':
				if (!player->GetIsSpecialAttack())
					player->SetIsSpecialAttack(true);
				break;
			}
		}
		break;
	case WM_KEYUP:
		if (isTitle)
			break;
		if (GetIsStage())
		{
			if (wParam == VK_DOWN && player->GetIsDown())
				player->SetIsDown(false);
		}
		if (!player->GetCanInput())
			break;
		switch (wParam)
		{
		case VK_LEFT:
			if (GetPlayer()->dir.x == -1)
			{
				GetPlayer()->dir.x = 0;
				GetPlayer()->SetLastForward(LAST_FORWARD_IS_LEFT);
			}
			break;
		case VK_RIGHT:
			if (GetPlayer()->dir.x == 1)
			{
				GetPlayer()->dir.x = 0;
				GetPlayer()->SetLastForward(LAST_FORWARD_IS_RIGHT);
			}
			break;
		case 'a':
		case 'A':
			if (isWorld && fadeEffect == nullptr)
			{
				Tripper *tripper = GetBackground()->GetTripper();
				if (tripper->GetCollidedPlayer())
					fadeEffect = new FadeEffect();
			}
			break;
		case 'X':
		case 'x':
			if (player->GetIsShooting())
				player->SetIsShooting(false);
			break;
		case 'C':
		case 'c':
			if (player->GetIsLockin())
				player->SetIsLockin(false);
		}
		break;
	}
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

		for (auto collider : *background->GetColliders())
		{
			if (CompairTilePos(*collider))
				Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
		}

		if (player != nullptr)
		{
			Collider* collider;
			if (!player->GetBullets().empty())
			{
				for (auto bullet : player->GetBullets())
				{
					if (!bullet->GetisActive()) continue;
					collider = bullet->GetCollider();
					Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
				}
			}
			collider = player->GetCollider();
			Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
		}

		if (background->GetTripper() != nullptr)
		{
			Collider* collider = background->GetTripper()->GetKeyCollider();
			Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
		} 

		if (boss != nullptr)
		{
			Collider* collider = boss->GetCollider();
			Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
		}

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(myBrush);
		DeleteObject(hPen);
	}
#pragma endregion

	Gdi_Draw(hdc);


#pragma region Fade Effect
	static bool effectOut = false;

	if (fadeEffect != nullptr)
	{
		fadeEffect->Draw(hdc);
		if (fadeEffect->GetIsFadeIn() && !effectOut)
		{
			if (GetIsTitle())
				SetIsTitle(false);
			else if (!GetIsTitle() && GetIsWorld() && !GetIsStage())
				SetStage(background->GetTripper()->GetStage());
			effectOut = true;
		}
		if (fadeEffect->GetIsEnd())
		{
			delete fadeEffect;
			fadeEffect = nullptr;
			effectOut = false;
		}
	}
#pragma endregion
}

void GameManager::Update()
{
	if (frontImage != nullptr)
	{
		if (frontImage->GetIsActive() == false)
		{
			delete frontImage;
			frontImage = nullptr;
		}
	}

	if (player != nullptr)
	{
		player->Update();
		if (player->GetJumpDust())
		{
			player->SetJumpDust(false);
			effects.push_back(new EffectObject(EEffectType::JumpDownDust, player->GetXPos(), player->GetYPos()));
		}

		if (boss != nullptr)
		{
			boss->Update();

			for (auto bullet : player->GetBullets())
			{
				if (bullet->GetisActive() && !bullet->GetIsCollided())
				{
					if (bullet->Collided(boss->GetCollider()))
						boss->Hit(bullet);
				}
			}

			if (!player->GetIsGraceTime() && player->GetCanInput())
				player->Collided(boss->GetCollider());
		}
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
	if (isTitle)
		return;

	static bool isMoveCameraY = true;
	static bool isMoveCameraX = true;

	if (!GetIsWorld())
	{
		isMoveCameraX = false;
		isMoveCameraY = false;
	}

	int deltaX = (camera_x - x);
	int deltaY = (camera_y - y);

	if (background != nullptr)
	{
		if (isMoveCameraX)
			background->SetXPos(-camera_x);
		if (isMoveCameraY)
			background->SetYPos(-camera_y);
	}

	int mapSizeWidth = background->GetWidth();
	int mapSizeHeight = background->GetHeight();

	if (CollidedPlayerWithWorldCollisions(deltaX, deltaY))
		return;

	if (GetIsWorld())
	{
		if (background->GetTripper() != nullptr)
		{
			if (background->GetTripper()->CollidedKey(player->GetCollider(), deltaX, deltaY))
				background->GetTripper()->SetCollidedPlayer(true);
			else background->GetTripper()->SetCollidedPlayer(false);

		}
#pragma region Check player camera

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
		if (!isMoveCameraX && player->GetXPos() >= WINDOWS_WIDTH / 2 + MOVE_DISTANCE && camera_x <= 100)
		{
			camera_x = 0;
			isMoveCameraX = true;
			player->SetXPos(WINDOWS_WIDTH / 2 + MOVE_DISTANCE);
		}
		if (!isMoveCameraX && player->GetXPos() <= mapSizeWidth - WINDOWS_WIDTH / 2 && camera_x >= 1000)
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
		if (!isMoveCameraY && player->GetYPos() >= 405 && camera_y <= 50)
		{
			camera_y = 0;
			isMoveCameraY = true;
			player->SetYPos(405);
		}
		if (!isMoveCameraY && player->GetYPos() <= mapSizeHeight - WINDOWS_HEIGHT / 2 && camera_y >= 800)
		{
			camera_y = 1275;
			isMoveCameraY = true;
			player->SetYPos(1670);
		}
#pragma endregion
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
			float speed = player->GetSpeed();
			player->Move(deltaX * speed, deltaY * speed);
			player->SetCameraPos(camera_x + deltaY * speed, camera_y + deltaY * speed);
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

		for (int i = 0; i < background->GetColliders()->size(); i++)
		{
			if ((*background->GetColliders())[i]->Compare(*collider))
			{
				(*background->GetColliders()).erase((*background->GetColliders()).begin() + i);
				return;
			}
		}

		(*background->GetColliders()).push_back(collider);
		(*background->GetColliders()).erase(std::unique((*background->GetColliders()).begin(), (*background->GetColliders()).end()), (*background->GetColliders()).end());
	}
}

bool GameManager::CompairTilePos(Collider& collider)
{
	if (collider.left >= cameraView.right ) return false;  //- TILE_SIZE) return false;
	if (collider.right <= cameraView.left ) return false;  //+ TILE_SIZE) return false;
	if (collider.top >= cameraView.bottom ) return false;  //- TILE_SIZE) return false;
	if (collider.bottom <= cameraView.top ) return false;  //+ TILE_SIZE) return false;
	return true;
}

void GameManager::SetDebugMode()
{
	debugMode = !debugMode;
	background->SetDebugMode(debugMode);
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

Background* GameManager::GetBackground()
{
	return background;
}

bool GameManager::GetIsWorld()
{
	return isWorld;
}

void GameManager::SetIsWorld(bool isWorld)
{
	isWorld = isWorld;
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
		isWorld = true;
		delete background;

		background = new WorldMap();
		background->SetRectView(*rectView);
		player = new Player(WORLD_START_POINT_X + WINDOWS_WIDTH / 2, WORLD_START_POINT_Y + WINDOWS_HEIGHT / 2);

		// TODO:
		SetStage(1);
	}
}

bool GameManager::GetIsStage()
{
	return isStage;
}

void GameManager::SetIsStage(bool isStage)
{
	this->isStage = isStage;
}

void GameManager::SetStage(int stage)
{
	isWorld = false;
	isStage = true;
	stage = 1;
	delete background;

	background = new StageMap();
	background->SetRectView(*rectView);

	camera_x = 0;
	camera_y = 0;
	SetCameraPos(0, 0);

	player->SetStage();
	boss = new Boss();
	boss->SetPlayer(player);

	frontImage = new FrontImage();
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

	for (auto collider : (*background->GetColliders()))
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

void GameManager::Gdi_Init()
{
	GdiplusStartupInput gpsi;

	GdiplusStartup(&g_GdipPlusToken, &gpsi, NULL);
}

void GameManager::Gdi_Draw(HDC hdc)
{
	Graphics graphics(hdc);

	if (boss != nullptr)
	{
		boss->Draw(hdc, graphics);
	}


	if (player != nullptr)
	{
		player->Draw(hdc, graphics);

		for (auto bullet : player->GetBullets())
		{
			if (bullet->GetisActive())
				bullet->Draw(hdc, graphics);
		}
	}

	if (!effects.empty())
	{
		for (auto it = effects.begin(); it != effects.end(); )
		{
			EffectObject *effect = (*it);

			if (!effect->GetisActive())
				it = effects.erase(it);
			else
			{
				effect->Draw(hdc, graphics);
				it++;
			}
		}
	}

	if (frontImage != nullptr)
	{
		frontImage->Draw(hdc, graphics);
	}
}

void GameManager::Gdi_End()
{
	GdiplusShutdown(g_GdipPlusToken);
}
