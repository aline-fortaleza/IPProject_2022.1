#include "raylib.h"
#include "car.h"
#include "colisao.h"
#include "player.h"
#include "upgrade.h"
 


void upgradePlayerLife (Player *player) {
    (*player).life += 20; 
}

/* void upgradeSpike (Spikes *spike) {
    (*spike).

} */

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
}