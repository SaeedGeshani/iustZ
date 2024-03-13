#include "Enemy.h"
using namespace std;
class Enemy;
class EnemyModel;
class EnemyView;
class EnemyController;

    void Enemy::setEnemyModel(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }
    EnemyModel* Enemy::getEnemyModel()
    {
        return Enemymodel;
    }
    void Enemy::setEnemyView(EnemyView* enemyview)
    {
        Enemyview = enemyview;
    }
    EnemyView* Enemy::getEnemyView()
    {
        return Enemyview;
    }
    void Enemy::setEnemyController(EnemyController* enemycontroller)
    {
        Enemycontroller = enemycontroller;
    }
    EnemyController* Enemy::getEnemyController()
    {
        return Enemycontroller;
    }
    //Constructor==============================
    Enemy::Enemy() = default;
    Enemy::Enemy(EnemyModel* enemymodel , EnemyView* enemyview , EnemyController* enemycontroller)
    {
        Enemymodel = enemymodel;
        Enemyview = enemyview;
        Enemycontroller = enemycontroller;
    }

