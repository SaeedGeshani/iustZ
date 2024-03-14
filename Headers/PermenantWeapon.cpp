#include<iostream>
#include<string>
#include "Weapon.h"
#include "MainCharacter.h"
#include "PermenantWeapon.h"

using namespace std;


    //Constructors==================================
    PermenantWeapon::PermenantWeapon() = default;
    PermenantWeapon::PermenantWeapon(int damageperattack , int neededstaminaperattack , int level , string type , string name)
    {
        damagePerAttack = damageperattack;
        neededStaminaPerAttack = neededstaminaperattack;
        Level = level;
        Type = type;
        Name = name;
    }    
