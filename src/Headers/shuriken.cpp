#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
#include "HotWeapon.h"
#include "shuriken.h"
#include <iostream>
using namespace std;
 
	shuriken::shuriken()=default;
	shuriken::shuriken(int damageperattack , int neededstaminaperattack  , string name , int price) : ColdWeapon( damageperattack ,  neededstaminaperattack ,name ,  price){
	}

