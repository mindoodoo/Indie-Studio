//g++ testmain.cpp InputManager.cpp -o main -O1 -Wall  -Wno-missing-braces -L ./lib/ -lraylib -ldl -pthread

#include <raylib.h>
#include "InputManager.hpp"
#include "Window.hpp"
#include "Drawer.hpp"

int main(void)
{
    //gRayLib GFX();
    RL::InputManager InputManager("TESTINPUTMANAGER");
    RL::Drawer Drawer("TESTDRAWER");
    //RL::Window Window("TESTMAIN");

    //Window.init();

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
    camera.up = (Vector3){ 0.0f, 0.50f, 0.0f };          // Camera up vector (rotation towards target)
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

        if (InputManager.isMouseLeftClicked())
            skullposition.x += 0.1f;

        //std::cout << InputManager.getMousePosition().x << " " << InputManager.getMousePosition().y << std::endl;
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                Drawer.draw_3D_model(skullmodel, skullposition.x, skullposition.y, skullposition.z);
                //DrawModelEx(skullmodel, skullposition, (Vector3){ 1.0f, 0.0f, 0.0f }, rotationangle, (Vector3){ 0.1f, 0.1f, 0.1f }, WHITE);
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