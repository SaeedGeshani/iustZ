#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "ThrowableWeapon.h"
#include "PermenantWeapon.h"
#include "ColdWeapon.h"
#include "HotWeapon.h"
#include "MiniGun.h"
#include <iostream>
using namespace std;
 
	MiniGun::MiniGun()=default;
	MiniGun::MiniGun(int damageperattack , int neededstaminaperattack  , string name , int price) : HotWeapon( damageperattack ,  neededstaminaperattack ,name ,  price){
	}

