#include "donut.h"

Donut::Donut() {
}

void Donut::Update() {

    al += 0.4; // *st.delta;
    be += 0.2; // *st.delta;

    for (float th = 0; th < 2 * PI; th += thspc) {
        float cTh = cos(th), sTh = sin(th);

        for (float ph = 0; ph < 2 * PI; ph += phspc) {
            float cPh = cos(ph), sPh = sin(ph);

            float crX = midR + cirR * cTh;
            float crY = cirR * sTh;

            vector<vector<float>> mRy = {
                vector<float>{cos(ph), 0, -sin(ph)},
                vector<float>{0, 1, 0},
                vector<float>{sin(ph), 0, cos(ph)} };
            MatMult(crX, crY, dist, mRy, Prypx, Prypy, Prypz);
            
            vector<vector<float>> mRx = {
                vector<float>{1, 0, 0},
                vector<float>{0, cos(al), sin(al)},
                vector<float>{0, -sin(al), cos(al)} };
            MatMult(RyPx, RyPy, RyPz, mRx, Prxpx, Prxpy, Prxpz);

            vector<vector<float>> mRz = {
                vector<float>{cos(be), sin(be), 0},
                vector<float>{-sin(be), cos(be), 0},
                vector<float>{0, 0, 1} };
            MatMult(RxPx, RxPy, RxPz, mRz, Przpx, Przpy, Przpz);

            float z = 1 / (TorCamDist - RzPz);  // oldDist - z

            vector<Vector3> pjM = {
                Vector3{z, 0, 0},
                Vector3{0, z, 0}
            };

            float pX = RzPx * pjM[0].x + RzPy * pjM[1].x;
            float pY = RzPx * pjM[0].y + RzPy * pjM[1].y;

            pX = int(pX * st.scale + st.scrWid / 2);
            pY = int(pY * st.scale + st.scrHei / 2);

            DrawCircle(pX, pY, 5, WHITE);
        }
    }
}

void Donut::MatMult(float mx, float my, float mz, vector<vector<float>> mat, float* outX, float* outY, float* outZ) {
    *outX = mx * mat[0][0] + my * mat[1][0] + mz * mat[2][0];
    *outY = mx * mat[0][1] + my * mat[1][1] + mz * mat[2][1];
    *outZ = mx * mat[0][2] + my * mat[1][2] + mz * mat[2][2];
}

/*
#include <Eigen/Dense>
using namespace Eigen;

int main() {
    MatrixXd mat1(2, 3); // 2x3 matrix
    MatrixXd mat2(3, 2); // 3x2 matrix
    mat1 << 1, 2, 3, 4, 5, 6;
    mat2 << 7, 8, 9, 10, 11, 12;
    MatrixXd result = mat1 * mat2;
    std::cout << "Result:\n" << result << std::endl;
    return 0;
}

========================

#include <armadillo>
using namespace arma;

int main() {
    mat mat1 = {{1, 2, 3}, {4, 5, 6}}; // 2x3 matrix
    mat mat2 = {{7, 8}, {9, 10}, {11, 12}}; // 3x2 matrix
    mat result = mat1 * mat2;
    result.print("Result:");
    return 0;
}

=========================


*/