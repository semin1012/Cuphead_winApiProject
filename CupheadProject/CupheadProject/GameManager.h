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
#include "HealthUI.h"
#include "CardUI.h"
#include "ClearMap.h"
#include "TutorialMap.h"
#include "Sound.h"
#define TILE_SIZE 30

enum class ESceneState
{
	Title,
	World,
	Stage,
	Clear,
	GameOver,
	Restart,
	Tutorial,
	Max
};

class GameManager
{
public:
	std::vector<EffectObject*>	effects;
	std::vector<ParryObject*>	parryObjects;
	std::vector<FrontImage*>	frontImages;
	std::vector<CardUI*>		cards;
	std::vector<int>		xInputs;
	Sound*					bgm;
	Sound*					tripSound;
	Sound*					announcer;
	Background*				background;
	Player*					player;
	Boss*					boss;
	HealthUI*				health;
	bool					debugMode;
	RECT					cameraView;
	int						camera_x;
	int						camera_y;
	int						shakeX;
	int						shakeY;
	LPPOINT					mouseDelta;
	bool					bMouseDrag;
	RECT*					rectView;
	int						sceneState;
	int						stage;
	bool					playingCameraShake;
	clock_t					cameraShakeStartTime;
	clock_t					clearTime;
	clock_t					gameOverTime;
	bool					isMoveCameraY;
	bool					isMoveCameraX;
	bool					isTutorial;
	ETripperType			tripperType;

	ULONG_PTR				g_GdipPlusToken;
	bool					effectOut = false;

public:
	FadeEffect* fadeEffect;
	GameManager(RECT* rectView);
	~GameManager();

	void		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void		Draw(HDC& hdc);
	void		Update();
	void		SetCameraView();
	void		SetCameraPos(int x, int y);
	void		AddTile(HWND& hWnd, LPPOINT& mousePos);
	bool		CompairTilePos(Collider& collide);
	void		CameraShake();
	
	void		SetDebugMode();

	void		SetMouseDrageState(bool state);

	int			GetCameraXPos();
	int			GetCameraYPos();
	bool		GetMouseDragState();
	Player*		GetPlayer();
	Background* GetBackground();
	std::vector<int> GetInputs() { return xInputs; }

	bool		GetIsWorld();
	void		SetIsWorld(bool isWorld);
	bool		GetIsTitle();
	void		SetIsTitle(bool isTitle);
	bool		GetIsStage();
	void		SetWorld();
	void		SetTutorial();
	void		PlayAnnounerSound(EAnnouncerSound type);

	void		SetStage(int stage);
	void		Clear();
	void		GameOver();
	void		DeleteObjects();
	void		SetReplay(bool isTitle);
	Sound*		GetSoundManager() { return bgm; }

	void		SetTripperType(ETripperType type)		{ tripperType = type; }
	ETripperType GetTripperType()						{ return tripperType; }

	// mouse event
	void		SetMouseDeltaPos(HWND& hWnd);
	void		DragAndMoveWorldMap(HWND& hWnd);
	void		SetCameraInWorld();

	// World Map
	bool		CollidedPlayerWithWorldCollisions(int deltaX, int deltaY);
	bool		CollidedPlayer(Collider* collider, int deltaX, int deltaY);
	void		DestroySound();

	// gdi+
	void Gdi_Init();
	void Gdi_Draw(HDC hdc);
	void Gdi_End();
};

