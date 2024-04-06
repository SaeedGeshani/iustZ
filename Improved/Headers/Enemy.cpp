#include "Enemy.h"
#include<string>
#include "MainCharacter.h"

using namespace std;

//Enemy/////////////////////////////////////////////////////////////////////////////
    //Getter and Setter=====================
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyModel//////////////////////////////////////////////////////////////////////////////////////////////////

    //Setter & Getters ==========================
    void EnemyModel::setEnemyWeapons(vector<Weapon*> enemyweapon)
    {
        EnemyWeapons = enemyweapon;
    }

    vector<Weapon*> EnemyModel::getEnemyWeapons()
    {
        return EnemyWeapons;
    }

    void EnemyModel::setEnemyUseableItems(vector<UseableItems*> enemyuseableitem)
    {
        EnemyUseableItems = enemyuseableitem;
    }

    vector<UseableItems*> EnemyModel:: getEnemyUseableItems()
    {
        return EnemyUseableItems;
    }

    void EnemyModel::setNeededStaminaPerAttack(int neededstperattack)
    {
        if(neededstperattack < 0)
        {
            cout << "Enemy can't attack the player." << endl;
        }
        else{
            neededStaminaPerAttack = neededstperattack;
        }
    }
    int EnemyModel::getNeededStaminaPerAttack()
    {
        return neededStaminaPerAttack;
    }
    void EnemyModel::setLevel(int level)
    {
        Level = level;
    }
    int EnemyModel::getLevel()
    {
        return Level;
    }
    void EnemyModel::setName(std::string name)
    {
        Name = name;
    }
    std::string EnemyModel::getName()
    {
        return Name;
    }
    void EnemyModel::setHP(int hp)
    {
        HP = hp;
    }
    int EnemyModel::getHP()
    {
        return HP;
    }
    void EnemyModel::setDamagePerAttack(int damageperattack)
    {
        DamagePerAttack = damageperattack;
    }
    int EnemyModel::getDamagePerAttack()
    {
        return DamagePerAttack;
    }
    void EnemyModel::setStamina(int stamina)
    {
        Stamina = stamina;
    }
    int EnemyModel::getStamina()
    {
        return Stamina;
    }
    //=========================================
    //Constructor==============================
    EnemyModel::EnemyModel() = default;
    EnemyModel::EnemyModel(string name , int hp , int stamina , int damageperattack , int level , int neededstaminaperattack)
    {
        Name = name;
        HP = hp;
        Stamina = stamina;
        DamagePerAttack = damageperattack;
        Level = level;
        neededStaminaPerAttack = neededstaminaperattack;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyView/////////////////////////////////////////////////////////////////////////////////////////
 
    //Setter and Getters=========================
    void EnemyView::setEnemyModel(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }
    EnemyModel* EnemyView::getEnemyModel()
    {
        return Enemymodel;
    }
    //Constructors===============================
    EnemyView::EnemyView() = default;
    EnemyView::EnemyView(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }

    //Functions==================================
    void EnemyView::ShowEnemyInfo()
    {
        cout << "Here is status of enemy : " << endl;
        cout << "Enemy's Name: " << Enemymodel->getName() << endl;
        cout << "Enemy's HP : " << Enemymodel->getHP() << endl;
        cout << "Enemy's Stamina: " << Enemymodel->getStamina() << endl;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyController/////////////////////////////////////////////////////////////////////////////////////////



    //Constructor======================
    EnemyController::EnemyController() = default;
    EnemyController::EnemyController(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }
    //Setter and Getters===============
    void EnemyController::setEnemyModel(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }
    EnemyModel* EnemyController::getEnemyModel()
    {
        return Enemymodel;
    }
    //Functions========================
   
