#pragma once
#include<iostream>
#include<string>
#include "MainCharacter.h"
#include "Weapon.h"

using namespace std;

class ThrowableWeapon : virtual public Weapon{
public:
    //Constructors==================================
    ThrowableWeapon();
    ThrowableWeapon(int damageperattack , int neededstaminaperattack  , string name, int price);
};
