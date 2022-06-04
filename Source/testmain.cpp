//g++ testmain.cpp InputManager.cpp Renderer.cpp Map.cpp Drawable3D.cpp Drawable2D.cpp Window.cpp Logger.cpp -o main -O1  -Wno-missing-braces -L ./lib/ -lraylib -ldl -pthread -std=c++2a -g3
#include <raylib.h>
#include "InputManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Map.hpp"
#include "Drawable3D.hpp"
#include "Drawable2D.hpp"
#include "CollisionManager.hpp"

int main(void)
{

    std::string skulltex = "./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/Skull.png";
    std::string skullmod = "./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/12140_Skull_v3_L2.obj";

    int keystroke;
    bool collision = false;
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL::Window Window("TESTMAIN");

    //for everything to work, we need to init everything else AFTER THE WINDOW
    RL::InputManager InputManager("TESTINPUTMANAGER");

    RL::Renderer Drawer("TESTDRAWER");

    RL::Map Map("./Maps/TestMap/test.csv", "./Maps/TestMap/TEST_WALL.png", "./Maps/TestMap/Floor.png" );

    RL::CollisionManager ColMan;

    RL::Drawable3D Skull(skulltex, skullmod, 0.04, RL::MODEL);
    Skull.setPosition(0, 1.0f, 0); //add 3dmodel_getmodel
    Vector3 SkullPosition;


    RL::Drawable3D TestMOB(skulltex, skullmod, 0.04, RL::MODEL);
    TestMOB.setPosition(5, 1.0f, 2);


    RL::Drawable2D playerIcon("./2d_models/FrogIcon/frog-prince.png");
    Vector2 newSize = {50, 50};
    playerIcon.resize(newSize);
    playerIcon.setPosition(80, 150, 0);

    int text_x = playerIcon.getPosition().x;
    int text_y = playerIcon.getPosition().y;
    int player_height = playerIcon.getTexture().height;
    
    //required for text and font
    Font SquidFont = LoadFontEx("./Fonts/Game_Of_Squids.ttf", 20, 0, 250);

    // Set our game to run at 60 frames-per-second
    SetTargetFPS(60);

    


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key ,add to Window Class
    {

        //collisions

        // Update
        if ((keystroke = InputManager.recordInput()) != 0)
            std::cout << keystroke << std::endl;        
        if (keystroke == -4){
                SkullPosition = Skull.getPosition();
                SkullPosition.z -= 0.05f;
            if (ColMan.collisionsWithWalls(SkullPosition, Map) == false &&
                ColMan.collisionsWithModels(SkullPosition, TestMOB) == false) {
                Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
            }
        }
        if (keystroke == -3){
                SkullPosition = Skull.getPosition();
                SkullPosition.x -= 0.05f;
            if (ColMan.collisionsWithWalls(SkullPosition, Map) == false &&
                ColMan.collisionsWithModels(SkullPosition, TestMOB) == false) {
                Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
            }
        }
        if (keystroke == -2){
                SkullPosition = Skull.getPosition();
                SkullPosition.z += 0.05f;
            if (ColMan.collisionsWithWalls(SkullPosition, Map) == false &&
                ColMan.collisionsWithModels(SkullPosition, TestMOB) == false) {
                Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
            }
        }
        if (keystroke == -1){
                SkullPosition = Skull.getPosition();
                SkullPosition.x += 0.05f;
            if (ColMan.collisionsWithWalls(SkullPosition, Map) == false &&
                ColMan.collisionsWithModels(SkullPosition, TestMOB) == false) {
                Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
            }
        }
        // Draw
        //----------------------------------------------------------------------------------
        Drawer.beginDrawing();

            Drawer.clearBackground();

            Drawer.begin3DMode(Window.getCamera());
                TestMOB.draw();
                Skull.draw();
                Map.draw_map();
            Drawer.end3DMode();

            playerIcon.draw();             
            Drawer.draw_text("Player 1", RED, text_x  , text_y + player_height , SquidFont);

            collision = false;
//             for (int i = 0; i < Map.getMapDepth(); i++) {
//                 for (int j = 0; j < Map.getMapWidth(); j++) {
//                     if (Map.getParsedMap()[i][j].tile == 1) {
//                         //COLLISION HANDLER 
//                         collision = do_collision_walls(Skull, i, j, Map);
//                         if (collision)
//                             Drawer.draw_text("COLLISION DETECTED", BLUE, 500, 500, SquidFont);
//                     }
// ;   
//                 }
//             }
        Drawer.endDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    Window.close();
    //--------------------------------------------------------------------------------------

    return 0;
}



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