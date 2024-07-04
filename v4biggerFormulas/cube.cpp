#include "cube.h"

Cube::Cube() {
    pt.radius = 5;
}

void Cube::Update() {

    th += 0.01;

    vector<vector<float>> tRx = {
        vector<float>{1, 0, 0, 0},
        vector<float>{0, cos(th), sin(th), 0},
        vector<float>{0, -sin(th), cos(th), 0},
        vector<float>{0, 0, 0, 1} };

    vector<vector<float>> tRy = {
        vector<float>{cos(th), 0, -sin(th), 0},
        vector<float>{0, 1, 0, 0},
        vector<float>{sin(th), 0, cos(th), 0},
        vector<float>{0, 0, 0, 1} };

    vector<vector<float>> tRz = {
        vector<float>{cos(th), sin(th), 0, 0},
        vector<float>{-sin(th), cos(th), 0, 0},
        vector<float>{0, 0, 1, 0},
        vector<float>{0, 0, 0, 1} };


    for (int i = 0; i < matrixB.size(); i++) {
        vector<int> p = matrixB[i];

        float RxPx = p[0] * tRx[0][0] + p[1] * tRx[1][0] + p[2] * tRx[2][0] + p[3] * tRx[3][0];
        float RxPy = p[0] * tRx[0][1] + p[1] * tRx[1][1] + p[2] * tRx[2][1] + p[3] * tRx[3][1];
        float RxPz = p[0] * tRx[0][2] + p[1] * tRx[1][2] + p[2] * tRx[2][2] + p[3] * tRx[3][2];
        float RxPt = p[0] * tRx[0][3] + p[1] * tRx[1][3] + p[2] * tRx[2][3] + p[3] * tRx[3][3];

        float RyPx = RxPx * tRy[0][0] + RxPy * tRy[1][0] + RxPz * tRy[2][0] + RxPt * tRy[3][0];
        float RyPy = RxPx * tRy[0][1] + RxPy * tRy[1][1] + RxPz * tRy[2][1] + RxPt * tRy[3][1];
        float RyPz = RxPx * tRy[0][2] + RxPy * tRy[1][2] + RxPz * tRy[2][2] + RxPt * tRy[3][2];
        float RyPt = RxPx * tRy[0][3] + RxPy * tRy[1][3] + RxPz * tRy[2][3] + RxPt * tRy[3][3];

        float RzPx = RyPx * tRz[0][0] + RyPy * tRz[1][0] + RyPz * tRz[2][0] + RyPt * tRz[3][0];
        float RzPy = RyPx * tRz[0][1] + RyPy * tRz[1][1] + RyPz * tRz[2][1] + RyPt * tRz[3][1];
        float RzPz = RyPx * tRz[0][2] + RyPy * tRz[1][2] + RyPz * tRz[2][2] + RyPt * tRz[3][2];
        float RzPt = RyPx * tRz[0][3] + RyPy * tRz[1][3] + RyPz * tRz[2][3] + RyPt * tRz[3][3];

        RzPz = maxDist - RzPz;

        float Px = RzPx * pM[0][0] + RzPy * pM[1][0] + RzPz * pM[2][0] + RzPt * pM[3][0];
        float Py = RzPx * pM[0][1] + RzPy * pM[1][1] + RzPz * pM[2][1] + RzPt * pM[3][1];
        float Pz = RzPx * pM[0][2] + RzPy * pM[1][2] + RzPz * pM[2][2] + RzPt * pM[3][2];
        float Pt = RzPx * pM[0][3] + RzPy * pM[1][3] + RzPz * pM[2][3] + RzPt * pM[3][3];

        if (Pt != 0) {
            Px /= Pt; Py /= Pt; Pz /= Pt;
        }

        Px = (Px * st.scale + st.scrWid / 2);
        Py = (Py * st.scale + st.scrHei / 2);

        DrawCircle(Px, Py, pt.radius, BLACK);

        matrixAt[i].x = Px;
        matrixAt[i].y = Py;
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
    DrawLine(matrixAt[i].x, matrixAt[i].y, matrixAt[j].x, matrixAt[j].y, BLACK);
}
