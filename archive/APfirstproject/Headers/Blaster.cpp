#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
#include "HotWeapon.h"
#include "Blaster.h"
#include <iostream>
using namespace std;
 
	Blaster::Blaster()=default;
	Blaster::Blaster(int damageperattack , int neededstaminaperattack  , string name , int price){

		damagePerAttack = damageperattack;
		neededStaminaPerAttack = neededstaminaperattack;
		Name = name;
		Price = price;
	}