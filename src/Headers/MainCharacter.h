#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<cmath>

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
    int Kills;

public:
    //Setter & Getters ================
    void setKills(int kills);

    int getKills();
    
    void setGold(int gold);
   
    int getGold();

    void setName(const string& name);
  
    string getName();
    
    void setLevel(int level);
    
    int getLevel();
   
    void setHP(int hp);
    
    int getHP();
    
    void setXP(int xp);
   
    int getXP();
    
    void setGender(const string& gender);
   
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

    void CalculateLevel();
   
    //Attack func==========================
    void Attack(Enemy* enemy, Weapon* weapon);

    void getEnemyWeapons(const vector<Weapon*>& enemyweps);

    void getEnemyUseableItems(const vector<UseableItems*>& enemyuseableitems);

    //Constructors=========================
    MainCharacter();
    MainCharacter(const string& name , int hp , int xp , int stamina , const string& gender , int gold);
    
    //=====================================
};
