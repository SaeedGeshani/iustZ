#include<iostream>
#include<string>
#include "Enemy.h"
#include "MainCharacter.h"
#include "Zombie.h"
#include "ConsoleUI.h"

//Zombie////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Constructor===================
    Zombie::Zombie() = default;
    Zombie::Zombie(ZombieModel* enemymodel , ZombieView* enemyview , ZombieController* enemycontroller)
    {
        Enemymodel = (EnemyModel*)enemymodel;
        Enemyview = (EnemyView*)enemyview;
        Enemycontroller =(EnemyController*) enemycontroller;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ZombieModel///////////////////////////////////////////////////////////////////////////////////////////////////

    ZombieModel::ZombieModel() = default;
    ZombieModel::ZombieModel(string name , int hp , int stamina , int damageperattack , int level , int neededstaminaperattack , int zarib)
    :EnemyModel(name , hp , stamina , damageperattack , level , neededstaminaperattack , zarib)
    {
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ZombieView///////////////////////////////////////////////////////////////////////////////////////////////////

    ZombieView::ZombieView(EnemyModel* enemymodel)
    :EnemyView(enemymodel)
    {
    
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ZombieController/////////////////////////////////////////////////////////////////////////////////////////////

    ZombieController::ZombieController(EnemyModel* zombieModel)
    :EnemyController(zombieModel)
    {

    }

    void ZombieController::WeaponAttack(MainCharacter* player , int number)
    {

    }

    void ZombieController::Attack(MainCharacter* player)
    {
        if((Enemymodel->getStamina() - Enemymodel->getNeededStaminaPerAttack()) > 0 && Enemymodel->getHP() > 0)
        {
            const int hpBefore = player->getHP();
            const int baseDamage = Enemymodel->getDamagePerAttack();
            const int defenseValue = 0;
            const int finalDamage = baseDamage;

            player->setHP(player->getHP() - finalDamage);
            Enemymodel->setStamina(Enemymodel->getStamina() - Enemymodel->getNeededStaminaPerAttack());

            ui::LogAttack(Enemymodel->getName(), player->getName(), "Claws", baseDamage, defenseValue, finalDamage, hpBefore, player->getHP());
        }
        else
        {
            ui::centeredLine(Enemymodel->getName() + " cannot attack (not enough stamina or defeated).");
        }

    }

    void ZombieController::useItems(int number)
    {

    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
