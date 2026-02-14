#pragma once
#include<vector>
#include<string>
#include "Items.h"
using namespace std;

class Weapon: public Items{
protected:
    int damagePerAttack;
    int neededStaminaPerAttack;
public:
    //Setter & Getter
    void setPrice(int price);
 
    int getPrice();

    void setDamagePerAttack(int damageperattack);
   
    int getDamagePerAttack();
    
    void setNeededStaminaPerAttack(int neededstaminaperattack);
    
    int getNeededStaminaPerAttack();
    
    
    //============================
    //Constructor=================
    Weapon();
    Weapon(int damageperattack , int neededstaminaperattack  , string name , int price);
    
    //====================================================================
    //destructor:
    virtual ~Weapon() ;
    //Attack Function ====================================================
    //virtual void Attack(MainCharacter* Player , EnemyModel* zombie);
    
};
