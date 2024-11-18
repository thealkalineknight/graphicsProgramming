#pragma once
#include "settings.h"

class Donut
{
private:
    vector<float> cosThValues;
    vector<float> sinThValues;
    vector<float> cosPhValues;
    vector<float> sinPhValues;

    float cAl;
    float sAl;
    float cBe;
    float sBe;

    const int cirR = 1; // donut cross circ radius Z
    const int midR = 2; // donut radius
    const int TorCamDist = 5; // distance from donut to camera
    const int torR = cirR + midR; // custom var

    const float thspc = 0.07;
    const float phspc = 0.02;

    float RyPx, RyPy, RyPz;

    float al = 0; float be = 0;

    float RxPx, RxPy, RxPz;

    float RzPx, RzPy, RzPz;

    // old
    float dist = 3;

public:
    Settings st;

    Donut();

    void Update();

    void calcTrig();

    void MatMult(float mx, float my, float mz, float mat[3][3], float& outX, float& outY, float& outZ);
    // void Draw();
};