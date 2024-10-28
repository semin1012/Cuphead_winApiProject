#include "TutorialMap.h"
#include <fstream>

TutorialMap::TutorialMap()
{
	CreateImage();
	width = 5650;
	height = 800;
	LoadMapInfo();
	curAnimCnt = 0;
	curAnimMax = 3;
	animLastTime = clock();
	hitObject = new HitObject(EHitObjectType::TutorialParry, 3430, 220);
	hitObject->SetCamera(camera_x, camera_y);
	parryObjects.push_back(new ParryObject(3900, 400, true));
	parryObjects.push_back(new ParryObject(4100, 400, true));
	parryObjects.push_back(new ParryObject(4300, 400, true));
	tripper = new Tripper(*rectView, 5800, 400, ETripperType::Door);
}

TutorialMap::~TutorialMap()
{
	delete backgroundFrontImage;
	delete tutorialText;
	delete downText;
	delete jump;
	delete dash;
	delete shoot;
	delete lock;
	delete parry;
	delete parry2;
	delete supperAttack;
}

void TutorialMap::Draw(HDC& hdc, Graphics& graphics)
{
	clock_t curTime = clock();
	if (curTime - animLastTime > 33)
	{
		curAnimCnt++;
		if (curAnimCnt >= curAnimMax)
			curAnimCnt = 0;
	}
	Rect rect = { 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT };
	backgroundBackImage.Draw(hdc, rect.X, rect.Y, rect.Width, rect.Height);

	CurlingToPosition(tutorialText, graphics, 200, 300 + camera_y);
	CurlingToPosition(downText, graphics, 700, 300 + camera_y);
	CurlingToPosition(jump, graphics, 1330, 385 + camera_y);
	CurlingToPosition(dash, graphics, 1760, 215 + camera_y);
	CurlingToPosition(shoot, graphics, 2500, 300 + camera_y);
	CurlingToPosition(lock, graphics, 3000, 245 + camera_y);

	// hit
	if (hitObject != nullptr)
	{
		hitObject->SetCollider();
		hitObject->SetCamera(camera_x, camera_y);
		hitObject->Draw(hdc, graphics);
	}
	for (int i = 0; i < parryObjects.size(); i++)
	{
		parryObjects[i]->SetCollider();
		parryObjects[i]->SetCamera(camera_x, camera_y);
		parryObjects[i]->Draw(hdc, graphics);
	}
	CurlingToPosition(parry, graphics, 3900, 100 + camera_y);
	CurlingToPosition(parry2, graphics, 4310, 200 + camera_y);
	CurlingToPosition(supperAttack, graphics, 5100, 300 + camera_y);

	if (tripper != nullptr)
	{
		tripper->SetCameraX(camera_x);
		tripper->SetCameraY(camera_y);
		tripper->Draw(hdc, graphics);
	}

	// front
	rect = { 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT };
	graphics.DrawImage(backgroundFrontImage, rect);
}

void TutorialMap::CreateImage()
{
	backgroundBackImage.Load(L"../Resource/Image/Background/Tutorial/back_image.png");
	backgroundFrontImage = new Image(L"../Resource/Image/Background/Tutorial/front_image.png");
	tutorialText = new Image(L"../Resource/Image/Background/Tutorial/Tutorial.png");
	downText = new Image(L"../Resource/Image/Background/Tutorial/down.png");
	jump = new Image(L"../Resource/Image/Background/Tutorial/jump.png");
	dash = new Image(L"../Resource/Image/Background/Tutorial/dash.png");
	shoot = new Image(L"../Resource/Image/Background/Tutorial/shoot.png");
	lock = new Image(L"../Resource/Image/Background/Tutorial/lock.png");
	parry = new Image(L"../Resource/Image/Background/Tutorial/parry.png");
	parry2 = new Image(L"../Resource/Image/Background/Tutorial/parry2.png");
	supperAttack = new Image(L"../Resource/Image/Background/Tutorial/supper_attack.png");
}

void TutorialMap::CurlingToPosition(Image* image, Graphics& graphics, int x, int y)
{
	Rect rect = { x + camera_x, y, (int)image->GetWidth(), (int)image->GetHeight() };
	if (x + rect.Width + camera_x > 0 && x + camera_x < WINDOWS_WIDTH)
		graphics.DrawImage(image, rect);
}

void TutorialMap::SaveMapInfo()
{
	std::ofstream ofs("../Resource/Save/Map/TutorialMapSave.txt", std::ios::out);
	if (ofs.fail())
	{
		MessageBox(NULL, _T("TutorialMapSave.txt 파일 열기 실패"), _T("에러"), MB_OK);
		return;
	}

	ofs << colliders.size() << std::endl;
	for (auto collider : colliders)
	{
		ofs << collider->left << " " << collider->top << " " << collider->right << " " << collider->bottom << std::endl;
	}

	MessageBox(NULL, _T("TutorialMapSave.txt 파일에 월드 맵의 정보를 저장했습니다."), _T("성공"), MB_OK);
	ofs.close();
}

void TutorialMap::LoadMapInfo()
{
	int size;

	std::ifstream ifs("../Resource/Save/Map/TutorialMapSave.txt", std::ios::in);
	if (ifs.fail())
	{
		MessageBox(NULL, _T("TutorialMapSave.txt 파일 열기 실패"), _T("에러"), MB_OK);
		return;
	}

	if (!ifs.eof())
		ifs >> size;

	while (!ifs.eof())
	{
		Collider* collider = new Collider();
		ifs >> collider->left >> collider->top >> collider->right >> collider->bottom;

		colliders.push_back(collider);
	}

	ifs.close();
}

void TutorialMap::ClearMapInfo()
{
	for (auto it = colliders.begin(); it != colliders.end(); it++)
	{
		delete (*it);
	}

	colliders.clear();
}
