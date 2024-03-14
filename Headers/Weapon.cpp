#include<string>
#include<vector>
#include<iostream>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Enemy.h"

using namespace std;

//Weapon//////////////////////////////////////////////////////////////////////////////////////////

    //Setter & Getter
    void Weapon::setPrice(int price)
    {
        Price = price;
    }
    int Weapon::getPrice()
    {
        return Price;
    }
    void Weapon::setDamagePerAttack(int damageperattack)
    {
        damagePerAttack = damageperattack;
    }
    int Weapon::getDamagePerAttack()
    {
        return damagePerAttack;
    }
    void Weapon::setNeededStaminaPerAttack(int neededstaminaperattack)
    {
        neededStaminaPerAttack = neededstaminaperattack;
    }
    int Weapon::getNeededStaminaPerAttack()
    {
        return neededStaminaPerAttack;
    }
    void Weapon::setName(string name)
    {
        Name = name;
    }
    string Weapon::getName()
    {
        return Name;
    }
    void Weapon::Weapon::setType(string type)
    {
        Type = type;
    }
    string Weapon::getType()
    {
        return Type;
    }
    //============================
    //Constructor=================
    Weapon::Weapon() = default;
    Weapon::Weapon(int damageperattack , int neededstaminaperattack , int level , string type , string name)
    {
        Type = type;
        Name = name;
        damagePerAttack = damageperattack;
        neededStaminaPerAttack = neededstaminaperattack;
        Level = level;
    }
    //====================================================================
    //Attack Function ====================================================
    void Weapon::Attack(MainCharacter* Player , EnemyModel* zombie)
    {
        if(Player->getStamina() >= neededStaminaPerAttack)
        {
            zombie->setHP(zombie->getHP() - damagePerAttack);
            Player->setStamina(Player->getStamina() - neededStaminaPerAttack);
        }
        else{

            cout << "your stamina is less than gun's needed stamina and you will die soon :)";
        }

    }


