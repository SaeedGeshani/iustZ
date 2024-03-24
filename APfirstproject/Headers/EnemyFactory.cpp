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

    HumanEnemy* EnemyFactory::makeHuman()
    {
        HumanEnemyModel* humanModel = new HumanEnemyModel("HumanEnemy" , 70 + Player->getLevel()*10 , 80 + Player->getLevel()*8 , -10 , Player->getLevel());
        //================================================
        vector<UseableItems*>usaItem;
        vector<Weapon*>wepItem;
        srand(time(0));
        Katana* a = nullptr;
        Blaster* b = nullptr;
        grenade* c = nullptr;
        Batarang* d = nullptr;
        Egg* e = nullptr;
        WheyProtein* f = nullptr;

        while(true)
        {
            a = new Katana(25 , 15 , "Katana" , 75);
            if(a != nullptr)
            {
                break;
            }
            delete a;
        }
        while(true)
        {
            b = new Blaster(10 , 10 , "Blaster" , 50);
            if(b != nullptr)
            {
                break;
            }
            delete b;
        }
        while(true)
        {
            c = new grenade(25 , 15 , "Katana" , 100);
            if(c != nullptr)
            {
                break;
            }
            delete c;
        }
        while(true)
        {
            d = new Batarang(15 , 10 , "Batrang" , 50);
            if(d != nullptr)
            {
                break;
            }
            delete d;
        }
        while(true)
        {
            e = new Egg(15 , 15 , "Egg" , 20 , 10);
            if(e != nullptr)
            {
                break;
            }
            delete e;
        }
        while(true)
        {
            f = new WheyProtein(15 , 25 , "Whey Protein" , 50 , 10);
            if(f != nullptr)
            {
                break;
            }
            delete f;
        }

        vector<Weapon*>wepi{a , b , c , d};
        vector<UseableItems*>usi{e , f};
        int randomPlace;
        int number;
        for(int i = 1 ; i < 4 ; i++)
        {   
            randomPlace = rand();
            if(randomPlace%2 == 1)
            {
                number = rand();
                number = number % 5;
                for(int j = 0 ; j < number ; j++)
                {
                    wepItem.push_back(wepi[i]);
                }
            }
        }

        wepItem.push_back(a);
        for(int i = 0 ; i < 2 ; i++)
        {
            randomPlace = rand();
            randomPlace = 1;
            if(randomPlace % 2 == 1)
            {
                number = rand();
                number = number % 5;
                for(int j = 0 ; j < number ; j++)
                {
                    usaItem.push_back(usi[i]);
                }
            } 
        }


        humanModel->setEnemyWeapons(wepItem);
        humanModel->setEnemyUsableItems(usaItem);
        //================================================
        HumanEnemyView* humanView = new HumanEnemyView(humanModel);
        HumanEnemyController* humanController = new HumanEnemyController(humanModel);
        HumanEnemy* human = new HumanEnemy(humanModel , humanView , humanController);
        return human;
    }

