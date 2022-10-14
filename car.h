#ifndef CAR
#define CAR
#include "raylib.h"
#include "player.h"
#define AIMING 100
#define RUNNING 101


typedef struct{
    float posX;
    float posY;
    Rectangle carLife;
    float angle;
    float speed;
    int life;
    float timeChangingAngle;
    int mode;// aiming at player or running
    float timeCounter;
    bool isReadytoCollide;// sempre começa falso
    bool isReadytoHitSpikes;// sempre começa verdadeiro
    
} Car;

typedef struct{
    float posX;
    float posY;
    Rectangle spikeCollision;
} Spikes;

void changeCarAngle(Car *car, Player player);

void DrawCar(Car car, Texture2D carTexture);

void moveCar(Car *car);

void carStop(cars, Numbercars, i, cars[i].posX, cars[i].posY);

bool collidedWalls(Car car, Rectangle walls[]);

void MasterUpdateCars(Car *cars, int numberCars, Rectangle walls[], Player player, float *mainTimer);





#endif