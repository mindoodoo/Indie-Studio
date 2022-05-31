//g++ testmain.cpp InputManager.cpp Drawer.cpp -o main -O1  -Wno-missing-braces -L ./lib/ -lraylib -ldl -pthread -std=c++2a 

#include <raylib.h>
#include "InputManager.hpp"
//#include "Window.hpp"
#include "Drawer.hpp"
#include "Map.hpp"

int main(void)
{
    RL::InputManager InputManager("TESTINPUTMANAGER");
    RL::Drawer Drawer("TESTDRAWER");
    //RL::Window Window("TESTMAIN");
    RL::Map Map("./Maps/TestMap/test.csv");

    //Window.init();

    int keystroke;
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");
    

    // Define the camera to look into our 3d world, this settings work ok with the grid
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 15.0f, 13.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    //required steps to load a 3d model (no animation)
    Model skullmodel = LoadModel("./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/12140_Skull_v3_L2.obj");
    Texture2D skulltexture = LoadTexture("./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/Skull.png");
    SetMaterialTexture(&skullmodel.materials[0], MATERIAL_MAP_DIFFUSE, skulltexture);
    Vector3 skullposition = { 0.0f, 0.0f, 0.0f };

    //required steps to load a 2dicon through load as image process
    Image playerIconIMG = LoadImage("./2d_models/FrogIcon/frog-prince.png");
    ImageResize(&playerIconIMG, 50, 50);    
    Texture2D playerIcon = LoadTextureFromImage(playerIconIMG);
    UnloadImage(playerIconIMG);

    //required for text and font
    Font SquidFont = LoadFontEx("./Fonts/Game_Of_Squids.ttf", 20, 0, 250);



    float rotationangle = 0.0f;

         // Set our game to run at 60 frames-per-second
    SetTargetFPS(60);

    std::cout << Map._parsedMap.size() << std::endl;
    std::cout << Map._parsedMap[0].size() << std::endl;

    for (int i = 0; i < Map._parsedMap.size(); i++) {
        for (int j = 0; j < Map._parsedMap[i].size(); j++) {
            std::cout << Map._parsedMap[i][j].tile << " ";
        }
        std::cout << std::endl;

    }

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key ,add to Window Class
    {
        // Update
        if ((keystroke = InputManager.recordInput()) != 0)
            std::cout << keystroke << std::endl;        
        if (keystroke == -4)
            skullposition.z -= 0.1f;
        if (keystroke == -3)
            skullposition.x -= 0.1f;
        if (keystroke == -2)
            skullposition.z += 0.1f;
        if (keystroke == -1)
            skullposition.x += 0.1f;

        //std::cout << InputManager.getMousePosition().x << " " << InputManager.getMousePosition().y << std::endl;
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        Drawer.beginDrawing();

            Drawer.clearBackground();


            Drawer.begin3DMode(camera);
                Drawer.draw_3D_model(skullmodel, skullposition.x, skullposition.y, skullposition.z);
                Drawer.draw_map(Map);
                //DrawModelEx(skullmodel, skullposition, (Vector3){ 1.0f, 0.0f, 0.0f }, rotationangle, (Vector3){ 0.1f, 0.1f, 0.1f }, WHITE);
            Drawer.end3DMode();

            Drawer.draw_2D_model(playerIcon, 100, 150);
            Drawer.draw_text("Player 1", RED, 100 , 150 + playerIcon.height, SquidFont);

        Drawer.endDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); //Add to window Class
    //--------------------------------------------------------------------------------------

    return 0;
}