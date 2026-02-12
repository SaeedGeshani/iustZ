#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "UseableItems.h"
#include "XPpotion.h"
#include <iostream>
using namespace std;
	XPpotion::XPpotion()=default;
	XPpotion::XPpotion(int energy , int healingpower , std::string name, int price, int addedxp) : UseableItems( energy ,  healingpower ,  name,  price,  addedxp){
	}