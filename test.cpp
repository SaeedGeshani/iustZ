#include<iostream>
#include<vector>
#include<string>
using namespace std;


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
		int Price = 10;
        int Level = 1;	
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
        void setLevel(int level)
        {
            Level = level;
        }
        int getLevel()
        {
            return Level;
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
class Weapon: public Item{
	protected:
        
		int damagePerAttack = Level *40;
		int neededStamina = Level * 20;
		
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
		virtual void weaponAttack(MainCharacter*User , Enemy* currentEnemy){};
};
class ColdWeapon: public Weapon{};
class PermanentWeapon : public Weapon{};
class Shop{
private:
    string Name;
    vector<vector<Item*>> items;
    vector<ThrowableItem*> ptrThrowableItems;
    vector<UsableItems*> ptrUseableItems; 
    vector<HotWeapon*> ptrHotWeapon;
    vector<ColdWeapon*> ptrColdWeapon;
    vector<PermanentWeapon*> ptrPermanent;
    
public:
    
    
    Shop(string name)
    {
        Name = name;
    }
    

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


    void buyItem(MainCharacter* consumer , string NameOfItem)
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
class HotWeapon: public Weapon{};
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
class ThrowableItem: public Weapon{};
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
    MainCharacter(string name , int level , int xp , int hp ,int stamina , int gold)
    {
        Name = name;
        Level = level;
        XP = xp;
        Stamina = stamina;
        Gold = gold;
        HP = hp;
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
class Katana : public ColdWeapon,PermanentWeapon{
    private:
 
	public:
        Katana(string name)
        {
            ColdWeapon::Name = name;
        }
		void weaponAttack(MainCharacter* User , Enemy* currentEnemy) override
        {
			if(User->getStamina() >= ColdWeapon::neededStamina){
				currentEnemy->setHP(currentEnemy->getHP()-ColdWeapon::damagePerAttack);
				currentEnemy->setStamina(currentEnemy->getStamina()- ColdWeapon::damagePerAttack/4);
				User->setStamina(User->getStamina()- ColdWeapon::neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};




int main()
{
    MainCharacter Saeed = MainCharacter("Saeed" , 4 , 40 , 100 , 100 , 5000);
    Shop Hypermarket = Shop("Mashti ro kakolat taf mafe");
    Katana katana("Samorayi");
    Hypermarket += &katana;
    Hypermarket.buyItem(&Saeed , "Samorayi");

    vector<Weapon*> show;
    show[0] = Saeed.getWeapons()[0];

    for(int i = 0 ; i < show.size() ; i++)
    {
        cout << show[i] << "   ";
    }
    return 0;
}