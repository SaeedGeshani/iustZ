#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
#include "HotWeapon.h"
#include "RocketLauncher.h"
#include <iostream>
using namespace std;
 
	RocketLauncher::RocketLauncher()=default;
	RocketLauncher::RocketLauncher(int damageperattack , int neededstaminaperattack  , string name , int price) : HotWeapon( damageperattack ,  neededstaminaperattack ,name ,  price){
	}

