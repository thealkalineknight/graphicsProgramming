#pragma once
#include "settings.h"

class Point
{
public:
    Settings st;

    Point();
    void Update();
    void Draw();

    int x;
    int y;
    int speedX;
    int speedY;
    int radius;
};