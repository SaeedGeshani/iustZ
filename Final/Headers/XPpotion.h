#pragma once
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "UseableItems.h"
using namespace std;

class XPpotion : public UseableItems{
	public:
		XPpotion();
		XPpotion(int energy , int healingpower , std::string name, int price, int addedxp);
};