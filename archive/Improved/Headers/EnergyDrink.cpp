#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"
#include "UseableItems.h"
#include "EnergyDrink.h"
#include <iostream>
using namespace std;
	EnergyDrink::EnergyDrink()=default;
	EnergyDrink::EnergyDrink(int energy , int healingpower , std::string name, int price, int addedxp) : UseableItems( energy ,  healingpower ,  name,  price,  addedxp){
	}