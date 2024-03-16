#include<iostream>
#include<string>
#include<vector>
#include "EnemyFactory.h"
#include "Zombie.h"

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
        ZombieModel* zombiemodel = new ZombieModel("Zombie", CalculateHPForZombie(EnemyLevel) , CalculateSTforZombie(EnemyLevel) , CalculateDMPAforZombie(EnemyLevel) , EnemyLevel); 
        ZombieView* zombieview = new ZombieView(zombiemodel);      
        ZombieController* zombiecontroller = new ZombieController(zombiemodel);
        Zombie* zombie = new Zombie(zombiemodel , zombieview , zombiecontroller);
        return zombie;
        
    }

