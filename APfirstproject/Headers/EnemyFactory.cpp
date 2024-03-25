#include<iostream>
#include<string>
#include<vector>
#include "EnemyFactory.h"
#include "Zombie.h"
#include "human.h"

int CalculateHPForHuman(int);
int CalculateSTForHuman(int);

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
        ZombieModel* zombiemodel = new ZombieModel("Zombie", CalculateHPForZombie(Player->getLevel()) , CalculateSTforZombie(Player->getLevel()) , CalculateDMPAforZombie(Player->getLevel()) , Player->getLevel() , Player->getLevel() * 4 + 5); 
        ZombieView* zombieview = new ZombieView(zombiemodel);      
        ZombieController* zombiecontroller = new ZombieController(zombiemodel);
        Zombie* zombie = new Zombie(zombiemodel , zombieview , zombiecontroller);
        return zombie;
        
    }

    HumanEnemy* EnemyFactory::makeHuman()
    {
        HumanEnemyModel* humanmodel = new HumanEnemyModel("Human" , CalculateHPForHuman(Player->getLevel()) , CalculateSTForHuman(Player->getLevel()) , -1 , Player->getLevel());
        //Giving him a random Inventory===========================================================================================================
        Katana* a = nullptr;
        Blaster* b = nullptr;
        Batarang* c = nullptr;
        grenade* d = nullptr;
        WheyProtein* e = nullptr;
        Egg* f = nullptr;

        vector<Weapon*>weps;
        vector<UseableItems*>item;
        while(true)
        {
            a = new Katana(20 , 15 , "Katana" , 50);
            if(a != nullptr)
            {
                break;
            }
            delete a;
        }

        while(true)
        {
            b = new Blaster(17 , 10 , "Blaster" , 50);
            if(b != nullptr)
            {
                break;
            }
            delete b;
        }

        while(true)
        {
            c = new Batarang(30 , 15 , "Batrang" , 75);
            if(c != nullptr)
            {
                break;
            }
            delete c;
        }

        while(true)
        {
            d = new grenade(50 , 30 , "Grenade" , 120);
            if(d != nullptr)
            {
                break;
            }
            delete d;
        }

        while(true)
        {
            f = new Egg(15 , 15 , "Egg" , 20 , 10);
            if(f != nullptr)
            {
                break;
            }
            delete f;
        }
        while(true)
        {
            e = new WheyProtein(15 , 30 , "Whey Protein" , 50 , 10);
            if(e != nullptr)
            {
                break;
            }
            delete e;
        }

        weps.push_back(b);

        vector<Weapon*> galleryWep{b , a , c , d};
        
        for(int i = 1 ; i < 4 ; i++)
        {
            int random = rand()%2;
            if(random == 1)
            {
               if(dynamic_cast<ThrowableWeapon*>(galleryWep[i]) != NULL)
               {
                int number = rand() % 5 + 1;
                for(int j = 0 ; j < number ; j++)
                {
                    weps.push_back(galleryWep[i]);
                }
               }
               else{

                weps.push_back(galleryWep[i]);
               }
            }
        }

        int number = rand()%5 + 1;
        for(int i = 0 ; i < number ;i++)
        {
            item.push_back(e);
        }
        number = rand()%5 + 1;
        for(int i = 0 ; i < number ; i++)
        {
            item.push_back(f);
        }

        humanmodel->setEnemyWeapons(weps);
        humanmodel->setEnemyUseableItems(item);
        //========================================================================================================================================
        HumanEnemyView* humanview = new HumanEnemyView(humanmodel);
        HumanEnemyController* humancontroller = new HumanEnemyController(humanmodel);
        HumanEnemy* human = new HumanEnemy(humanmodel , humanview , humancontroller);
        return human;
    }
