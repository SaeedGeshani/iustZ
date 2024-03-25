#pragma once
#include<string>
#include<vector>
#include<iostream>
#include "MainCharacter.h"
#include "Enemy.h"
#include "Zombie.h"
using namespace std;

class Enemy;
class EnemyModel;
class EnemyView;
class EnemyController;
class MainCharacter;
class Zombie;
class ZombieModel;
class ZombieView;
class ZombieController;
class UseableItems;
class Weapon;
class Enemy;


class HumanEnemy : public Enemy{

protected :
    // HumanEnemyModel* humanenemymodel;
    // HumanEnemyView* humanenemyview;
    // HumanEnemyController* humanenemycontroller;
public :
    //Getter and Setter=====================
    void setHumanEnemyModel(EnemyModel* humanenemymodel);

    EnemyModel* getHumanEnemyModel();

    void setHumanEnemyView(EnemyView* humanenemyview);
    
    EnemyView* getHumanEnemyView();
    
    void setHumanEnemyController(EnemyController* humanenemycontroller);
   
    EnemyController* getHumanEnemyController();
    
    //Constructor==============================
    HumanEnemy();
    HumanEnemy(EnemyModel* humanenemymodel , EnemyView* humanenemyview , EnemyController* humanenemycontroller);
   
};

class HumanEnemyController : public EnemyController{
protected:
    // HumanEnemyModel* humanenemymodel;
public:
    //Constructor======================
    HumanEnemyController();
    HumanEnemyController(EnemyModel* humanenemymodel);
    
    //Setter and Getters===============
    void setHumanEnemyModel(EnemyModel* humanenemymodel);
    
    EnemyModel* getHumanEnemyModel();
   
    //Functions=========================
    void WeaponAttack(MainCharacter* player , int number) override;
    void Attack(MainCharacter* player ) override;
    void useItems(int number) override;
    int CheckHealth();
    int CheckStamina();
    
};
class HumanEnemyView : public EnemyView{
protected:
    // HumanEnemyModel* humanenemymodel;
public: 
    //Setter and Getters=========================
    void setHumanEnemyModel(EnemyModel* humanenemymodel);
    
    EnemyModel* getHumanEnemyModel();
   
    //Constructors===============================
    HumanEnemyView();
    HumanEnemyView(EnemyModel* humanenemymodel);
    
    //Friend classes and Functions===============
    friend class HumanEnemyModel;
    friend class HumanEnemyController;
    //Functions==================================
    virtual void ShowHumanEnemyInfo();
    
};
class HumanEnemyModel : public EnemyModel{
protected:
    
public:
    //Friend classes ==========================
    friend class HumanEnemyView;
    friend class HumanEnemyController;
    //Setter & Getters ==========================
    virtual void setEnemyWeapons(vector<Weapon*>enemyweapon);

    virtual vector<Weapon*> getEnemyWeapons();

    virtual void setEnemyUseableItems(vector<UseableItems*>enemyuseableitems);

    virtual vector<UseableItems*> getEnemyUseableItems();

    void setNeededStaminaPerAttack(int neededstperattack);
    
    int getNeededStaminaPerAttack();
   
    void setLevel(int level);
  
    int getLevel();
    
    void setName(string name);
    
    string getName();
   
    void setHP(int hp);
  
    int getHP();
    
    void setDamagePerAttack(int damageperattack);
    
    int getDamagePerAttack();
    
    void setStamina(int stamina);
   
    int getStamina();
   
    //=========================================
    //Constructor==============================
    HumanEnemyModel();
    HumanEnemyModel(string name , int hp , int stamina , int damageperattack , int level);
    
};

class HumanEnemyFactory{
private:
    int HumanEnemyLevel;
public:
    //Constructor========================
    HumanEnemyFactory();
    HumanEnemyFactory(int enemylevel);
   
    //Setter and Getters=================
    void setHumanEnemyLevel(int enemylevel);
   
    int getHumanEnemyLevel();
    
    //Algorithm Of Calculating==========

    // Code is in functions and they're below.
    //Functions=========================
    Zombie* makeZombie();

    
};

enum Healing {
    Low = 0 ,
    Average = 50 ,
    High = 100
};

enum Stamina {
    low = 0 ,
    average = 50 ,
    high = 100
};
