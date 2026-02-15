#pragma once
#include<string>
#include<vector>
#include<iostream>
#include "Zombie.h"
#include "human.h"
#include "Katana.h"
#include "Blaster.h"
#include "Batarang.h"
#include "grenade.h"
#include "Egg.h"
#include "WheyProtein.h"
#include "EnergyDrink.h"
#include "shuriken.h"
#include "KratosBlades.h"
#include "MiniGun.h"
#include "XPpotion.h"
#include "RocketLauncher.h"
#include "Mjolnir.h"
#include "Spear.h"
#include "EnemyStats.h"


using namespace std;

class EnemyFactory{
private:
    MainCharacter* Player;
    int Zarib;
public:
    //Constructor========================
    EnemyFactory();
    EnemyFactory(MainCharacter* player , int zarib);
   
    //Setter and Getters=================
    void setEnemy(MainCharacter* player);
   
    MainCharacter* getEnemy();

    int getZarib();
    
    //Algorithm Of Calculating==========

    // Code is in functions and they're below.
    //Functions=========================
    Zombie* makeZombie();
    HumanEnemy* makeHuman();
    
};
