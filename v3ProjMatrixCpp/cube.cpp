#include "cube.h"

Cube::Cube() {
    pt.radius = 5;
}

void Cube::Update() {
    th += 0.01;
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

    for (int i = 0; i < matrixA.size(); i++) {
        Vector3 p = matrixA[i];
        float RxPx = p.x * mRx[0].x + p.y * mRx[1].x + p.z * mRx[2].x;
        float RxPy = p.x * mRx[0].y + p.y * mRx[1].y + p.z * mRx[2].y;
        float RxPz = p.x * mRx[0].z + p.y * mRx[1].z + p.z * mRx[2].z;

        float RyPx = RxPx * mRy[0].x + RxPy * mRy[1].x + RxPz * mRy[2].x;
        float RyPy = RxPx * mRy[0].y + RxPy * mRy[1].y + RxPz * mRy[2].y;
        float RyPz = RxPx * mRy[0].z + RxPy * mRy[1].z + RxPz * mRy[2].z;

        float RzPx = RyPx * mRz[0].x + RyPy * mRz[1].x + RyPz * mRz[2].x;
        float RzPy = RyPx * mRz[0].y + RyPy * mRz[1].y + RyPz * mRz[2].y;
        float RzPz = RyPx * mRz[0].z + RyPy * mRz[1].z + RyPz * mRz[2].z;

        float z = 1 / (dist - RzPz);

        vector<Vector3> pjM = {
            Vector3{z, 0, 0},
            Vector3{0, z, 0}
        };

        float pX = RzPx * pjM[0].x + RzPy * pjM[1].x;
        float pY = RzPx * pjM[0].y + RzPy * pjM[1].y;

        pX = int(pX * st.scale + st.scrWid / 2);
        pY = int(pY * st.scale + st.scrHei / 2);

        DrawCircle(pX, pY, pt.radius, WHITE);

        matrixAt[i].x = pX;
        matrixAt[i].y = pY;
    }
    ConnectLine();
}

void Cube::ConnectLine() {
    for (int i = 0; i < 4; i++) {
        Connect(i, (i + 1) % 4);
        Connect(i + 4, (i + 1) % 4 + 4);
        Connect(i, i + 4);
    }
}

void Cube::Connect(int i, int j) {
    DrawLine(matrixAt[i].x, matrixAt[i].y, matrixAt[j].x, matrixAt[j].y, WHITE);
}