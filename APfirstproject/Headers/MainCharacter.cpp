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
        if(numberOfItemInInventory <= useAbleItems.size() && numberOfItemInInventory >= 1)
        {
            HP = HP + useAbleItems[numberOfItemInInventory-1]->getHealingPower();   
            Stamina = Stamina + useAbleItems[numberOfItemInInventory-1]->getEnergy();
            XP = XP + useAbleItems[numberOfItemInInventory-1]->getAddedXP();
            delete useAbleItems[numberOfItemInInventory-1];
            useAbleItems.erase(useAbleItems.begin() + numberOfItemInInventory-1);
            useAbleItems.shrink_to_fit();
        }
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
                        delete weapons[i];
						weapons.erase(weapons.begin()+i);
                        weapons.shrink_to_fit();
						break;
					}	
				}
			}
			
		}
        else{

            cout << "Character Doesn't have enough energy to use weapon" << endl;
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
    

