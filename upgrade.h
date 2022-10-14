#ifndef UPGRADE
#define UPGRADE
#include "raylib.h"
#include "car.h"
#include "colisao.h"
#include "player.h"
 

/*void upgradePlayerLife (Player *player); 

void upgradenumberSpikes(Spikes *spike, int *numberSpike); 
    
void upgradePlayerSpeed(Player *player);*/

void healPlayer(Player *player);

Spikes *generateNewRandomSpikes(Spikes *spikes, int *numberSpikes);

void increasePlayerSpeed(Player *player);

 #endif 