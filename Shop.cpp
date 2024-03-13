#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
#include<ctime>
using namespace std;

class MainCharacter;
class Enemy;
class Weapon;
class UseableItems;
class Shop;

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
class EnemyModel{};
class EnemyView{};
class EnemyController{};
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
    virtual void Attack(MainCharacter* Player , Enemy* zombie)
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
    virtual void Attack(MainCharacter* Player , Enemy* zombie) override
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
void RecieveAttack(Enemy* zombie , MainCharacter* Playar)
{
    Playar->setHP(Playar->getHP() - zombie->getDamagePerAttack());

}
void Attack(MainCharacter* Player , Enemy* zombie , Weapon* gun)
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

//if return value was 1 MainCharacter goes shopping if return value was 0 MainCharacter fights ;
int randomShuffle ( int Difficulty , int Level ) {
    srand(time(0)) ;   
    vector<int> shuffle ;     
    int random ;
    if (Difficulty == 1) {
        random = ((rand() % 100) / Level) - (Level%10) + 35 ;
        if (random>=100 ){
            random = 90 ;
        }
        if (random<=0 ){
            random = 10 ;
        }
        for (int i=0 ; i<random ; ++i){
            shuffle.push_back(1);
        }
        for (int i=0 ; i<100-shuffle.size() ; ++i){
            shuffle.push_back(0);
        }
        random_shuffle(shuffle.begin() , shuffle.end());
        if (shuffle[0] == 1){
            cout << "go to shop" << endl ;
            return 1 ;
        }
        if (shuffle[0] == 0){
            cout << "FIGHT" << endl ;
            return 0 ;
        }
        shuffle.clear() ;
        shuffle.shrink_to_fit();
    }
    if (Difficulty == 2) {
        random = ((rand() % 100) / Level) - (Level%10) + 25 ;
        if (random>=100 ){
            random = 90 ;
        }
        if (random<=0 ){
            random = 10 ;
        }
        for (int i=0 ; i<random ; ++i){
            shuffle.push_back(1);
        }
        for (int i=0 ; i<100-shuffle.size() ; ++i){
            shuffle.push_back(0);
        }
        random_shuffle(shuffle.begin() , shuffle.end());
        if (shuffle[0] == 1){
            cout << "go to shop" << endl ;
            return 1 ;
        }
        if (shuffle[0] == 0){
            cout << "FIGHT" << endl ;
            return 0 ;
        }
        shuffle.clear() ;
        shuffle.shrink_to_fit();
    }
    if (Difficulty == 3) {
        random = ((rand() % 100) / Level) - (Level%10) + 15 ;
        if (random>=100 ){
            random = 90 ;
        }
        if (random<=0 ){
            random = 10 ;
        }  
        for (int i=0 ; i<random ; ++i){
            shuffle.push_back(1);
        }
        for (int i=0 ; i<100-shuffle.size() ; ++i){
            shuffle.push_back(0);
        }
        random_shuffle(shuffle.begin() , shuffle.end());
        if (shuffle[0] == 1){
            //cout << "go to shop" << endl ;
            return 1 ;
        }
        if (shuffle[0] == 0){
            //cout << "FIGHT" << endl ;
            return 0 ;
        }
        shuffle.clear() ;
        shuffle.shrink_to_fit();
    }
}

int main()
{

	MainCharacter player{"Saeed" , 10 , 100 , 100 , 100 , "male" , 10000};
    ThrowableWeapon batrang{10 , 5 , 1 , "ThrowableItem" , "bating"};
	Shop market;
	Enemy zombie{"name" , 50 , 45 , 10};
    player.addWeapon(&batrang);
    player.addWeapon(&batrang);
    
 
    cout << zombie.getHP() << endl;
    for(int i = 0 ; i < player.getWeapons().size() ; i++)
    {
        cout << i << "." << player.getWeapons()[i]->getName() << endl;
    }


    batrang.Attack(&player , &zombie);

    cout << zombie.getHP() << endl;
    for(int i = 0 ; i < player.getWeapons().size() ; i++)
    {
        cout << i << "." << player.getWeapons()[i]->getName() << endl;
    }


	return 0;
}