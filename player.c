#include "raylib.h"
#include "player.h"
#define HEADING_LEFT 1
#define HEADING_RIGHT 2
#include "animations.h"
#define HEADING_UP 4
#define HEADING_DOWN 3

void movePlayer(Player *player, Rectangle walls_player[]){
    if(IsKeyDown(KEY_LEFT)==true && CheckCollisionRecs(player->playerCollision, walls_player[1])==false){
        player[0].posX-=player[0].speed;
        player[0].heading = HEADING_LEFT;
        player[0].isMoving = true;

    }
    if(IsKeyDown(KEY_RIGHT)==true && CheckCollisionRecs(player->playerCollision, walls_player[2])==false){
        player[0].posX+=player[0].speed;
        player[0].heading = HEADING_RIGHT;
        player[0].isMoving = true;

    }
    if(IsKeyDown(KEY_UP)==true && CheckCollisionRecs(player->playerCollision, walls_player[0])==false){
        player[0].posY-=player[0].speed;
        //Se o player n for ter animação de andar para cima, comentar a linha abaixo
        player[0].heading = HEADING_UP;
        //a linha acima
        player[0].isMoving = true;
    }
    if(IsKeyDown(KEY_DOWN)==true && CheckCollisionRecs(player->playerCollision, walls_player[3])==false){
        player[0].posY+=player[0].speed;
        //Se o player n for ter animação de andar para baixo, comentar a linha abaixo
        player[0].heading = HEADING_DOWN;
        //a linha acima
        player[0].isMoving = true;
    }
    if(IsKeyDown(KEY_LEFT)==false && IsKeyDown(KEY_RIGHT)==false && IsKeyDown(KEY_UP)==false && IsKeyDown(KEY_DOWN)==false){
        player[0].isMoving = false;
    }
    

}

void initPlayerAnim(int frames, int *frameCounter, int walkMode, bool isRunning, Texture2D walkingUp[], Texture2D walkingDown[], Texture2D walkingLeft[], Texture2D walkingRight[], Player *player){
    if(*frameCounter==4){
        *frameCounter = 0;
    }
    if(isRunning==false){
        *frameCounter = 0;
        if(walkMode==HEADING_DOWN){
            DrawTextureEx(walkingDown[*frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1.0, RAYWHITE);
        }
        else if(walkMode==HEADING_LEFT){
            DrawTextureEx(walkingLeft[*frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1.0, RAYWHITE);
        }
        else if(walkMode==HEADING_UP){
            DrawTextureEx(walkingUp[*frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1.0, RAYWHITE);
        }
        else if(walkMode==HEADING_RIGHT){
            DrawTextureEx(walkingRight[*frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1.0, RAYWHITE);
        }
    }
    else{
        if(walkMode==HEADING_DOWN){
            DrawTextureEx(walkingDown[*frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1.0, RAYWHITE);
            if(frames%4==0){
                *frameCounter = *frameCounter + 1;
            }
        }
        else if(walkMode==HEADING_LEFT){
            DrawTextureEx(walkingLeft[*frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1.0, RAYWHITE);
            if(frames%4==0){
                *frameCounter = *frameCounter + 1;
            }
        }
        else if(walkMode==HEADING_UP){
            DrawTextureEx(walkingUp[*frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1.0, RAYWHITE);
            if(frames%4==0){
                *frameCounter = *frameCounter + 1;
            }
        }
        else if(walkMode==HEADING_RIGHT){
            DrawTextureEx(walkingRight[*frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1.0, RAYWHITE);
            if(frames%4==0){
                *frameCounter = *frameCounter + 1;
            }
        }
    }
}
