//g++ main.cpp -o main -O1 -Wall  -Wno-missing-braces -L ./lib/ -lraylib -ldl -pthread

#include "GFX.hpp"

int main() {

    GFX GraphicsClass("TESTWINDOW");


    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        void BeginMode3D(Camera3D camera); 
        // Update
        GraphicsClass.clearWindow();

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

        GraphicsClass.drawText("LOLILOL", 200, 200, 20, RED);

        

        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}