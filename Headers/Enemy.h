#pragma once
#include<string>
#include<iostream>
#include "MainCharacter.h"
using namespace std;
    class EnemyView;
    class EnemyModel;
    class EnemyController;
    class MainCharacter;

class EnemyController{
protected:
    EnemyModel* Enemymodel;
public:
    //Constructor======================
    EnemyController() = default;
    EnemyController(EnemyModel* enemymodel);
    
    //Setter and Getters===============
    void setEnemyModel(EnemyModel* enemymodel);
    
    EnemyModel* getEnemyModel();
   
    //Functions=========================
    void Attack(MainCharacter* player);
    
};
class EnemyView{
protected:
    EnemyModel* Enemymodel;
public: 
    //Setter and Getters=========================
    void setEnemyModel(EnemyModel* enemymodel);
    
    EnemyModel* getEnemyModel();
   
    //Constructors===============================
    EnemyView() = default;
    EnemyView(EnemyModel* enemymodel);
    
    //Friend classes and Functions===============
    friend class EnemyModel;
    friend class EnemyController;
    //Functions==================================
    virtual void ShowEnemyInfo();
    
};
class EnemyModel{
protected:
    string Name;
    int HP;
    int DamagePerAttack;
    int Stamina;
    int Level;
    int neededStaminaPerAttack; 
public:
    //Friend classes ==========================
    friend class EnemyView;
    friend class EnemyController;
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
    EnemyModel() = default;
    EnemyModel(string name , int hp , int stamina , int damageperattack , int level);
    
};
class Enemy{
  
protected:
    EnemyModel* Enemymodel;
    EnemyView* Enemyview;
    EnemyController* Enemycontroller;
public:
    //Getter and Setter=====================
    void setEnemyModel(EnemyModel* enemymodel);

    EnemyModel* getEnemyModel();

    void setEnemyView(EnemyView* enemyview);
    
    EnemyView* getEnemyView();
    
    void setEnemyController(EnemyController* enemycontroller);
   
    EnemyController* getEnemyController();
    
    //Constructor==============================
    Enemy() = default;
    Enemy(EnemyModel* enemymodel , EnemyView* enemyview , EnemyController* enemycontroller);
   
};

