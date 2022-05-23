//g++ main.cpp -o main -O1 -Wall  -Wno-missing-braces -L ./lib/ -lraylib -ldl -pthread

#include "GFX.hpp"

int main() {

    GFX GraphicsClass("TESTWINDOW");

    Vector2 ballPosition = { GraphicsClass.getWindowWidth() / 2.0f, GraphicsClass.getWindowHeight() / 2.0f };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    float ballRadius = 20;
    
    GraphicsClass.init();


    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        void BeginMode3D(Camera3D camera); 
        // Update
        GraphicsClass.clearWindow();

        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;
        if ((ballPosition.x >= (GraphicsClass.getWindowWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
        if ((ballPosition.y >= (GraphicsClass.getWindowHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

        GraphicsClass.drawText("LOLILOL", 200, 200, 20, RED);
        DrawCircleV(ballPosition, ballRadius, MAROON);
        if (IsKeyPressed(KEY_V))
        {
            if (IsWindowState(FLAG_VSYNC_HINT)) ClearWindowState(FLAG_VSYNC_HINT);
            else SetWindowState(FLAG_VSYNC_HINT);
        }

        if (IsKeyPressed(KEY_R))
        {
            std::cout << "LOL" << std::endl;
            GraphicsClass.set_window_size(1000,1000);
            GraphicsClass.init();
        }

        

        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}