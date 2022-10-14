#include "raylib.h"
#include "car.h"
#include "colisao.h"
#include "player.h"
#include "upgrade.h"
 


/*void upgradePlayerLife (Player *player) {
    (*player).life += 20; 
}

 void upgradeSpike (Spikes *spike) {
    (*spike).

} 

void upgradenumberSpikes(Spikes *spike, int *numberSpike) { 
    
    (*numberSpike)++; 
    spike = MemRealloc(spike, (*numberSpike)); 
    
    for (int i=0; i< (*numberSpike); i++) {
        spike[i].posX = GetRandomValue (100, 300); 
        spike[i].posY = GetRandomValue (100, 300); 
    }
} //lembrar de dar MemFree 


 void upgradePlayerSpeed(Player *player){
    (*player).speed += 10;  
}*/

void healPlayer(Player *player){
    player[0].life = 50;

}

Spikes *generateNewRandomSpikes(Spikes *spikes, int *numberSpikes){
    spikes = realloc(spikes, sizeof(Spikes)*(*numberSpikes+1));
    Spikes newSpike;
    Rectangle newSpikeCollision;
    newSpike.posX = GetRandomValue(335, 1915);
    newSpike.posY = GetRandomValue(335, 1915);
    newSpikeCollision.x = newSpike.posX;
    newSpikeCollision.y = newSpike.posY;
    newSpikeCollision.width = 55;
    newSpikeCollision.height = 55;
    newSpike.spikeCollision = newSpikeCollision;
    spikes[*numberSpikes] = newSpike;
    *numberSpikes = *numberSpikes+1;
    return spikes;
}

void increasePlayerSpeed(Player *player){
    player[0].speed++;
}
