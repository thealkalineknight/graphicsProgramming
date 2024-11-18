#include "donut.h"

Donut::Donut() {
    calcTrig();
}

void Donut::calcTrig() {
    for (float th = 0; th < 2 * PI; th += thspc) {
        cosThValues.push_back(cos(th));
        sinThValues.push_back(sin(th));
    }
    for (float ph = 0; ph < 2 * PI; ph += phspc) {
        cosPhValues.push_back(cos(ph));
        sinPhValues.push_back(sin(ph));
    }
}

void Donut::Update() {

    al += 0.04; // *st.delta;
    be += 0.02; // *st.delta;

    cAl = cos(al);
    sAl = sin(al);
    cBe = cos(be);
    sBe = sin(be);

    for (size_t i = 0; i < cosThValues.size(); ++i) {
        float cTh = cosThValues[i], sTh = sinThValues[i];

        float crX = midR + cirR * cTh;
        float crY = cirR * sTh;

        for (size_t j = 0; j < cosPhValues.size(); ++j) {
            float cPh = cosPhValues[j];
            float sPh = sinPhValues[j];

            float mRy[3][3] = {
                {cPh, 0, -sPh},
                {0, 1, 0},
                {sPh, 0, cPh} };
            MatMult(crX, crY, dist, mRy, RyPx, RyPy, RyPz);
            
            float mRx[3][3] = {
                {1, 0, 0},
                {0, cAl, sAl},
                {0, -sAl, cAl} };
            MatMult(RyPx, RyPy, RyPz, mRx, RxPx, RxPy, RxPz);

            float mRz[3][3] = {
                {cBe, sBe, 0},
                {-sBe, cBe, 0},
                {0, 0, 1} };
            MatMult(RxPx, RxPy, RxPz, mRz, RzPx, RzPy, RzPz);

            float z = 1 / (TorCamDist - RzPz);  // oldDist - z

            float pjM[2][3] = {
                {z, 0, 0},
                {0, z, 0}
            };

            float pX = RzPx * pjM[0][0] + RzPy * pjM[1][0];
            float pY = RzPx * pjM[0][1] + RzPy * pjM[1][1];

            pX = int(pX * st.scale + st.scrWid / 2.0);
            pY = int(pY * st.scale + st.scrHei / 2.0);

            DrawCircle(pX, pY, 5, WHITE);
        }
    }
}

void Donut::MatMult(float mx, float my, float mz, float mat[3][3], float& outX, float& outY, float& outZ) {
    outX = mx * mat[0][0] + my * mat[1][0] + mz * mat[2][0];
    outY = mx * mat[0][1] + my * mat[1][1] + mz * mat[2][1];
    outZ = mx * mat[0][2] + my * mat[1][2] + mz * mat[2][2];
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