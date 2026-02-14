#include<iostream>
#include<string>
#include "Weapon.h"
#include "MainCharacter.h"
#include "PermenantWeapon.h"

using namespace std;


    //Constructors==================================
    PermenantWeapon::PermenantWeapon() = default;
    PermenantWeapon::PermenantWeapon(int damageperattack , int neededstaminaperattack   , string name, int price) : Weapon( damageperattack ,  neededstaminaperattack   ,  name,  price){
	}
//    {
//        damagePerAttack = damageperattack;
//        neededStaminaPerAttack = neededstaminaperattack;
//        Level = level;
//        Name = name;
//    }    
