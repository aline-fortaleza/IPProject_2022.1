#ifndef UPGRADE
#define UPGRADE
#include "raylib.h"
#include "car.h"
#include "colisao.h"
#include "player.h"
 

void upgradePlayerLife (Player *player); 

void upgradenumberSpikes(Spikes *spike, int *numberSpike); 
    //lembrar de dar MemFree 
 void upgradePlayerSpeed(Player *player);

 #endif 