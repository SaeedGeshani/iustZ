#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
#include "HotWeapon.h"
#include "Mjolnir.h"
#include <iostream>
using namespace std;
 
	Mjolnir::Mjolnir()=default;
	Mjolnir::Mjolnir(int damageperattack , int neededstaminaperattack  , string name , int price) : ColdWeapon( damageperattack ,  neededstaminaperattack ,name ,  price){
	}

