#include "cube.h"
#include <iostream>
using namespace std;


int main() {
    Settings st;
    Cube cb;

    InitWindow(st.scrWid, st.scrHei, "I like turtles");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(st.darkGreen);

        cb.Update();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
