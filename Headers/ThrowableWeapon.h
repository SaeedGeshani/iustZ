#pragma once
#include<iostream>
#include<string>
#include "MainCharacter.h"
#include "Weapon.h"

using namespace std;

class ThrowableWeapon : public Weapon{
public:
    //Constructors==================================
    ThrowableWeapon();
    ThrowableWeapon(int damageperattack , int neededstaminaperattack , int level  , string name, int price);
};
