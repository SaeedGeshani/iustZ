#include<iostream>
#include<string>
#include<vector>
#include "EnemyFactory.h"

using namespace std;
//EnemyFactory///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Constructor========================
    EnemyFactory::EnemyFactory() = default;
    EnemyFactory::EnemyFactory(int enemylevel)
    {
        EnemyLevel = enemylevel;
    }
    //Setter and Getters=================
    void EnemyFactory::setEnemyLevel(int enemylevel)
    {
        EnemyLevel = enemylevel;
    }
    int EnemyFactory::getEnemyLevel()
    {
        return EnemyLevel;
    }
    //Algorithm Of Calculating==========

    // Code is in functions and they're below.
    //Functions=========================
    Zombie* EnemyFactory::makeZombie()
    {
        ZombieModel zombiemodel{"Zombie", CalculateHPForZombie(EnemyLevel) , CalculateSTforZombie(EnemyLevel) , CalculateDMPAforZombie(EnemyLevel) , EnemyLevel}; 
        ZombieView zombieview = ZombieView(&zombiemodel);      
        ZombieController zombiecontroller{&zombiemodel};
        Zombie zombie{&zombiemodel , &zombieview , &zombiecontroller};
        Zombie* ptrZombie = &zombie;
        return ptrZombie;
    }

