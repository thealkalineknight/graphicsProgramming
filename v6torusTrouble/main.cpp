#include "donut.h"
#include <iostream>
using namespace std;


int main() {
    Settings st;
    Donut dn;

    InitWindow(st.scrWid, st.scrHei, "I like turtles");
    // SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(st.darkGreen);

        // st.delta = GetFrameTime();

        dn.Update();

        // cout << GetFPS() << '\n';

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

/*
https://bedroomcoders.co.uk/posts/218
https://www.reddit.com/r/raylib/comments/wf1nxu/game_going_slow/
*/