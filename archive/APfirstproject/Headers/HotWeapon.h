#pragma once
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
using namespace std;
class HotWeapon: virtual public Weapon{
	public:
		HotWeapon();
		HotWeapon(int damageperattack , int neededstaminaperattack  , string name , int price);
};