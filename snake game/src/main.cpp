/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "stdio.h"
static void loopwork(void);
static void initgame(void);

typedef enum {
    //STORAGE_POSITION_SCORE      = 0,
    STORAGE_POSITION_HISCORE    = 1
} StorageData;


Vector2 arr[251];
Vector2 snakePosition[251];
Vector2 apppos;
Vector2 offset={15.0,15.0};
int framescounter=120;
const int screenWidth = 800;
const int screenHeight = 600;
float speed =20.0f;
int snakesize=20;
int dir=2;
int ctr=0;

int main(void)
{
    // Initialization

    bool front=false;
    bool turn=true;
    
    
    int appsize=10;
    //int headsize=24;
    int fcounter=0;
    int hiscore = LoadStorageValue(STORAGE_POSITION_HISCORE);
    printf(TextFormat("High Score: %i", hiscore));
    bool gameover=false;
    bool growth=true;    
    //double time=0.0;

    
  
    
    //Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Snake");
    initgame();
    hiscore = LoadStorageValue(STORAGE_POSITION_HISCORE);
    // Main game loop

    LOOP:
    while (!WindowShouldClose() && !gameover)    // Detect window close button or ESC key
    {   //hiscore = LoadStorageValue(STORAGE_POSITION_HISCORE);
        if (ctr>hiscore)
        {
            hiscore=ctr;
            //SaveStorageValue(STORAGE_POSITION_HISCORE, ctr);
        }
        if ((int(ctr%10)==0)&& ctr!=0&&growth)
        {
            snakesize+=2;
            speed+=2;
            growth=false;
        }
        //out of window
        if(arr[0].x>screenWidth)
       {
           arr[0].x=0.0f;
       }
       if(arr[0].x<0)
       {
           arr[0].x=screenWidth;
       }
       if(arr[0].y>screenHeight)
       {
           arr[0].y=0.0f;
       }
       if(arr[0].y<0)
       {
           arr[0].y=screenHeight;
       }
        framescounter++;
        fcounter++;
        //apple collision
        if ((arr[0].x < (apppos.x + appsize) && ((arr[0].x + snakesize) > apppos.x) &&
                (arr[0].y < (apppos.y + appsize) && (arr[0].y + snakesize) > apppos.y)))
        {
           ctr++; 
           loopwork();
           growth=true;
        }
        //body collision
        for (int i = 1; i <=ctr; i++)
            {
                if ((arr[0].x == arr[i].x) && (arr[0].y == arr[i].y)) {
                    printf("game over");
                    SaveStorageValue(STORAGE_POSITION_HISCORE, ctr);
                    gameover=true;
                    break;
            
            }
            }
        //apple spawning
        if((framescounter/180)%2==1)
        {
            loopwork();
        }
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT )&& turn) {dir=0;turn=false;front=true;}//ballPosition.x += 4.0f;}
        if (IsKeyDown(KEY_LEFT)&& turn) {dir=1;turn=false;front=true;}//ballPosition.x -= 4.0f;}
        if (IsKeyDown(KEY_UP)&&front) {dir=2;turn=true;front=false;}//ballPosition.y -= 4.0f;}
        if (IsKeyDown(KEY_DOWN)&&front) {dir=3;turn=true;front=false;}//ballPosition.y += 4.0f;}
        if (IsKeyDown(KEY_SPACE))
            {arr[1]={(float)arr[0].x,(float)arr[0].y};}
        /*if(IsKeyPressed(KEY_R))
        {
            ctr++;
            growth=true;
        }*/

    //previous position for body   
    for (int i = 0; i < ctr; i++){ 
    
    
    snakePosition[i]=arr[i];
    }
    
    //will execute 20 times in a sec
      if(fcounter>3)
    {   //snake movement
        if(dir==1)
        {
            arr[0].x -= speed;
        }
        else if(dir==2)
        {
            arr[0].y -= speed;
        }
        else if(dir==3)
        {
            arr[0].y += speed;
        }
        else{
            arr[0].x += speed;
        }
    if(ctr!=0){
    //snake body movement
    for(int i=1;i<=ctr;i++)
    {

        arr[i]=snakePosition[i-1];
    
    }
       
        } 
         fcounter=0;   
    }

    
        
       
        
        BeginDrawing();

            DrawText(TextFormat("apples eaten: %i", ctr), 10, 10, 30, DARKBLUE);
             DrawText(TextFormat("High Score: %i", hiscore), 10, 40, 30, DARKBLUE);
            ClearBackground(GRAY);
            DrawRectangleV(apppos, {(float)appsize,(float)appsize}, RED);
                DrawRectangleV(arr[0], {(float)snakesize,(float)snakesize},DARKGREEN);
            for(int i=1;i<=ctr;i++){
            
                 DrawRectangleV(arr[i], {(float)snakesize,(float)snakesize},GREEN);
            }
            


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    while (!WindowShouldClose() && gameover)
    {
        BeginDrawing();
        DrawText(TextFormat("Yuo DED NOOB"), screenWidth/2-MeasureText("Yuo DED NOOB", 50)/2, screenHeight/2, 50, RED);
        DrawText(TextFormat("PRESS ENTER TO RESTART"), screenWidth/2-MeasureText("PRESS ENTER TO RESTART", 50)/2, (screenHeight/2)+50, 50, RED);
        if(IsKeyPressed(KEY_ENTER))
        {
            initgame();
            gameover=false;
            goto LOOP;
        }
        EndDrawing();
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void loopwork(void)
{
            apppos.x=GetRandomValue(0,screenWidth);
            apppos.y=GetRandomValue(0,screenHeight);
            framescounter=0;
}
void initgame(void)
{   
    dir=2;
   speed =20.0f;
    snakesize=20;
    for (int i=0;i<251;i++)
    {
        arr[i]={0.0,0.0};
    }
    arr[0] = { (float)screenWidth/2, (float)screenHeight/2 };
    ctr=0;
}