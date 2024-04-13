#pragma once
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
#include "HotWeapon.h"
using namespace std;
class MiniGun : public HotWeapon, public PermenantWeapon{
	public:
		MiniGun();
		MiniGun(int damageperattack , int neededstaminaperattack  , string name , int price);
};