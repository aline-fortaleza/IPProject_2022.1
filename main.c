#include "raylib.h"
#include <math.h>
#include "car.c"
#include "player.c"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "colisao.c"








#define INITMENU 10
#define RULES 11
#define GAME 12
#define UPGRADE 13
#define LOST 14

int main()
{
   
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

   

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    Texture2D carTexture = LoadTexture("SportsRacingCar_0.png");
    Texture2D playerTexture = LoadTexture("Assets/CharacterSprites/PlayerIdleLeft.png");
    Texture2D backgroundTexture = LoadTexture("fundojogo.png");
    Texture2D menuTexture = LoadTexture("menu.png");
    Texture2D rulesTexture = LoadTexture("rules2.0.png");
    Texture2D lostTexture = LoadTexture("lost.png");
    

    




    Rectangle exemplo;

   
    exemplo.x = 0;
    exemplo.y = 0;
    exemplo.height = 10;
    exemplo.y = 10;

    int Wave = 1;
    int Numbercars = 4 * Wave;
    Car *cars;
    cars = malloc(sizeof(Car)*Numbercars);
    for(int i = 0; i < Numbercars; i++){
        if(i % 2 == 0){
        cars[i] = (Car){rand() % 2250 , 25, exemplo, 0, 5, 70, 5, AIMING, 0, false, false};
        }else{
        cars[i] = (Car){rand() % 2250 , 2250, exemplo, 0, 5, 70, 5, AIMING, 0, false, false};
        }  
    }
    Rectangle playerCollision;
    playerCollision.x = 100;
    playerCollision.y = 100;
    playerCollision.width = 30;
    playerCollision.height = 35;
    Player player = (Player){400, 400, 0, 50, playerCollision, exemplo, 5, 5, false, true, true, 2};
    
    
    

   Rectangle walls[4];
    walls[0].x = 00;
    walls[0].y = 00;
    walls[0].width = 2250;
    walls[0].height = 5;
    walls[1].x = 00;
    walls[1].y = 00;
    walls[1].width = 5;
    walls[1].height = 2250;
    walls[2].x = 2250;
    walls[2].y = 0;
    walls[2].width = 5;
    walls[2].height = 2250;
    walls[3].x = 0;
    walls[3].y = 2250;
    walls[3].width = 2250;
    walls[3].height = 5; 


    




    Rectangle walls_player[4];
    walls_player[0].x = 335;
    walls_player[0].y = 335;
    walls_player[0].width = 1580;
    walls_player[0].height = 5;
    walls_player[1].x = 335;
    walls_player[1].y = 335;
    walls_player[1].width = 5;
    walls_player[1].height = 1580;
    walls_player[2].x = 1915;
    walls_player[2].y = 335;
    walls_player[2].width = 5;
    walls_player[2].height = 1580;
    walls_player[3].x = 335;
    walls_player[3].y = 1915;
    walls_player[3].width = 1580;
    walls_player[3].height = 5;

    
    float mainTimer = 0;
    Rectangle spikeCollision;
    spikeCollision.x = 700;
    spikeCollision.y = 700;
    spikeCollision.width = 55;
    spikeCollision.height = 55;
    Texture2D spikeTexture = LoadTexture("spike.png");
    Spikes spike;
    spike.posX = 700;
    spike.posY = 700;
    spike.spikeCollision = spikeCollision;
    char playerlife[5];
    char playerPosX[5];
    char playerPosY[5];
    char CarsDestorided[5];
    char waveChar[10] = "WAVE:";
    char waveNumber[3];
    int carsDestroyed = 0; 

    Camera2D cam;
    cam.offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/2};
    cam.rotation = 0;
    cam.zoom = 1.2;
    

    
    Vector2 selectorPosition = {(int) (menuTexture.width/2) +150, (int) 550 };
    bool PRESS_UP = false;
    bool PRESS_DOWN = false; 
    int mode = INITMENU; 
      
    while (!WindowShouldClose()){    
        
        switch(mode){
            case INITMENU:
                if (IsKeyDown(KEY_UP) == true && selectorPosition.y != 550 && PRESS_UP == false) {
                    
                    selectorPosition.y -= 100;
                    PRESS_UP = true;
                       
                }
                if(IsKeyDown(KEY_UP) == false) {
                    PRESS_UP = false;
                }
                if (IsKeyDown(KEY_DOWN) == true && selectorPosition.y != 750 && PRESS_DOWN == false) {
                     
                   selectorPosition.y += 100;
                   PRESS_DOWN = true;
                }
                if(IsKeyDown(KEY_DOWN) == false) {
                    PRESS_DOWN = false;
                }

                if(IsKeyDown(KEY_ENTER) == true && selectorPosition.y == 550){
                    EndDrawing();
                    mode = GAME;

                }
                if(IsKeyDown(KEY_ENTER) == true && selectorPosition.y == 650){
                    EndDrawing();
                    mode = RULES;

                }
                if(IsKeyDown(KEY_ENTER) == true && selectorPosition.y == 750){
                    EndDrawing();
                    CloseWindow();

                }


                BeginDrawing();
                ClearBackground(GRAY);
                DrawTextureEx(menuTexture, (Vector2){200,7},0,0.75, RAYWHITE);
                DrawText("Play", (menuTexture.width/2) -150 , 500, 100, WHITE);
                DrawText("Rules", (menuTexture.width/2) -180 , 600, 100, WHITE);
                DrawText("Exit", (menuTexture.width/2) -145 , 700, 100, WHITE);
                DrawCircleV(selectorPosition, 10, GOLD);
                
                
                EndDrawing();

                break;

            case RULES:
                if(IsKeyDown(KEY_SPACE) == true) {
                    EndDrawing();
                    mode = INITMENU;
                    
                }
                BeginDrawing();
                ClearBackground(GRAY);
                DrawTextureEx(rulesTexture, (Vector2){200,7},0,0.75, RAYWHITE);
                EndDrawing();


            break;
            case GAME:
                // sprintf(playerPosX, "%d", player.posX);
                // sprintf(playerPosY, "%d", player.posY);
                
                sprintf(playerlife, "%d", player.life);
                player.isMoving = false;
                mainTimer+=GetFrameTime();
                player.playerCollision.x = player.posX;
                player.playerCollision.y = player.posY;
                for(int i=0;i<Numbercars;i++){
                    cars[i].timeCounter+=GetFrameTime();
                }
                if(verifyPlayerSpikesCollision(player, &spike, 1)==true){
                    player.invencibilityTime-=GetFrameTime();
                }

                



                
                
                cam.target = (Vector2){player.posX, player.posY};
                
                
                
                movePlayer(&player, walls_player);

                if(player.heading == HEADING_LEFT) {
                    playerTexture = LoadTexture("Assets/CharacterSprites/PlayerIdleLeft.png");
                } else if (player.heading == HEADING_RIGHT) {
                    playerTexture = LoadTexture("Assets/CharacterSprites/PlayerIdleRight.png");
                }
                
                BeginDrawing();
                BeginMode2D(cam);
                ClearBackground(LIME);
                DrawTextureEx (backgroundTexture, (Vector2) {0,0},0, 1.5, RAYWHITE);
                //DrawText(playerlife, 600, 600, 30, PINK);
                //DrawText(playerPosX, 600, 300, 30, RED);
                //DrawText(playerPosY, 700, 400, 30, RED);
                sprintf(waveNumber, "%d", Wave);
                DrawText(waveChar, 1125, 1125, 60, PINK);
                DrawText(waveNumber, 1340, 1125, 60, PINK);
                
                
                DrawTextureEx(spikeTexture, (Vector2){700, 700}, 0, 0.4, RAYWHITE);
                for(int i=0;i<4;i++){
                    DrawRectangleRec(walls[i], BLACK);
                    DrawRectangleRec(walls_player[i], GRAY);
                }
                DrawTexture(playerTexture, player.posX, player.posY, RAYWHITE);
                for(int i=0;i<Numbercars;i++){
                    DrawCar(cars[i], carTexture);
                }
                DrawLineEx ((Vector2){player.posX - 30, player.posY - 10}, (Vector2){(player.posX - 30) + (player.life * 2), player.posY - 10}, 10, GOLD); 
                if(player.life<=0){

                    EndDrawing();
                    mode = LOST;
                    Wave = 1;
                    player.life = 50;
                    Numbercars = 4;
                    
                    cars = malloc(sizeof(Car)*Numbercars);
                    for(int i = 0; i < Numbercars; i++){
                        if(i % 2 == 0){
                            cars[i] = (Car){rand() % 2250 , 25, exemplo, 0, 5, 70, 5, AIMING, 0, false, false};
                        }else{
                            cars[i] = (Car){rand() % 2250 , 2250, exemplo, 0, 5, 70, 5, AIMING, 0, false, false};
                        }  
                    }
                    carsDestroyed = 0; 
                }

                for(int j=0; j< Numbercars; j++){
                    if(cars[j].life > 0 && cars[j].life < 200){
                        DrawRectangle(cars[j].posX-25, cars[j].posY-32, cars[j].life, 7, GREEN);
                    }
                }

                //Conta a qnt de carros destruidos
                for(int i = 0; i< Numbercars; i++){
                    if(cars[i].life <=0){
                        carsDestroyed ++;
                        cars[i].life = 300;
                    }
                }
                //Aumenta o Numero de carros a cada Wave
                if(carsDestroyed == Numbercars){
                    Wave +=1;
                    Numbercars = 4 * Wave;
                    cars = (Car *) realloc(cars, Numbercars * sizeof(Car));
                    for(int i = 0; i < Numbercars; i++){
                        /*if(i % 2 == 0){
                        cars[i] = (Car){rand() % 1400 , 25, exemplo, 0, 5, 50, 5, AIMING, 0, false, false};
                        }else{
                        cars[i] = (Car){rand() % 1400 , 2250, exemplo, 0, 5, 50, 5, AIMING, 0, false, false};
                        }*/
                        if(i%4==0){
                            cars[i] = (Car){rand() % 2250 , 25, exemplo, 0, 5, 70, 5, AIMING, 0, false, false};
                        }
                        else if((i+1)%4==0){
                            cars[i] = (Car){rand() % 2250 , 2250, exemplo, 0, 5, 70, 5, AIMING, 0, false, false};
                        }
                        else if((i+2)%4==0){
                            cars[i] = (Car){0 , rand() % 2250, exemplo, 0, 5, 70, 5, AIMING, 0, false, false};
                        }
                        else{
                            cars[i] = (Car){2250 , rand() % 2250, exemplo, 0, 5, 70, 5, AIMING, 0, false, false};
                        }    
                    }
                    carsDestroyed = 0;
                }

                sprintf(CarsDestorided, "%d", Wave);
                DrawText(CarsDestorided, 200, 400 , 60, PURPLE);


                MasterUpdateCars(cars, Numbercars, walls, player, &mainTimer);

                applyCarDamage(&spike, cars, Numbercars, 1);

                applyPlayerDamage(&player, cars, &spike, Numbercars, 1);



                
                EndDrawing();
                EndMode2D();
                break;
            case UPGRADE:
                //código da escolha do upgrade no final de cada wave
                break;
            case LOST:
                BeginDrawing();
                ClearBackground(GRAY);
                DrawTextureEx(lostTexture, (Vector2){200,7},0,0.75, RAYWHITE);
                if (IsKeyDown(KEY_SPACE) == true){
                    EndDrawing(); 
                    mode = INITMENU;
                }
                EndDrawing();
                break;
        }

        
        
    }
    UnloadTexture(playerTexture);
    UnloadTexture(carTexture);
    UnloadTexture(spikeTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(menuTexture);
    UnloadTexture(rulesTexture);
    UnloadTexture(lostTexture);
    free(cars);
    CloseWindow();
          
    return 0;
}