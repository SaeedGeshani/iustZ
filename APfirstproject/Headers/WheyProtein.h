#pragma once
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "UseableItems.h"
using namespace std;

class WheyProtein : public UseableItems{
	public:
		WheyProtein();
		WheyProtein(int energy , int healingpower , std::string name, int price, int addedxp);
};