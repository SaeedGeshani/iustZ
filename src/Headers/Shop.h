#pragma once
#include "MainCharacter.h"
#include "Weapon.h"
#include "UseableItems.h"
#include "PermenantWeapon.h"
#include "ThrowableWeapon.h"

using namespace std;

class Shop{
private:

    // vector<UseableItems*> useableitems;
    // vector<Weapon*> weapons;
	vector<UseableItems*> availableUseables;
    vector<Weapon*> availableWeapons;
public:

    Shop();

    bool isFirst(const string& , MainCharacter* , int);

    void showDetailOfInventory(MainCharacter* player);
    
    int numberInInventory(const string& , MainCharacter*);

    void ShowItems();

    void BuyItem(MainCharacter* player);
     
    vector<UseableItems*> &getUseableItem();

    vector<Weapon*> &getWeapon();

    void setWeapon(const vector<Weapon*>& wep);

    void setUsableItems(const vector<UseableItems*>& usa);

    


};
