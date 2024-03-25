#include<iostream>
#include<string>
#include "Enemy.h"
#include "Zombie.h"

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
    ZombieModel::ZombieModel(string name , int hp , int stamina , int damageperattack , int level , int neededstaminaperattack)
    :EnemyModel(name , hp , stamina , damageperattack , level , neededstaminaperattack)
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
        
        if((Enemymodel->getStamina() - Enemymodel->getNeededStaminaPerAttack()) > 0)
        {
        player->setHP(player->getHP() - Enemymodel->getDamagePerAttack());
        Enemymodel->setStamina(Enemymodel->getStamina() - Enemymodel->getNeededStaminaPerAttack());
        }
        else{
            cout << "Enemy Doesn't have enough Energy to attack" << endl;
        }

    }

    void ZombieController::useItems(int number)
    {

    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
