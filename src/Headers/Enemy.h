#pragma once
#include<string>
#include<iostream>
#include<vector>
#include "Weapon.h"
#include "UseableItems.h"
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
    EnemyController();
    EnemyController(EnemyModel* enemymodel);
    
    //Setter and Getters===============
    void setEnemyModel(EnemyModel* enemymodel);


    
    EnemyModel* getEnemyModel();
    
    //Functions=========================
    virtual void WeaponAttack(MainCharacter* player , int number) = 0;

    virtual void Attack(MainCharacter* player) = 0;

    virtual void useItems(int number) = 0;

    
    
};
class EnemyView{
protected:
    EnemyModel* Enemymodel;
public: 
    //Setter and Getters=========================
    void setEnemyModel(EnemyModel* enemymodel);
    
    EnemyModel* getEnemyModel();
   
    //Constructors===============================
    EnemyView();
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
    int Zarib;
    
public:
    //Friend classes ==========================
    vector<Weapon*>EnemyWeapons;
    vector<UseableItems*>EnemyUseableItems;
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

    void setZarib(int zarib);

    int getZarib();

    //=========================================
    //Constructor==============================
    EnemyModel();
    EnemyModel(string name , int hp , int stamina , int damageperattack , int level , int neededstaminaperattack , int zarib);
    
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
    Enemy();
    Enemy(EnemyModel* enemymodel , EnemyView* enemyview , EnemyController* enemycontroller);
   
};
