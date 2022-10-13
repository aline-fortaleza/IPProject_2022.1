#include "raylib.h"
#include "car.h"
#include "player.h"
#include <math.h>




void changeCarAngle(Car *car, Player player){
    
    float dist = sqrt(pow(fabs(player.posY+13-car[0].posY), 2)+pow(fabs(player.posX+8-car[0].posX), 2));

    if(player.posX>car->posX){

        car[0].angle = asin((player.posY+13-car->posY)/dist)*180/PI;
    }
    else{
        car[0].angle = 180 - asin((player.posY+13-car->posY)/dist)*180/PI;
    }

    
    
   



}



void DrawCar(Car car, Texture2D carTexture){
    Rectangle source;
    source.x = 0;
    source.y = 0;
    source.width = 65;
    source.height = 45;
    Rectangle destination;
    destination.x = car.posX;
    destination.y = car.posY;
    destination.height = 45;
    destination.width = 65;
    Vector2 origin = (Vector2){30, 30};
    if(car.life>0  && car.life < 200){
        DrawTexturePro(carTexture, source, destination, origin, car.angle, RAYWHITE);
    }
   
}

void moveCar(Car *car){
    car[0].posY+=sin(car->angle*PI/180)*car->speed;
    car[0].posX+=cos(car->angle*PI/180)*car->speed;
    
}

bool collidedWalls(Car car, Rectangle walls[]){
    bool isColliding = false;
    for(int i=0;i<4;i++){
        if(CheckCollisionCircleRec((Vector2){car.posX, car.posY}, 30, walls[i])==true){
            isColliding = true;
        }
    }
    return isColliding;
}

void MasterUpdateCars(Car *cars, int numberCars, Rectangle walls[], Player player, float *mainTimer){
    
    
    for(int i=0;i<numberCars;i++){
        
        if(cars[i].mode==AIMING){
            cars[i].isReadytoCollide = false;
            changeCarAngle(&cars[i], player);
            if(cars[i].timeCounter>=cars[i].timeChangingAngle){
                cars[i].mode = RUNNING;
                
            }
        }
        if(cars[i].mode==RUNNING){
            cars[i].timeCounter = 0;
            moveCar(&cars[i]);
            if(collidedWalls(cars[i], walls)==false){
                cars[i].isReadytoCollide = true;
                
            }
            if(cars[i].isReadytoCollide==true && collidedWalls(cars[i], walls)==true){
                cars[i].mode = AIMING;
            }
        }
    }
    if(*mainTimer>10){
        for(int i=0;i<numberCars;i++){
            cars[i].speed+=2;
            cars[i].timeChangingAngle-=0.5;
            if(cars[i].timeChangingAngle<0.1){
                cars[i].timeChangingAngle = 0.1;
            }
        }
        *mainTimer = 0;
    }
    
}










