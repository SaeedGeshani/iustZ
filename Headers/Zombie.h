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
};
class ZombieView : public EnemyView{
protected:

public:
    ZombieView(EnemyModel* enemymodel);
};
class ZombieModel : public EnemyModel{
protected:

public:
    ZombieModel() = default;
    ZombieModel(string name , int hp , int stamina , int damageperattack , int level);
};
class Zombie : public Enemy{
protected:

public:
    //Constructor===================
    Zombie() = default;
    Zombie(ZombieModel* enemymodel , ZombieView* enemyview , ZombieController* enemycontroller);
};
