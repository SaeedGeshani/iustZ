#pragma once
#include<vector>
#include<string>
#include "MainCharacter.h"
#include "Enemy.h"
using namespace std;

class Weapon{
protected:
    int damagePerAttack;
    int neededStaminaPerAttack;
    int Level;
    int Price;
    string Type;
    string Name;
public:
    //Setter & Getter
    void setPrice(int price);
   
    int getPrice();
    
    void setDamagePerAttack(int damageperattack);
   
    int getDamagePerAttack();
    
    void setNeededStaminaPerAttack(int neededstaminaperattack);
    
    int getNeededStaminaPerAttack();
    
    void setName(string name);
    
    string getName();
    
    void setType(string type);
    
    string getType();
    
    //============================
    //Constructor=================
    Weapon() = default;
    Weapon(int damageperattack , int neededstaminaperattack , int level , string type , string name);
    
    //====================================================================
    //Attack Function ====================================================
    virtual void Attack(MainCharacter* Player , EnemyModel* zombie);
    
};