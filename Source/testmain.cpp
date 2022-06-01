//g++ testmain.cpp InputManager.cpp Renderer.cpp Map.cpp Drawable3D.cpp Drawable2D.cpp -o main -O1  -Wno-missing-braces -L ./lib/ -lraylib -ldl -pthread -std=c++2a -g3
#include <raylib.h>
#include "InputManager.hpp"
//#include "Window.hpp"
#include "Renderer.hpp"
#include "Map.hpp"
#include "Drawable3D.hpp"
#include "Drawable2D.hpp"

int main(void)
{

    std::string skulltex = "./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/Skull.png";
    std::string skullmod = "./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/12140_Skull_v3_L2.obj";

    
    //RL::Window Window("TESTMAIN");
    

    //Window.init();

    int keystroke;
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    //for everything to work, we need to init everything else AFTER THE WINDOW
    RL::InputManager InputManager("TESTINPUTMANAGER");

    RL::Renderer Drawer("TESTDRAWER");

    RL::Map Map("./Maps/TestMap/test.csv", "./Maps/TestMap/TEST_WALL.png", "./Maps/TestMap/Floor.png" );

    RL::Drawable3D Skull(skulltex, skullmod, 0.1, RL::MODEL);
    Skull.setPosition(5, 0.5, 5);
    Vector3 SkullPosition;

    RL::Drawable2D playerIcon("./2d_models/FrogIcon/frog-prince.png");
    Vector2 newSize = {50, 50};
    playerIcon.resize(newSize);
    playerIcon.setPosition(80, 150, 0);

    int text_x = playerIcon.getPosition().x;
    int text_y = playerIcon.getPosition().y;
    int player_height = playerIcon.getTexture().height;
    

    // Define the camera to look into our 3d world, this settings work ok with the grid
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 15.0f, 13.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    //required steps to load a 3d model (no animation)
    // Model skullmodel = LoadModel("./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/12140_Skull_v3_L2.obj");
    // Texture2D skulltexture = LoadTexture("./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/Skull.png");
    // SetMaterialTexture(&skullmodel.materials[0], MATERIAL_MAP_DIFFUSE, skulltexture);
    // Vector3 skullposition = { 0.0f, 0.0f, 0.0f };

    //required steps to load a 2dicon through load as image process
    // Image playerIconIMG = LoadImage("./2d_models/FrogIcon/frog-prince.png");
    // ImageResize(&playerIconIMG, 50, 50);    
    // Texture2D playerIcon = LoadTextureFromImage(playerIconIMG);
    // UnloadImage(playerIconIMG);

    //required for text and font
    Font SquidFont = LoadFontEx("./Fonts/Game_Of_Squids.ttf", 20, 0, 250);



    float rotationangle = 0.0f;

         // Set our game to run at 60 frames-per-second
    SetTargetFPS(60);

    // std::cout << Map._parsedMap.size() << std::endl;
    // std::cout << Map._parsedMap[0].size() << std::endl;

    // for (int i = 0; i < Map._parsedMap.size(); i++) {
    //     for (int j = 0; j < Map._parsedMap[i].size(); j++) {
    //         std::cout << Map._parsedMap[i][j].tile << " ";
    //     }
    //     std::cout << std::endl;

    // }

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key ,add to Window Class
    {
        // Update
        if ((keystroke = InputManager.recordInput()) != 0)
            std::cout << keystroke << std::endl;        
        if (keystroke == -4){
            SkullPosition = Skull.getPosition();
            SkullPosition.z -= 0.1f;
            Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
        }
        if (keystroke == -3){
            SkullPosition = Skull.getPosition();
            SkullPosition.x -= 0.1f;
            Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
        }
        if (keystroke == -2){
            SkullPosition = Skull.getPosition();
            SkullPosition.z += 0.1f;
            Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
        }
        if (keystroke == -1){
            SkullPosition = Skull.getPosition();
            SkullPosition.x += 0.1f;
            Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
        }

        //std::cout << InputManager.getMousePosition().x << " " << InputManager.getMousePosition().y << std::endl;
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        Drawer.beginDrawing();

            Drawer.clearBackground();


            Drawer.begin3DMode(camera);
                Skull.draw();
                //Drawer.draw_3D_model(skullmodel, skullposition.x, skullposition.y, skullposition.z);
                //Drawer.draw_map(Map);
                Map.draw_map();
                //DrawModelEx(skullmodel, skullposition, (Vector3){ 1.0f, 0.0f, 0.0f }, rotationangle, (Vector3){ 0.1f, 0.1f, 0.1f }, WHITE);
            Drawer.end3DMode();

            playerIcon.draw();
            //Drawer.draw_2D_model(playerIcon, 100, 150);
             
            Drawer.draw_text("Player 1", RED, text_x  , text_y + player_height , SquidFont);

        Drawer.endDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); //Add to window Class
    //--------------------------------------------------------------------------------------

    return 0;
}