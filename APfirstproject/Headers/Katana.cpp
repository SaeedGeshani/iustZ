
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
#include "HotWeapon.h"
#include "Katana.h"
#include <iostream>
using namespace std;
 
	Katana::Katana()=default;
	Katana::Katana(int damageperattack , int neededstaminaperattack  , string name , int price) : ColdWeapon( damageperattack ,  neededstaminaperattack ,name ,  price){
	}

