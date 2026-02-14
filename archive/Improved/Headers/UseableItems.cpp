#include "MainCharacter.h"
#include "Weapon.h"
#include "UseableItems.h"
#include<string>
using namespace std;



    //Setter & Getters---------

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
    void UseableItems::setAddedXP(int adxp)
    {
        addedXP = adxp;
    }
    int UseableItems::getAddedXP()
    {
        return addedXP;
    }
    
    //------------------------
    //Constructors============
    UseableItems::UseableItems() = default;
    UseableItems::UseableItems(int energy , int healingpower  , string name, int price, int addedxp) : Items( name,  price)
    {  
        Energy = energy;
        HealingPower = healingpower;
        addedXP=addedxp;
    }
    UseableItems::~UseableItems()
    {
        int a;
        a++;
    }
