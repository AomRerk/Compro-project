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
    MEMBER,
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
static int framesCounter = 1800;

static const int screenWidth = 1280;
static const int screenHeight = 720;

static Umbrella bolly = { 0 };
static Meteor baht10baht[MAX_MEDIUM_METEORS] = { 0 };
static Meteor baht1baht[MAX_SMALL_METEORS] = { 0 };

int main(void)
{
    
    InitWindow(screenWidth, screenHeight, "Drop Some Money");

    GameScreen currentScreen = LOGO;
    int brek = 0;

    Image firstImage = LoadImage("./Pic/firstnew.png");
    ImageResize(&firstImage, screenWidth, screenHeight);
    Texture2D firstTexture = LoadTextureFromImage(firstImage);

    Image kum1 = LoadImage("./Pic/kumkom.png");
    Texture2D kumkom1 = LoadTextureFromImage(kum1);

    Image kum2 = LoadImage("./Pic/kumkom2.png");
    Texture2D kumkom2 = LoadTextureFromImage(kum2);

    Image kum3 = LoadImage("./Pic/kumkom3.png");
    Texture2D kumkom3 = LoadTextureFromImage(kum3);

    Image kum4 = LoadImage("./Pic/kumkom4.png");
    Texture2D kumkom4 = LoadTextureFromImage(kum4);

    Image kum5 = LoadImage("./Pic/kumkom5.png");
    Texture2D kumkom5 = LoadTextureFromImage(kum5);


    Image button1 = LoadImage("./Pic/Group-button.png");
    //ImageResize(&button, 240, 120);
    Texture2D startpic = LoadTextureFromImage(button1);

    Image button2 = LoadImage("./Pic/Group 2.png");
    ImageResize(&button2, button2.width/1.5, button2.height/1.5);
    Texture2D mempic = LoadTextureFromImage(button2);

    Image Umbrellaaa = LoadImage("./Pic/umbrella2.png");
    ImageResize(&Umbrellaaa, Umbrellaaa.width/2, Umbrellaaa.height/2);
    Texture2D Umbrell = LoadTextureFromImage(Umbrellaaa);

    Image onebaht = LoadImage("./Pic/1.png");
    ImageResize(&onebaht, onebaht.width/2, onebaht.height/2);
    Texture2D one = LoadTextureFromImage(onebaht); 

    Image tenbaht = LoadImage("./Pic/10.png");
    ImageResize(&tenbaht, tenbaht.width/1.2, tenbaht.height/1.2);
    Texture2D ten = LoadTextureFromImage(tenbaht);

    Image member = LoadImage("./Pic/credit.png");
    
    Texture2D members = LoadTextureFromImage(member);

    float startframeHeight = (float)startpic.height / NUM_FRAMES;
    float memframeHeight = (float)mempic.height / NUM_FRAMES;
    Rectangle startrec = {0, 0, (float)startpic.width, startframeHeight};
    Rectangle memrec = {0, 0, (float)mempic.width, memframeHeight};
    Rectangle startbotton = {screenWidth / 2.0f - startpic.width / 2.0f, 350, (float)startpic.width, startframeHeight};
    Rectangle memberbotton = {screenWidth / 2.0f - mempic.width / 2.0f, 520, (float)mempic.width, memframeHeight};
    
    int startbottonstate = 0;
    int memberbottonstate = 0;
    Vector2 mousePoint = {0.0f, 0.0f};
    int countdown = 240;
    int gameover = 1,start=1,score=0;
    int kumkomtee;
    int cooldown = 30;

    SetTargetFPS(60); 
    
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        mousePoint = GetMousePosition();
        //bool startbottonAction = false;
        //bool memberbottonAction = false;
        switch (currentScreen)
        {
        case LOGO:
        {
            if (cooldown>0){
                cooldown--;
            }
            else{
                kumkomtee = GetRandomValue(0, 4);

                if (CheckCollisionPointRec(mousePoint, startbotton))
                {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
                        startbottonstate = 2;
                    }
                    else
                    {
                        startbottonstate = 1;
                    }
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                    {
                        //startbottonAction = true;
                        currentScreen = TITLE;
                    }
                }
                else
                    startbottonstate = 0;
                startrec.y = startbottonstate * startframeHeight;

                if (CheckCollisionPointRec(mousePoint, memberbotton))
                {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
                        memberbottonstate = 2;
                    }
                    else
                    {
                        memberbottonstate = 1;
                    }
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                    {
                        //memberbottonAction = true;
                        currentScreen = MEMBER;
                    }
                }
                else
                    memberbottonstate = 0;
                memrec.y = memberbottonstate * memframeHeight;

                
            }
           

        }
        break;
        case MEMBER:
        {
            
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = LOGO;
                    cooldown = 30;
                }
        }
        break;
        case TITLE:
        {
            
            brek++;
            for (int j = 0; j < MAX_SMALL_METEORS; j++)
                    {
                    baht10baht[j].position = (Vector2){-100, 0};
                    baht10baht[j].speed = (Vector2){0, 0};
                    baht1baht[j].position = (Vector2){-100, 0};
                    baht1baht[j].speed = (Vector2){0, 0};
                    }
            bolly.position = (Vector2){ screenWidth/2, screenHeight*7/8 };
            bolly.size = (Vector2){ screenWidth/10, 20 };
            score = 0;
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
            int  vely;
            //velx,
            bool correctRange = false;

            // TODO: Update GAMEPLAY screen variables here!

            // Press enter to change to ENDING screen
            //321
            // ร่ม ขนาดร่ม x เปลี่ยนตามkeyleft keyright
            //แรนดอม ความเร็ว ขนาด ตำแหน่ง x เหรียญ y+++++++
            //คะแนนเมื่อเหรียญชนร่ม
            if (IsKeyPressed(KEY_X)){
                    currentScreen = ENDING;
                    break;
                }
            if (gameover&&start){
                framesCounter = 1800;
                
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

                                //velx = GetRandomValue(1, METEORS_SPEED);
                                vely = GetRandomValue(1, METEORS_SPEED);
                                baht10baht[i].position = (Vector2){posx, posy};
                                baht10baht[i].speed = (Vector2){0, vely};
                                baht10baht[i].radius = 60;
                                baht10baht[i].active = true;
                                baht10baht[i].color = GREEN;
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
                                //velx = GetRandomValue(1, METEORS_SPEED);
                                vely = GetRandomValue(1, METEORS_SPEED);
                                baht1baht[i].position = (Vector2){posx, posy};
                                baht1baht[i].speed = (Vector2){0, vely};
                                baht1baht[i].radius = 40;
                                baht1baht[i].active = true;
                                baht1baht[i].color = YELLOW;
                            }
                        correctRange = false;




                    }
                
            //
                        
                    
            }
            }
            
            else if (gameover&&!start){
                
                if (IsKeyPressed(KEY_R)){
                    currentScreen = TITLE;
                    start = 1;
                    kumkomtee = GetRandomValue(0, 4);
                    break;
                }
                framesCounter--;
                if (IsKeyDown(KEY_LEFT)) bolly.position.x -= 10;
                if ((bolly.position.x - bolly.size.x/2) <= 0) bolly.position.x = bolly.size.x/2;
                if (IsKeyDown(KEY_RIGHT)) bolly.position.x += 10;
                if ((bolly.position.x + bolly.size.x/2) >= screenWidth) bolly.position.x = screenWidth - bolly.size.x/2;
                //
                
               
            
                for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
                    {
                        if (baht10baht[i].active)
                        {
                            // movement
                           // baht10baht[i].position.x += baht10baht[i].speed.x;
                            baht10baht[i].position.y += baht10baht[i].speed.y;
                            if (CheckCollisionCircleRec(baht10baht[i].position, baht10baht[i].radius,(Rectangle){ bolly.position.x - bolly.size.x/2, bolly.position.y - bolly.size.y/2, bolly.size.x, bolly.size.y}))
                            {
                                //if (baht10baht[i].position.y == 450){
                                posx = GetRandomValue(0, screenWidth);
                                baht10baht[i].position = (Vector2){posx, -(baht10baht[i].radius)};
                                //baht10baht[i].position.y = -(baht10baht[i].radius);
                                

                                score += 10;
                            //}
                            
                            }
                            // wall behaviour
                            //if  (baht10baht[i].position.x > screenWidth + baht10baht[i].radius) baht10baht[i].position.x = -(baht10baht[i].radius);
                            //else if (baht10baht[i].position.x < 0 - baht10baht[i].radius) baht10baht[i].position.x = screenWidth + baht10baht[i].radius;
                            if (baht10baht[i].position.y > screenHeight + baht10baht[i].radius) 
                            {
                                posx = GetRandomValue(0, screenWidth);
                                baht10baht[i].position = (Vector2){posx, -(baht10baht[i].radius)};
                            }
                            
                            else if (baht10baht[i].position.y < 0 - baht10baht[i].radius) baht10baht[i].position.y = screenHeight + baht10baht[i].radius;
                        }
                    }

                    for (int i = 0; i < MAX_SMALL_METEORS; i++)
                    {
                        if (baht1baht[i].active)
                        {
                            // movement
                            //baht1baht[i].position.x += baht1baht[i].speed.x;
                            baht1baht[i].position.y += baht1baht[i].speed.y;
                            if (CheckCollisionCircleRec(baht1baht[i].position, baht1baht[i].radius,(Rectangle){ bolly.position.x - bolly.size.x/2, bolly.position.y - bolly.size.y/2, bolly.size.x, bolly.size.y}))
                            {
                                //if (baht1baht[i].position.y == 450){
                                posx = GetRandomValue(0, screenWidth);
                                baht1baht[i].position = (Vector2){posx, -(baht1baht[i].radius)};
                                //baht1baht[i].position.y = -(baht1baht[i].radius);
                                score++;
                            //}
                            
                            }
                            // wall behaviour
                            //if  (baht1baht[i].position.x > screenWidth + baht1baht[i].radius) baht1baht[i].position.x = -(baht1baht[i].radius);
                            //else if (baht1baht[i].position.x < 0 - baht1baht[i].radius) baht1baht[i].position.x = screenWidth + baht1baht[i].radius;
                            if (baht1baht[i].position.y > screenHeight + baht1baht[i].radius)
                            {
                                posx = GetRandomValue(0, screenWidth);
                                baht1baht[i].position = (Vector2){posx, -(baht1baht[i].radius)};
                            }
                            else if (baht1baht[i].position.y < 0 - baht1baht[i].radius) baht1baht[i].position.y = screenHeight + baht1baht[i].radius;
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
           
            if (framesCounter == 0)
            {
                currentScreen = ENDING;
                start = 1;
            }

            
        }
        break;
        case ENDING:
        {
            
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = LOGO;
                cooldown = 30;
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
         
            DrawTextureRec(firstTexture, (Rectangle){0, 0, 1280.0, 720.0}, (Vector2){0, 0}, WHITE);

            DrawTextureRec(startpic, startrec, (Vector2){startbotton.x, startbotton.y}, WHITE);

            DrawTextureRec(mempic, memrec, (Vector2){memberbotton.x, memberbotton.y}, WHITE);
        }
        break;
        case TITLE:
        {
           
            if (kumkomtee == 0){DrawTextureRec(kumkom1, (Rectangle){0, 0, 1280.0, 720.0}, (Vector2){0, 0}, WHITE);}
            else if (kumkomtee == 1){DrawTextureRec(kumkom2, (Rectangle){0, 0, 1280.0, 720.0}, (Vector2){0, 0}, WHITE);}
            else if (kumkomtee == 2){DrawTextureRec(kumkom3, (Rectangle){0, 0, 1280.0, 720.0}, (Vector2){0, 0}, WHITE);}
            else if (kumkomtee == 3){DrawTextureRec(kumkom4, (Rectangle){0, 0, 1280.0, 720.0}, (Vector2){0, 0}, WHITE);}
            else if (kumkomtee == 4){DrawTextureRec(kumkom5, (Rectangle){0, 0, 1280.0, 720.0}, (Vector2){0, 0}, WHITE);}
            
            
        }
        break;
        case MEMBER:
        {
         
            
            DrawTextureRec(members, (Rectangle){0, 0, 1280.0, 720.0}, (Vector2){0, 0}, WHITE);
            DrawText("PRESS ENTER or CLICK to GET BACK", (screenWidth/2)-200, 600, 20, WHITE);
            
        }
        break;
        case GAMEPLAY:
        {
      
            DrawRectangle(0, 0, screenWidth, screenHeight, SKYBLUE);
            
            
            for (int i = 0;i < MAX_MEDIUM_METEORS; i++)
            {
                if (baht10baht[i].active) DrawCircleV(baht10baht[i].position, baht10baht[i].radius, BLANK);
                else DrawCircleV(baht10baht[i].position, baht10baht[i].radius, Fade(BLANK, 0.3f));
                DrawTextureRec(ten, (Rectangle){0, 0, ten.width, ten.height}, (Vector2){baht10baht[i].position.x-60, baht10baht[i].position.y-60}, GRAY);
                

            for (int i = 0;i < MAX_SMALL_METEORS; i++)
            {
                if (baht1baht[i].active) DrawCircleV(baht1baht[i].position, baht1baht[i].radius, BLANK);
                else DrawCircleV(baht1baht[i].position, baht1baht[i].radius, Fade(BLANK, 0.3f));
                DrawTextureRec(one, (Rectangle){0, 0, one.width, one.height}, (Vector2){baht1baht[i].position.x-40, baht1baht[i].position.y-40}, GRAY);
            }
                
            }
            DrawText(TextFormat("TIME: %.02f", (float)framesCounter/60), 10, 50, 20, BLACK);
            DrawText(TextFormat("SCORE: %d", (int)score), 10, 70, 20, BLACK);
          
            DrawTextureRec(Umbrell, (Rectangle){0, 0, Umbrell.width, Umbrell.height}, (Vector2){bolly.position.x - bolly.size.x, 450}, WHITE);
     
            

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
                    DrawText(TextFormat("press <-- or --> to control your brolly"),(screenWidth/2)-475, (screenHeight/2)-55, 50, (Color){ 255, 255, 255, 255 });
                    DrawText(TextFormat("press X skip to scoreboard"),(screenWidth/2)-220, (screenHeight/2)+60, 30, (Color){ 255, 255, 255, 150 });
                    DrawText(TextFormat("press R to restart"),(screenWidth/2)-130, (screenHeight/2)+90, 30, (Color){ 255, 255, 255, 150 });
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
    
            DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
      
           
            DrawText(TextFormat("SCORE:%04d", score),(screenWidth/2)-300 , (screenHeight/2)-100, 100, WHITE);
            DrawText("PRESS ENTER or CLICK to RETURN to MAIN MENU", (screenWidth/2)-255, 600, 20, DARKBLUE);
        }
        break;
        default:
            break;
        }

        DrawFPS(10, 10);

        EndDrawing();
        
    }


    UnloadTexture(startpic);
    CloseWindow(); 

    return 0;
}

