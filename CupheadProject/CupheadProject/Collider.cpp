#include "Collider.h"

bool operator==(const Collider& a, const Collider& b)
{
    
    if (a.left != b.left) return false;
    if (a.right != b.right) return false;
    if (a.top != b.top) return false;
    if (a.bottom != b.bottom) return false;

    return true;
}

bool Collider::Compare(Collider& collider)
{
    if (left != collider.left) return false;
    if (right != collider.right) return false;
    if (top != collider.top) return false;
    if (bottom != collider.bottom) return false;
    return true;
}

bool Collider::IsOverlaps(Collider& collider)
{
    if (right < collider.left) return false;
    if (left > collider.right) return false;
    if (top > collider.bottom) return false;
    if (bottom < collider.top) return false;
    return true;
}
