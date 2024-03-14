#include<string>
#include<iostream>
#include<vector>
#include "MainCharacter.h"
#include "Weapon.h"
#include "ThrowableWeapon.h"

using namespace std;

//ThrowableWeapon//////////////////////////////////////////////////////////////////////////////////////////////////

    //Constructors==================================
    ThrowableWeapon::ThrowableWeapon() = default;
    ThrowableWeapon::ThrowableWeapon(int damageperattack , int neededstaminaperattack , int level , string type , string name)
    {
        damagePerAttack = damageperattack;
        neededStaminaPerAttack = neededstaminaperattack;
        Level = level;
        Type = type;
        Name = name;
    }
    //==============================================
    //Attack function===============================
    void ThrowableWeapon::Attack(MainCharacter* Player , EnemyModel* zombie) 
    {
        if(Player->getStamina() >= neededStaminaPerAttack)
        {
            zombie->setHP(zombie->getHP() - damagePerAttack);
            Player->setStamina(Player->getStamina() - neededStaminaPerAttack);

            for(int i = 0 ; i < Player->getWeapons().size() ; i++)
            {
                if(Player->getWeapons()[i] == this)
                {
                    Player->getWeapons().erase(Player->getWeapons().begin() + i);
                    break;
                }
            }
        }
        else{

            cout << "your stamina is less than gun's needed stamina and you will die soon :)";
        }
    }

