#pragma once
#include<string>
#include<vector>
#include<iostream>
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
    EnemyModel();
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
    Enemy();
    Enemy(EnemyModel* enemymodel , EnemyView* enemyview , EnemyController* enemycontroller);
   
};

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
    ZombieModel();
    ZombieModel(string name , int hp , int stamina , int damageperattack , int level);
};
class Zombie : public Enemy{
protected:

public:
    //Constructor===================
    Zombie();
    Zombie(ZombieModel* enemymodel , ZombieView* enemyview , ZombieController* enemycontroller);
};

class Items{
	protected:
		string Name;
		int Price;
	public:
		//constructor
		
		Items();
		Items(string name, int price);

		//getter and setter
	    void setName(string name);
    	
    	string getName();
    	
	   void setPrice(int price);
    	
    	
    	int getPrice();
    	
	//operator overloading:
	bool operator==(Items other);
};

class Weapon{
protected:
    int damagePerAttack;
    int neededStaminaPerAttack;
    int Level;
    int Price;
    string Type;
    string Name;
public:
    //Setter & Getter
    void setLevel(int);

    int getLevel();
    
    void setPrice(int price);
   
    int getPrice();
    
    void setDamagePerAttack(int damageperattack);
   
    int getDamagePerAttack();
    
    void setNeededStaminaPerAttack(int neededstaminaperattack);
    
    int getNeededStaminaPerAttack();
    
    void setName(string name);
    
    string getName();
    
    void setType(string type);
    
    string getType();
    
    //============================
    //Constructor=================
    Weapon();
    Weapon(int damageperattack , int neededstaminaperattack , int level , string type , int price);
    
    //====================================================================
    //Attack Function ====================================================
    //virtual void Attack(MainCharacter* Player , EnemyModel* zombie);
    
};

class PermenantWeapon : public Weapon{

public:
    //Constructors==================================
    PermenantWeapon();
    PermenantWeapon(int damageperattack , int neededstaminaperattack , int level  , string name, int price);
     
};

class Shop{
private:
    int Level;
    string Name;

public:
    Shop();
    Shop(string name , int level);
    
    //Setter & Getters=================
    void setName(string name);
    
    string getName();
    
    void setLevel(int level);
    
    int getLevel();

    void ShowItems();

    void BuyItem(MainCharacter* player);

};

class ThrowableWeapon : public Weapon{
public:
    //Constructors==================================
    ThrowableWeapon();
    ThrowableWeapon(int damageperattack , int neededstaminaperattack , int level  , string name, int price);
};

class UseableItems: public Items{

private:
    int Energy;
    int HealingPower;
    int Level;
    std::string className;

public:
    //Setter & Getters---------
    void setType(std::string classname);
   
    std::string getType();
    
    void setEnergy(int energy);
    
    int getEnergy();
   
    void setHealingPower(int healingpower);
    
    int getHealingPower();
    
    //------------------------
    //Constructors============
    UseableItems();
    UseableItems(int energy , int healingpower , int level , std::string classname , std::string name, int price);
    
};

class EnemyFactory{
private:
    int EnemyLevel;
public:
    //Constructor========================
    EnemyFactory();
    EnemyFactory(int enemylevel);
   
    //Setter and Getters=================
    void setEnemyLevel(int enemylevel);
   
    int getEnemyLevel();
    
    //Algorithm Of Calculating==========

    // Code is in functions and they're below.
    //Functions=========================
    Zombie* makeZombie();
    
};

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

int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);
