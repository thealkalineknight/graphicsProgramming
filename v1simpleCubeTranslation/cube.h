#pragma once
#include "point.h"

class Cube
{
public:
    Settings st;
    Point pt;

    Cube();
    void Update();
    void Draw();
    float Remap(float point, int p);
    void Transform(char mode, int coor);
    void AnimateT(int coor);

    float Tf = -0.05;

    float Sx = 1;
    float Sy = 1;
    float Sz = 1;
    float Sf = 1;

    float th = -0.43;

private:
    vector<Vector3> matrixA = {
        Vector3{-1, 1, -3},
        Vector3{1, 1, -3},
        Vector3{1, -1, -3},
        Vector3{-1, -1, -3},

        Vector3{-1, -1, -5},
        Vector3{1, -1, -5},
        Vector3{1, 1, -5},
        Vector3{-1, 1, -5} };

    vector<Vector3> matrixAt = {
        Vector3{0, 0, 0},
        Vector3{0, 0, 0},
        Vector3{0, 0, 0},
        Vector3{0, 0, 0},

        Vector3{0, 0, 0},
        Vector3{0, 0, 0},
        Vector3{0, 0, 0},
        Vector3{0, 0, 0} };

    //----------

    vector<Vector3> mS = {
        Vector3{Sx, 0, 0},
        Vector3{0, Sy, 0},
        Vector3{0, 0, Sz} };

    //----------

    vector<Vector3> mRx = {
        Vector3{1, 0, 0},
        Vector3{0, cos(th), sin(th)},
        Vector3{0, -sin(th), cos(th)} };

    vector<Vector3> mRy = {
        Vector3{cos(th), 0, -sin(th)},
        Vector3{0, 1, 0},
        Vector3{sin(th), 0, cos(th)} };

    vector<Vector3> mRz = {
        Vector3{cos(th), sin(th), 0},
        Vector3{-sin(th), cos(th), 0},
        Vector3{0, 0, 1} };
};
