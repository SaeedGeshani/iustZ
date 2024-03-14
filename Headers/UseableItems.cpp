#include "MainCharacter.h"
#include "Weapon.h"
#include "UseableItems.h"
using namespace std;


    //Setter & Getters---------
    void UseableItems::setName(string name)
    {
        Name = name;
    }
    string UseableItems::getName()
    {
        return Name;
    }
    void UseableItems::setType(string classname)
    {
        className = classname;
    }
    string UseableItems::getType()
    {
        return className;
    }
    void UseableItems::setPrice(int price)
    {
        Price = price;
    }
    int UseableItems::getPrice()
    {
        return Price;
    }
    void UseableItems::setEnergy(int energy)
    {
        Energy = energy;
    }
    int UseableItems::getEnergy()
    {
        return Energy;
    }
    void UseableItems::setHealingPower(int healingpower)
    {
        HealingPower = healingpower;
    }
    int UseableItems::getHealingPower()
    {
        return HealingPower;
    }
    //------------------------
    //Constructors============
    UseableItems::UseableItems() = default;
    UseableItems::UseableItems(int energy , int healingpower , int level , string classname , string name)
    {  
        className = classname;
        Name = name;
        Energy = energy;
        HealingPower = healingpower;
        Level = level;
    }
