#pragma once
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"

using namespace std; 

class UseableItems: public Items{

protected:
    int Energy;
    int HealingPower;
	int addedXP;

public:
    //Setter & Getters---------

    
    void setEnergy(int energy);
    
    int getEnergy();
   
    void setHealingPower(int healingpower);
    
    int getHealingPower();
    
    void setAddedXP(int adxp);
    
    int getAddedXP();
	
    
    //------------------------
    //Constructors============
    UseableItems();
    UseableItems(int energy , int healingpower , std::string name, int price, int addedxp);
    
};