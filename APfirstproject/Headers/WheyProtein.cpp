#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "UseableItems.h"
#include "WheyProtein.h"
#include <iostream>
using namespace std;
	WheyProtein::WheyProtein()=default;
	WheyProtein::WheyProtein(int energy , int healingpower , std::string name, int price, int addedxp) : UseableItems( energy ,  healingpower ,  name,  price,  addedxp){
	}