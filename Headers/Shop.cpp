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
    vector<UseableItems*> Shop::getUseableItem()
    {
        return useableitems;
    }
    vector<Weapon*> Shop::getWeapon()
    {
        return weapons;
    }
    //Add Items========================
    void Shop::addWeapon(Weapon* weapon)
    {
        weapons.push_back(weapon);
    }
    void  Shop::addUseableItems(UseableItems* useableitem)
    {
        useableitems.push_back(useableitem);
    }




