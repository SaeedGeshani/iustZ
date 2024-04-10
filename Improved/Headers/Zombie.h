#pragma once
#include<string>
#include<iostream>
#include "Enemy.h"

using namespace std;
class ZombieModel;
class ZombieView;
class ZombieController;

class ZombieController : public EnemyController{
protected:

public:
    ZombieController(EnemyModel* zombieModel);
    virtual void WeaponAttack(MainCharacter*player , int number) override;
    virtual void Attack(MainCharacter* player) override;
    virtual void useItems(int number) override;
};
class ZombieView : public EnemyView{
protected:

public:
    ZombieView(EnemyModel* enemymodel);
};
class ZombieModel : public EnemyModel{
protected:

public:
    ZombieModel();
    ZombieModel(string name , int hp , int stamina , int damageperattack , int level , int neededdamageperattack , int zarib);
};
class Zombie : public Enemy{
protected:

public:
    //Constructor===================
    Zombie();
    Zombie(ZombieModel* enemymodel , ZombieView* enemyview , ZombieController* enemycontroller);
};
