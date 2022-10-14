#include "raylib.h"
#include <math.h>
#include "car.c"
#include "player.c"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "colisao.c"
#include "upgrade.c"








#define INITMENU 10
#define RULES 11
#define GAME 12
#define UPGRADES 13
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
    Texture2D upgradesTexture = LoadTexture("upgrade_menu.png");
    Texture2D carTextureDestroyed = LoadTexture("Assets/cardestroyed.png");
    
    //carregando animações do personagem;
    Texture2D walkingLeft[4];
    walkingLeft[0] = LoadTexture("Assets/CharacterSprites/PlayerIdleLeft.png");
    walkingLeft[1] = LoadTexture("Assets/CharacterSprites/PlayerWalkingLeft (1).png");
    walkingLeft[2] = LoadTexture("Assets/CharacterSprites/PlayerIdleLeft.png");
    walkingLeft[3] = LoadTexture("Assets/CharacterSprites/PlayerWalkingLeft (2).png");

    Texture2D walkingRight[4];
    walkingRight[0] = LoadTexture("Assets/CharacterSprites/PlayerIdleRight.png");
    walkingRight[1] = LoadTexture("Assets/CharacterSprites/PlayerWalkingRight (1).png");
    walkingRight[2] = LoadTexture("Assets/CharacterSprites/PlayerIdleRight.png");
    walkingRight[3] = LoadTexture("Assets/CharacterSprites/PlayerWalkingRight (2).png");


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
    Player player = (Player){400, 400, 0, 50, playerCollision, exemplo, 5, HEADING_LEFT, false, true, true, 2};
    
    
    

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
    spikeCollision.x = 1000;
    spikeCollision.y = 1000;
    spikeCollision.width = 55;
    spikeCollision.height = 55;
    Texture2D spikeTexture = LoadTexture("spike.png");
    Spikes *spike = malloc(sizeof(Spikes)*1);
    Spikes firstSpike;
    firstSpike.posX = 1000;
    firstSpike.posY = 1000;
    firstSpike.spikeCollision = spikeCollision;
    spike[0] = firstSpike;

    char playerlife[5];
    char playerPosX[5];
    char playerPosY[5];
    char CarsDestorided[5];
    char waveChar[10] = "WAVE:";
    char waveNumber[3];
    int carsDestroyed = 0; 
    int numberSpikes = 1;
    int frames = 0;
    Camera2D cam;
    cam.offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/2};
    cam.rotation = 0;
    cam.zoom = 1.2;
    

    
    Vector2 selectorPosition = {(int) (menuTexture.width/2) +150, (int) 550 };
    Vector2 selectorUpgrades = {(int) (upgradesTexture.width/2) -715 , (int) 540};
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
                frames++;
                if(frames>24){
                    frames = 0;
                }
                sprintf(playerlife, "%d", player.life);
                player.isMoving = false;
                mainTimer+=GetFrameTime();
                player.playerCollision.x = player.posX;
                player.playerCollision.y = player.posY;
                for(int i=0;i<Numbercars;i++){
                    cars[i].timeCounter+=GetFrameTime();
                }
                if(verifyPlayerSpikesCollision(player, spike, numberSpikes)==true){
                    player.invencibilityTime-=GetFrameTime();
                }

                



                
                
                cam.target = (Vector2){player.posX, player.posY};
                
                
                
                movePlayer(&player, walls_player);

                
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
                
                
                for(int i=0;i<numberSpikes;i++){
                    DrawTextureEx(spikeTexture, (Vector2){spike[i].posX, spike[i].posY}, 0, 0.4, RAYWHITE);
                }
                for(int i=0;i<4;i++){
                    DrawRectangleRec(walls[i], BLACK);
                    DrawRectangleRec(walls_player[i], GRAY);
                }
                startPlayerAnim(frames, walkingLeft, walkingRight, &player);
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
                    numberSpikes = 1;
                    Spikes *spike = malloc(sizeof(Spikes)*1);
                    Spikes firstSpike;
                    firstSpike.posX = 1000;
                    firstSpike.posY = 1000;
                    firstSpike.spikeCollision = spikeCollision;
                    spike[0] = firstSpike;
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
                    //Fazer carro ficar destruido na cena
                    if(cars[i].life <= 0 || cars[i].life == 300){
                        DrawTextureEx(carTextureDestroyed, (Vector2){cars[i].posX, cars[i].posY},0,0.1,RAYWHITE);
                        carStop(cars, Numbercars, i, cars[i].posX, cars[i].posY);
                    }
                    //qualquer coisa, só tirar esse if

                }
                //Aumenta o Numero de carros a cada Wave
                if(carsDestroyed == Numbercars){
                    Wave +=1;
                    Numbercars = 4 * Wave;
                    mode = UPGRADES;
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

                applyCarDamage(spike, cars, Numbercars, numberSpikes);

                applyPlayerDamage(&player, cars, spike, Numbercars, numberSpikes);



                
                EndDrawing();
                EndMode2D();
                break;

            case UPGRADES:
                if (IsKeyDown(KEY_UP) == true && selectorUpgrades.y != 540 && PRESS_UP == false) {

                    selectorUpgrades.y -= 100;
                    PRESS_UP = true;

                }
                if(IsKeyDown(KEY_UP) == false) {
                    PRESS_UP = false;
                }
                if (IsKeyDown(KEY_DOWN) == true && selectorUpgrades.y != 840 && PRESS_DOWN == false) {

                   selectorUpgrades.y += 100;
                   PRESS_DOWN = true;
                }
                if(IsKeyDown(KEY_DOWN) == false) {
                    PRESS_DOWN = false;
                }

                if(IsKeyDown(KEY_ENTER) == true && selectorUpgrades.y == 540){
                    EndDrawing();
                    healPlayer(&player);
                    mode = GAME;

                }
                if(IsKeyDown(KEY_ENTER) == true && selectorUpgrades.y == 640){
                    EndDrawing();
                    generateNewRandomSpikes(&spike, &numberSpikes);
                    mode = GAME;

                }
                if(IsKeyDown(KEY_ENTER) == true && selectorUpgrades.y == 740){
                    EndDrawing();
                    increasePlayerSpeed(&player);
                    CloseWindow();

                }
                if(IsKeyDown(KEY_ENTER) == true && selectorUpgrades.y == 840){
                    EndDrawing();
                    cam.zoom -= 0.1;
                    CloseWindow();

                }

                BeginDrawing();
                ClearBackground(GRAY);
                DrawTextureEx(upgradesTexture, (Vector2){200,7},0,0.75, RAYWHITE);
                DrawCircleV(selectorUpgrades, 10, GOLD);

                DrawText("Recuperar vida", (rulesTexture.width/2) -700 , 500, 80, WHITE);
                DrawText("Adicionar novo espinho", (rulesTexture.width/2) -700 , 600, 80, WHITE);
                DrawText("Aumentar velocidade ", (rulesTexture.width/2) -700 , 700, 80, WHITE);
                DrawText("Aumentar a visao da camera ", (rulesTexture.width/2) -700 , 800, 80, WHITE);

                EndDrawing();
                break;
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
    UnloadPlayerAnimation(walkingLeft, walkingRight);
    UnloadTexture(upgradesTexture);
    free(cars);
    CloseWindow();
          
    return 0;
}