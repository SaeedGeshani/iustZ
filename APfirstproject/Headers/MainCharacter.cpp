#include<string>
#include<vector>
#include "MainCharacter.h"
#include "Zombie.h"
#include "UseableItems.h"
#include "Weapon.h"
#include "Enemy.h"

using namespace std;

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
            cout << i+1 << "." << this->getWeapons()[i]->getName() << endl;
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
        this->setXP( this->getXP() + this->getUseableItems()[numberOfItemInInventory]->getAddedXP());
        this->getUseableItems().erase(this->getUseableItems().begin() + numberOfItemInInventory);
    }

    //Attack func==========================
     void MainCharacter::Attack(Enemy* enemy, Weapon* weapon){
    	if(Stamina >= weapon->getNeededStaminaPerAttack() ){
    		int totalDamage = weapon->getDamagePerAttack()  + (weapon->getDamagePerAttack())*(Level-1)/5;
    		enemy->getEnemyModel()->setHP(enemy->getEnemyModel()->getHP()-totalDamage);
    		enemy->getEnemyModel()->setStamina(enemy->getEnemyModel()->getStamina()-(totalDamage/4));
			Stamina -= weapon->getNeededStaminaPerAttack();   
			if(dynamic_cast<ThrowableWeapon*> (weapon) != NULL){
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
    

