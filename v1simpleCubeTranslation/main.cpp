#include "square.h"
#include "cube.h"
#include <iostream>
using namespace std;


int main() {
    Settings st;
    Point pt;
    Square sq;
    Cube cb;

    InitWindow(st.scrWid, st.scrHei, "I like turtles");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(st.darkGreen);

        pt.Update();
        pt.Draw();
        sq.Update();
        sq.Draw();
        cb.Update();
        cb.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
