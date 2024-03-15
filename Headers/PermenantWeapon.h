#pragma once
#include "MainCharacter.h"
#include "Weapon.h"
using namespace std;

class PermenantWeapon : public Weapon{

public:
    //Constructors==================================
    PermenantWeapon();
    PermenantWeapon(int damageperattack , int neededstaminaperattack , int level  , string name, int price);
//    {
//        damagePerAttack = damageperattack;
//        neededStaminaPerAttack = neededstaminaperattack;
//        Level = level;
//        Name = name;
//    }    
};