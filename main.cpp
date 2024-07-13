#include "raylib.h"



typedef enum {
    STORAGE_POSITION_HISCORE = 0
} StorageData;
//Enemy Body
struct {
    float xpos;
    float ypos;
    float h;
    float w;
    
} ghost_1, ghost_2;

//Player Body
struct {
    float xpos;
    float ypos;
    float w;
    float h;
    

} player;


int main (void)
{
    const int screenWidth = 600;
    const int screenHeigth = 800;


    

    InitWindow (screenWidth, screenHeigth, "One Ship");

    //Texture Debug
    Texture2D Ship = LoadTexture("../source/ship.png");
    //Bullet
    Texture2D bullet_anim = LoadTexture("../source/laser-bolts-fixed.png");
    float bullet_Framewidth = (float)(bullet_anim.width / 2);
    //Player
    float framWidth = (float)(Ship.width / 6);
    //IngameFrames Settings
    int maxFrames = (int)(Ship.width / (int)framWidth);
    float timer = 0.0f;
    int frame = 0;
    //Enemy
    Texture2D enemy_Anim = LoadTexture("../source/enemy-small-test1.png");
    float enemy_Framewidth = (float)(enemy_Anim.width / 2);
    //Background
    Texture2D back_Ground = LoadTexture("../source/desert-backgorund.png");
    Image icon = LoadImage ("../source/ico_ship.png");

    //InitWindow (screenWidth, screenHeigth, "Test");

    SetTargetFPS(60);
    SetWindowIcon (icon);

    //Player
    float bull_x = 0;
    float bull_y = 0;
    player.h = 40;
    player.w = 40;
    //Indicator to playershoot
    bool shoot = false;

    //System
    HideCursor();
    


    //Atributes
    int score = 0;
    int Hi_Score = LoadStorageValue(STORAGE_POSITION_HISCORE);
    int Life = 1;



    //Enemies
    /*
        Enemy1
    */
    ghost_1.h = 40;
    ghost_1.w = 40;
    ghost_1.xpos = GetRandomValue (0, 600);
    ghost_1.ypos = 20;
    /*
        Enemy2
    */
    ghost_2.h = 40;
    ghost_2.w = 40;
    ghost_2.xpos = GetRandomValue (0, 600);
    ghost_2.ypos = 20;  

    
      


    //Main Game Loop 

    while (!WindowShouldClose())
    {
        //Update
        

        //Player position
        player.xpos = GetMouseX ();
        player.ypos = GetMouseY ();
        //Initialize Player to Rectangle
        Rectangle Main_Player = {player.xpos, player.ypos, player.w, player.h};
        //Initialize Bullet to Rectangle
        Rectangle bullet = {bull_x, bull_y, 20, 20 };
        //GetFrameTime
        timer += GetFrameTime();

        //how fast is the animation
        if (timer >= 0.1f){
            timer = 0.0f;
            frame += 1;
        }

        //Frame modulo to maxFrames
        frame = frame % maxFrames;

        //Reset bullet
        if (bull_y < 0)
        {
            bull_y = player.ypos + 20;
            bull_x = player.xpos;
            
        }


        //Activate Shooting
        if (shoot == false)
        {
            bull_x = player.xpos;
            bull_y = player.ypos + 40;

        }

        if (IsKeyPressed(KEY_SPACE))
        {
            shoot = true;
        }

        
        //Continious shooting bullet speed  
        bull_y -= 24;


        // Enemy fall
        ghost_1.ypos += 10;
        ghost_2.ypos += 10;
        //Loop Enemy Position
        Rectangle enemy1 = {ghost_1.xpos, ghost_1.ypos, ghost_1.w, ghost_1.h};
        Rectangle enemy2 = {ghost_2.xpos, ghost_2.ypos, ghost_2.w, ghost_2.h};

        
        if (CheckCollisionRecs(bullet, enemy1) || CheckCollisionRecs(bullet, enemy2))
        {
            //bull_y = player.ypos + 20;
            //bull_x = player.xpos;
            score += 1;

            if (CheckCollisionRecs(bullet, enemy1)){
                //reset enemy 1
                ghost_1.ypos = 20;
                ghost_1.xpos = GetRandomValue (10, 550);

            } else if (CheckCollisionRecs(bullet, enemy2)){
                //reset enemy 2
                ghost_2.ypos = 20;
                ghost_2.xpos = GetRandomValue (10, 550);

            }

        }
         
        if (CheckCollisionRecs(enemy1, Main_Player) || CheckCollisionRecs(enemy1, Main_Player))
        {
            Life -= 1;

        }

        if (Life <= 0 )
        {
            score = 0;
            Life = 1;
            SaveStorageValue (STORAGE_POSITION_HISCORE, Hi_Score);
            SetMousePosition (300, 700);
            
        }

        //HiScore
        if (score == Hi_Score)
        {
            Hi_Score = score;
        } else if (score > Hi_Score){
            Hi_Score = score;
            
        } else if (score < Hi_Score){
            Hi_Score = Hi_Score;
            
        }
        

        //reset enemy
        /*
            Enemy1
        */
        if (ghost_1.ypos > screenHeigth)
        {
            ghost_1.ypos = 20;
            ghost_1.xpos = GetRandomValue (10, 550);

        }
        /*
            Enemy2
        */
        if (ghost_2.ypos > screenHeigth)
        {
            ghost_2.ypos = 20;
            ghost_2.xpos = GetRandomValue (10, 550);
        }
        

        BeginDrawing();
            ClearBackground(BLACK);
            //Render Background
            DrawTexture (back_Ground, 0, 0, WHITE);


            
            //Hitboxes
            DrawRectangleRec (bullet, BLANK);
            DrawRectangleRec (enemy1, BLANK);
            DrawRectangleRec (enemy2, BLANK);
            //DrawShip
            DrawTextureRec (
                Ship,
                Rectangle {(framWidth * frame), 0, framWidth, (float)Ship.height},
                Vector2 { player.xpos, player.ypos},
                RAYWHITE
            );

            //DrawBullet
            DrawTextureRec (
                bullet_anim,
                Rectangle {(bullet_Framewidth * frame), 0, bullet_Framewidth, (float)bullet_anim.height},
                Vector2 {bull_x, bull_y},
                RAYWHITE
            );

            //DrawEnemy
            /*
                Enemy1
            */
            DrawTextureRec (
                enemy_Anim,
                Rectangle {(enemy_Framewidth * frame), 0, enemy_Framewidth, (float)enemy_Anim.height},
                Vector2 {ghost_1.xpos, ghost_1.ypos},
                RAYWHITE
            );
            /*
                Enemy2
            */
            DrawTextureRec (
                enemy_Anim,
                Rectangle {(enemy_Framewidth * frame), 0, enemy_Framewidth, (float)enemy_Anim.height},
                Vector2 {ghost_2.xpos, ghost_2.ypos},
                RAYWHITE
            );

            //Render Main Player Hit Box
            DrawRectangleRec (Main_Player, BLANK);            
            
            //Score
            DrawText (TextFormat("Score: %0i", score), 0, 0, 40, ORANGE);
            DrawText (TextFormat("Hi-Score: %0i", Hi_Score), 0, 40, 40, ORANGE);
            DrawText (TextFormat("Life: %0i", Life), 0, 750, 40, ORANGE);
            DrawFPS (500, 0);
        EndDrawing();
    }



    CloseWindow();


    return 0;

}
