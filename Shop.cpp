#include<string>
#include<iostream>
#include<vector>
using namespace std;
class Weapon;
class MainCharacter;
class HotWeapon;
class ColdWeapon;
class UseableItem;
class PermenantItem;

class Enemy{
private:
    int HP;
    int Stamina;


public:
    Enemy() = default;
    Enemy(int hp , int stamina)
    {
        HP = hp;
        Stamina = stamina;
    }
    void setHP(int hp)
    {
        HP = hp;
    }
    int getHP()
    {
        return HP;
    }
    void setStamina(int ST)
    {
        Stamina = ST;
    }
    int getStamina()
    {
        return Stamina;
    }

};

class Item{
	protected:
		string Name;
		int Price;	
	public:
        Item() = default;
        Item(string name , int price)
        {
            Name = name;
            Price = price;
        }

		string getName(){
			return Name;
		}
		int getPrice(){
			return Price;
		}
		void setName(string name){
			Name = name;
		}
		void setPrice(int price){
			Price = price;
		}
		bool operator==(Item other){
			if(other.getName()== Name && other.getPrice() == Price){
				return true;
			}
			else{
				return false;
			}
		}
		
};

class MainCharacter{
protected:
    string Name;
    int Level;
    int XP;
    int HP;
    int Stamina;
    int Gold;
    vector<Item*>Inventory;
    vector<UsableItems*> UseAbleItems;
    vector<Weapon*> weapons;
    
    

public:
    MainCharacter() = default;
    MainCharacter(string name , int level , int xp , int stamina , int gold)
    {
        Name = name;
        Level = level;
        XP = xp;
        Stamina = stamina;
        Gold = gold;
       
    }
    
    int getHP()
    {
        return HP;
    }
    void setHP(int hp)
    {
        HP = hp;
    }
    void setStamina(int stamina)
    {
        Stamina = stamina;
    }
    int getStamina()
    {
        return Stamina;
    }
    int getGold()
    {
        return Gold;
    }
	void setLevel(int level)
	{
		Level = level;
	}
	int getLevel()
	{
		return Level;
	}

    vector<UsableItems*> getUsableItems()
    {
        return UseAbleItems;
    }
    vector<Weapon*> getWeapons()
    {
        return weapons;
    }
    
    void addUsableItem(UsableItems* useableitem)
    {
        UseAbleItems.push_back(useableitem);
    }
    void addWeapon(Weapon* weapon)
    {
        weapons.push_back(weapon);
    }
    void addInventory(Item* item)
    {
        Inventory.push_back(item);
    }
    
};

class Weapon: public Item{
	protected:
        
		int damagePerAttack;
		int neededStamina;
		
	public:
        
		void setDamagePerAttack(int dpa){
			damagePerAttack = dpa;
		}
		int getDamagePerAttack(){
			return damagePerAttack;
		}
		void setNeededS(int ns){
			neededStamina = ns;
		}
		int getNeededS(){
			return neededStamina;
		}
		virtual void weaponAttack(Enemy currentEnemy){};
};

class PermanentWeapon : public Weapon{};
class ThrowableItem: public Weapon{};
class UsableItems: public Item{
	protected:
		int addedHP;
		int AddedStamina;
        MainCharacter* User;
	public:
		void setAddedHP(int ahp){
			addedHP = ahp;
		}
		int getAddedHP(){
			return addedHP;
			
		}
		void setAddedStamina(int ast){
			AddedStamina = ast;
		}
		int getAddedStamina(){
			return AddedStamina;
		}
		virtual void HPandStincreaser() = 0;

		};
class HotWeapon: public Weapon{};
class ColdWeapon: public Weapon{};
class AK_47 : public HotWeapon , public PermanentWeapon{};
class WheyProtein: public UsableItems{
    
	public :
		void HPandStincreaser() override{
			User->setHP(User->getHP()+addedHP);
			User->setStamina(User->getStamina()+AddedStamina);
			for(int i=0;i<User->getUsableItems().size();i++){
					if(dynamic_cast<WheyProtein*>(User->getUsableItems()[i]) != NULL){
						User->getUsableItems().erase(User->getUsableItems().begin()+ i);
						break;
					}
				}
		}
};
class Egg : public UsableItems{
    private:
    MainCharacter User;
	public :
		void HPandStincreaser() override{
			User.setHP(User.getHP()+addedHP);
			User.setStamina(User.getStamina()+AddedStamina);
			for(int i=0;i<User.getUsableItems().size();i++){
					if(dynamic_cast<WheyProtein*>(User.getUsableItems()[i]) != NULL){
						User.getUsableItems().erase(User.getUsableItems().begin()+ i);
						break;
					}
				}
		}
};
class Katana : public ColdWeapon,PermanentWeapon{
    private:
    MainCharacter User;
    
	public:
		void weaponAttack(Enemy currentEnemy) override
        {
			if(User.getStamina() >= ColdWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-ColdWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()- ColdWeapon::damagePerAttack/4);
				User.setStamina(User.getStamina()- ColdWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Shuriken: public ColdWeapon, ThrowableItem{
    private:
    MainCharacter User;
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>= ColdWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-ColdWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-ColdWeapon::damagePerAttack/4);
				for(int i=0;i<User.getWeapons().size();i++){
					if(dynamic_cast<Shuriken*>(User.getWeapons()[i]) != NULL){
						User.getWeapons().erase(User.getWeapons().begin()+ i);
						break;
					}
				}
				User.setStamina(User.getStamina()- ColdWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Batarang: public ColdWeapon, ThrowableItem{
    private:
    MainCharacter User;
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=ColdWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-ColdWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-ColdWeapon::damagePerAttack/4);
				for(int i=0;i<User.getWeapons().size();i++){
					if(dynamic_cast<Batarang*>(User.getWeapons()[i]) != NULL){
						User.getWeapons().erase(User.getWeapons().begin()+ i);
						break;
					}
				}
				User.setStamina(User.getStamina()- ColdWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Trident : public ColdWeapon,PermanentWeapon{
    private:
    MainCharacter User;
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=ColdWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-ColdWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-ColdWeapon::damagePerAttack/4);
				User.setStamina(User.getStamina()- ColdWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Spear: public ColdWeapon, ThrowableItem{
	private:
    MainCharacter User;
    public:

		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=ColdWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-ColdWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-ColdWeapon::damagePerAttack/4);
				for(int i=0;i<User.getWeapons().size();i++){
					if(dynamic_cast<Spear*>(User.getWeapons()[i]) != NULL){
						User.getWeapons().erase(User.getWeapons().begin()+ i);
						break;
					}
				}
				User.setStamina(User.getStamina()- ColdWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class FlameThrower: public HotWeapon, PermanentWeapon{
	private:
    MainCharacter User;
    public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=HotWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-HotWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-HotWeapon::damagePerAttack/4);
				User.setStamina(User.getStamina()- HotWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Blaster: public HotWeapon, PermanentWeapon{
	private:
    MainCharacter User;
    public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=HotWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-HotWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-HotWeapon::damagePerAttack/4);
				User.setStamina(User.getStamina()- HotWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class LightSaber: public HotWeapon, PermanentWeapon{
	private:
    MainCharacter User;
    public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=HotWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-HotWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-HotWeapon::damagePerAttack/4);
				User.setStamina(User.getStamina()- HotWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class ElderWand: public ColdWeapon, PermanentWeapon{
	private:
    MainCharacter User;
    public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=ColdWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-ColdWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-ColdWeapon::damagePerAttack/4);
				User.setStamina(User.getStamina()- ColdWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Grenade: public HotWeapon, ThrowableItem{
	private:
    MainCharacter User;
    public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=HotWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-HotWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-HotWeapon::damagePerAttack/4);
				for(int i=0;i<User.getWeapons().size();i++){
					if(dynamic_cast<Grenade*>(User.getWeapons()[i]) != NULL){
						User.getWeapons().erase(User.getWeapons().begin()+ i);
						break;
					}
				}
				User.setStamina(User.getStamina()- HotWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class CapsShield: public ColdWeapon, ThrowableItem{
	private:
    MainCharacter User;
    public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=ColdWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-ColdWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-ColdWeapon::damagePerAttack/4);
				for(int i=0;i<User.getWeapons().size();i++){
					if(dynamic_cast<CapsShield*>(User.getWeapons()[i]) != NULL){
						User.getWeapons().erase(User.getWeapons().begin()+ i);
						break;
					}
				}
				User.setStamina(User.getStamina()- ColdWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Mjolnir: public ColdWeapon, PermanentWeapon{
	private:
    MainCharacter User;

    public:
		void weaponAttack(Enemy currentEnemy) override{
			if(User.getStamina()>=ColdWeapon::neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-ColdWeapon::damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-ColdWeapon::damagePerAttack/4);
				User.setStamina(User.getStamina()- ColdWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};

class Shop{
private:
    string Name;
    vector<vector<Item*>> items;
    vector<ThrowableItem*> ptrThrowableItems;
    vector<UsableItems*> ptrUseableItems; 
    vector<HotWeapon*> ptrHotWeapon;
    vector<ColdWeapon*> ptrColdWeapon;
    vector<PermanentWeapon*> ptrPermanent;
    MainCharacter* consumer;
	int Level = consumer->getLevel();
    

public:
    
        

        
    

    void operator+=(ThrowableItem* ThroOBJ)
    {
        ptrThrowableItems.push_back(ThroOBJ);
    }
    void operator+=(UsableItems* UseOBJ)
    {
        ptrUseableItems.push_back(UseOBJ);
    }
    void operator+=(HotWeapon* HotOBJ)
    {
        ptrHotWeapon.push_back(HotOBJ);
    }
    void operator+=(ColdWeapon* ColdOBJ)
    {
        ptrColdWeapon.push_back(ColdOBJ);
    }

    vector<ThrowableItem*> getThrowableItems()
    {
        return ptrThrowableItems;
    }
    vector<UsableItems*> getUseableItems()
    {
        return ptrUseableItems;
    }
    vector<HotWeapon*> getHotItems()
    {
        return ptrHotWeapon;
    }
    vector<ColdWeapon*> getColdItems()
    {
        return ptrColdWeapon;
    }


    void buyItem(string NameOfItem)
    {
        for(int i = 0 ; i < items.size() ; i++)
        {
            for(int j = 0 ; j < items[i].size() ; j++)
            {
                if(items[i][j]->getName() == NameOfItem)
                {
                    if(consumer->getGold() >= items[i][j]->getPrice())
                    {
                        consumer->addInventory(items[i][j]);
                        break;
                    }
                }
            }
        }

        cout << "These is more than your currency" << endl;
    }
    
};



int main()
{



}