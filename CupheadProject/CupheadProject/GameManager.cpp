#include "GameManager.h"
#include <iostream>
#include <algorithm>

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
	health = nullptr;

	background = new TitleMap();
	background->SetRectView(*rectView);
	sceneState = (int)ESceneState::Title;
	fadeEffect = nullptr;
	playingCameraShake = false;
	shakeX = 0;
	shakeY = 0;
	isMoveCameraY = true;
	isMoveCameraX = true;

	SetCameraPos(camera_x, camera_y);
	frontImages.push_back(new FrontImage(EFrontImage::FX));
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
		if (sceneState == (int)ESceneState::Clear)
		{
			if (wParam == 'R' || wParam == 'r')
			{
				if (fadeEffect == nullptr)
				{
					sceneState = (int)ESceneState::Restart;
					fadeEffect = new FadeEffect();
				}
			}
			break;
		}
		if (sceneState == (int)ESceneState::GameOver)
		{
			if (wParam == 'R' || wParam == 'r')
			{
				if (fadeEffect == nullptr)
				{
					fadeEffect = new FadeEffect();
				}
			}
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
				{
					player->SetIsJumping(true);
				}
				if (!parryObjects.empty())
				{
					for (auto it = parryObjects.begin(); it < parryObjects.end(); )
					{
						ParryObject* obj = *it;
						if (obj->Collided(player))
						{
							player->Parry();
							it = parryObjects.erase(it);
							break;
						}
						else it++;
					}
				}
				break;
			case VK_LEFT:
				if (xInputs.empty())
					xInputs.push_back(-1);
				else if (find(xInputs.begin(), xInputs.end(), -1) == xInputs.end())
					xInputs.push_back(-1);
				if (GetPlayer()->GetIsDown())
					GetPlayer()->SetDirection(xInputs.back());
				GetPlayer()->SetDirection(xInputs.back(), 99);
				break;
			case VK_RIGHT:
				if (xInputs.empty())
					xInputs.push_back(1);
				else if (find(xInputs.begin(), xInputs.end(), 1) == xInputs.end())
					xInputs.push_back(1);

				if (GetPlayer()->GetIsDown())
					GetPlayer()->SetDirection(xInputs.back());
				GetPlayer()->SetDirection(xInputs.back(), 99);
				break;
			case VK_SHIFT:
				if (!player->GetIsDashing() && player->dir.x != 0 && !player->GetIsSpecialAttack())
					player->SetIsDashing(true);
				break;
			case VK_DOWN:
				if (!player->GetIsDown() && !player->GetIsLockin() && !player->GetIsSpecialAttack() && !player->GetIsDashing())
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
				if (player->GetSpecailAttackCount() > 0)
				{
					if (!player->GetIsSpecialAttack())
					{
						player->SetIsSpecialAttack(true);
						delete cards.back();
						cards.pop_back();
					}
				}
				break;
			}
		}
		break;
	case WM_KEYUP:
		if (sceneState == (int)ESceneState::Title)
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
			if (!xInputs.empty())
			{
				auto it = find(xInputs.begin(), xInputs.end(), -1);
				if (it != xInputs.end())
					xInputs.erase(it);
				if (!xInputs.empty())
				{
					GetPlayer()->SetDirection(xInputs.back(), 99);
				}
			}
			break;
		case VK_RIGHT:
			if (GetPlayer()->dir.x == 1)
			{
				GetPlayer()->dir.x = 0;
				GetPlayer()->SetLastForward(LAST_FORWARD_IS_RIGHT);
			}
			if (!xInputs.empty())
			{
				auto it = find(xInputs.begin(), xInputs.end(), 1);
				if (it != xInputs.end())
					xInputs.erase(it);
				if (!xInputs.empty())
				{
					GetPlayer()->SetDirection(xInputs.back(), 99);
				}
			}
			break;
		case 'a':
		case 'A':
			if (sceneState == (int)ESceneState::World && fadeEffect == nullptr)
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
	Gdi_Draw(hdc);

#pragma region Fade Effect
	static bool effectOut = false;

	if (fadeEffect != nullptr)
	{
		fadeEffect->Draw(hdc);
		if (fadeEffect->GetIsFadeIn() && !effectOut)
		{
			if (sceneState == (int)ESceneState::Title)
				SetIsTitle(false);
			else if (sceneState == (int)ESceneState::World)
				SetStage(background->GetTripper()->GetStage());
			else if (sceneState == (int)ESceneState::Clear)
			{
				delete background;
				background = new ClearMap();
			}
			else if (sceneState == (int)ESceneState::Restart)
				SetReplay(true);
			else if (sceneState == (int)ESceneState::GameOver)
				SetReplay(false);
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

		if (!parryObjects.empty())
		{
			for (auto obj : parryObjects)
			{
				Collider* collider = obj->GetCollider();
				Rectangle(hdc, collider->left - camera_x, collider->top - camera_y, collider->right - camera_x, collider->bottom - camera_y);
			}
		}

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(myBrush);
		DeleteObject(hPen);
	}
#pragma endregion
}

void GameManager::Update()
{
	if (sceneState == (int)ESceneState::Clear)
		return;

	if (playingCameraShake)
		CameraShake();

	if (!frontImages.empty())
	{
		for (auto it = frontImages.begin(); it != frontImages.end(); )
		{
			if ((*it)->GetIsActive() == false)
			{
				it = frontImages.erase(it);
			}
			else it++;
		}
	}

	if (player != nullptr)
	{
		if (player->GetSpecailAttackCount() != cards.size() && sceneState != (int)ESceneState::World)
		{
			for (int i = cards.size(); i < player->GetSpecailAttackCount(); i++)
				cards.push_back(new CardUI(i));
		}
		if (!xInputs.empty())
			GetPlayer()->dir.x = xInputs.back();
		if (player->GetHealth() <= 0)
			GameOver();
		player->Update();
		if (player->GetJumpDust())
		{
			player->SetJumpDust(false);
			effects.push_back(new EffectObject(EEffectType::JumpDownDust, player->GetXPos(), player->GetYPos(), false, false, true));
		}

		if (boss != nullptr)
		{
			if (boss->GetIsDeath())
				Clear();

			boss->Update();

			if (boss->GetIsCameraShake())
			{
				cameraShakeStartTime = clock();
				playingCameraShake = true;
				boss->SetIsCameraShake(false);
			}

			if (boss->GetIsTransitionToPhase())
			{
				int dir = 0;
				if (boss->GetXDirection() == -1)
					dir = -100;
				parryObjects.push_back(new ParryObject(boss->GetXPosition() - 170 + dir, 400));
				parryObjects.push_back(new ParryObject(boss->GetXPosition() + dir, 300));
				parryObjects.push_back(new ParryObject(boss->GetXPosition() + 170 + dir, 400));
				boss->SetIsShowParry(true);
			}

			for (auto bullet : player->GetBullets())
			{
				if (bullet->GetisActive() && !bullet->GetIsCollided())
				{
					if (bullet->Collided(boss->GetCollider()))
					{
						boss->Hit(bullet);
						if (boss->GetIsDeath())
						{
							frontImages.push_back(new FrontImage(EFrontImage::KnockOut));
							clearTime = clock();
						}
					}
				}
			}

			if (!player->GetIsGraceTime() && player->GetCanInput() && player->GetHealth() > 0)
			{
				if (player->Collided(boss))
				{
					xInputs.clear();
					health->SetHealth(player->GetHealth());
					if (player->GetHealth() <= 0)
					{
						effects.push_back(new EffectObject(EEffectType::Died, 0, 0, true));
						gameOverTime = clock();
					}
				}
			}
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
	if (sceneState == (int)ESceneState::Title)
		return;

	int deltaX = (camera_x - x);
	int deltaY = (camera_y - y);

	if (!GetIsWorld())
	{
		isMoveCameraX = false;
		isMoveCameraY = false; 
		
		float speed = player->GetSpeed();
		player->Move(deltaX * speed, 0);
		return;
	}

	if (CollidedPlayerWithWorldCollisions(deltaX, deltaY))
		return;

	if (background != nullptr)
	{
		if (isMoveCameraX)
			background->SetXPos(-camera_x);
		if (isMoveCameraY)
			background->SetYPos(-camera_y);
	}

	int mapSizeWidth = background->GetWidth();
	int mapSizeHeight = background->GetHeight();
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

void GameManager::CameraShake()
{
	clock_t curTime = clock();
	playingCameraShake = true;

	if (curTime - cameraShakeStartTime > 500)
	{
		playingCameraShake = false;
		shakeX = 0;
		shakeY = 0;
	}

	shakeX = (rand() % 200 - 100) / 20;
	shakeY = (rand() % 200 - 100) / 20;
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
	return sceneState == (int)ESceneState::World;
}

void GameManager::SetIsWorld(bool isWorld)
{
	isWorld = isWorld;
	player->SetInWorld(isWorld);
}

bool GameManager::GetIsTitle()
{
	return sceneState == (int)ESceneState::Title;
}

void GameManager::SetIsTitle(bool isTitle)
{
	if (isTitle == true)
		sceneState = (int)ESceneState::Title;
	else
	{
		sceneState = (int)ESceneState::World;
		delete background;

		background = new WorldMap();
		background->SetRectView(*rectView);
		background->SetXPos(-WORLD_START_POINT_X);
		background->SetYPos(-WORLD_START_POINT_Y);
		player = new Player(WORLD_START_POINT_X + WINDOWS_WIDTH / 2, WORLD_START_POINT_Y + WINDOWS_HEIGHT / 2);

		SetCameraPos(camera_x, camera_y);
		// TODO:
		//SetStage(1);
	}
}

bool GameManager::GetIsStage()
{
	return sceneState == (int)ESceneState::Stage;
}

void GameManager::SetStage(int stage)
{
	sceneState = (int)ESceneState::Stage;
	this->stage = stage;
	if (background != nullptr)
		delete background;
	background = new StageMap();
	background->SetRectView(*rectView);

	if (player == nullptr)
		player = new Player();
	player->SetStage();
	boss = new Boss();
	boss->SetPlayer(player);
	frontImages.push_back(new FrontImage(EFrontImage::Ready));
	health = new HealthUI();

	camera_x = 0;
	camera_y = 0;
	SetCameraPos(0, 0);
}

void GameManager::Clear()
{
	if (sceneState == (int)ESceneState::Restart)
		return;

	clock_t curTime = clock();
	if (curTime - clearTime > 2000)
	{
		camera_x = 0;
		camera_y = 0;
		if (fadeEffect == nullptr)
			fadeEffect = new FadeEffect();
		sceneState = (int)ESceneState::Clear;
	}
}

void GameManager::GameOver()
{
	if (sceneState == (int)ESceneState::GameOver)
		return;

	clock_t curTime = clock();
	if (curTime - gameOverTime > 2000)
	{
		camera_x = 0;
		camera_y = 0;
		effects.push_back(new EffectObject(EEffectType::GameOver, WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2, true));
		sceneState = (int)ESceneState::GameOver;
	}
}

void GameManager::DeleteObjects()
{
	for (auto it = effects.begin(); it != effects.end(); it++)
		delete (*it);
	effects.clear();
	for (auto it = parryObjects.begin(); it != parryObjects.end(); it++)
		delete (*it);
	parryObjects.clear();
	for (auto it = cards.begin(); it != cards.end(); it++)
		delete (*it);
	cards.clear();
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	if (boss != nullptr)
	{
		delete boss;
		boss = nullptr;
	}
	if (health != nullptr)
	{
		delete health;
		health = nullptr;
	}
	xInputs.clear();
}

void GameManager::SetReplay(bool isTitle)
{
	DeleteObjects();
	if (isTitle)
	{
		delete background;
		background = new TitleMap();
		background->SetRectView(*rectView);
		sceneState = (int)ESceneState::Title;
		camera_x = WORLD_START_POINT_X;
		camera_y = WORLD_START_POINT_Y;
		isMoveCameraY = true;
		isMoveCameraX = true;
	}
	else
		SetStage(1);
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
	temp.left	-= deltaX - 4;
	temp.right	-= deltaX + 4;
	temp.top	-= deltaY - 4;
	temp.bottom -= deltaY + 4;

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

	if (background != nullptr)
	{
		background->Draw(hdc, graphics);
		if (!GetIsWorld())
			background->SetCameraPos(shakeX, shakeY);
	}

	if (sceneState != (int)ESceneState::Clear && sceneState != (int)ESceneState::Restart)
	{
		if (boss != nullptr)
		{
			boss->Draw(hdc, graphics);
			boss->SetCameraPos(shakeX, shakeY);
		}

		if (player != nullptr)
		{
			player->Draw(hdc, graphics);

			if (!GetIsWorld())
				player->SetCameraPos(shakeX, shakeY);

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
				EffectObject* effect = (*it);

				if (!effect->GetisActive())
					it = effects.erase(it);
				else
				{
					effect->Draw(hdc, graphics);
					effect->SetCameraPos(shakeX, shakeY);
					it++;
				}
			}
		}

		if (!parryObjects.empty())
		{
			for (auto it = parryObjects.begin(); it != parryObjects.end(); )
			{
				ParryObject* parry = (*it);
				if (!parry->GetIsActive())
					it = parryObjects.erase(it);
				else
				{
					if (parry->StartAnimation())
					{
						parry->SetCameraPos(shakeX, shakeY);
						parry->Draw(hdc, graphics);
					}
					it++;
				}
			}
		}

		if (health != nullptr)
			health->Draw(hdc);

		if (!cards.empty())
		{
			for (auto card : cards)
				card->Draw(hdc);
		}

		if (!frontImages.empty())
		{
			for (auto frontImage : frontImages)
				frontImage->Draw(hdc, graphics);
		}
	}
}

void GameManager::Gdi_End()
{
	GdiplusShutdown(g_GdipPlusToken);
}
