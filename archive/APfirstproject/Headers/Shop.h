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

        

    void ShowItems();

    void BuyItem(MainCharacter* player);
     
    vector<UseableItems*> &getUseableItem();

    vector<Weapon*> &getWeapon();

    void setWeapon(vector<Weapon*> wep);

    void setUsableItems(vector<UseableItems*> usa);

    


};
