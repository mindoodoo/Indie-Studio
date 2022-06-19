//g++ testmain.cpp InputManager.cpp Renderer.cpp Map.cpp Drawable3D.cpp Drawable2D.cpp Window.cpp Logger.cpp CollisionManager.cpp SoundManager.cpp -o main -O1  -Wno-missing-braces -L ./lib/ -lraylib -ldl -pthread -std=c++2a -g3
#include <raylib.h>
#include "InputManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Map.hpp"
#include "Drawable3D.hpp"
#include "Drawable2D.hpp"
#include "CollisionManager.hpp"
#include "SoundManager.hpp"

int main(void)
{

    std::string skulltex = "./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/Skull.png";
    std::string skullmod = "./3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/12140_Skull_v3_L2.obj";

    std::string SpeedUpTex = "./PowerUps/Speed.png";

    int keystroke;
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL::Window Window("TESTMAIN");

    //for everything to work, we need to init everything else AFTER THE WINDOW
    RL::InputManager InputManager("TESTINPUTMANAGER");

    RL::Renderer Drawer("TESTDRAWER");

    RL::SoundManager SoundManager;

    RL::Map Map("./Maps/Stage2/test.csv", "./Maps/Stage2/TEST_WALL.png", "./Maps/Stage2/Floor.png", "./Maps/Stage2/crate.png" );

    RL::CollisionManager ColMan;

    RL::Drawable3D Skull(skulltex, skullmod,"", RL::MODEL, 0.04);
    Skull.setPosition(0, 1.0f, 0); //add 3dmodel_getmodel
    Vector3 SkullPosition;


    RL::Drawable3D TestMOB(skulltex, skullmod,"", RL::MODEL, 0.04);
    TestMOB.setPosition(-5, 1.0f, 2);

    RL::Drawable3D SpeedUp(SpeedUpTex, "", "", RL::POWER);
    SpeedUp.setPosition(5, 1.0f, 2);


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
        SoundManager.updateMusicStream();
        InputManager.recordInputs();

        for (int i = 0; i < InputManager.getInputs().size(); i++)
            std::cout << InputManager.getInputs()[i] << std::endl;


        if (InputManager.playerHasPressedKeyAsChar(-4)){
                SkullPosition = Skull.getPosition();
                SkullPosition.z -= 0.05f;
            if (ColMan.collisionsWithWalls(SkullPosition, Map) == false &&
                ColMan.collisionsWithModels(SkullPosition, TestMOB) == false &&
                ColMan.collisionsWithCrates(SkullPosition, Map) == false) {
                Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
            }
        }
        if (InputManager.playerHasPressedKeyAsChar(-3)){
                SkullPosition = Skull.getPosition();
                SkullPosition.x -= 0.05f;
            if (ColMan.collisionsWithWalls(SkullPosition, Map) == false &&
                ColMan.collisionsWithModels(SkullPosition, TestMOB) == false &&
                ColMan.collisionsWithCrates(SkullPosition, Map) == false) {
                Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
            }
        }
        if (InputManager.playerHasPressedKeyAsChar(-2)){
                SkullPosition = Skull.getPosition();
                SkullPosition.z += 0.05f;
            if (ColMan.collisionsWithWalls(SkullPosition, Map) == false &&
                ColMan.collisionsWithModels(SkullPosition, TestMOB) == false &&
                ColMan.collisionsWithCrates(SkullPosition, Map) == false) {
                Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
            }
        }
        if (InputManager.playerHasPressedKeyAsChar(-1)){
                SkullPosition = Skull.getPosition();
                SkullPosition.x += 0.05f;
            if (ColMan.collisionsWithWalls(SkullPosition, Map) == false &&
                ColMan.collisionsWithModels(SkullPosition, TestMOB) == false &&
                ColMan.collisionsWithCrates(SkullPosition, Map) == false) {
                Skull.setPosition(SkullPosition.x, SkullPosition.y, SkullPosition.z);
            }
        }
        
        //MUSIC HANDLING
        if (InputManager.playerHasPressedKeyAsChar('p'))
            SoundManager.playSpecificMusic("SeruGemû");
        if (InputManager.playerHasPressedKeyAsChar('o'))
            SoundManager.playSpecificMusic("RestuSen");
        if (InputManager.playerHasPressedKeyAsChar('k'))
            SoundManager.playSpecificMusic("MiraiKaraNoShonen");
        if (InputManager.playerHasPressedKeyAsChar('m'))
            SoundManager.playSpecificMusic("MiraiKaraKitaShonen");
        
        if (InputManager.playerHasPressedKeyAsChar('l'))
            SoundManager.pauseOrPlayMusic();
        if (InputManager.playerHasPressedKeyAsChar('r'))
            SoundManager.enableDisableShuffle();

        if (InputManager.playerHasPressedKeyAsChar('e'))
            SoundManager.playSpecificSoundFx("Explosion1");
        
        if (InputManager.playerHasPressedKeyAsChar('+'))
            SoundManager.increaseMusicVolume();
        if (InputManager.playerHasPressedKeyAsChar('-'))
            SoundManager.decreaseMusicVolume();
        // Draw
        //----------------------------------------------------------------------------------
        Drawer.beginDrawing();

            Drawer.clearBackground();

            Drawer.begin3DMode(Window.getCamera());
                TestMOB.draw();
                Skull.draw();
                SpeedUp.drawPower();
                Map.draw_map();

            Drawer.end3DMode();

            playerIcon.draw();             
            Drawer.draw_text("Player 1", RED, text_x  , text_y + player_height , SquidFont, 20.0f);


            Drawer.draw_text("Press r to enable/disable shuffle", BLUE, 600  , text_y + player_height -60, SquidFont, 20.0f);
            Drawer.draw_text("Press m to play Mirai Kara Kita Shonen song", RED, 600  , text_y + player_height -140, SquidFont, 20.0f);
            Drawer.draw_text("Press k to play Mirai Kara no Shonen song", RED, 600  , text_y + player_height -160, SquidFont, 20.0f);
            Drawer.draw_text("Press l to PAUSE/PLAY Current music", BLACK, 600  , text_y + player_height-180 , SquidFont, 20.0f);
            Drawer.draw_text("Press o to play Restu Sen song", RED, 600  , text_y + player_height -120 , SquidFont, 20.0f);
            Drawer.draw_text("Press p to play Seru Gemû song", RED, 600  , text_y + player_height -100, SquidFont, 20.0f);
            Drawer.draw_text("Press e to play Explosion1 sound effect", GREEN, 600  , text_y + player_height -80, SquidFont, 20.0f);
        Drawer.endDrawing();
        //----------------------------------------------------------------------------------

        InputManager.popInputs();
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