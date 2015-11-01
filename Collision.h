#pragma once
#include <limits>

namespace CollisionObject
{
    enum
    {
        None = -1,
        L_Wall = -2,
        R_Wall = -4,
        U_Wall = -8,
        D_Wall = -16,
    };
};

struct Collision
{
    Collision() : occurTime(std::numeric_limits<float>::max()), 
        object1(CollisionObject::None), object2(CollisionObject::None) {};

    Collision(float occurTime, int object1, int object2) : occurTime(occurTime), 
        object1(object1), object2(object2) {};

    float occurTime;
    int object1;
    int object2;
};
