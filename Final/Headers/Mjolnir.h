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
class Mjolnir : public ColdWeapon, public PermenantWeapon{
	public:
		Mjolnir();
		Mjolnir(int damageperattack , int neededstaminaperattack  , string name , int price);
};