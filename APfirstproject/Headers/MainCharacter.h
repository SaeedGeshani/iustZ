#pragma once
#include<string>
#include<iostream>
#include<vector>
#include "Enemy.h"
#include "Weapon.h"
#include "ThrowableWeapon.h"
#include "UseableItems.h"

using namespace std;
class UseableItems;
class Weapon;
class Enemy;

class MainCharacter{
protected:
    string Name;
    int HP;
    int XP;
	int Level;
    string Gender;
    int Stamina;
    int Gold;
    vector<UseableItems*> useAbleItems;
    vector<Weapon*>weapons;

public:
    //Setter & Getters ================
    void setGold(int gold);
   
    int getGold();

    void setName(string name);
  
    string getName();
    
    void setLevel(int level);
    
    int getLevel();
   
    void setHP(int hp);
    
    int getHP();
    
    void setXP(int xp);
   
    int getXP();
    
    void setGender(string gender);
   
    string getGender();
    
    void setStamina(int stamina);
    
    int getStamina();
    
    //=====================================
    void addWeapon(Weapon * weapon);
    
    vector<Weapon*> &getWeapons();
   
    void addUseableItems(UseableItems* useableitem);
   
    vector<UseableItems*> &getUseableItems();

    void showCharacterWeapons();

    void showCharacterUsableItems();

    void useItem(int);
   
    //Attack func==========================
    void Attack(Enemy* enemy, Weapon* weapon);

    //Constructors=========================
    MainCharacter();
    MainCharacter(string name , int hp , int xp , int stamina , string gender , int gold);
    
    //=====================================
};