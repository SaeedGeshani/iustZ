#pragma once
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
#include <iostream>
using namespace std;

	ColdWeapon::ColdWeapon()=default;
	ColdWeapon::ColdWeapon(int damageperattack , int neededstaminaperattack  , string name , int price) : Weapon( damageperattack ,  neededstaminaperattack ,name ,  price){
	}

