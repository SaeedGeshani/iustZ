#pragma once
#include <string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Items.h"

using namespace std; 

class UseableItems: public Items{

private:
    int Energy;
    int HealingPower;
    int Level;
    std::string className;

public:
    //Setter & Getters---------
    void setType(std::string classname);
   
    std::string getType();
    
    void setEnergy(int energy);
    
    int getEnergy();
   
    void setHealingPower(int healingpower);
    
    int getHealingPower();
    
    //------------------------
    //Constructors============
    UseableItems();
    UseableItems(int energy , int healingpower , int level , std::string classname , std::string name, int price);
    
};