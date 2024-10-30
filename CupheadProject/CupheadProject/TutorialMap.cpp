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
	tripper = (new Tripper(*rectView, 5800, 400, ETripperType::Door));
}

TutorialMap::~TutorialMap()
{
	delete backgroundFrontImage;
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

	CurlingToPosition(&tutorialText, hdc, 200, 300 + camera_y, 211, 211, 211);
	CurlingToPosition(&downText, hdc, 700, 300 + camera_y, 211, 211, 211);
	CurlingToPosition(&jump, hdc, 1330, 385 + camera_y, 211, 211, 211);
	CurlingToPosition(&dash, hdc, 1760, 215 + camera_y, 211, 211, 211);
	CurlingToPosition(&shoot, hdc, 2500, 300 + camera_y, 211, 211, 211);
	CurlingToPosition(&lock, hdc, 3000, 245 + camera_y, 211, 211, 211);

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
	CurlingToPosition(&parry, hdc, 3900, 100 + camera_y, 211, 211, 211);
	CurlingToPosition(&parry2, hdc, 4310, 200 + camera_y, 211, 211, 211);
	CurlingToPosition(&supperAttack, hdc, 5100, 300 + camera_y, 211, 211, 211);

	DrawTrippers(hdc, graphics);

	// front
	rect = { 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT };
	graphics.DrawImage(backgroundFrontImage, rect);
}

void TutorialMap::CreateImage()
{
	backgroundBackImage.Load(L"../Resource/Image/Background/Tutorial/back_image.png");
	backgroundFrontImage = new Image(L"../Resource/Image/Background/Tutorial/front_image.png");
	tutorialText.Load(L"../Resource/Image/Background/Tutorial/Tutorial1.png");
	downText.Load(L"../Resource/Image/Background/Tutorial/down1.png");
	jump.Load(L"../Resource/Image/Background/Tutorial/jump1.png");
	dash.Load(L"../Resource/Image/Background/Tutorial/dash1.png");
	shoot.Load(L"../Resource/Image/Background/Tutorial/shoot1.png");
	lock.Load(L"../Resource/Image/Background/Tutorial/lock11.png");
	parry.Load(L"../Resource/Image/Background/Tutorial/parry1.png");
	parry2.Load(L"../Resource/Image/Background/Tutorial/parry21.png");
	supperAttack.Load(L"../Resource/Image/Background/Tutorial/supper_attack1.png");
}

void TutorialMap::CurlingToPosition(Image* image, Graphics& graphics, int x, int y)
{
	Rect rect = { x + camera_x, y, (int)image->GetWidth(), (int)image->GetHeight() };
	if (x + rect.Width + camera_x > 0 && x + camera_x < WINDOWS_WIDTH)
		graphics.DrawImage(image, rect);
}

void TutorialMap::CurlingToPosition(CImage* image, HDC& hdc, int x, int y, int r, int g, int b)
{
	Rect rect = { x + camera_x, y, (int)image->GetWidth(), (int)image->GetHeight() };
	if (x + rect.Width + camera_x > 0 && x + camera_x < WINDOWS_WIDTH)
		image->TransparentBlt(hdc, RECT{ rect.X, rect.Y, rect.X + rect.Width, rect.Y + rect.Height }, RGB(r, g, b));
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
