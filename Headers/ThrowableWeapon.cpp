#include<string>
#include<iostream>
#include<vector>
#include "MainCharacter.h"
#include "Weapon.h"
#include "ThrowableWeapon.h"

using namespace std;


    //Constructors==================================
    ThrowableWeapon::ThrowableWeapon() = default;
    ThrowableWeapon::ThrowableWeapon(int damageperattack , int neededstaminaperattack , int level  , string name, int price) : Weapon( damageperattack ,  neededstaminaperattack ,  level  ,  name,  price){
	}