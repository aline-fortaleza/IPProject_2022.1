#include "raylib.h"
#include "player.h"
#define HEADING_LEFT 1
#define HEADING_RIGHT 2

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
        player[0].isMoving = true;
    }
    if(IsKeyDown(KEY_DOWN)==true && CheckCollisionRecs(player->playerCollision, walls_player[3])==false){
        player[0].posY+=player[0].speed;
        player[0].isMoving = true;
    }
    if(IsKeyDown(KEY_LEFT)==false && IsKeyDown(KEY_RIGHT)==false && IsKeyDown(KEY_UP)==false && IsKeyDown(KEY_DOWN)==false){
        player[0].isMoving = false;
    }
    

}
void startPlayerAnim(int frames, Texture2D walkingLeft[], Texture2D walkingRight[], Player *player){
    if(player[0].frameCounter==4){
        player[0].frameCounter = 0;
    }
    if(player[0].isMoving == false){
        player[0].frameCounter = 0;
        if(player[0].heading==HEADING_LEFT){
            DrawTextureEx(walkingLeft[player[0].frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1, RAYWHITE);
        }
        else if(player[0].heading==HEADING_RIGHT){
            DrawTextureEx(walkingRight[player[0].frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1, RAYWHITE);
        }
    }
    else{
        if(player[0].heading==HEADING_LEFT){
            DrawTextureEx(walkingLeft[player[0].frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1, RAYWHITE);
            if(frames%4==0){
                player[0].frameCounter++;
            }
        }
        else if(player[0].heading == HEADING_RIGHT){
            DrawTextureEx(walkingRight[player[0].frameCounter], (Vector2){player[0].posX, player[0].posY}, 0, 1, RAYWHITE);
            if(frames%4==0){
                player[0].frameCounter++;
            }
        }
    }
}
