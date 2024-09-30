#pragma once
#include "framework.h"

class Collider
{
public:
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;

public:
    Collider(LONG left, LONG top, LONG right, LONG bottom) : left(left), top(top), right(right), bottom(bottom) {}

    bool Compare(Collider& collider);

    bool operator==(Collider& rect)
    {
        if (left !=     rect.left) return false;
        if (right !=    rect.right) return false;
        if (top !=      rect.top) return false;
        if (bottom !=   rect.bottom) return false;

        return true;
    }

    friend bool operator==(const Collider& a, const Collider& b);
};
