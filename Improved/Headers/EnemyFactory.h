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


using namespace std;

int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);

class EnemyFactory{
private:
    MainCharacter* Player;
public:
    //Constructor========================
    EnemyFactory();
    EnemyFactory(MainCharacter* player);
   
    //Setter and Getters=================
    void setEnemy(MainCharacter* player);
   
    MainCharacter* getEnemy();
    
    //Algorithm Of Calculating==========

    // Code is in functions and they're below.
    //Functions=========================
    Zombie* makeZombie();
    HumanEnemy* makeHuman();
    
};
