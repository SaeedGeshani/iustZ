#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
using namespace std;

class MainCharacter;
class Enemy;
class Items;
class Weapon;
class UseableItems;
class Shop;

class Items{
	protected:
		string Name;
		int Price;
	public:
		//constructor
		
		Items()= default;
		Items(string name, int price){
			Name = name;
			Price = price;
		} 
		//getter and setter
	    void setName(string name)
    	{		
       		Name = name;
    	}
    	string getName()
    	{
        	return Name;
    	}	
	   void setPrice(int price)
    	{
        	Price = price;
    	}
    	int getPrice()
    	{
        	return Price;
    	}
	//operator overloading:
	bool operator==(Items other){
		if(other.getName()==Name && other.getPrice()==Price){
			return true;
		}
		else{
			return false;
		}
	}
};
class Weapon: public Items{
protected:
    int damagePerAttack;
    int neededStaminaPerAttack;
    int Level;
//    int Price;
//    string Type;
//    string Name;
public:
    //Setter & Getter

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

    void setLevel(int level)
    {
        Level = level;
    }
    int getLevel()
    {
        return Level;
    }
    //============================
    //Constructor=================
    Weapon() = default;
    Weapon(int damageperattack , int neededstaminaperattack , int level , string name, int price) : Items( name ,  price)
    {
//        Type = type;
//        Name = name;
        damagePerAttack = damageperattack;
        neededStaminaPerAttack = neededstaminaperattack;
        Level = level;
    }
    //====================================================================
    //Attack Function ====================================================
//    virtual void Attack(MainCharacter* Player , Enemy* zombie)
//    {
//        if(Player->getStamina() >= neededStaminaPerAttack)
//        {
//            zombie->setHP(zombie->getHP() - damagePerAttack);
//            Player->setStamina(Player->getStamina() - neededStaminaPerAttack);
//        }
//        else{
//
//            cout << "your stamina is less than gun's needed stamina and you will die soon :)";
//        }
//
//    }

};
class Enemy{
private:
    string Name;
    int HP;
    int DamagePerAttack;
    int Stamina;

public:
    //Setter & Getters ==========================
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
    Enemy() = default;
    Enemy(string name , int hp , int stamina , int damageperattack)
    {
        Name = name;
        HP = hp;
        Stamina = stamina;
        DamagePerAttack = damageperattack;
    }
};
class ThrowableWeapon : public Weapon{
public:
    //Constructors==================================
    ThrowableWeapon() = default;
    ThrowableWeapon(int damageperattack , int neededstaminaperattack , int level  , string name, int price) : Weapon( damageperattack ,  neededstaminaperattack ,  level  ,  name,  price){
	}

//    {
//        damagePerAttack = damageperattack;
//        neededStaminaPerAttack = neededstaminaperattack;
//        Level = level;
//        Type = type;
//        Name = name;
//    }
    //==============================================
    //Attack function===============================
//    virtual void Attack(MainCharacter* Player , Enemy* zombie) override
//    {
//        if(Player->getStamina() >= neededStaminaPerAttack)
//        {
//            zombie->setHP(zombie->getHP() - damagePerAttack);
//            Player->setStamina(Player->getStamina() - neededStaminaPerAttack);
//
//            for(int i = 0 ; i < Player->getWeapons().size() ; i++)
//            {
//                if(Player->getWeapons()[i] == this)
//                {
//                    Player->getWeapons().erase(Player->getWeapons().begin() + i);
//                    break;
//                }
//            }
//        }
//        else{
//
//            cout << "your stamina is less than gun's needed stamina and you will die soon :)";
//        }
//    }
};
class PermenantWeapon : public Weapon{

public:
    //Constructors==================================
    PermenantWeapon() = default;
    PermenantWeapon(int damageperattack , int neededstaminaperattack , int level  , string name, int price) : Weapon( damageperattack ,  neededstaminaperattack ,  level  ,  name,  price){
	}
//    {
//        damagePerAttack = damageperattack;
//        neededStaminaPerAttack = neededstaminaperattack;
//        Level = level;
//        Name = name;
//    }    
};
class UseableItems: public Items{

private:
    int Energy;
    int HealingPower;
    int Level;
//    int Price;
    string className;
//    string Name;
public:
    //Setter & Getters---------
    void setType(string classname)
    {
        className = classname;
    }
    string getType()
    {
        return className;
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
    UseableItems(int energy , int healingpower , int level , string classname , string name, int price) : Items( name,  price)
    {  
        className = classname;
//        Name = name;
        Energy = energy;
        HealingPower = healingpower;
        Level = level;
    }
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
    vector<Weapon*> &getWeapons()
    {
        return weapons;
    }
    void addUseableItems(UseableItems* useableitem)
    {
        useAbleItems.push_back(useableitem);
    }
    vector<UseableItems*> &getUseableItems()
    {
        return useAbleItems;
    }
    //Attack func==========================
    void Attack(Enemy* enemy, Weapon* weapon){
    	if(Stamina >= weapon->getNeededStaminaPerAttack() ){
    		int totalDamage = (weapon->getDamagePerAttack() + (weapon->getLevel()-1)*weapon->getDamagePerAttack()/8) + (weapon->getDamagePerAttack() + (weapon->getLevel()-1)*weapon->getDamagePerAttack()/8)*(Level-1)/5;
    		enemy->setHP(enemy->getHP()-totalDamage);
    		enemy->setStamina(enemy->getStamina()-(totalDamage/4));
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
    //Constructors=========================
    MainCharacter() = default;
    MainCharacter(string name , int hp , int xp , int stamina , string gender , int gold)
    {
        Gold = gold;
        Name = name;
        Level = (xp/50)+1;
        HP = hp;
        XP = xp;
        Stamina = stamina;
        Gender = gender;
    }
    //=====================================
};
class Shop{
private:
    vector<UseableItems*> availableUseables;
    vector<Weapon*> availableWeapons;

public:

    Shop() = default;

    vector<UseableItems*> &getUseableItem()
    {
        return availableUseables;
    }
    vector<Weapon*> &getWeapon()
    {
        return availableWeapons;
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
void buyitemFromShop(Shop Market, MainCharacter* mychar)
{
	showItemsOfShop(Market);
	cout<<"Enter the number of the item you would like to purchase"<<endl;
	int firstInput;
	cin>>firstInput;
	if(firstInput<=Market.getWeapon().size()){
		if(mychar->getGold()>= Market.getWeapon()[firstInput-1]->getPrice()){
			mychar->addWeapon(Market.getWeapon()[firstInput-1]);
			mychar->setGold(mychar->getGold()- Market.getWeapon()[firstInput-1]->getPrice());	
		}
		else{
			cout<<"Not enough gold!"<<endl;
			buyitemFromShop(Market, mychar);
		}
			
	}
	else if(firstInput>Market.getWeapon().size() && firstInput<= Market.getUseableItem().size()){
		if(mychar->getGold()>= Market.getWeapon()[firstInput-1-Market.getWeapon().size()]->getPrice()){
			mychar->addUseableItems(Market.getUseableItem()[firstInput-1-Market.getWeapon().size()]);
			mychar->setGold(mychar->getGold()-Market.getWeapon()[firstInput-1-Market.getWeapon().size()]->getPrice());
		}
		else{
			cout<<"Not enough gold!"<<endl;
			buyitemFromShop(Market, mychar);
		}
			
	} 
	else{
		cout<<"invalid input! Try again"<<endl;
		buyitemFromShop(Market, mychar);
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
	
	cout << "==Now you should pick up a powerful permenant weapon wich will be with you till the end of the war :==" << endl;
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
	MainCharacter Batman("Batman", 100, 100, 100, "Male", 100);
	Enemy croc("Killer Croc", 100 , 200, 20);
	ThrowableWeapon Batarang(5,5,1,"Batarang", 50 );
	Shop Market;
	Market.getWeapon().push_back(&Batarang);
	cout<<Market.getWeapon().size()<<endl;
	buyitemFromShop(Market, &Batman);
	cout<<croc.getHP()<<"  "<<Batman.getGold()<<endl<<"========="<<endl;
	Batman.Attack(&croc , &Batarang);
	cout<<croc.getHP()<<"  "<<Batman.getGold()<<endl<<"========="<<endl;
	return 0;
}