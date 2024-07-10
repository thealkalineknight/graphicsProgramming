#include "cube.h"

Cube::Cube() {
    pt.radius = 5;
}

void Cube::Update() {

    KeyPress();

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

        if (dir == 1) {
            Rx = p[0] * tRx[0][0] + p[1] * tRx[1][0] + p[2] * tRx[2][0] + p[3] * tRx[3][0];
            Ry = p[0] * tRx[0][1] + p[1] * tRx[1][1] + p[2] * tRx[2][1] + p[3] * tRx[3][1];
            Rz = p[0] * tRx[0][2] + p[1] * tRx[1][2] + p[2] * tRx[2][2] + p[3] * tRx[3][2];
            Rt = p[0] * tRx[0][3] + p[1] * tRx[1][3] + p[2] * tRx[2][3] + p[3] * tRx[3][3];
        }

        if (dir == 2) {
            Rx = p[0] * tRy[0][0] + p[1] * tRy[1][0] + p[2] * tRy[2][0] + p[3] * tRy[3][0];
            Ry = p[0] * tRy[0][1] + p[1] * tRy[1][1] + p[2] * tRy[2][1] + p[3] * tRy[3][1];
            Rz = p[0] * tRy[0][2] + p[1] * tRy[1][2] + p[2] * tRy[2][2] + p[3] * tRy[3][2];
            Rt = p[0] * tRy[0][3] + p[1] * tRy[1][3] + p[2] * tRy[2][3] + p[3] * tRy[3][3];
        }

        if (dir == 3) {
            Rx = p[0] * tRz[0][0] + p[1] * tRz[1][0] + p[2] * tRz[2][0] + p[3] * tRz[3][0];
            Ry = p[0] * tRz[0][1] + p[1] * tRz[1][1] + p[2] * tRz[2][1] + p[3] * tRz[3][1];
            Rz = p[0] * tRz[0][2] + p[1] * tRz[1][2] + p[2] * tRz[2][2] + p[3] * tRz[3][2];
            Rt = p[0] * tRz[0][3] + p[1] * tRz[1][3] + p[2] * tRz[2][3] + p[3] * tRz[3][3];
        }

        if (dir == 0) {
            Rx = p[0];
            Ry = p[1];
            Rz = p[2];
            Rt = p[3];
        }

        Rz = maxDist - Rz;

        float Px = Rx * pM[0][0] + Ry * pM[1][0] + Rz * pM[2][0] + Rt * pM[3][0];
        float Py = Rx * pM[0][1] + Ry * pM[1][1] + Rz * pM[2][1] + Rt * pM[3][1];
        float Pz = Rx * pM[0][2] + Ry * pM[1][2] + Rz * pM[2][2] + Rt * pM[3][2];
        float Pt = Rx * pM[0][3] + Ry * pM[1][3] + Rz * pM[2][3] + Rt * pM[3][3];

        if (Pt != 0) {
            Px /= Pt; Py /= Pt; Pz /= Pt;
        }

        Px = Px / -Pz;
        Py = Py / -Pz;
            
        Px = (Px * st.scale + st.scrWid / 2);
        Py = (Py * st.scale + st.scrHei / 2);

        DrawCircle(Px, Py, pt.radius, BLACK);

        matrixAt[i].x = Px;
        matrixAt[i].y = Py;
    }
    ConnectLine();
}

void Cube::KeyPress() {
    if (IsKeyDown(KEY_A)) {
        th += 0.1;
        dir = 2;
    }
    if (IsKeyDown(KEY_D)) {
        th -= 0.1;
        dir = 2;
    }
    if (IsKeyDown(KEY_W)) {
        th += 0.1;
        dir = 1;
    }
    if (IsKeyDown(KEY_S)) {
        th -= 0.1;
        dir = 1;
    }
    if (IsKeyDown(KEY_Q)) {
        th += 0.1;
        dir = 3;
    }
    if (IsKeyDown(KEY_Z)) {
        th -= 0.1;
        dir = 3;
    }
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
