#include<string>
#include<iostream>
#include<vector>
using namespace std;

class Enemy{
protected:
    int Health;
    string Name;
    int Level;


public:
    void costHealth(int damage)
    {
        Health -= damage;
    }
    
};

class ColdWeapon{
protected:
    string Name;
    int Level;

public:
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

    void Attack(MainCharacter maincharacter , Enemy enemy)
    {
        enemy.costHealth(40);
        maincharacter.costStamina(30);
    }

};

class MainCharacter{
protected:
//  Properties
    string Name;
    int Level;
    string Gender;
    int Age;
    int Health;
    int Stamina;
    int XP;
    ColdWeapon CLWeapon;
    HotWeapon HTWeapon;
    vector<ThrowableItems> THItems;
    vector<UseableItems> USItems;

public:
    MainCharacter(string name , int age , string gender)
    {
        Name = name;
        Age = age;
        Gender = gender;
    }

    void setName(string name)
    {
        Name = name;
    }
    string getName()
    {
        return Name;
    }

    void setAge(int age)
    {
        Age = age;
    }
    int getAge()
    {
        return Age;
    }

    void setGender(string gender)
    {
        Gender = gender;
    }
    string getGender()
    {
        return Gender;
    }

    void Attack(string weaponName)
    {
        // Write Suitable code here...
    }

    void ShowItems()
    {
        //Write Suitable code here...
    }

    void UseItems()
    {
        //Write Suitable code here...
    }


};

int main()
{
    return 0;
}