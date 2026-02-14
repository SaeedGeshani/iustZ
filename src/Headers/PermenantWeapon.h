#pragma once
#include "MainCharacter.h"
#include "Weapon.h"
using namespace std;

class PermenantWeapon : virtual public Weapon{

public:
    //Constructors==================================
    PermenantWeapon();
    PermenantWeapon(int damageperattack , int neededstaminaperattack  , string name, int price);
//    {
//        damagePerAttack = damageperattack;
//        neededStaminaPerAttack = neededstaminaperattack;
//        Level = level;
//        Name = name;
//    }    
};