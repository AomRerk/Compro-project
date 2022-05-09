/*******************************************************************************************
 *
 *   raylib [core] example - Basic 3d example
 *
 *   Welcome to raylib!
 *
 *   To compile example, just press F5.
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_FRAMES 3

#define METEORS_SPEED       10
#define MAX_MEDIUM_METEORS  5
#define MAX_SMALL_METEORS   5


typedef enum GameScreen
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
} GameScreen;

typedef struct Umbrella
{
    Vector2 position;
    Vector2 size;
} Umbrella;

typedef struct Meteor {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
    Color color;
} Meteor;


////////////////////
static int framesCounter = 600;

static const int screenWidth = 1280;
static const int screenHeight = 720;

static Umbrella bolly = { 0 };
static Meteor mediumMeteor[MAX_MEDIUM_METEORS] = { 0 };
static Meteor smallMeteor[MAX_SMALL_METEORS] = { 0 };

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "Drop Some Money");

    GameScreen currentScreen = LOGO;
    int brek = 0;

    Image firstImage = LoadImage("./Pic/firstnew.png");
    ImageResize(&firstImage, screenWidth, screenHeight);
    Texture2D firstTexture = LoadTextureFromImage(firstImage);

    Image kumkom = LoadImage("./Pic/kumkom2.png");
    // ImageResize(&kumkom, screenWidth, screenHeight);
    Texture2D kumkompage = LoadTextureFromImage(kumkom);

    Image button = LoadImage("./Pic/button (1).png");
    //ImageResize(&button, 240, 120);
    Texture2D button2 = LoadTextureFromImage(button);

    Image Umbrellaaa = LoadImage("./Pic/umbrella2.png");
    ImageResize(&Umbrellaaa, Umbrellaaa.width/2, Umbrellaaa.height/2);
    Texture2D Umbrell = LoadTextureFromImage(Umbrellaaa);

    Image onebaht = LoadImage("./Pic/1.png");
    ImageResize(&onebaht, onebaht.width/2, onebaht.height/2);
    Texture2D one = LoadTextureFromImage(onebaht); 

    Image tenbaht = LoadImage("./Pic/10.png");
    ImageResize(&tenbaht, tenbaht.width/1.2, tenbaht.height/1.2);
    Texture2D ten = LoadTextureFromImage(tenbaht);

    float frameHeight = (float)button2.height / NUM_FRAMES;
    Rectangle sourceRec = {0, 0, (float)button2.width, frameHeight};
    Rectangle btnBounds = {screenWidth / 2.0f - button2.width / 2.0f, screenHeight / 2.0f - button2.height / NUM_FRAMES / 2.0f, (float)button2.width, frameHeight};
    int btnState = 0;
    bool btnAction = false;
    Vector2 mousePoint = {0.0f, 0.0f};
    int countdown = 240;
    int gameover = 1,start=1,score=0;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
// ----------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        mousePoint = GetMousePosition();
        btnAction = false;
        switch (currentScreen)
        {
        case LOGO:
        {
            // TODO: Update LOGO screen variables here!

            if (CheckCollisionPointRec(mousePoint, btnBounds))
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    btnState = 2;
                }
                else
                {
                    btnState = 1;
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    btnAction = true;
                    currentScreen = TITLE;
                }
            }
            else
                btnState = 0;
            sourceRec.y = btnState * frameHeight;
        }
        break;
        case TITLE:
        {
            // TODO: Update TITLE screen variables here!
            brek++;
            for (int j = 0; j < MAX_SMALL_METEORS; j++)
                    {
                    mediumMeteor[j].position = (Vector2){-100, 0};
                    mediumMeteor[j].speed = (Vector2){0, 0};
                    smallMeteor[j].position = (Vector2){-100, 0};
                    smallMeteor[j].speed = (Vector2){0, 0};
                    }
            bolly.position = (Vector2){ screenWidth/2, screenHeight*7/8 };
            bolly.size = (Vector2){ screenWidth/10, 20 };
            // Press enter to change to GAMEPLAY screen
            if (brek > 180)
            {
                brek = 0;
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            int posx, posy;
            int velx, vely;
            
            bool correctRange = false;

            // TODO: Update GAMEPLAY screen variables here!

            // Press enter to change to ENDING screen
            //321
            // ร่ม ขนาดร่ม x เปลี่ยนตามkeyleft keyright
            //แรนดอม ความเร็ว ขนาด ตำแหน่ง x เหรียญ y+++++++
            //คะแนนเมื่อเหรียญชนร่ม
            if (gameover&&start){
                framesCounter = 600;
                
                posx = GetRandomValue(0, screenWidth);
                
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP) || countdown < 240)
                {
                    countdown -= 1;
                    if (countdown == 0)
                    {
                        countdown = 240;
                        start = 0;
                        bolly.position = (Vector2){ screenWidth/2, screenHeight*7/8 };
                        bolly.size = (Vector2){ screenWidth/10, 20 };
                        //
                        for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
                            {
                                posx = GetRandomValue(0, screenWidth);
                                posy = 0;

                                velx = GetRandomValue(1, METEORS_SPEED);
                                vely = GetRandomValue(1, METEORS_SPEED);
                                mediumMeteor[i].position = (Vector2){posx, posy};
                                mediumMeteor[i].speed = (Vector2){0, vely};
                                mediumMeteor[i].radius = 60;
                                mediumMeteor[i].active = true;
                                mediumMeteor[i].color = GREEN;
                            }
                        correctRange = false;
                        for (int i = 0; i < MAX_SMALL_METEORS; i++)
                            {
                                posx = GetRandomValue(0, screenWidth);

                                while (!correctRange)
                                {
                                    if (posx > screenWidth/2 - 150 && posx < screenWidth/2 + 150) posx = GetRandomValue(0, screenWidth);
                                    else correctRange = true;
                                }

                                correctRange = false;


                                correctRange = false;
                                velx = GetRandomValue(1, METEORS_SPEED);
                                vely = GetRandomValue(1, METEORS_SPEED);
                                smallMeteor[i].position = (Vector2){posx, posy};
                                smallMeteor[i].speed = (Vector2){0, vely};
                                smallMeteor[i].radius = 40;
                                smallMeteor[i].active = true;
                                smallMeteor[i].color = YELLOW;
                            }
                        correctRange = false;




                    }
                
            //
                        
                    
            }
            }
            
            else if (gameover&&!start){
                
                framesCounter--;
                if (IsKeyDown(KEY_LEFT)) bolly.position.x -= 10;
                if ((bolly.position.x - bolly.size.x/2) <= 0) bolly.position.x = bolly.size.x/2;
                if (IsKeyDown(KEY_RIGHT)) bolly.position.x += 10;
                if ((bolly.position.x + bolly.size.x/2) >= screenWidth) bolly.position.x = screenWidth - bolly.size.x/2;
                //
                
               
            
                for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
                    {
                        if (mediumMeteor[i].active)
                        {
                            // movement
                           // mediumMeteor[i].position.x += mediumMeteor[i].speed.x;
                            mediumMeteor[i].position.y += mediumMeteor[i].speed.y;
                            if (CheckCollisionCircleRec(mediumMeteor[i].position, mediumMeteor[i].radius,(Rectangle){ bolly.position.x - bolly.size.x/2, bolly.position.y - bolly.size.y/2, bolly.size.x, bolly.size.y}))
                            {
                                //if (mediumMeteor[i].position.y == 450){
                                posx = GetRandomValue(0, screenWidth);
                                mediumMeteor[i].position = (Vector2){posx, -(mediumMeteor[i].radius)};
                                //mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
                                

                                score += 10;
                            //}
                            
                            }
                            // wall behaviour
                            //if  (mediumMeteor[i].position.x > screenWidth + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
                            //else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = screenWidth + mediumMeteor[i].radius;
                            if (mediumMeteor[i].position.y > screenHeight + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
                            else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = screenHeight + mediumMeteor[i].radius;
                        }
                    }

                    for (int i = 0; i < MAX_SMALL_METEORS; i++)
                    {
                        if (smallMeteor[i].active)
                        {
                            // movement
                            //smallMeteor[i].position.x += smallMeteor[i].speed.x;
                            smallMeteor[i].position.y += smallMeteor[i].speed.y;
                            if (CheckCollisionCircleRec(smallMeteor[i].position, smallMeteor[i].radius,(Rectangle){ bolly.position.x - bolly.size.x/2, bolly.position.y - bolly.size.y/2, bolly.size.x, bolly.size.y}))
                            {
                                //if (smallMeteor[i].position.y == 450){
                                posx = GetRandomValue(0, screenWidth);
                                smallMeteor[i].position = (Vector2){posx, -(smallMeteor[i].radius)};
                                //smallMeteor[i].position.y = -(smallMeteor[i].radius);
                                score++;
                            //}
                            
                            }
                            // wall behaviour
                            //if  (smallMeteor[i].position.x > screenWidth + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
                            //else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = screenWidth + smallMeteor[i].radius;
                            if (smallMeteor[i].position.y > screenHeight + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
                            else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = screenHeight + smallMeteor[i].radius;
                        }
                    }
                    

            }
            
            
            else{
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                currentScreen = ENDING;
                start = 1;
                }
            }
            //
            
            //
            

            //
            
            //if (CheckCollisionCircleRec(me.position, me.radius,
                //(Rectangle){ bolly.position.x - bolly.size.x/2, bolly.position.y - bolly.size.y/2, bolly.size.x, bolly.size.y}))
            //{
                //score++;
            //}
            if (framesCounter == 0)
            {
                currentScreen = ENDING;
                start = 1;
            }

            
        }
        break;
        case ENDING:
        {
            // TODO: Update ENDING screen variables here!

            // Press enter to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = LOGO;
            }
        }
        break;
        default:
            break;
        }

        BeginDrawing();

        switch (currentScreen)
        {
        case LOGO:
        {
            // TODO: Draw LOGO screen here!
            DrawTextureRec(firstTexture, (Rectangle){0, 0, 1280.0, 720.0}, (Vector2){0, 0}, WHITE);
            DrawTextureRec(button2, sourceRec, (Vector2){btnBounds.x, btnBounds.y}, WHITE);
        }
        break;
        case TITLE:
        {
            // TODO: Draw TITLE screen here!
            
            DrawTextureRec(kumkompage, (Rectangle){0, 0, 1280.0, 720.0}, (Vector2){0, 0}, WHITE);
            
        }
        break;
        case GAMEPLAY:
        {
            // TODO: Draw GAMEPLAY screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, SKYBLUE);
            
            
            for (int i = 0;i < MAX_MEDIUM_METEORS; i++)
            {
                if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, BLANK);
                else DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, Fade(BLANK, 0.3f));
                DrawTextureRec(ten, (Rectangle){0, 0, ten.width, ten.height}, (Vector2){mediumMeteor[i].position.x-60, mediumMeteor[i].position.y-60}, GRAY);
                

            for (int i = 0;i < MAX_SMALL_METEORS; i++)
            {
                if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, BLANK);
                else DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, Fade(BLANK, 0.3f));
                DrawTextureRec(one, (Rectangle){0, 0, one.width, one.height}, (Vector2){smallMeteor[i].position.x-40, smallMeteor[i].position.y-40}, GRAY);
            }
                
            }
            DrawText(TextFormat("TIME: %.02f", (float)framesCounter/60), 10, 50, 20, BLACK);
            DrawText(TextFormat("SCORE: %d", (int)score), 10, 70, 20, BLACK);
            //DrawRectangle(bolly.position.x - bolly.size.x/2, bolly.position.y - bolly.size.y/2, bolly.size.x, bolly.size.y, BLACK);
            DrawTextureRec(Umbrell, (Rectangle){0, 0, Umbrell.width, Umbrell.height}, (Vector2){bolly.position.x - bolly.size.x, 450}, WHITE);
            //DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
            

            if (gameover&&start){
                if (countdown < 240){
                    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){ 0, 0, 0, 150 });
                    if ((int)countdown/60 == 0 )
                    {
                        DrawText(TextFormat("GO!"),(screenWidth/2)-50, (screenHeight/2)-50, 100, WHITE);
                    }
                    else
                    {
                        DrawText(TextFormat("%d", (int)countdown/60),(screenWidth/2), (screenHeight/2)-50, 100, WHITE);
                    }
                    
                    
                }
                else{
                    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){ 0, 0, 0, 150 });
                    DrawText("PRESS ENTER or CLICK to PLAY", (screenWidth/2)-160, 600, 20, WHITE);
                }
                
            }

            if ((float)framesCounter/60 < 4 && (int)framesCounter/60 != 0 )
            {
                DrawText(TextFormat("%d", (int)framesCounter/60),(screenWidth/2), (screenHeight/2)-50, 100, WHITE);
            }
            
        }
        break;
        case ENDING:
        {
            // TODO: Draw ENDING screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
            //DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText(TextFormat("SCORE:%d", score),(screenWidth/2) -200, (screenHeight/2)-100, 100, WHITE);
            DrawText("PRESS ENTER or CLICK to RETURN to MAIN MENU", (screenWidth/2)-255, 600, 20, DARKBLUE);
        }
        break;
        default:
            break;
        }

        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(button2);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

