#include<string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Shop.h"

using namespace std;


    Shop::Shop() = default;
    Shop::Shop(string name , int level)
    {
        Name = name;
        Level = level;
    }
    //Setter & Getters=================
    void Shop::setName(string name)
    {
        Name = name;
    }
    string Shop::getName()
    {
        return Name;
    }
    void Shop::setLevel(int level)
    {
        Level = level;
    }
    int Shop::getLevel()
    {
        return Level;
    }
    // vector<UseableItems*> Shop::getUseableItem()
    // {
    //     return useableitems;
    // }
    // vector<Weapon*> Shop::getWeapon()
    // {
    //     return weapons;
    // }
    // //Add Items========================
    // void Shop::addWeapon(Weapon* weapon)
    // {
    //     weapons.push_back(weapon);
    // }
    // void  Shop::addUseableItems(UseableItems* useableitem)
    // {
    //     useableitems.push_back(useableitem);
    // }

    void Shop::ShowItems()
    {
        cout << "Here are the ThrowableWeapons: ========"<< endl;
        cout << "1.Batrang" << endl;
        cout << "2.Grenade" << endl;
        cout << "3.TNT" << endl;
        cout << "And these are UsableItems and Healers: ========" << endl;
        cout << "4.WheyProtein" << endl;
        cout << "5.Egg" << endl;
        cout << "6.Peace Herbal Tea" << endl;
    }

    void Shop::BuyItem(MainCharacter* player)
    {
        this->ShowItems();

        int ChosenNumber;
        
        do{
            cout << "Please enter the number of Item you wanna buy" << endl;
            cin >> ChosenNumber;
            
            
                if(ChosenNumber == 1) 
                {
                    ThrowableWeapon* Batrang = new ThrowableWeapon(50 + ((player->getLevel())+5)*5/4 , 10 + (player->getLevel())*9/7 , player->getLevel() , "Batrang" , 50 );
                    player->addWeapon(Batrang);
                    player->setGold(player->getGold() - 50);
                }
                
                else if(ChosenNumber == 2) 
                {
                    ThrowableWeapon* Grenade = new ThrowableWeapon(80 + (player->getLevel())*10 , 30 + 3*(player->getLevel()) , player->getLevel() , "Grenade" , 150);
                    player->addWeapon(Grenade);
                    player->setGold(player->getGold()-150);
                }

                else if(ChosenNumber == 3)
                {
                    ThrowableWeapon* TNT = new ThrowableWeapon(100 + (player->getLevel())*12 , 35 + 4*(player->getLevel()) , player->getLevel() , "TNT" , 300);
                    player->addWeapon(TNT);
                    player->setGold(player->getGold()-300);
                }

                else if(ChosenNumber == 4) 
                {
                    UseableItems* WheyProtein = new UseableItems(40 , 50 , player->getLevel() , "Healing" , "WheyProtein" , 50);
                    player->addUseableItems(WheyProtein);
                    player->setGold(player->getGold() - 50);
                }

                else if(ChosenNumber == 5)
                {
                    UseableItems* Egg = new UseableItems(20 , 30 , player->getLevel() , "Healing" , "Egg" , 10);
                    player->addUseableItems(Egg);
                    player->setGold(player->getGold() - 10);
                }

                else if(ChosenNumber == 6)
                {
                    UseableItems* PeaceHT = new UseableItems(100 , -20 , player->getLevel() , "Healing" , "PeaceHT" , 80);
                    player->addUseableItems(PeaceHT);
                    player->setGold(player->getGold() - 80);break;
                }
                else
                {
                    continue;
                }

        


        }while(ChosenNumber < 0 || ChosenNumber > 7);
    }



