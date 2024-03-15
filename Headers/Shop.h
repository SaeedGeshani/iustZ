#pragma once
#include "MainCharacter.h"
#include "Weapon.h"
#include "UseableItems.h"
#include "PermenantWeapon.h"
#include "ThrowableWeapon.h"

using namespace std;

class Shop{
private:
    int Level;
    string Name;
    // vector<UseableItems*> useableitems;
    // vector<Weapon*> weapons;

public:
    Shop();
    Shop(string name , int level);
    
    //Setter & Getters=================
    void setName(string name);
    
    string getName();
    
    void setLevel(int level);
    
    int getLevel();

    void ShowItems();

    void BuyItem(MainCharacter* player);
    
    // vector<UseableItems*> getUseableItem();
    
    // vector<Weapon*> getWeapon();
    
    // //Add Items========================
    // void addWeapon(Weapon* weapon);
    
    // void addUseableItems(UseableItems* useableitem);
    


};

