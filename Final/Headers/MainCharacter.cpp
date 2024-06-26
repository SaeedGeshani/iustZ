#include<string>
#include<vector>
#include "MainCharacter.h"
#include "Zombie.h"
#include "UseableItems.h"
#include "Weapon.h"
#include "Enemy.h"

using namespace std;

    //Setter & Getters ================
    void MainCharacter::setKills(int kills)
    {
        Kills = kills;
    }

    int MainCharacter::getKills()
    {
        return Kills;
    }
    
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
        if(hp > 90 + Level * 10)
        {
            HP = 90 + Level*10;
        }
        else{
            HP = hp;
        }
        
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
        if(stamina > 90 + 15*Level)
        {
            Stamina = 90 + 15*Level;
        }
        else{

            Stamina = stamina;
        }
        
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
        vector<Weapon*> t;
        
        
        for(int i = 0 ; i < this->getWeapons().size() ; i++)
        {
        	bool p=true;
        	for(int h=0;h<t.size();h++){
        		if(*(this->getWeapons()[i])==*t[h]){
        			p=false;
        			break;
				}
			}
			if(p==false){
				continue;
			}
			
            cout << i+1 << "." << this->getWeapons()[i]->getName() << "(Damage per Attack: "<<this->getWeapons()[i]->getDamagePerAttack()<<", Needed Stamina per Attack: "<<this->getWeapons()[i]->getNeededStaminaPerAttack()<<") ";
            int n=1;
            t.push_back(this->getWeapons()[i]);
            for(int j=i+1;j<this->getWeapons().size();j++){
            	if(*(this->getWeapons()[i])==*(this->getWeapons()[j])){
            		n++;
				}
			}
			if(n>1){
				cout<<"(x"<<n<<")"<<endl;
			}
			else{
				cout<<endl;
			}
			
        }
    }

    void MainCharacter::showCharacterUsableItems()
    {
        cout << "The Items are: =======================" << endl;
		vector <UseableItems*> v;
		
        for(int i = 0 ; i < this->getUseableItems().size() ; i++)
        {
        	bool p=true;
        	for(int h=0;h<v.size();h++){
        		if(*(this->getUseableItems()[i])==*v[h]){
        			p=false;
        			break;
				}
			}
			if(p==false){
				continue;
				
			}
		
            cout << i+1 << "." << this->getUseableItems()[i]->getName() << "(increases HP by "<<this->getUseableItems()[i]->getHealingPower()<<", Stamina by "<<this->getUseableItems()[i]->getEnergy()<<" and XP by "<<this->getUseableItems()[i]->getAddedXP()<<") ";
            v.push_back(this->getUseableItems()[i]);
			int n=1;
            
            for(int j=i+1;j<this->getUseableItems().size();j++){
            	if(*(this->getUseableItems()[i])==*(this->getUseableItems()[j])){
            		n++;
				}
			}
			if(n>1){
				cout<<"(x"<<n<<")"<<endl;
			}
			else{
				cout<<endl;
			}
        }
        
    }

    void MainCharacter::CalculateLevel()
    {
        int exLevel = Level;
        Level = floor((double)sqrt(((double)(XP/10)+((1.0)*81/4))) - 0.5) - 3; 
        if(Level > exLevel)
        {
            cout << "===============================" << endl;
            cout << "           Level UP            " << endl;
            cout << "===============================" << endl;
            setHP(HP + Level*5 + 30);
            setStamina(Stamina + Level*7 + 10);
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
            CalculateLevel();
        }
    }

    //Attack func==========================
     void MainCharacter::Attack(Enemy* enemy, Weapon* weapon){
    	if(Stamina >= weapon->getNeededStaminaPerAttack() ){
    		int totalDamage = weapon->getDamagePerAttack()  + (weapon->getDamagePerAttack())*(Level-1)/10;
    		enemy->getEnemyModel()->setHP(enemy->getEnemyModel()->getHP()-totalDamage);
    		enemy->getEnemyModel()->setStamina(enemy->getEnemyModel()->getStamina()-(totalDamage/5));
			Stamina -= weapon->getNeededStaminaPerAttack();   
			
            cout << "==================Attacking==========================================" << endl;
            cout << "Damage enemy: " << totalDamage << "  Costed ST from Enemy: " << (totalDamage/4) << "  Costed St From Warior: " << weapon->getNeededStaminaPerAttack() << endl;
			cout << "=====================================================================" << endl;
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
			this_thread::sleep_for(chrono::seconds(3));
			system("cls");
			
		}
        else{

            cout << "======================================" << endl;
            cout << "               LOW ENERGY             "<< endl;
            cout << "======================================" << endl;
        }
		
	}

    void MainCharacter::getEnemyWeapons(vector<Weapon*> enemyweps)
    {
        for(int i = 0 ; i < enemyweps.size() ; i++)
        {
            if(dynamic_cast<ThrowableWeapon*>(enemyweps[i])!= NULL)
            {
                 weapons.push_back(enemyweps[i]);
            }
        }
    }

    void MainCharacter::getEnemyUseableItems(vector<UseableItems*> enemyuseableitems)
    {
        for(int i = 0 ; i < enemyuseableitems.size() ; i++)
        {
            useAbleItems.push_back(enemyuseableitems[i]);
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
        XP = xp;
    }
    
   