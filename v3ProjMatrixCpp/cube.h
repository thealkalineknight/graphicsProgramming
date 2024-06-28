#pragma once
#include "point.h"

class Cube
{
public:
    Settings st;
    Point pt;

    Cube();
    void Update();
    void ConnectLine();
    void Connect(int i, int j);
    // void UpdateRots();
    // void CalcRots();
    // void ProjPoints(float rzpx, float rzpy, float rzpz);
    // void Draw(float x, float y);

    float dist = 3;

    float Tf = -1.3;

    float Sx = 1;
    float Sy = 1;
    float Sz = 1;
    float Sf = 1.9;

    float th = 0;

private:
    vector<Vector3> matrixA = {
        Vector3{-1, -1, 1},
        Vector3{1, -1, 1},
         Vector3{1, 1, 1}, 
         Vector3{-1, 1, 1}, 
    
         Vector3{-1, -1, -1}, 
         Vector3{1, -1, -1}, 
         Vector3{1, 1, -1}, 
         Vector3{-1, 1, -1} };

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