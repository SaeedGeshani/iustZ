#include<iostream>
#include<vector>
#include<string>
using namespace std;



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
void RecieveAttack(Enemy* zombie , MainCharacter* Playar)
{
    Playar->setHP(Playar->getHP() - zombie->getDamagePerAttack());

}
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


int main()
{
    MainCharacter Saeed{"Saeed" , 4 , 45 , 40 , 100 , "male" , 4000};
    Weapon katana{10 , 5 , 1 , "katana" , "Hkatana"};
    Enemy Zombie{"Big" , 40 , 40 , 5};
    UseableItems wheyProtein{20 , 30 , 4 , "WheyProtein" , "gg"};

    Attack(&Saeed , &Zombie , &katana);
    RecieveAttack(&Zombie , &Saeed);


    cout << Saeed.getHP() << endl << Zombie.getHP() << endl << Saeed.getStamina();

    return 0;
}
