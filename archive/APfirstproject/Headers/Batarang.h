#pragma once
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
using namespace std;
class Batarang : public ColdWeapon, public ThrowableWeapon{
	public:
		
		Batarang();
		Batarang(int damageperattack , int neededstaminaperattack  , string name , int price);
};