#include "point.h"

Point::Point() {
    x = 700;
    y = 100;
    radius = 5;
}

void Point::Update() {
}

void Point::Draw() {
    DrawCircle(x, y, radius, WHITE);
}