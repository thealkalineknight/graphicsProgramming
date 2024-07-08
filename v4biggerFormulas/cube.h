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

private:

    float th = 0;
    float maxDist = 3;

    float fov = PI / 2;
    float zNear = 0.1;
    float zFar = 1000;

    float a = st.scrWid / st.scrHei;
    float F = 1 / tan(fov / 2);

    float aF = a * F;
    float q = zFar / (zFar - zNear);
    float Znq = zNear * q;

    vector<vector<float>> pM = {
        vector<float>{aF, 0, 0, 0},
        vector<float>{0, F, 0, 0},
        vector<float>{0, 0, q, 1},
        vector<float>{0, 0, -Znq, 0} };

    vector<vector<int>> matrixB = {
        vector<int>{-1, -1, 1, 1},
        vector<int>{1, -1, 1, 1},
        vector<int>{1, 1, 1, 1},
        vector<int>{-1, 1, 1, 1},

        vector<int>{-1, -1, -1, 1},
        vector<int>{1, -1, -1, 1},
        vector<int>{1, 1, -1, 1},
        vector<int>{-1, 1, -1, 1} };

    vector<Vector3> matrixAt = {
        Vector3{0, 0, 0},
        Vector3{0, 0, 0},
        Vector3{0, 0, 0},
        Vector3{0, 0, 0},

        Vector3{0, 0, 0},
        Vector3{0, 0, 0},
        Vector3{0, 0, 0},
        Vector3{0, 0, 0} };
};
