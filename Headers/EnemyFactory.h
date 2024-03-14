#pragma once
#include<string>
#include<vector>
#include<iostream>
#include"Zombie.h"
using namespace std;

int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);

class EnemyFactory{
private:
    int EnemyLevel;
public:
    //Constructor========================
    EnemyFactory();
    EnemyFactory(int enemylevel);
   
    //Setter and Getters=================
    void setEnemyLevel(int enemylevel);
   
    int getEnemyLevel();
    
    //Algorithm Of Calculating==========

    // Code is in functions and they're below.
    //Functions=========================
    Zombie* makeZombie();
    
};
