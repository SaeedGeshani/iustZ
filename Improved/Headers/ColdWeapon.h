#pragma once
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
using namespace std;
class ColdWeapon: virtual public Weapon{
	public:
		ColdWeapon();
		ColdWeapon(int damageperattack , int neededstaminaperattack  , string name , int price);
};