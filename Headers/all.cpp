#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<ctime>
#include "all.h"

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
    void EnemyModel::setNeededStaminaPerAttack(int neededstperattack)
    {
        if(neededstperattack < 0)
        {
            cout << "The enemy can't attack on player." << endl;
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
    EnemyModel::EnemyModel(string name , int hp , int stamina , int damageperattack , int level)
    {
        Name = name;
        HP = hp;
        Stamina = stamina;
        DamagePerAttack = damageperattack;
        Level = level;
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
    //Functions=========================
    void EnemyController::Attack(MainCharacter* player)
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

//EnemyFactory///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Constructor========================
    EnemyFactory::EnemyFactory() = default;
    EnemyFactory::EnemyFactory(int enemylevel)
    {
        EnemyLevel = enemylevel;
    }
    //Setter and Getters=================
    void EnemyFactory::setEnemyLevel(int enemylevel)
    {
        EnemyLevel = enemylevel;
    }
    int EnemyFactory::getEnemyLevel()
    {
        return EnemyLevel;
    }
    //Algorithm Of Calculating==========

    // Code is in functions and they're below.
    //Functions=========================

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

    Zombie* EnemyFactory::makeZombie()
    {
        ZombieModel* zombiemodel = new ZombieModel("Zombie", CalculateHPForZombie(EnemyLevel) , CalculateSTforZombie(EnemyLevel) , CalculateDMPAforZombie(EnemyLevel) , EnemyLevel); 
        ZombieView* zombieview = new ZombieView(zombiemodel);      
        ZombieController* zombiecontroller = new ZombieController(zombiemodel);
        Zombie* zombie = new Zombie(zombiemodel , zombieview , zombiecontroller);
        return zombie;
        
    }

	Items::Items()= default;
	Items::Items(string name, int price){
		Name = name;
		Price = price;
	} 
	//getter and setter
    void Items::setName(string name)
	{		
   		Name = name;
	}
	string Items::getName()
	{
    	return Name;
	}	
    void Items::setPrice(int price)
	{
    	Price = price;
	}
	int Items::getPrice()
	{
    	return Price;
	}
//operator overloading:
bool Items::operator==(Items other){
	if(other.getName()==Name && other.getPrice()==Price){
		return true;
	}
	else{
		return false;
	}
}

    //Setter & Getters ================
    void MainCharacter::setGold(int gold)
    {
        Gold = gold;
    }
    int MainCharacter::getGold()
    {
        return Gold;
    }
    void MainCharacter::setName(string name)
    {
        Name = name;
    }
    string MainCharacter::getName()
    {
        return Name;
    }
    void MainCharacter::setLevel(int level)
    {
        Level = level;
    }
    int MainCharacter::getLevel()
    {
        return Level;
    }
    void MainCharacter::setHP(int hp)
    {
        HP = hp;
    }
    int MainCharacter::getHP()
    {
        return HP;
    }
    void MainCharacter::setXP(int xp)
    {
        XP = xp;
    }
    int MainCharacter::getXP()
    {
        return XP;
    }
    void MainCharacter::setGender(string gender)
    {
        Gender = gender;
    }
    string MainCharacter::getGender()
    {
        return Gender;
    }
    void MainCharacter::setStamina(int stamina)
    {
        Stamina = stamina;
    }
    int MainCharacter::getStamina()
    {
        return Stamina;
    }
    //=====================================
    void MainCharacter::addWeapon(Weapon * weapon)
    {
        weapons.push_back(weapon);
    }
    vector<Weapon*> &MainCharacter::getWeapons()
    {
        return weapons;
    }
    void MainCharacter::addUseableItems(UseableItems* useableitem)
    {
        useAbleItems.push_back(useableitem);
    }
    vector<UseableItems*> &MainCharacter::getUseableItems()
    {
        return useAbleItems;
    }

    void MainCharacter::showCharacterWeapons()
    {
        cout << "The Inventory Includes:" << endl;

        cout << "Weapons==========================================" << endl;
        for(int i = 0 ; i < this->getWeapons().size() ; i++)
        {
            cout << i+1 << "." << this->getWeapons()[i]->getType() << endl;
        }
    }

    void MainCharacter::showCharacterUsableItems()
    {
        cout << "The Items are: =======================" << endl;

        for(int i = 0 ; i < this->getUseableItems().size() ; i++)
        {
            cout << i+1 << "." << this->getUseableItems()[i]->getName() << endl;
        }
    }

    void MainCharacter::useItem(int numberOfItemInInventory)
    {
        this->setHP(this->getHP() + this->getUseableItems()[numberOfItemInInventory]->getHealingPower());
        this->setStamina(this->getStamina() + this->getUseableItems()[numberOfItemInInventory]->getEnergy());
        this->getUseableItems().erase(this->getUseableItems().begin() + numberOfItemInInventory);
    }

    //Attack func==========================
     void MainCharacter::Attack(Enemy* enemy, Weapon* weapon){
    	if(Stamina >= weapon->getNeededStaminaPerAttack() ){
    		int totalDamage = (weapon->getDamagePerAttack() + (weapon->getLevel()-1)*weapon->getDamagePerAttack()/8) + (weapon->getDamagePerAttack() + (weapon->getLevel()-1)*weapon->getDamagePerAttack()/8)*(Level-1)/5;
    		enemy->getEnemyModel()->setHP(enemy->getEnemyModel()->getHP()-totalDamage);
    		enemy->getEnemyModel()->setStamina(enemy->getEnemyModel()->getStamina()-(totalDamage/4));
			Stamina -= weapon->getNeededStaminaPerAttack();   
			if((ThrowableWeapon *)weapon != NULL){
				for(int i=0;i<weapons.size();i++){
					if(weapons[i]==weapon){
						weapons.erase(weapons.begin()+i);
						break;
					}	
				}
			}
			
		}
		
	}

     //Constructors=====================
    MainCharacter::MainCharacter() = default;
    MainCharacter::MainCharacter(string name , int hp , int xp , int stamina , string gender , int gold)
    {
        Name = name;
        HP = hp;
        Stamina = stamina;
        Gender = gender;
        Gold = gold;
    }
    
    //Constructors==================================
    PermenantWeapon::PermenantWeapon() = default;
    PermenantWeapon::PermenantWeapon(int damageperattack , int neededstaminaperattack , int level  , string name, int price) : Weapon( damageperattack ,  neededstaminaperattack ,  level  ,  name,  price){
	}

    Shop::Shop() = default;
    Shop::Shop(string name , int level)
    {
        Name = name;
        Level = level;
    }
    //Setter & Getters=================
    void Shop::setName(string name)
    {
        Name = name;
    }
    string Shop::getName()
    {
        return Name;
    }
    void Shop::setLevel(int level)
    {
        Level = level;
    }
    int Shop::getLevel()
    {
        return Level;
    }
    // vector<UseableItems*> Shop::getUseableItem()
    // {
    //     return useableitems;
    // }
    // vector<Weapon*> Shop::getWeapon()
    // {
    //     return weapons;
    // }
    // //Add Items========================
    // void Shop::addWeapon(Weapon* weapon)
    // {
    //     weapons.push_back(weapon);
    // }
    // void  Shop::addUseableItems(UseableItems* useableitem)
    // {
    //     useableitems.push_back(useableitem);
    // }

    void Shop::ShowItems()
    {
        cout << "Here are the ThrowableWeapons: ========"<< endl;
        cout << "1.Batrang" << endl;
        cout << "2.Grenade" << endl;
        cout << "3.TNT" << endl;
        cout << "And these are UsableItems and Healers: ========" << endl;
        cout << "4.WheyProtein" << endl;
        cout << "5.Egg" << endl;
        cout << "6.Peace Herbal Tea" << endl;
    }

    void Shop::BuyItem(MainCharacter* player)
    {
        this->ShowItems();

        int ChosenNumber;
        
        do{
            cout << "Please enter the number of Item you wanna buy" << endl;
            cin >> ChosenNumber;
            
            
                if(ChosenNumber == 1) 
                {
                    ThrowableWeapon* Batrang = new ThrowableWeapon(50 + ((player->getLevel())+5)*5/4 , 10 + (player->getLevel())*9/7 , player->getLevel() , "Batrang" , 50 );
                    player->addWeapon(Batrang);
                    player->setGold(player->getGold() - 50);
                }
                
                else if(ChosenNumber == 2) 
                {
                    ThrowableWeapon* Grenade = new ThrowableWeapon(80 + (player->getLevel())*10 , 30 + 3*(player->getLevel()) , player->getLevel() , "Grenade" , 150);
                    player->addWeapon(Grenade);
                    player->setGold(player->getGold()-150);
                }

                else if(ChosenNumber == 3)
                {
                    ThrowableWeapon* TNT = new ThrowableWeapon(100 + (player->getLevel())*12 , 35 + 4*(player->getLevel()) , player->getLevel() , "TNT" , 300);
                    player->addWeapon(TNT);
                    player->setGold(player->getGold()-300);
                }

                else if(ChosenNumber == 4) 
                {
                    UseableItems* WheyProtein = new UseableItems(40 , 50 , player->getLevel() , "Healing" , "WheyProtein" , 50);
                    player->addUseableItems(WheyProtein);
                    player->setGold(player->getGold() - 50);
                }

                else if(ChosenNumber == 5)
                {
                    UseableItems* Egg = new UseableItems(20 , 30 , player->getLevel() , "Healing" , "Egg" , 10);
                    player->addUseableItems(Egg);
                    player->setGold(player->getGold() - 10);
                }

                else if(ChosenNumber == 6)
                {
                    UseableItems* PeaceHT = new UseableItems(100 , -20 , player->getLevel() , "Healing" , "PeaceHT" , 80);
                    player->addUseableItems(PeaceHT);
                    player->setGold(player->getGold() - 80);break;
                }
                else
                {
                    continue;
                }

        


        }while(ChosenNumber < 0 || ChosenNumber > 7);
    }

    //Constructors==================================
    ThrowableWeapon::ThrowableWeapon() = default;
    ThrowableWeapon::ThrowableWeapon(int damageperattack , int neededstaminaperattack , int level  , string name, int price) : Weapon( damageperattack ,  neededstaminaperattack ,  level  ,  name,  price){
	}

    //Setter & Getters---------
    void UseableItems::setType(std::string classname)
    {
        className = classname;
    }
    std::string UseableItems::getType()
    {
        return className;
    }
    void UseableItems::setEnergy(int energy)
    {
        Energy = energy;
    }
    int UseableItems::getEnergy()
    {
        return Energy;
    }
    void UseableItems::setHealingPower(int healingpower)
    {
        HealingPower = healingpower;
    }
    int UseableItems::getHealingPower()
    {
        return HealingPower;
    }
    //------------------------
    //Constructors============
    UseableItems::UseableItems() = default;
    UseableItems::UseableItems(int energy , int healingpower , int level , string classname , string name, int price) : Items( name,  price)
    {  
        className = classname;
//        Name = name;
        Energy = energy;
        HealingPower = healingpower;
        Level = level;
    }

//Weapon//////////////////////////////////////////////////////////////////////////////////////////

    //Setter & Getter
    void Weapon::setLevel(int level)
    {
        Level = level;
    }

    int Weapon::getLevel()
    {
        return Level;
    }

    void Weapon::setPrice(int price)
    {
        Price = price;
    }
    int Weapon::getPrice()
    {
        return Price;
    }
    void Weapon::setDamagePerAttack(int damageperattack)
    {
        damagePerAttack = damageperattack;
    }
    int Weapon::getDamagePerAttack()
    {
        return damagePerAttack;
    }
    void Weapon::setNeededStaminaPerAttack(int neededstaminaperattack)
    {
        neededStaminaPerAttack = neededstaminaperattack;
    }
    int Weapon::getNeededStaminaPerAttack()
    {
        return neededStaminaPerAttack;
    }
    void Weapon::setName(string name)
    {
        Name = name;
    }
    string Weapon::getName()
    {
        return Name;
    }
    void Weapon::Weapon::setType(string type)
    {
        Type = type;
    }
    string Weapon::getType()
    {
        return Type;
    }
    //============================
    //Constructor=================
    Weapon::Weapon() = default;
    Weapon::Weapon(int damageperattack , int neededstaminaperattack , int level , string type , int price)
    {
        Type = type;
        Price = price;
        damagePerAttack = damageperattack;
        neededStaminaPerAttack = neededstaminaperattack;
        Level = level;
    }
    //====================================================================
    //Attack Function ====================================================
    // void Weapon::Attack(MainCharacter* Player , EnemyModel* zombie)
    // {
    //     if(Player->getStamina() >= neededStaminaPerAttack)
    //     {
    //         zombie->setHP(zombie->getHP() - damagePerAttack);
    //         Player->setStamina(Player->getStamina() - neededStaminaPerAttack);
    //     }
    //     else{

    //         cout << "your stamina is less than gun's needed stamina and you will die soon :)";
    //     }

    // }

//Zombie////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Constructor===================
    Zombie::Zombie() = default;
    Zombie::Zombie(ZombieModel* enemymodel , ZombieView* enemyview , ZombieController* enemycontroller)
    {
        Enemymodel = (EnemyModel*)enemymodel;
        Enemyview = (EnemyView*)enemyview;
        Enemycontroller =(EnemyController*) enemycontroller;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ZombieModel///////////////////////////////////////////////////////////////////////////////////////////////////

    ZombieModel::ZombieModel() = default;
    ZombieModel::ZombieModel(string name , int hp , int stamina , int damageperattack , int level)
    :EnemyModel(name , hp , stamina , damageperattack , level)
    {
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ZombieView///////////////////////////////////////////////////////////////////////////////////////////////////

    ZombieView::ZombieView(EnemyModel* enemymodel)
    :EnemyView(enemymodel)
    {
    
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ZombieController/////////////////////////////////////////////////////////////////////////////////////////////

    ZombieController::ZombieController(EnemyModel* zombieModel)
    :EnemyController(zombieModel)
    {

    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Enemy/////////////////////////////////////////////////////////////////////////////
    //Getter and Setter=====================
    void HumanEnemy::setHumanEnemyModel(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }
    HumanEnemyModel* HumanEnemy::getHumanEnemyModel()
    {
        return humanenemymodel;
    }
    void HumanEnemy::setHumanEnemyView(HumanEnemyView* humanenemyview)
    {
        this->humanenemyview = humanenemyview;
    }
    HumanEnemyView* HumanEnemy::getHumanEnemyView()
    {
        return humanenemyview;
    }
    void HumanEnemy::setHumanEnemyController(HumanEnemyController* humanenemycontroller)
    {
        this->humanenemycontroller = humanenemycontroller;
    }
    HumanEnemyController* HumanEnemy::getHumanEnemyController()
    {
        return humanenemycontroller;
    }
    //Constructor==============================
    HumanEnemy::HumanEnemy() = default;
    HumanEnemy::HumanEnemy(HumanEnemyModel* humanenemymodel , HumanEnemyView* humanenemyview , HumanEnemyController* humanenemycontroller)
    {
        this->humanenemymodel = humanenemymodel;
        this->humanenemyview = humanenemyview;
        this->humanenemycontroller = humanenemycontroller;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyModel//////////////////////////////////////////////////////////////////////////////////////////////////

    //Setter & Getters ==========================
    void HumanEnemyModel::setNeededStaminaPerAttack(int neededstperattack)
    {
        if(neededstperattack < 0)
        {
            cout << "The enemy can't attack on player." << endl;
        }
        else{
            neededStaminaPerAttack = neededstperattack;
        }
    }
    int HumanEnemyModel::getNeededStaminaPerAttack()
    {
        return neededStaminaPerAttack;
    }
    void HumanEnemyModel::setLevel(int level)
    {
        Level = level;
    }
    int HumanEnemyModel::getLevel()
    {
        return Level;
    }
    void HumanEnemyModel::setName(std::string name)
    {
        Name = name;
    }
    std::string HumanEnemyModel::getName()
    {
        return Name;
    }
    void HumanEnemyModel::setHP(int hp)
    {
        HP = hp;
    }
    int HumanEnemyModel::getHP()
    {
        return HP;
    }
    void HumanEnemyModel::setDamagePerAttack(int damageperattack)
    {
        DamagePerAttack = damageperattack;
    }
    int HumanEnemyModel::getDamagePerAttack()
    {
        return DamagePerAttack;
    }
    void HumanEnemyModel::setStamina(int stamina)
    {
        Stamina = stamina;
    }
    int HumanEnemyModel::getStamina()
    {
        return Stamina;
    }
    //=========================================
    //Constructor==============================
    HumanEnemyModel::HumanEnemyModel() = default;
    HumanEnemyModel::HumanEnemyModel(string name , int hp , int stamina , int damageperattack , int level)
    {
        Name = name;
        HP = hp;
        Stamina = stamina;
        DamagePerAttack = damageperattack;
        Level = level;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyView/////////////////////////////////////////////////////////////////////////////////////////
 
    //Setter and Getters=========================
    void HumanEnemyView::setHumanEnemyModel(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }
    HumanEnemyModel* HumanEnemyView::getHumanEnemyModel()
    {
        return humanenemymodel;
    }
    //Constructors===============================
    HumanEnemyView::HumanEnemyView() = default;
    HumanEnemyView::HumanEnemyView(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }

    //Functions==================================
    void HumanEnemyView::ShowHumanEnemyInfo()
    {
        cout << "Here is status of enemy : " << endl;
        cout << "Enemy's Name: " << humanenemymodel->getName() << endl;
        cout << "Enemy's HP : " << humanenemymodel->getHP() << endl;
        cout << "Enemy's Stamina: " << humanenemymodel->getStamina() << endl;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyController/////////////////////////////////////////////////////////////////////////////////////////



    //Constructor======================
    HumanEnemyController::HumanEnemyController() = default;
    HumanEnemyController::HumanEnemyController(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }
    //Setter and Getters===============
    void HumanEnemyController::setHumanEnemyModel(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }
    HumanEnemyModel* HumanEnemyController::getHumanEnemyModel()
    {
        return humanenemymodel;
    }
    //Functions=========================
    void HumanEnemyController::Attack(MainCharacter* player)
    {

        switch (CheckHealth(player))
        {
        case Low:
            ///////
            //use an item to heal or more than one , Hp is under 10 percent ;
            ///////
            switch (CheckStamina(player))
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                ///////  

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                break;
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                break;
            default:
                break;
            }
            break;
        case Average:
            ///////
            //use an item to heal , Hp is under 50 percent ;
            ///////
            switch (CheckStamina(player))
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                /////// 

                ///////
                //use an item to attack ;
                /////// 
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                break;
            default:
                break;
            }
            break;
        case High:
            switch (CheckStamina(player))
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                ///////  

                ///////
                //use an item to attack ;
                ///////
            case average:
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        
        //if((humanenemymodel->getStamina() - humanenemymodel->getNeededStaminaPerAttack()) > 0)
        //{
        //player->setHP(player->getHP() - humanenemymodel->getDamagePerAttack());
        //humanenemymodel->setStamina(humanenemymodel->getStamina() - humanenemymodel->getNeededStaminaPerAttack());
        //}
        //else{
        //    cout << "Enemy Doesn't have enough Energy to attack" << endl;
        //}
    }
    int HumanEnemyController::CheckHealth(MainCharacter* player){
        //*************add percent of Health , now it is just a number between 0 to 100 ;*****************
        if (player->getHP() <= 10){
            return 0 ;
        }
        else if (player->getHP()>10 and player->getHP()<=50){
            return 50 ;
        }
        else if (player->getHP()<=100 and player->getHP()>50){
            return 100 ;
        }
    }
    int HumanEnemyController::CheckStamina(MainCharacter* player){
        //*************add percent of Health , now it is just a number between 0 to 100 ;*****************
        if (player->getStamina() <= 10){
            return 0 ;
        }
        else if (player->getStamina()>10 and player->getStamina()<=50){
            return 50 ;
        }
        else if (player->getStamina()<=100 and player->getStamina()>50){
            return 100 ;
        }
    }

//HumanEnemyFactory///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Constructor========================
    HumanEnemyFactory::HumanEnemyFactory() = default;
    HumanEnemyFactory::HumanEnemyFactory(int humanenemylevel)
    {
        HumanEnemyLevel = humanenemylevel;
    }
    //Setter and Getters=================
    void HumanEnemyFactory::setHumanEnemyLevel(int humanenemylevel)
    {
        HumanEnemyLevel = humanenemylevel;
    }
    int HumanEnemyFactory::getHumanEnemyLevel()
    {
        return HumanEnemyLevel;
    }
    Zombie* HumanEnemyFactory::makeZombie()
    {
        ZombieModel* zombiemodel = new ZombieModel("Zombie", CalculateHPForZombie(HumanEnemyLevel) , CalculateSTforZombie(HumanEnemyLevel) , CalculateDMPAforZombie(HumanEnemyLevel) , HumanEnemyLevel); 
        ZombieView* zombieview = new ZombieView(zombiemodel);      
        ZombieController* zombiecontroller = new ZombieController(zombiemodel);
        Zombie* zombie = new Zombie(zombiemodel , zombieview , zombiecontroller);
        return zombie;
        
    }



