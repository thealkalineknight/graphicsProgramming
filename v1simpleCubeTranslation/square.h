#pragma once
#include "point.h"

class Square
{
public:
    Settings st;
    Point pt;

    Square();
    void Update();
    void Draw();

private:
    vector<Vector2> matrixA = {
        Vector2{100, 100},
        Vector2{200, 100},
        Vector2{100, 200},
        Vector2{200, 200} };
};
