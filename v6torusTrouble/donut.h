#pragma once
#include "settings.h"

class Donut
{
private:
    static constexpr float thspc = 0.07f;
    static constexpr float phspc = 0.07f;

    static constexpr size_t thSize = static_cast<size_t>(2 * PI / thspc);
    static constexpr size_t phSize = static_cast<size_t>(2 * PI / phspc);

    vector<float> arrCTh; 
    vector<float> arrSTh;
    vector<float> arrCPh;
    vector<float> arrSPh;

    float al, be = 0.0;

    float cAl, sAl;
    float cBe, sBe;

    float cTh, sTh;

    static constexpr int cirR = 1; // donut cross circ radius Z
    static constexpr int midR = 2; // donut radius
    static constexpr int TorCamDist = 5; // distance from donut to camera
    static constexpr int torR = cirR + midR; // custom var

    float crX, crY;

    float cPh, sPh;

    static constexpr float dist = 3.0f;  // trad

    float RyPx, RyPy, RyPz;
    float RxPx, RxPy, RxPz;
    float RzPx, RzPy, RzPz;

    float z;

    float pX, pY;


public:
    Settings st;

    Donut();

    void Update();

    void calcTrig();

    void MatMult(float mx, float my, float mz, float mat[3][3], float& outX, float& outY, float& outZ);
    // void Draw();
};