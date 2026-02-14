#include<iostream>
#include<string>
#include<vector>
#include "EnemyFactory.h"
#include "Zombie.h"

using namespace std;
//EnemyFactory///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Constructor========================
    EnemyFactory::EnemyFactory() = default;
    EnemyFactory::EnemyFactory(MainCharacter* player)
    {
        Player = player;
    }
    //Setter and Getters=================
    void EnemyFactory::setEnemy(MainCharacter* player)
    {
        Player = player;
    }
    MainCharacter* EnemyFactory::getEnemy()
    {
        return Player;
    }
    //Algorithm Of Calculating==========

    // Code is in functions and they're below.
    //Functions=========================
    Zombie* EnemyFactory::makeZombie()
    {
        ZombieModel* zombiemodel = new ZombieModel("Zombie", CalculateHPForZombie(Player->getLevel()) , CalculateSTforZombie(Player->getLevel()) , CalculateDMPAforZombie(Player->getLevel()) , Player->getLevel()); 
        ZombieView* zombieview = new ZombieView(zombiemodel);      
        ZombieController* zombiecontroller = new ZombieController(zombiemodel);
        Zombie* zombie = new Zombie(zombiemodel , zombieview , zombiecontroller);
        return zombie;
        
    }

