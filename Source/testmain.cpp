//g++ testmain.cpp GFX.cpp -o main -O1 -Wall  -Wno-missing-braces -L ./lib/ -lraylib -ldl -pthread

#include <raylib.h>
//#include "RayLib.hpp"
#include "InputManager.hpp"

// int main() {

//     GFX GraphicsClass("TESTWINDOW");

//     Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

//     Vector3 camPos = { 0.0f, 10.0f, 10.0f };
//     Vector3 camTar = { 0.0f, 0.0f, 0.0f };
//     Vector3 camHeight = { 0.0f, 1.0f, 0.0f };
//     float camFov = 45.0f; 
    
//     GraphicsClass.init();
//     GraphicsClass.setCameraPosition(camPos, camTar, camHeight, camFov);


//     //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//     //----------------------------------------------------------

//     // Main game loop
//     while (!WindowShouldClose())    // Detect window close button or ESC key
//     {
//         // Update
//         // Draw
//         //-----------------------------------------------------
//         BeginDrawing();
//             GraphicsClass.clearWindow();

//             BeginMode3D(GraphicsClass.getCamera()); 
//                 DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
//                 DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
//                 DrawGrid(10, 1.0f);
//             EndMode3D();

//             GraphicsClass.drawText("LOLILOL", 200, 200, 20, RED);
//         if (IsKeyPressed(KEY_V))
//         {
//             if (IsWindowState(FLAG_VSYNC_HINT)) ClearWindowState(FLAG_VSYNC_HINT);
//             else SetWindowState(FLAG_VSYNC_HINT);
//         }

//         if (IsKeyPressed(KEY_R))
//         {
//             std::cout << "LOL" << std::endl;
//             GraphicsClass.set_window_size(1000,1000);
//             GraphicsClass.init();
//         }       

//         EndDrawing();
//         //-----------------------------------------------------
//     }

//     // De-Initialization
//     //---------------------------------------------------------
//     CloseWindow();        // Close window and OpenGL context
//     //----------------------------------------------------------

//     return 0;
// }

int main(void)
{
    //gRayLib GFX();
    RL::InputManager InputManager("IMANAGER");

    int keystroke;
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");
    

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };


    Model skullmodel = LoadModel("./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/12140_Skull_v3_L2.obj");
    Texture2D skulltexture = LoadTexture("./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/Skull.png");
    SetMaterialTexture(&skullmodel.materials[0], MATERIAL_MAP_DIFFUSE, skulltexture);

    Vector3 skullposition = { 0.0f, 0.0f, 0.0f };
    float rotationangle = 0.0f;

         // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if ((keystroke = InputManager.recordInput()) != 0)
            std::cout << keystroke << std::endl;

        std::cout << InputManager.getMousePosition().x << " " << InputManager.getMousePosition().y << std::endl;
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawModelEx(skullmodel, skullposition, (Vector3){ 1.0f, 0.0f, 0.0f }, rotationangle, (Vector3){ 0.1f, 0.1f, 0.1f }, WHITE);
            EndMode3D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}