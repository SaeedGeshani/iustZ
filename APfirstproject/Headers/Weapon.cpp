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

    //============================
    //Constructor=================
    Weapon::Weapon() = default;
    Weapon::Weapon(int damageperattack , int neededstaminaperattack  , string name , int price) : Items(name, price)
    {

        damagePerAttack = damageperattack;
        neededStaminaPerAttack = neededstaminaperattack;
 
    }
    Weapon::~Weapon(){
    	int b=0;
    	b++;
	}
    //====================================================================
    //Attack Function ====================================================
    // void Weapon::Attack(MainCharacter* Player , EnemyModel* zombie)
    // {
    //     if(Player->getStamina() >= neededStaminaPerAttack)
    //     {
    //         zombie->setHP(zombie->getHP() - damagePerAttack);
    //         Player->setStamina(Player->getStamina() - neededStaminaPerAttack);
    //     }
    //     else{

    //         cout << "your stamina is less than gun's needed stamina and you will die soon :)";
    //     }

    // }


