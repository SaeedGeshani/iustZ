#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
#include "HotWeapon.h"
#include "Spear.h"
#include <iostream>
using namespace std;
 
	Spear::Spear()=default;
	Spear::Spear(int damageperattack , int neededstaminaperattack  , string name , int price) : ColdWeapon( damageperattack ,  neededstaminaperattack ,name ,  price){
	}

