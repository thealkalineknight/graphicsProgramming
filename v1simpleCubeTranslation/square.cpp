#include "square.h"

Square::Square() {
    pt.radius = 5;
}

void Square::Update() {
}

void Square::Draw() {
    for (int i = 0; i < matrixA.size(); i++) {
        DrawCircle(matrixA[i].x, matrixA[i].y, pt.radius, BLUE);
    }
}
