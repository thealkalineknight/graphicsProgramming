#include "donut.h"

Donut::Donut() {
    arrCTh.reserve(thSize);
    arrSTh.reserve(thSize);
    arrCPh.reserve(phSize);
    arrSPh.reserve(phSize);
    calcTrig();
}

void Donut::calcTrig() {
    for (float th = 0; th < 2 * PI; th += thspc) {
        arrCTh.push_back(cos(th));
        arrSTh.push_back(sin(th));
    }
    for (float ph = 0; ph < 2 * PI; ph += phspc) {
        arrCPh.push_back(cos(ph));
        arrSPh.push_back(sin(ph));
    }
}

void Donut::Update() {

    al += 0.04f; // *st.delta;
    be += 0.02f; // *st.delta;

    cAl = cos(al);
    sAl = sin(al);
    cBe = cos(be);
    sBe = sin(be);

    for (size_t i = 0; i < arrCTh.size(); ++i) {
        cTh = arrCTh[i], sTh = arrSTh[i];

        crX = midR + cirR * cTh;
        crY = cirR * sTh;

        for (size_t j = 0; j < arrCPh.size(); ++j) {
            cPh = arrCPh[j];
            sPh = arrSPh[j];

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

            z = 1 / (TorCamDist - RzPz);  // oldDist - z

            float pjM[2][3] = {
                {z, 0, 0},
                {0, z, 0}
            };

            pX = RzPx * pjM[0][0] + RzPy * pjM[1][0];
            pY = RzPx * pjM[0][1] + RzPy * pjM[1][1];

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
