#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "UseableItems.h"
#include "Egg.h"
#include <iostream>
using namespace std;
	Egg::Egg()=default;
	Egg::Egg(int energy , int healingpower , std::string name, int price, int addedxp) : UseableItems( energy ,  healingpower ,  name,  price,  addedxp){
	}