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


class HumanEnemy {

protected :
    HumanEnemyModel* humanenemymodel;
    HumanEnemyView* humanenemyview;
    HumanEnemyController* humanenemycontroller;
public :
    //Getter and Setter=====================
    void setHumanEnemyModel(HumanEnemyModel* humanenemymodel);

    HumanEnemyModel* getHumanEnemyModel();

    void setHumanEnemyView(HumanEnemyView* humanenemyview);
    
    HumanEnemyView* getHumanEnemyView();
    
    void setHumanEnemyController(HumanEnemyController* humanenemycontroller);
   
    HumanEnemyController* getHumanEnemyController();
    
    //Constructor==============================
    HumanEnemy();
    HumanEnemy(HumanEnemyModel* humanenemymodel , HumanEnemyView* humanenemyview , HumanEnemyController* humanenemycontroller);
   
};

class HumanEnemyController{
protected:
    HumanEnemyModel* humanenemymodel;
public:
    //Constructor======================
    HumanEnemyController();
    HumanEnemyController(HumanEnemyModel* humanenemymodel);
    
    //Setter and Getters===============
    void setHumanEnemyModel(HumanEnemyModel* humanenemymodel);
    
    HumanEnemyModel* getHumanEnemyModel();
   
    //Functions=========================
    void Attack(MainCharacter* player);
    int CheckHealth(MainCharacter* player);
    int CheckStamina(MainCharacter* player);
    
};
class HumanEnemyView{
protected:
    HumanEnemyModel* humanenemymodel;
public: 
    //Setter and Getters=========================
    void setHumanEnemyModel(HumanEnemyModel* humanenemymodel);
    
    HumanEnemyModel* getHumanEnemyModel();
   
    //Constructors===============================
    HumanEnemyView();
    HumanEnemyView(HumanEnemyModel* humanenemymodel);
    
    //Friend classes and Functions===============
    friend class HumanEnemyModel;
    friend class HumanEnemyController;
    //Functions==================================
    virtual void ShowHumanEnemyInfo();
    
};
class HumanEnemyModel{
protected:
    string Name;
    int HP;
    int DamagePerAttack;
    int Stamina;
    int Level;
    int neededStaminaPerAttack; 
public:
    //Friend classes ==========================
    friend class HumanEnemyView;
    friend class HumanEnemyController;
    //Setter & Getters ==========================
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
