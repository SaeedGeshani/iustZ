#include "MainCharacter.h"
#include "Weapon.h"
#include "UseableItems.h"
#include<string>
using namespace std;



    //Setter & Getters---------
    void UseableItems::setType(std::string classname)
    {
        className = classname;
    }
    std::string UseableItems::getType()
    {
        return className;
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
    UseableItems::UseableItems(int energy , int healingpower , int level , string classname , string name, int price) : Items( name,  price)
    {  
        className = classname;
//        Name = name;
        Energy = energy;
        HealingPower = healingpower;
        Level = level;
    }
