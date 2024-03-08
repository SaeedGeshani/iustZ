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
    //============================
    //Constructor=================
    Weapon() = default;
    Weapon(int damageperattack , int neededstaminaperattack , int level)
    {
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
public:
    //Setter & Getters---------
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
    UseableItems(int energy , int healingpower , int level)
    {
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
    vector<UseableItems*> useAbleItems;
    vector<Weapon*>weapons;

public:
    //Setter & Getters ================
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
    MainCharacter(string name , int level , int hp , int xp , int stamina , string gender)
    {
        Name = name;
        Level = level;
        HP = hp;
        XP = xp;
        Stamina = stamina;
        Gender = gender;
    }
    //=====================================
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

int main()
{
    MainCharacter Saeed{"Saeed" , 4 , 45 , 40 , 100 , "male"};
    Weapon katana{10 , 5 , 1};
    Enemy Zombie{"Big" , 40 , 40 , 5};
    UseableItems wheyProtein{20 , 30 , 4};

    Attack(&Saeed , &Zombie , &katana);
    RecieveAttack(&Zombie , &Saeed);


    cout << Saeed.getHP() << endl << Zombie.getHP() << endl << Saeed.getStamina();

    return 0;
}
