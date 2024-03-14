#pragma once
#include "MainCharacter.h"
#include "Weapon.h"

using namespace std;

class UseableItems{

private:
    int Energy;
    int HealingPower;
    int Level;
    int Price;
    string className;
    string Name;
public:
    //Setter & Getters---------
    void setName(string name);
    
    string getName();
    
    void setType(string classname);
    
    string getType();
   
    void setPrice(int price);
    
    int getPrice();
    
    void setEnergy(int energy);
    
    int getEnergy();
    
    void setHealingPower(int healingpower);
    
    int getHealingPower();
    
    //------------------------
    //Constructors============
    UseableItems() = default;
    UseableItems(int energy , int healingpower , int level , string classname , string name);
   
};
