#include "colisao.h"
#include "raylib.h"




bool verifyPlayerSpikesCollision(Player player, Spikes *spikes, int numberSpikes){
    bool hit = false;
    for(int i=0;i<numberSpikes;i++){
        if(CheckCollisionRecs(player.playerCollision, spikes[i].spikeCollision)==true){
            hit = true;
        }
    }
    return hit;
}

bool verifyPlayerCarsCollision(Player player, Car *cars, int numberCars){
    bool hit = false;
    for(int i=0;i<numberCars;i++){
        if(CheckCollisionCircleRec((Vector2){cars[i].posX, cars[i].posY}, 30, player.playerCollision)==true && cars[i].life<100){
            hit = true;
        }
    }
    return hit;
}

void applyPlayerDamage(Player *player, Car *cars, Spikes *spikes, int numberCars, int numberSpikes){
    // colisão com spikes primeiro:
    if(player[0].isReadytoHitSpikes==false && verifyPlayerSpikesCollision(player[0], spikes, numberSpikes)==false){
        player[0].isReadytoHitSpikes = true;
        player[0].invencibilityTime = 2;
    }
    if(player[0].isReadytoHitSpikes == true && verifyPlayerSpikesCollision(player[0], spikes, numberSpikes)==true){
        player[0].life-=10;
        player[0].isReadytoHitSpikes = false;
    }
    if(player[0].invencibilityTime<=0){
        player[0].isReadytoHitSpikes = true;
        player[0].invencibilityTime = 2;
    }
    
    // colisão com os carrinhos
    if(player[0].isReadytoHitCar==false && verifyPlayerCarsCollision(player[0], cars, numberCars)==false){
        player[0].isReadytoHitCar = true;
    }
    if(player[0].isReadytoHitCar == true && verifyPlayerCarsCollision(player[0], cars, numberCars)==true){
        player[0].life-=10;// diminuindo a vida do player em 10
        player[0].isReadytoHitCar = false;
    }
}

bool checkCarSpikesCollision(Spikes *spikes, Car car, int numberSpikes){
    bool hit = false;
    for(int i=0;i<numberSpikes;i++){
        if(CheckCollisionCircleRec((Vector2){car.posX, car.posY}, 30, spikes[i].spikeCollision)==true){
            hit = true;
        }
    }
    return hit;
}

void applyCarDamage(Spikes *spikes, Car *cars, int numberCars, int numberSpikes){
    for(int i=0;i<numberCars;i++){
        if(cars[i].isReadytoHitSpikes==false && checkCarSpikesCollision(spikes, cars[i], numberSpikes)==false){
            cars[i].isReadytoHitSpikes = true;
        }
        if(cars[i].isReadytoHitSpikes==true && checkCarSpikesCollision(spikes, cars[i], numberSpikes)==true){
            cars[i].life-=20;//diminuindo a vida do carrinho em 20
            cars[i].isReadytoHitSpikes = false;
        }
    }
}