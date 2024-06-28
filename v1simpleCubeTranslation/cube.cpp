#include "cube.h"

Cube::Cube() {
    pt.radius = 5;

    //Transform('t', 0);
   // Transform('s', 0);
    Transform('r', 2);
    // everything works normal except multiple rotations (look into it later) maybe its the trig..?
}

void Cube::Update() {
    if (st.EventTrigger(0.05)) {
        AnimateT(0);
        AnimateT(1);
        AnimateT(2);
        //numS += varS;
        //if (numS < 1 or numS > 2) varS *= -1;
        //Sf += varS;  //varS = 0.01; numS = 1;
        //Transform('s', 0);
    }
}

void Cube::AnimateT(int coor) {
    if (coor == 0) {
        if (matrixA[0].x < -3 or matrixA[2].x > 3) Tf *= -1;
        Transform('t', 0);
    }
    if (coor == 1) {
        if (matrixA[3].y < -3 or matrixA[1].y > 3) Tf *= -1;
        Transform('t', 1);
    }
    if (coor == 2) {
        if (matrixA[0].z < -4 or matrixA[0].z > -1) Tf *= -1;
        Transform('t', 2);
    }
}

void Cube::Draw() {
    for (int i = 0; i < matrixA.size(); i++) {
        float x = matrixA[i].x / -matrixA[i].z;
        float y = matrixA[i].y / -matrixA[i].z;
        x = Remap(x, 0);
        y = Remap(y, 1);

        DrawCircle(x, y, pt.radius, RED);
        matrixAt[i].x = x; matrixAt[i].y = y;

        if (i + 1 < matrixAt.size()) {
            DrawLine(matrixAt[i].x, matrixAt[i].y, matrixAt[i + 1].x, matrixAt[i + 1].y, ORANGE);
        }
        if (i < 3) {
            DrawLine(matrixAt[i].x, matrixAt[i].y, matrixAt[7 - i].x, matrixAt[7 - i].y, ORANGE);
        }
    }
    DrawLine(matrixAt[0].x, matrixAt[0].y, matrixAt[3].x, matrixAt[3].y, ORANGE);
    DrawLine(matrixAt[4].x, matrixAt[4].y, matrixAt[7].x, matrixAt[7].y, ORANGE);
}

float Cube::Remap(float point, int p) {
    point = (1 + point) / 2;
    if (p == 0) point *= st.scrWid;
    if (p == 1) point *= st.scrHei;
    return point;
}

void Cube::Transform(char mode, int coor) {

    for (int i = 0; i < matrixA.size(); i++) {
        int x = matrixA[i].x;
        int y = matrixA[i].y;
        int z = matrixA[i].z;

        if (mode == 't') {
            if (coor == 0) matrixA[i].x += Tf;
            if (coor == 1) matrixA[i].y += Tf;
            if (coor == 2) matrixA[i].z += Tf;
        }

        else {
            vector<Vector3> M{};
            if (mode == 's') {
                M = mS;
                if (coor == 0) M[0].x = Sf;
                if (coor == 1) M[1].y = Sf;
                if (coor == 2) M[2].z = Sf;
            }
            else if (mode == 'r') {

                if (coor == 0) M = mRx;
                if (coor == 1) M = mRy;
                if (coor == 2) M = mRz;
            }

            matrixA[i].x = x * M[0].x + y * M[1].x + z * M[2].x;
            matrixA[i].y = x * M[0].y + y * M[1].y + z * M[2].y;
            matrixA[i].z = x * M[0].z + y * M[1].z + z * M[2].z;
        }
    }
}


//Remap Func:
// Goal; Normalize, then remap.
// Range [-1, 1] to [0, 1]
// Why?; although og always -z then conv to z, if -x/-y, will be [-1, 0]
// Then; Increase with wid, hei as a factor.












//void Cube::Update() {
    //Transform('r', 0);
    //th += 0.01;
    /* if (st.EventTrigger(0.05)) {
        Sf += varS;
        if (1 <= Sf <= 3) {  // -1 <= Sf && Sf <= 1
            Transform('s', 0);
        }
        else varS *= -1;
    }

    if (Sf < 0.5) {  // -1 <= Sf && Sf <= 1
        varS *= -1;
    }
    else if (Sf > 2) {
        varS *= -1;
    }
    else if (st.EventTrigger(0.05)) {
        Transform('s', 0);
        Sf += varS;
        cout << Sf << "\n";
    }
    */
//}



// https://www.scratchapixel.com/lessons/3d-basic-rendering/computing-pixel-coordinates-of-3d-point/mathematics-computing-2d-coordinates-of-3d-points.html
