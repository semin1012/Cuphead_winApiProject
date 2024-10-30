#include "Background.h"

Background::Background()
{
    rectView = nullptr;
    x = 0;
    y = 0;
    camera_x = 0;
    camera_y = 0;
    width = 0;
    height = 0;
    debugMode = false;
    hitObject = nullptr;
    tripper = nullptr;
    tutorialTripper = nullptr;
}

Background::Background(RECT& rectView, int x, int y) : Background()
{
    this->rectView = &rectView;
    this->x = x;
    this->y = y;
}

Background::~Background()
{
    if (hitObject != nullptr)
    {
        delete hitObject;
        hitObject = nullptr;
    }
    if (tripper != nullptr)
        delete tripper;
    if (tutorialTripper != nullptr)
        delete tutorialTripper;
    for (auto it = parryObjects.begin(); it != parryObjects.end(); it++)
        delete (*it);
    parryObjects.clear();
    if (!colliders.empty())
    {
        for (auto it = colliders.begin(); it != colliders.end(); it++)
            delete (*it);
        colliders.clear();
    }
}

void Background::DrawTrippers(HDC& hdc, Graphics& graphics)
{
    if (tripper != nullptr)
    {
        if (tripper->GetTripperType() != ETripperType::Door)
        {
            tripper->SetCameraX(x);
            tripper->SetCameraY(y);
        }
        else
        {
            tripper->SetCameraX(camera_x);
            tripper->SetCameraY(camera_y);
        }
        tripper->Draw(hdc, graphics);
    }
    if (tutorialTripper != nullptr)
    {
        if (tutorialTripper->GetTripperType() != ETripperType::Door)
        {
            tutorialTripper->SetCameraX(x);
            tutorialTripper->SetCameraY(y);
        }
        else
        {
            tutorialTripper->SetCameraX(camera_x);
            tutorialTripper->SetCameraY(camera_y);
        }
        tutorialTripper->Draw(hdc, graphics);
    }
}

void Background::SetRectView(RECT& rectView)
{
    this->rectView = &rectView;
}

void Background::SetCameraPos(int x, int y)
{
    int deltaX = (camera_x - x);
    this->x -= deltaX;
    camera_x = x;
    int deltaY = (camera_y - y);
    this->y -= deltaY;
    camera_y = y;
}

int Background::GetXPos()
{
    return x;
}

int Background::GetYPos()
{
    return y;
}

void Background::SetXPos(int x)
{
    this->x = x;
}

void Background::SetYPos(int y)
{
    this->y = y;
}

void Background::SetDebugMode(bool debugMode)
{
    this->debugMode = debugMode;
}

bool Background::CheckCollidedHitObject(Player* player, int deltaX, int deltaY)
{
    if (hitObject == nullptr)
        return false;
    Collider hitCollider = hitObject->GetCollider();
    Collider playerCollider = *player->GetCollider();
    playerCollider.left -= deltaX + 1;
    playerCollider.right -= deltaX + 1;
    playerCollider.top -= deltaY + 1;
    playerCollider.bottom -= deltaY + 1;
    playerCollider.left += camera_x;
    playerCollider.right += camera_x;
    if (hitCollider.IsOverlaps(playerCollider))
        return true;
    return false;
}

void Background::SetColliders(std::vector<Collider*> *colliders)
{
    this->colliders = *colliders;
}

std::vector<Collider*>* Background::GetColliders()
{
    return &colliders;
}

int Background::GetWidth()
{
    return width;
}

int Background::GetHeight()
{
    return height;
}

void Background::SetWidth(int width)
{
    this->width = width;
}

void Background::SetHeight(int height)
{
    this->height = height;
}

void Background::RemoveHitObject()
{
    if (hitObject == nullptr)
        return;
    delete hitObject;
    hitObject = nullptr;
}
