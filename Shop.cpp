#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<ctime>
#include "Headers/EnemyFactory.h"
#include "Headers/EnemyFactory.cpp"
#include "Headers/Zombie.h"
#include "Headers/Zombie.cpp"
#include "Headers/Enemy.h"
#include "Headers/Enemy.cpp"
#include "Headers/MainCharacter.h"
#include "Headers/MainCharacter.cpp"
using namespace std;

class MainCharacter;
class Weapon;
class UseableItems;
class Shop;
class EnemyModel;
class EnemyView;
class EnemyController;
class Enemy;
class EnemyFactory;
class Zombie;
class ZombieModel;
class ZombieView;
class ZombieController;

int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);

class ZombieController : public EnemyController{
protected:

public:
    ZombieController(EnemyModel* zombieModel)
    :EnemyController(zombieModel)
    {

    }
};
class ZombieView : public EnemyView{
protected:

public:
    ZombieView(EnemyModel* enemymodel)
    :EnemyView(enemymodel)
    {
    
    }
};
class ZombieModel : public EnemyModel{
protected:

public:
    ZombieModel() = default;
    ZombieModel(string name , int hp , int stamina , int damageperattack , int level)
    :EnemyModel(name , hp , stamina , damageperattack , level)
    {
    }
};
class Enemy{
protected:
    EnemyModel* Enemymodel;
    EnemyView* Enemyview;
    EnemyController* Enemycontroller;
public:
    //Getter and Setter=====================
    void setEnemyModel(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }
    EnemyModel* getEnemyModel()
    {
        return Enemymodel;
    }
    void setEnemyView(EnemyView* enemyview)
    {
        Enemyview = enemyview;
    }
    EnemyView* getEnemyView()
    {
        return Enemyview;
    }
    void setEnemyController(EnemyController* enemycontroller)
    {
        Enemycontroller = enemycontroller;
    }
    EnemyController* getEnemyController()
    {
        return Enemycontroller;
    }
    //Constructor==============================
    Enemy() = default;
    Enemy(EnemyModel* enemymodel , EnemyView* enemyview , EnemyController* enemycontroller)
    {
        Enemymodel = enemymodel;
        Enemyview = enemyview;
        Enemycontroller = enemycontroller;
    }

};
class Zombie : public Enemy{
protected:

public:
    //Constructor===================
    Zombie() = default;
    Zombie(ZombieModel* enemymodel , ZombieView* enemyview , ZombieController* enemycontroller)
    {
        Enemymodel = (EnemyModel*)enemymodel;
        Enemyview = (EnemyView*)enemyview;
        Enemycontroller =(EnemyController*) enemycontroller;
    }
};
class EnemyFactory{
private:
    int EnemyLevel;
public:
    //Constructor========================
    EnemyFactory() = default;
    EnemyFactory(int enemylevel)
    {
        EnemyLevel = enemylevel;
    }
    //Setter and Getters=================
    void setEnemyLevel(int enemylevel)
    {
        EnemyLevel = enemylevel;
    }
    int getEnemyLevel()
    {
        return EnemyLevel;
    }
    //Algorithm Of Calculating==========

    // Code is in functions and they're below.
    //Functions=========================
    Zombie* makeZombie()
    {
        ZombieModel zombiemodel{"Zombie", CalculateHPForZombie(EnemyLevel) , CalculateSTforZombie(EnemyLevel) , CalculateDMPAforZombie(EnemyLevel) , EnemyLevel}; 
        ZombieView zombieview = ZombieView(&zombiemodel);      
        ZombieController zombiecontroller{&zombiemodel};
        Zombie zombie{&zombiemodel , &zombieview , &zombiecontroller};
        return &zombie;
    }
};
class MainCharacter{
protected:
    string Name;
    int Level;
    int HP;
    int XP;
    string Gender;
    int Stamina;
    int Gold;
    vector<UseableItems*> useAbleItems;
    vector<Weapon*>weapons;

public:
    //Setter & Getters ================
    void setGold(int gold)
    {
        Gold = gold;
    }
    int getGold()
    {
        return Gold;
    }
    void setName(string name)
    {
        Name = name;
    }
    string getName()
    {
        return Name;
    }
    void setLevel(int level)
    {
        Level = level;
    }
    int getLevel()
    {
        return Level;
    }
    void setHP(int hp)
    {
        HP = hp;
    }
    int getHP()
    {
        return HP;
    }
    void setXP(int xp)
    {
        XP = xp;
    }
    int getXP()
    {
        return XP;
    }
    void setGender(string gender)
    {
        Gender = gender;
    }
    string getGender()
    {
        return Gender;
    }
    void setStamina(int stamina)
    {
        Stamina = stamina;
    }
    int getStamina()
    {
        return Stamina;
    }
    //=====================================
    void addWeapon(Weapon * weapon)
    {
        weapons.push_back(weapon);
    }
    vector<Weapon*> getWeapons()
    {
        return weapons;
    }
    void addUseableItems(UseableItems* useableitem)
    {
        useAbleItems.push_back(useableitem);
    }
    vector<UseableItems*> getUseableItems()
    {
        return useAbleItems;
    }
    //Constructors=========================
    MainCharacter() = default;
    MainCharacter(string name , int level , int hp , int xp , int stamina , string gender , int gold)
    {
        Gold = gold;
        Name = name;
        Level = level;
        HP = hp;
        XP = xp;
        Stamina = stamina;
        Gender = gender;
    }
    //=====================================
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
    void setNeededStaminaPerAttack(int neededstperattack)
    {
        if(neededstperattack < 0)
        {
            cout << "The enemy can't attack on player." << endl;
        }
        else{
            neededStaminaPerAttack = neededstperattack;
        }
    }
    int getNeededStaminaPerAttack()
    {
        return neededStaminaPerAttack;
    }
    void setLevel(int level)
    {
        Level = level;
    }
    int getLevel()
    {
        return Level;
    }
    void setName(string name)
    {
        Name = name;
    }
    string getName()
    {
        return Name;
    }
    void setHP(int hp)
    {
        HP = hp;
    }
    int getHP()
    {
        return HP;
    }
    void setDamagePerAttack(int damageperattack)
    {
        DamagePerAttack = damageperattack;
    }
    int getDamagePerAttack()
    {
        return DamagePerAttack;
    }
    void setStamina(int stamina)
    {
        Stamina = stamina;
    }
    int getStamina()
    {
        return Stamina;
    }
    //=========================================
    //Constructor==============================
    EnemyModel() = default;
    EnemyModel(string name , int hp , int stamina , int damageperattack , int level)
    {
        Name = name;
        HP = hp;
        Stamina = stamina;
        DamagePerAttack = damageperattack;
        Level = level;
    }
};
class EnemyView{
protected:
    EnemyModel* Enemymodel;
public: 
    //Setter and Getters=========================
    void setEnemyModel(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }
    EnemyModel* getEnemyModel()
    {
        return Enemymodel;
    }
    //Constructors===============================
    EnemyView() = default;
    EnemyView(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }
    //Friend classes and Functions===============
    friend class EnemyModel;
    friend class EnemyController;
    //Functions==================================
    virtual void ShowEnemyInfo()
    {
        cout << "Here is status of enemy : " << endl;
        cout << "Enemy's Name: " << Enemymodel->getName() << endl;
        cout << "Enemy's HP : " << Enemymodel->getHP() << endl;
        cout << "Enemy's Stamina: " << Enemymodel->getStamina() << endl;
    }
};
class EnemyController{
protected:
    EnemyModel* Enemymodel;
public:
    //Constructor======================
    EnemyController() = default;
    EnemyController(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }
    //Setter and Getters===============
    void setEnemyModel(EnemyModel* enemymodel)
    {
        Enemymodel = enemymodel;
    }
    EnemyModel* getEnemyModel()
    {
        return Enemymodel;
    }
    //Functions=========================
    void Attack(MainCharacter* player)
    {
        if((Enemymodel->getStamina() - Enemymodel->getNeededStaminaPerAttack()) > 0)
        {
        player->setHP(player->getHP() - Enemymodel->getDamagePerAttack());
        Enemymodel->setStamina(Enemymodel->getStamina() - Enemymodel->getNeededStaminaPerAttack());
        }
        else{
            cout << "Enemy Doesn't have enough Energy to attack" << endl;
        }
    }
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
    void setPrice(int price)
    {
        Price = price;
    }
    int getPrice()
    {
        return Price;
    }
    void setDamagePerAttack(int damageperattack)
    {
        damagePerAttack = damageperattack;
    }
    int getDamagePerAttack()
    {
        return damagePerAttack;
    }
    void setNeededStaminaPerAttack(int neededstaminaperattack)
    {
        neededStaminaPerAttack = neededstaminaperattack;
    }
    int getNeededStaminaPerAttack()
    {
        return neededStaminaPerAttack;
    }
    void setName(string name)
    {
        Name = name;
    }
    string getName()
    {
        return Name;
    }
    void setType(string type)
    {
        Type = type;
    }
    string getType()
    {
        return Type;
    }
    //============================
    //Constructor=================
    Weapon() = default;
    Weapon(int damageperattack , int neededstaminaperattack , int level , string type , string name)
    {
        Type = type;
        Name = name;
        damagePerAttack = damageperattack;
        neededStaminaPerAttack = neededstaminaperattack;
        Level = level;
    }
    //====================================================================
    //Attack Function ====================================================
    virtual void Attack(MainCharacter* Player , EnemyModel* zombie)
    {
        if(Player->getStamina() >= neededStaminaPerAttack)
        {
            zombie->setHP(zombie->getHP() - damagePerAttack);
            Player->setStamina(Player->getStamina() - neededStaminaPerAttack);
        }
        else{

            cout << "your stamina is less than gun's needed stamina and you will die soon :)";
        }

    }

};
class ThrowableWeapon : public Weapon{
public:
    //Constructors==================================
    ThrowableWeapon() = default;
    ThrowableWeapon(int damageperattack , int neededstaminaperattack , int level , string type , string name)
    {
        damagePerAttack = damageperattack;
        neededStaminaPerAttack = neededstaminaperattack;
        Level = level;
        Type = type;
        Name = name;
    }
    //==============================================
    //Attack function===============================
    virtual void Attack(MainCharacter* Player , EnemyModel* zombie) override
    {
        if(Player->getStamina() >= neededStaminaPerAttack)
        {
            zombie->setHP(zombie->getHP() - damagePerAttack);
            Player->setStamina(Player->getStamina() - neededStaminaPerAttack);

            for(int i = 0 ; i < Player->getWeapons().size() ; i++)
            {
                if(Player->getWeapons()[i] == this)
                {
                    Player->getWeapons().erase(Player->getWeapons().begin() + i);
                    break;
                }
            }
        }
        else{

            cout << "your stamina is less than gun's needed stamina and you will die soon :)";
        }
    }
};
class PermenantWeapon : public Weapon{

public:
    //Constructors==================================
    PermenantWeapon() = default;
    PermenantWeapon(int damageperattack , int neededstaminaperattack , int level , string type , string name)
    {
        damagePerAttack = damageperattack;
        neededStaminaPerAttack = neededstaminaperattack;
        Level = level;
        Type = type;
        Name = name;
    }    
};
class UseableItems{

private:
    int Energy;
    int HealingPower;
    int Level;
    int Price;
    string className;
    string Name;
public:
    //Setter & Getters---------
    void setName(string name)
    {
        Name = name;
    }
    string getName()
    {
        return Name;
    }
    void setType(string classname)
    {
        className = classname;
    }
    string getType()
    {
        return className;
    }
    void setPrice(int price)
    {
        Price = price;
    }
    int getPrice()
    {
        return Price;
    }
    void setEnergy(int energy)
    {
        Energy = energy;
    }
    int getEnergy()
    {
        return Energy;
    }
    void setHealingPower(int healingpower)
    {
        HealingPower = healingpower;
    }
    int getHealingPower()
    {
        return HealingPower;
    }
    //------------------------
    //Constructors============
    UseableItems() = default;
    UseableItems(int energy , int healingpower , int level , string classname , string name)
    {  
        className = classname;
        Name = name;
        Energy = energy;
        HealingPower = healingpower;
        Level = level;
    }
};
class Shop{
private:
    int Level;
    string Name;
    vector<UseableItems*> useableitems;
    vector<Weapon*> weapons;

public:
    Shop() = default;
    Shop(string name , int level)
    {
        Name = name;
        Level = level;
    }
    //Setter & Getters=================
    void setName(string name)
    {
        Name = name;
    }
    string getName()
    {
        return Name;
    }
    void setLevel(int level)
    {
        Level = level;
    }
    int getLevel()
    {
        return Level;
    }
    vector<UseableItems*> getUseableItem()
    {
        return useableitems;
    }
    vector<Weapon*> getWeapon()
    {
        return weapons;
    }
    //Add Items========================
    void addWeapon(Weapon* weapon)
    {
        weapons.push_back(weapon);
    }
    void addUseableItems(UseableItems* useableitem)
    {
        useableitems.push_back(useableitem);
    }


};


void showItemsOfShop(Shop Market)
{
    cout << "Weapons: " << endl << "==================================" << endl;
    for(int i = 0 ; i < Market.getWeapon().size() ; i++)
    {
        cout << i+1 << "_ " << Market.getWeapon()[i]->getName() << endl;
    }
    cout << endl << "=================================";
    cout << "UseableItems: " << endl;
    for(int i = 0 ; i < Market.getUseableItem().size() ; i++)
    {
        cout << i + Market.getWeapon().size()+1 << "_ " << Market.getUseableItem()[i]->getType() << endl;
    }
    cout << "===================================" << endl;
}
void buyitemFromShop(Shop Market , int numberOfProduct , string classNameOfProduct , MainCharacter Player)
{
	showItemsOfShop(Market);
    if(numberOfProduct > Market.getUseableItem().size() || numberOfProduct <= 0)
    {
        cout << "Invalid input" << endl;
    }
    else{

        if(numberOfProduct <= Market.getWeapon().size())
        {
            if(Player.getGold() >= Market.getWeapon()[numberOfProduct - 1]->getPrice())
            {
                Player.addWeapon(Market.getWeapon()[numberOfProduct-1]);
            }
            else{

                cout << "your currency is not enough" << endl;
            }
        }
        else{

            if(Player.getGold() >= Market.getUseableItem()[numberOfProduct - 1 - Market.getWeapon().size()]->getPrice())
            {
                Player.addUseableItems(Market.getUseableItem()[numberOfProduct -1 - Market.getWeapon().size()]);
            }
            else{

                cout <<"your currency is not enough" << endl;
            }
        }
    }
}
void RecieveAttack(EnemyModel* zombie , MainCharacter* Playar)
{
    Playar->setHP(Playar->getHP() - zombie->getDamagePerAttack());

}
void Attack(MainCharacter* Player , EnemyModel* zombie , Weapon* gun)
{
    if(Player->getStamina() >= gun->getNeededStaminaPerAttack())
    {
        zombie->setHP(zombie->getHP() - gun->getDamagePerAttack());
        Player->setStamina(Player->getStamina() - gun->getNeededStaminaPerAttack());
    }
    else{

        cout << "your stamina is less than gun's needed stamina and you will die soon :)";
    }

}
void reciveInfoOfPlayer(MainCharacter* player)
{
	string name;
	int age;
	string gender;

	cout << "===============Section of making your dream wariror===============" << endl;
	cout << "Enter name of the Warior :" << endl;
	getline(cin , name);

	
	cout << "Enter gender of the Warior:(male - female) "  << endl;
	getline(cin , gender);
	while(gender != "male" || gender != "female")
	{
		cout << "Invalid Input try again: " << endl;
		getline(cin , gender);
	}

	player->setName(name);	
	player->setGender(gender);
	
	cout << "==Now you should pick up a powerful permenant weeapon wich will be with you till the end of the war :==" << endl;
	cout << "plese pick up one weapon: " << endl;
	cout << "1.Katana" << endl << "2.Ak_47" << endl << "3.Knife" << endl;
	
	cout << "Katana(High needestamina and High damageAerAttack)" << endl;
	cout << "Ak_47(Low needed stamina and Low damagePerAttack)" << endl;
	cout << "Knife(Balanced)" << endl;
	string ChosenWeapon;
	cin >> ChosenWeapon;
	

}


int main()
{
    EnemyFactory Factory{4};
    ZombieModel* Zmodel = new ZombieModel;
    Zombie* zombie = new Zombie;

    zombie->getEnemyView()->ShowEnemyInfo();
	
	return 0;
}

int CalculateDMPAforZombie(int level)
{
    int DMPA;
    DMPA = pow(level , 8/7) + 10;
    return DMPA;
}
int CalculateSTforZombie(int level)
{
    int ST;
    ST = pow(level , 7/5) + 80;
    return ST;
}
int CalculateHPForZombie(int level)
{
    int HP;
    HP = pow(level , 4/3) * 50 + 100;
    return HP;
}
