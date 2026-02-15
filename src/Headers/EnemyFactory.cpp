#include<iostream>
#include<string>
#include<vector>
#include "EnemyFactory.h"
#include "Zombie.h"
#include "human.h"

using namespace std;
//EnemyFactory///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Constructor========================
    EnemyFactory::EnemyFactory() = default;
    EnemyFactory::EnemyFactory(MainCharacter* player , int zarib)
    {
        Player = player;
        Zarib = zarib;
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
        ZombieModel* zombiemodel = new ZombieModel("Zombie", CalculateHPForZombie(Player->getLevel())*Zarib , CalculateSTforZombie(Player->getLevel())*Zarib , CalculateDMPAforZombie(Player->getLevel())*Zarib , Player->getLevel() , Player->getLevel() * 4 + 5 , Zarib); 
        ZombieView* zombieview = new ZombieView(zombiemodel);      
        ZombieController* zombiecontroller = new ZombieController(zombiemodel);
        Zombie* zombie = new Zombie(zombiemodel , zombieview , zombiecontroller);
        return zombie;
        
    }


    HumanEnemy* EnemyFactory::makeHuman()
    {
        HumanEnemyModel* humanmodel = new HumanEnemyModel("Human" , CalculateHPForHuman(Player->getLevel()) * Zarib , CalculateSTForHuman(Player->getLevel())*Zarib , -1 , Player->getLevel() , Zarib);
        //Giving him a random Inventory===========================================================================================================
        Katana* a = nullptr;
        Blaster* b = nullptr;
        Batarang* c = nullptr;
        grenade* d = nullptr;
        WheyProtein* e = nullptr;
        Egg* f = nullptr;
        KratosBlades* g = nullptr;
        EnergyDrink* h = nullptr;
        Mjolnir* I = nullptr;
        MiniGun* J = nullptr;
        RocketLauncher* k = nullptr;
        shuriken* l = nullptr;
        Spear* m = nullptr;
        XPpotion* n = nullptr;

        vector<Weapon*>weps;
        vector<UseableItems*>item;
        int tedad;
        tedad = rand()%2;
        for(int i = 0 ; i < tedad ; i++)
        {
             while(true)
            {
                a = new Katana(20 , 15 , "Katana" , 50);
                if(a != nullptr)
                {
                    break;
                }
                delete a;
            }
            weps.push_back(a);
        }
       
        tedad = rand()%2;
        for(int i = 0 ; i < tedad ; i++)
        {
            while(true)
            {
                b = new Blaster(23 , 10 , "Blaster" , 50);
                if(b != nullptr)
                {
                    break;
                }
                delete b;
            }
            weps.push_back(b);
        }
        
        tedad = rand()%3;
        for(int i = 0 ; i < tedad ; i++)
        {
             while(true)
            {
                c = new Batarang(30 , 15 , "Batrang" , 75);
                if(c != nullptr)
                {
                    break;
                }
                delete c;
            }

            weps.push_back(c);
        }
       
        tedad = rand()%3;
        for(int i = 0 ; i < tedad ; i++)
        {
             while(true)
            {
                d = new grenade(50 , 30 , "Grenade" , 120);
                if(d != nullptr)
                {
                    break;
                }
                delete d;
            }
            weps.push_back(d);
        }
       

        
        tedad = rand()%3;
        for(int i = 0 ; i < tedad ; i++)
        {
             while(true)
            {
                e = new WheyProtein(15 , 30 , "Whey Protein" , 50 , 0);
                if(e != nullptr)
                {
                    break;
                }
                delete e;
            }
            
            item.push_back(e);
        }
        tedad = rand()%3;
        for(int i = 0 ; i < tedad ; i++)
        {
            while(true)
            {
                f = new Egg(15 , 15 , "Egg" , 20 , 10);
                if(f != nullptr)
                {
                    break;
                }
                delete f;
            }
            item.push_back(f);
       
        }

        tedad = rand()%2;
        for(int i = 0 ; i < tedad ; i++)
        {
            while(true)
            {
                h = new EnergyDrink(40 , 0 , "Energy Drink" , 40 , 0);
                if(h != nullptr)
                {
                    break;
                }
                delete h;
            }
            item.push_back(h);
            
        }
    
        tedad = rand() % 2;
        for(int i = 0 ; i < tedad ; i++)
        {
            while(true)
            {
                k = new RocketLauncher(100 , 40 , "Rocket Launcher" , 100);
                if(k != nullptr)
                {
                    break;
                }
                delete k;
            }
            weps.push_back(k);
        }
        humanmodel->setEnemyWeapons(weps);
        humanmodel->setEnemyUseableItems(item);
        //========================================================================================================================================
        HumanEnemyView* humanview = new HumanEnemyView(humanmodel);
        HumanEnemyController* humancontroller = new HumanEnemyController(humanmodel);
        HumanEnemy* human = new HumanEnemy(humanmodel , humanview , humancontroller);
        return human;
    }
