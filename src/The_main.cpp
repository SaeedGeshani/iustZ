#include<string>
#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<fstream>
#include<stdlib.h>
#include <thread>
#include "Headers/Items.h"
#include "Headers/Items.h"
#include "Headers/EnemyFactory.h"
#include "Headers/EnemyFactory.h"
#include "Headers/Zombie.h"
#include "Headers/Zombie.h"
#include "Headers/Enemy.h"
#include "Headers/Enemy.h"
#include "Headers/MainCharacter.h"
#include "Headers/MainCharacter.h"
#include "Headers/Shop.h"
#include "Headers/Shop.h"
#include "Headers/UseableItems.h"
#include "Headers/UseableItems.h"
#include "Headers/PermenantWeapon.h"
#include "Headers/PermenantWeapon.h"
#include "Headers/ThrowableWeapon.h"
#include "Headers/ThrowableWeapon.h"
#include "Headers/Weapon.h"
#include "Headers/Weapon.h"
#include "Headers/ColdWeapon.h"
#include "Headers/ColdWeapon.h"
#include "Headers/HotWeapon.h"
#include "Headers/HotWeapon.h"
#include "Headers/Batarang.h"
#include "Headers/Batarang.h"
#include "Headers/Katana.h"
#include "Headers/Katana.h"
#include "Headers/grenade.h"
#include "Headers/grenade.h"
#include "Headers/Egg.h"
#include "Headers/Egg.h"
#include "Headers/WheyProtein.h"
#include "Headers/WheyProtein.h"
#include "Headers/Blaster.h"
#include "Headers/Blaster.h"
#include "Headers/human.h"
#include "Headers/human.h"
#include "Headers/KratosBlades.h"
#include "Headers/KratosBlades.h"
#include "Headers/EnergyDrink.h"
#include "Headers/EnergyDrink.h"
#include "Headers/shuriken.h"
#include "Headers/shuriken.h"
#include "Headers/Spear.h"
#include "Headers/Spear.h"
#include "Headers/XPpotion.h"
#include "Headers/XPpotion.h"
#include "Headers/Mjolnir.h"
#include "Headers/Mjolnir.h"
#include "Headers/MiniGun.h"
#include "Headers/MiniGun.h"
#include "Headers/RocketLauncher.h"
#include "Headers/RocketLauncher.h"

using namespace std;
void userSave (string name, string gender, int hp, int xp, int gold, int stamina, int level, int kills, int weaponsNum, int usablesNum, vector<Weapon*> weapons, vector<UseableItems*> usable);
ifstream userList ("data/users.txt");

const int UI_WIDTH = 92;
const int NORMAL_PAUSE_MS = 1200;

string centeredText(const string& text, int width = UI_WIDTH)
{
    if(static_cast<int>(text.size()) >= width)
    {
        return text;
    }

    int padding = (width - static_cast<int>(text.size())) / 2;
    return string(padding, ' ') + text;
}

void centeredLine(const string& text = "")
{
    cout << centeredText(text) << endl;
}

void uiSeparator(char fill = '=', int width = 54)
{
    centeredLine(string(width, fill));
}

void uiSectionTitle(const string& title)
{
    uiSeparator('=', 64);
    centeredLine(" " + title);
    uiSeparator('=', 64);
}

void uiBattleStatus(MainCharacter* warrior, Enemy* enemy)
{
    string lineOne =
        "Warrior HP: " + to_string(warrior->getHP()) +
        " | Warrior ST: " + to_string(warrior->getStamina()) +
        " | Enemy HP: " + to_string(enemy->getEnemyModel()->getHP());

    string enemyDamage = enemy->getEnemyModel()->getName() == "Human"
                             ? "Enemy DMPA: Weapon based"
                             : "Enemy DMPA: " + to_string(enemy->getEnemyModel()->getDamagePerAttack());

    string lineTwo = enemyDamage + " | Enemy ST: " + to_string(enemy->getEnemyModel()->getStamina());

    centeredLine(lineOne);
    centeredLine(lineTwo);
    uiSeparator('-', 64);
}

void pauseForReadability(int ms = NORMAL_PAUSE_MS)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}
void printS(const string& s)
{
    cout << s << endl << endl;
}

void prints(const string& s)
{
    cout << s << endl << endl;
}

//Global Objects And Variables==============================
    // static MainCharacter Warior;
    Shop* Store;
    int ZZAARRIIBB;

    int numberOfCharacters;
    static vector<MainCharacter*>Wariors;
    int findEnemyLevel()
    {
    int maxLVL;
    maxLVL = 1;
    int placeOfMaximum = 0;
        for(int i = 0 ; i < Wariors.size() ; i++)
        {
            if(Wariors[i]->getLevel() > maxLVL)
            {
                maxLVL = Wariors[i]->getLevel();
                placeOfMaximum = i;
            }
        }
        return placeOfMaximum;
    }

//==========================================================
//=====Function for cout slowly=============================
    // void printS(string s)
    // {
    //     for(int i = 0 ; i < s.size() ; i++)
    //     {
    //         cout << s[i];
    //         Sleep(20);
    //     }
    //     cout << endl << endl;
    // }
    // void prints(string s)
    // {
    //     for(int i = 0 ; i < s.size() ; i++)
    //     {
    //         cout << s[i];
    //         Sleep(8);
    //     }
    //     cout << endl << endl;
    // }
//==========================================================

bool checkContinue()
{
    bool check = false;

    for(int i = 0 ; i < Wariors.size() ; i++)
    {
        if(Wariors[i]->getUseableItems().size() > 0)
        {
            return true;
        }
        else
        {
            for(int j = 0 ; j < Wariors[i]->getWeapons().size() ; j++)
            {
                if(Wariors[i]->getStamina() > Wariors[i]->getWeapons()[j]->getNeededStaminaPerAttack())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool checkContinueForOne(int i)
{
    if(Wariors[i]->getUseableItems().size() > 0)
    {
        return true;
    }
    for(int j = 0 ; j < Wariors[i]->getWeapons().size() ; j++)
    {
        if(Wariors[i]->getStamina() > Wariors[i]->getWeapons()[j]->getNeededStaminaPerAttack())
        {
            return true;
        }
    }
    return false;
}
int CalculateHPForHuman(int);
int CalculateSTForHuman(int);
int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);

Shop* randomShopGenerator(){
    Shop* randomStore = nullptr;
    Batarang* a = nullptr;
    Blaster* b = nullptr;
    Katana* c = nullptr;
    grenade* d = nullptr;
    Egg* e = nullptr;
    WheyProtein* f = nullptr;
    KratosBlades* g = nullptr;
    EnergyDrink* h = nullptr;
    Mjolnir* I = nullptr;
    MiniGun* J = nullptr;
    RocketLauncher* k = nullptr;
    shuriken* l = nullptr;
    Spear* m = nullptr;
    XPpotion* n = nullptr;



    while(true)
    {
        randomStore = new Shop;
        if(randomStore != nullptr)
        {
            break;
        }
    }
    while(true)
    {
        a = new Batarang(20 , 5 , "Batrang" , 50);
        if(a != nullptr)
        {
            break;
        }
        delete a;
    }

    while(true)
    {
        b = new Blaster(35 , 10 , "Blaster" , 200);
        if(b != nullptr)
        {
            break;
        }
        delete b;
    }

    while(true)
    {
        c = new Katana(20 , 15 , "Katana" , 120);
        if(c != nullptr)
        {
            break;
        }
        delete c;
    }


    while(true)
    {
        d = new grenade(75 , 50 , "Grenade" , 150);
        if(d != nullptr)
        {
            break;
        }
        delete d;
    }

    while(true)
    {
        e = new Egg(10 , 30 , "Egg" , 50 , 0);
        if(e != nullptr)
        {
            break;
        }
        delete e;
    }

    while(true)
    {
        f = new WheyProtein(30 , 30 , "Whey Protein" , 75 , 0);
        if(f != nullptr)
        {
            break;
        }
        delete f;
    }
    while(true)
    {
        g = new KratosBlades(25 , 15 , "Kratos Blades" , 150 );
        if(g != nullptr)
        {
            break;
        }
        delete g;
    }
    while(true)
    {
        h = new EnergyDrink(60 , 0 , "Energy Drink" , 75 , 0);
        if(h != nullptr)
        {
            break;
        }
        delete h;
    }
    while(true)
    {
        I = new Mjolnir(25 , 20 , "Mjolnir" , 130 );
        if(I != nullptr)
        {
            break;
        }
        delete I;
    }
    while(true)
    {
        J = new MiniGun(55 , 30 , "MiniGun" , 600 );
        if(J != nullptr)
        {
            break;
        }
        delete J;
    }
    while(true)
    {
        k = new RocketLauncher(75 , 40 , "Rocket Launcher" , 1000);
        if(k != nullptr)
        {
            break;
        }
        delete k;
    }

    while(true)
    {
        l = new shuriken(15 , 1 , "shuriken" , 30);
        if(l != nullptr)
        {
            break;
        }
        delete l;
    }

    while(true)
    {
        m = new Spear(35 , 15 , "Spear" , 75);
        if(m != nullptr)
        {
            break;
        }
        delete m;
    }

    while(true)
    {
        n = new XPpotion(0 , 0 , "XP Potion" , 25, 50);
        if(n != nullptr)
        {
            break;
        }
        delete n;
    }

    vector<Weapon*> wp{a, b, c, d,g, I, J, k, l, m};
    vector<UseableItems*> itms{e, f,h,n};
    srand(time(0));
    vector<Weapon*> outputweapon;
    vector<UseableItems*> outputusable;
    for(int i=0;i<10;i++){
        if(rand()%2 == 0){
            outputweapon.push_back(wp[i]);
        }
        else{
            delete wp[i];
        }
    }
    for(int i=0 ; i<4 ;i++){
        if(rand()%2 == 0){
            outputusable.push_back(itms[i]);
        }
        else{

            delete itms[i];
        }
    }
    randomStore->setWeapon(outputweapon);
    randomStore->setUsableItems(outputusable);
    return randomStore;

}


void makingNewcharacter()
{
    string name;
    int age;
    string gender;

    prints("===============Section of making your dream wariror===============");
    cout << endl;
    printS("Enter name of the Warior :");
    getline(cin , name);
    system("cls");

    printS("Enter gender of the Warior:(male - female) ");
    getline(cin , gender);
    while(gender != "male" && gender != "female")
    {
        prints("Invalid Input try again: ");
        getline(cin , gender);
    }
    system("cls");


    // Warior.setName(name);
    // Warior.setGender(gender);
    cout << endl;
    prints("===============================================");
    cout << endl;
    prints("The worlds are colliding...parallel realities and dimensions are merging into one,causing a disaster! monsters and evil forces from corrupt universes are invading our realm and wish to conquer it!Even some former allies are taking advantage of the current situation and have joined the dark side in order to take over our world! You and your few comrades are  the empire's last hope...The king needs you to defend the kingdom and save your people from these hellish creatures.    thankfully, you'll have access to different kinds of weapons from all universes which will ease your crusade.");
    printS("KING Summoned you");
    printS("===This gift is given to you by the king to buy your Weapons and continue:===");
    cout << endl;
    printS("===== Here you are:" );
    cout << endl << endl;
    printS("Now you have 1000 G");
    // Warior.setGold(1000);
    // this_thread::sleep_for(chrono::seconds(33));
    system("cls");

    prints("================================================");

    printS("==========Here is the section where you should pick one glorious Permanent Weapon ==============");
    cout << endl;
    int ChosenWeapon;
    do{
        printS("==Now you should pick up a powerful permanent weapon which will be with you till the end of the war :==");
        printS("plese pick up one weapon: ");
        cout << endl;

        cout << "1.Katana" << endl << "2.Blaster" << endl<<"3.Kratos Blades"<<endl<<"4.MiniGun"<<endl<<"5.Mjiolnir"<<endl<<"6.Rocket Launcher"<<endl;

        printS("Katana(120 G)(Damage : 20) (NeededStamina : 15)");
        printS("Blaster(200 G) (Damage : 35) (Needed Stamina : 10)");
        printS("Kratos Blades(150 G) (Damage : 25) (Needed Stamina : 15)");
        printS("MiniGun(600 G) (Damage : 55) (Needed Stamina : 30)");
        printS("Mjiolnir(130 G) (Damage : 25) (Needed Stamina : 20)");
        printS("Rocket Launcher(1000 G) (Damage : 75) (Needed Stamina : 40)");


        cin >> ChosenWeapon;

        if(ChosenWeapon == 1)
        {
           Katana* yourkat = new Katana(20 , 15 , "Katana" , 120);
            // Warior.setGold(Warior.getGold()-yourkat->getPrice());
            // Warior.addWeapon(yourkat);
        }
        else if(ChosenWeapon == 2)
        {
           Blaster* yourblast = new Blaster(35 , 10 , "Blaster" , 200);
            // Warior.setGold(Warior.getGold()-yourblast->getPrice());
            // Warior.addWeapon(yourblast);

        }
        else if(ChosenWeapon == 3)
        {
           KratosBlades* yourblades = new KratosBlades(25 , 15 , "Kratos Blades" , 150 );
            // Warior.setGold(Warior.getGold()-yourblades->getPrice());
            // Warior.addWeapon(yourblades);

        }
        else if(ChosenWeapon == 4)
        {
           MiniGun* yourmini = new MiniGun(55 , 30 , "MiniGun" , 600 );
            // Warior.setGold(Warior.getGold()-yourmini->getPrice());
            // Warior.addWeapon(yourmini);

        }
        else if(ChosenWeapon == 5)
        {
           Mjolnir* yourmjo = new Mjolnir(25 , 20 , "Mjolnir" , 130 );
            // Warior.setGold(Warior.getGold()-yourmjo->getPrice());
            // Warior.addWeapon(yourmjo);

        }
        else if(ChosenWeapon == 6)
        {
           RocketLauncher* yourrock = new RocketLauncher(110 , 40 , "Rocket Launcher" , 1000);
            // Warior.setGold(Warior.getGold()-yourrock->getPrice());
            // Warior.addWeapon(yourrock);

        }

        else{

            cout << "You entered an invalid number! So enter a valid input" << endl;
            pauseForReadability();
           system("cls");
        }


    }while(ChosenWeapon != 1 && ChosenWeapon != 2 && ChosenWeapon != 3 && ChosenWeapon != 4 && ChosenWeapon != 5 && ChosenWeapon != 6 );
    system("cls");
    prints("==============================================");
    cout << endl;

    printS("========================== GIFT ===========================");
    printS("===== Now we will give you somthing that you can heal yourself with and give your muscular body a litle bit of Energy.So take them and add them to your Inventory");
    printS("The first one is WheyPowder which helps you get Stamina(by 30 ST) and heal your body(by 30 HP) you will have two :");
    WheyProtein* ptr1WheyPowder = new WheyProtein(30 , 30   , "Whey Protein" , 75, 0);
    WheyProtein* ptr2WheyPowder = new WheyProtein(30 , 30   , "Whey Protein" , 75, 0);
    // Warior.addUseableItems(ptr1WheyPowder);
    // Warior.addUseableItems(ptr2WheyPowder);

    // Warior.setLevel(1);
    // Warior.setHP(100);
    // Warior.setStamina(100);
    // Warior.setXP(0);
    pauseForReadability(1500);
    system("cls");

}

void makingSomeNewCharacter()
{
    // ofstream user("data/users.txt" , ios::app);
    int wariorMode;
    prints("How many playable character would you like to include in the game?");
    cin >> numberOfCharacters;
    ZZAARRIIBB = numberOfCharacters;
    system("cls");

    for (int w = 0; w < numberOfCharacters; w++)
    {
       while(true){
       if(numberOfCharacters>1)
            cout<<"Player "<<w+1<<"'s turn:"<<endl;

        system("cls");
        // if (wariorMode == 1)
        // {
        //    string hyhy;
        //     int n=0;
        //     while (userList >> hyhy){
        //         n++;
        //    }
        //    if(n!=0){
        //    	cout << "\nlist of users:\n";
        //        string username;

        //         userList.close();
        //         ifstream userList("data/users.txt");
        //        while (userList >> username)
        //            cout << username << endl;
        //        prints("Enter the name of the warior you'd like to choose:\n");
        //        string insideWarior;
        //        cin >> insideWarior;
        //        ifstream wariorDetail ("data/" + insideWarior + ".txt");
        //        string wariorName, wariorGender;
        //        int wariorHP, wariorXP, wariorStamina, wariorGold, wariorLevel, wariorKills, weaponNum, usableNum;
        //        wariorDetail >> wariorName >> wariorGender >> wariorHP >> wariorXP >> wariorGold >> wariorStamina >> wariorLevel >> wariorKills >> weaponNum >> usableNum;
        //        MainCharacter* newWarior = new MainCharacter(wariorName , wariorHP , wariorXP , wariorStamina , wariorGender , wariorGold);
        //        newWarior->setKills(wariorKills);
        //        newWarior->setLevel(wariorLevel);
        //        int o = 1;
        //        string itemTemp = "!";
        //        while (wariorDetail >> itemTemp)
        //        {
        //            for (int n = 0; n < weaponNum; n++)
        //            {
        //                 if(itemTemp == "Katana")
        //                 {
        //                    Katana* yourkat = new Katana(20 , 15 , "Katana" , 120);
        //                     newWarior->addWeapon(yourkat);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Blaster")
        //                 {
        //                    Blaster* yourblast = new Blaster(35 , 10 , "Blaster" , 200);
        //                     newWarior->addWeapon(yourblast);
        //                     break;

        //                 }
        //                 else if(itemTemp == "Kratos")
        //                 {
        //                    KratosBlades* yourblades = new KratosBlades(25 , 15 , "Kratos Blades" , 150 );
        //                     newWarior->addWeapon(yourblades);
        //                     break;
        //                 }
        //                 else if(itemTemp == "MiniGun")
        //                 {
        //                    MiniGun* yourmini = new MiniGun(55 , 30 , "MiniGun" , 600 );
        //                     newWarior->addWeapon(yourmini);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Mjolnir")
        //                 {
        //                    Mjolnir* yourmjo = new Mjolnir(25 , 20 , "Mjolnir" , 130 );
        //                     newWarior->addWeapon(yourmjo);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Rocket")
        //                 {
        //                    RocketLauncher* yourrock = new RocketLauncher(110 , 40 , "Rocket Launcher" , 1000);
        //                     newWarior->addWeapon(yourrock);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Spear")
        //                 {
        //                    Spear* yourspear = new Spear(35 , 15 , "Spear" , 75);
        //                     newWarior->addWeapon(yourspear);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Batarang")
        //                 {
        //                    Batarang* yourbat = new Batarang(20 , 5 , "Batrang" , 50);
        //                     newWarior->addWeapon(yourbat);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Grenade")
        //                 {
        //                    grenade* yournade = new grenade(75 , 50 , "Grenade" , 150);
        //                     newWarior->addWeapon(yournade);
        //                     break;
        //                 }
        //                 else if(itemTemp == "shuriken")
        //                 {
        //                    shuriken* yourshur = new shuriken(15 , 1 , "shuriken" , 30);
        //                     newWarior->addWeapon(yourshur);
        //                     break;
        //                 }
        //                 else if (itemTemp == "Launcher" || itemTemp == "Blades")
        //                 {
        //                     continue;
        //                 }

        //                 // newWarior->showCharacterWeapons();
        //            }
        //         for (int n = 0; n < usableNum; n++)
        //         {
        //             if(itemTemp == "Egg")
        //             {
        //                Egg* youregg = new Egg(10 , 30 , "Egg" , 50 , 0);
        //                 newWarior->addUseableItems(youregg);
        //                 break;
        //             }
        //             else if(itemTemp == "Whey")
        //             {
        //                WheyProtein* yourwhey = new WheyProtein(30 , 30 , "Whey Protein" , 75 , 0);
        //                 newWarior->addUseableItems(yourwhey);
        //                 break;
        //             }
        //             else if(itemTemp == "Energy")
        //             {
        //                EnergyDrink* yourenergy = new EnergyDrink(60 , 0 , "Energy Drink" , 75 , 0);
        //                 newWarior->addUseableItems(yourenergy);
        //                 break;
        //             }
        //             else if(itemTemp == "XP")
        //             {
        //                XPpotion* yourxp = new XPpotion(0 , 0 , "XP Potion" , 25, 50);
        //                 newWarior->addUseableItems(yourxp);
        //                 break;
        //             }
        //             else if (itemTemp == "Potion" || itemTemp == "Drink" || itemTemp == "Protein")
        //             {
        //                 continue;
        //             }

        //         }
        //           Wariors.push_back(newWarior);
        //        break;
        //     }

        //    }
        //    else{
        //    	prints("There are no available wariors saved on your memory!\nYou'll have to make one!");
        //    }

        // }


//           cout << endl;
//       	prints("===============================================");
//       	cout << endl;
//       	prints("The worlds are colliding...parallel realities and dimensions are merging into one,causing a disaster! monsters and evil forces from corrupt universes are invading our realm and wish to conquer it!Even some former allies are taking advantage of the current situation and have joined the dark side in order to take over our world! You and your few comrades are  the empire's last hope...The king needs you to defend the kingdom and save your people from these hellish creatures.    thankfully, you'll have access to different kinds of weapons from all universes which will ease your crusade.");
//       	this_thread::sleep_for(chrono::seconds(33));
//       	system("cls");
            int age;
            string gender , name;

            prints("===============making your dreamy warrior===============");
            cout << endl;
            cout << "Enter the name of your Warior" << endl;

            cin >> name;
            // cout << name;
            // user << name << endl;
            system("cls");

            printS("Enter gender of the Warior:(male - female) ");
            getline(cin >>ws, gender);
            while(gender != "male" && gender != "female")
            {
                prints("Invalid Input try again: ");
                getline(cin>>ws , gender);
            }
            system("cls");

            cout << endl;
            prints("===============================================");
            cout << endl;
            printS("KING Summoned you");
           printS("===This gift is given to you by the king to buy your Weapons and continue:===");
           cout << endl;
           printS("===== Here you are:" );
            prints("Your Character will have 1000 G at the begining");
            pauseForReadability(1000);
            system("cls");

            MainCharacter* newWarior = new MainCharacter(name , 100 , 0 , 100 , gender , 1000);
            newWarior->setKills(0);
            newWarior->setLevel(1);
            newWarior->setXP(0);
            printS("==========Here is the section where you should pick one glorious Permanent Weapon==============");
            cout << endl;
            int ChosenWeapon;
        do{
            printS("==Now you should pick up a powerful permanent weapon which will be with you till the end of the war :==");
            printS("plese pick up one weapon: ");
            cout << endl;

            cout << "1.Katana" << endl << "2.Blaster" << endl<<"3.Kratos Blades"<<endl<<"4.MiniGun"<<endl<<"5.Mjiolnir"<<endl<<"6.Rocket Launcher"<<endl;

            printS("Katana(120 G)(Damage : 20) (NeededStamina : 15)");
            printS("Blaster(200 G) (Damage : 35) (Needed Stamina : 10)");
            printS("Kratos Blades(150 G) (Damage : 25) (Needed Stamina : 15)");
            printS("MiniGun(600 G) (Damage : 55) (Needed Stamina : 30)");
            printS("Mjiolnir(130 G) (Damage : 25) (Needed Stamina : 20)");
            printS("Rocket Launcher(1000 G) (Damage : 75) (Needed Stamina : 40)");


            cin >> ChosenWeapon;

            if(ChosenWeapon == 1)
            {
               Katana* yourkat = new Katana(20 , 15 , "Katana" , 120);
                newWarior->setGold(newWarior->getGold()-yourkat->getPrice());
                newWarior->addWeapon(yourkat);
            }
            else if(ChosenWeapon == 2)
            {
               Blaster* yourblast = new Blaster(35 , 10 , "Blaster" , 200);
                newWarior->setGold(newWarior->getGold()-yourblast->getPrice());
                newWarior->addWeapon(yourblast);

            }
            else if(ChosenWeapon == 3)
            {
               KratosBlades* yourblades = new KratosBlades(25 , 15 , "Kratos Blades" , 150 );
                newWarior->setGold(newWarior->getGold()-yourblades->getPrice());
                newWarior->addWeapon(yourblades);

            }
            else if(ChosenWeapon == 4)
            {
               MiniGun* yourmini = new MiniGun(55 , 30 , "MiniGun" , 600 );
                newWarior->setGold(newWarior->getGold()-yourmini->getPrice());
                newWarior->addWeapon(yourmini);

            }
            else if(ChosenWeapon == 5)
            {
               Mjolnir* yourmjo = new Mjolnir(25 , 20 , "Mjolnir" , 130 );
                newWarior->setGold(newWarior->getGold()-yourmjo->getPrice());
                newWarior->addWeapon(yourmjo);

            }
            else if(ChosenWeapon == 6)
            {
               RocketLauncher* yourrock = new RocketLauncher(110 , 40 , "Rocket Launcher" , 1000);
                newWarior->setGold(newWarior->getGold()-yourrock->getPrice());
                newWarior->addWeapon(yourrock);

            }

            else{

                cout << "You entered an invalid number! So enter a valid input" << endl;
               pauseForReadability();
               system("cls");
            }


            }while(ChosenWeapon != 1 && ChosenWeapon != 2 && ChosenWeapon != 3 && ChosenWeapon != 4 && ChosenWeapon != 5 && ChosenWeapon != 6 );
            system("cls");

            printS("========================== GIFT ===========================");
           printS("===== Now we will give you somthing that you can heal yourself with and give your muscular body a litle bit of Energy.So take them and add them to your Inventory");
           printS("The first one is Whey Powder which helps you get Stamina(by 30 ST) and heal your body(by 30 HP) you will have two :");
            prints("Here are two whey powders for you");

            WheyProtein* ptr1WheyPowder = new WheyProtein(30 , 30   , "Whey Protein" , 75, 0);
            WheyProtein* ptr2WheyPowder = new WheyProtein(30 , 30   , "Whey Protein" , 75, 0);
            newWarior->addUseableItems(ptr1WheyPowder);
            newWarior->addUseableItems(ptr2WheyPowder);
            pauseForReadability(900);
            system("cls");
            userSave (newWarior->getName(), newWarior->getGender(), newWarior->getHP(), newWarior->getXP(), newWarior->getGold(), newWarior->getStamina(), newWarior->getLevel(), newWarior->getKills(), newWarior->getWeapons().size(), newWarior->getUseableItems().size() , newWarior->getWeapons(), newWarior->getUseableItems());
            Wariors.push_back(newWarior);

           break;



        }

    }

}
//Making Game ready to Start the story
// void makeGameplayReady()
// {
// //    Store.setLevel(1);
// //    Store.setName("BlackMarket");
//     Enemyhouse.setEnemyLevel();

// }

//if return value was 1 MainCharacter goes shopping if return value was 0 MainCharacter fights ;
bool randomShuffle ( int Difficulty , int Level ) {
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
            cout << "Go to shop" << endl ;
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
    return -1;
}

bool isAlive()
{
    // for(int i = 0 ; i < Wariors.size() ; i++)
    // {
    //     if(Wariors[i]->getHP() > 0)
    //     {
    //         return true;
    //     }
    // }
    // return false;

    if(Wariors.size() > 0)
    {
        return true;
    }
    return false;
}


int main()
{

    // string tttt;
    // userList >> tttt;
    // cout << tttt << endl;
    cout << endl;
    prints("===============================================");
    cout << endl;
      prints("The worlds are colliding...parallel realities and dimensions are merging into one,causing a disaster! monsters and evil forces from corrupt universes are invading our realm and wish to conquer it!Even some former allies are taking advantage of the current situation and have joined the dark side in order to take over our world! You and your few comrades are  the empire's last hope...The king needs you to defend the kingdom and save your people from these hellish creatures.    thankfully, you'll have access to different kinds of weapons from all universes which will ease your crusade.");
      // this_thread::sleep_for(chrono::seconds(33));
    system("cls");
    Enemy* enemy;
    // makingNewcharacter();
    makingSomeNewCharacter();

    EnemyFactory Enemyhouse(Wariors[findEnemyLevel()] , ZZAARRIIBB);
    int Difficulty;
    while(true)
    {
        uiSectionTitle("Difficulty Selection");
        centeredLine("  1) Casual");
        centeredLine("  2) Challenger");
        centeredLine("  3) Nightmare");
        uiSeparator('-');
        centeredLine("Choose difficulty [1-3]:");
        cout << centeredText("> ");
        cin >> Difficulty;
        if(Difficulty == 1 || Difficulty == 2 || Difficulty == 3)
        {
            system("cls");
            break;

        }
        system("cls");
    }


    bool checkStatus;
    int enemyCount = 0;

    while(isAlive() && checkContinue())
    {
       checkStatus = randomShuffle(Difficulty , Wariors[findEnemyLevel()]->getLevel());

       if(checkStatus)
       {


        for(int i = 0 ; i < Wariors.size() ; i++)
        {
            if(Wariors[i]->getHP() > 0)
            {
                Store = randomShopGenerator();
                prints("=========================================");
                centeredLine("Buying item for " + Wariors[i]->getName());
                prints("=========================================");
                Store->BuyItem(Wariors[i]);
                // userSave (Wariors[i]->getName(), Wariors[i]->getGender(), Wariors[i]->getHP(), Wariors[i]->getXP(), Wariors[i]->getGold(), Wariors[i]->getStamina(), Wariors[i]->getLevel(), Wariors[i]->getKills(), Wariors[i]->getWeapons().size(), Wariors[i]->getUseableItems().size() , Wariors[i]->getWeapons(), Wariors[i]->getUseableItems());
                delete Store;
            }

        }

       }

       else
       {
        int whichEnemy = rand()%2;
        if(whichEnemy == 0)
        {
            enemy = Enemyhouse.makeZombie();
        }
        else if(whichEnemy == 1)
        {
            enemy = Enemyhouse.makeHuman();
        }
        enemyCount++;

        while(enemy->getEnemyModel()->getHP() > 0 && isAlive() && checkContinue())
        {
            for(int i = 0 ; i < Wariors.size() && enemy->getEnemyModel()->getHP() > 0 ; i++)
            {
                if(Wariors[i]->getHP() > 0)
                {
                    if(checkContinueForOne(i))
                    {
                pauseForReadability();
                       system("cls");
                        uiSectionTitle("Battlefield");
                        centeredLine("Level " + to_string(Wariors[findEnemyLevel()]->getLevel()) + " encounter");
                        centeredLine("Enemy #" + to_string(enemyCount) + " race:");
                        if(enemy->getEnemyModel()->getName() == "Human")
                        {
                            centeredLine("Human");
                        }
                        else if(enemy->getEnemyModel()->getName() == "Zombie")
                        {
                            centeredLine("Zombie");
                        }

                        uiSeparator('-');
                        centeredLine(Wariors[i]->getName() + "'s turn");
                        uiSeparator('-');
                        centeredLine("Facing Enemy #" + to_string(enemyCount));
                        centeredLine("1) Fight");
                        centeredLine("2) Use inventory");
                        uiBattleStatus(Wariors[i], enemy);
                        cout << centeredText("Your choice: ");


                        int input;
                        cin >> input;
                        system("cls");

                        if(input == 1)
                        {
                            while(true)
                            {
                                system("cls");
                                uiSectionTitle("Choose a Weapon");
                                centeredLine("For " + Wariors[i]->getName() + " (0 to go back)");
                                uiSeparator('-');
                                Wariors[i]->showCharacterWeapons();
                                cout << centeredText("Weapon number: ");
                                cin >> input;

                                if(input <= Wariors[i]->getWeapons().size() && input >= 1)
                                {
                                    if(Wariors[i]->getStamina() > Wariors[i]->getWeapons()[input-1]->getNeededStaminaPerAttack())
                                    {
                                        Wariors[i]->Attack(enemy , Wariors[i]->getWeapons()[input-1]);
                                        if(enemy->getEnemyModel()->getHP() <= 0)
                                        {
                                            Wariors[i]->setKills(Wariors[i]->getKills() + 1);
                                            prints("===========================================");
                                            centeredLine("Enemy #" + to_string(enemyCount) + " was killed by " + Wariors[i]->getName() + " | " + to_string(Wariors[i]->getKills()) + " total kill(s)");
                                            prints("===========================================");
                                            pauseForReadability();
                                           system("cls");
                                            // for (int l = 0; l < Wariors.size(); l++)
                                            // {
                                            //     userSave (Wariors[l]->getName(), Wariors[l]->getGender(), Wariors[l]->getHP(), Wariors[l]->getXP(), Wariors[l]->getGold(), Wariors[l]->getStamina(), Wariors[l]->getLevel(), Wariors[l]->getKills(), Wariors[l]->getWeapons().size(), Wariors[l]->getUseableItems().size() , Wariors[l]->getWeapons(), Wariors[l]->getUseableItems());
                                            // }

                                            Wariors[i]->setGold(Wariors[i]->getGold() + 70);
                                            Wariors[i]->setXP(Wariors[i]->getXP() + 150);
                                            Wariors[i]->CalculateLevel();
                                            for(int j = 0 ; j < Wariors.size() ; j++)
                                            {
                                                if(j != i)
                                                {
                                                    Wariors[j]->setXP(Wariors[j]->getXP() + 40);
                                                    Wariors[j]->setGold(Wariors[j]->getGold() + 30);
                                                    Wariors[j]->CalculateLevel();
                                                }
                                            }
                                            if(enemy->getEnemyModel()->getName() == "Human")
                                            {
                                               system("cls");
                                                cout << "==========================" << endl;
                                                cout << "Inventory Of Enemy Looted" << endl;
                                                cout << "==========================" << endl;
                                                pauseForReadability(1000);
                                               system("cls");
                                                Wariors[i]->getEnemyUseableItems(enemy->getEnemyModel()->getEnemyUseableItems());
                                                Wariors[i]->getEnemyWeapons(enemy->getEnemyModel()->getEnemyWeapons());
                                            //     for (int l = 0; l < Wariors.size(); l++)
                                            // {
                                            //     userSave (Wariors[l]->getName(), Wariors[l]->getGender(), Wariors[l]->getHP(), Wariors[l]->getXP(), Wariors[l]->getGold(), Wariors[l]->getStamina(), Wariors[l]->getLevel(), Wariors[l]->getKills(), Wariors[l]->getWeapons().size(), Wariors[l]->getUseableItems().size() , Wariors[l]->getWeapons(), Wariors[l]->getUseableItems());
                                            // }

                                            }
                                            delete enemy;
                                            break;
                                        }

                                        break;
                                    }
                                    else
                                    {
                                        prints("   Your character doesn't have enough energy to use this weapon");
                                    }
                                }
                                else if(input == 0)
                                {
                                    i--;
                                    break;
                                }

                                else
                                {
                                    cout << "Invalid input " << endl;
                                }
                            }
                        }

                        else if(input == 2)
                        {
                            while(true)
                            {
                                system("cls");
                                uiSectionTitle("Use Inventory Item");
                                centeredLine("For " + Wariors[i]->getName() + " (0 to go back)");
                                uiSeparator('-');
                                Wariors[i]->showCharacterUsableItems();
                                cout << centeredText("Item number: ");
                                cin >> input;

                                if(input >= 1 && input <= Wariors[i]->getUseableItems().size())
                                {
                                    Wariors[i]->useItem(input);
                                    Wariors[i]->CalculateLevel();
                                    i--;

                                    break;
                                }
                                else if(input == 0)
                                {
                                    i--;
                                    break;
                                }
                            }
                        }
                        else{
                            system("cls");
                            i--;
                        }

                    }
                    else
                    {
                        centeredLine(Wariors[i]->getName() + " couldn't attack due to lack of stamina");


                    }
                }
            }
            int attackNumber = rand()%Wariors.size();
             if(enemy->getEnemyModel()->getHP() > 0)
            {
                while(true)
                {
                    attackNumber = rand()%Wariors.size();
                    if(Wariors[attackNumber]->getHP() > 0)
                    {
                        centeredLine("Enemy #" + to_string(enemyCount) + " attacks " + Wariors[attackNumber]->getName() + "!");
                        enemy->getEnemyController()->Attack(Wariors[attackNumber]);
                        if(Wariors[attackNumber]->getHP() < 0)
                        {
                            prints("==================================");
                            cout << "       " << Wariors[attackNumber]->getName() << " is dead" << endl;
                            prints("==================================");
                            // string username;
                            // ofstream userRewrite("data/users.txt");
                            // ofstream user("data/users.txt" , ios::app);
                            // userRewrite << "";
                            // while (userList >> username)
                            // {
                            //     if (username == Wariors[attackNumber]->getName())
                            //     {
                            //         continue;
                            //     }
                            //     else
                            //     {
                            //         user << username << endl;
                            //     }
                            // }

                            // for (int l = 0; l < Wariors.size(); l++)
                            // {
                            //     userSave (Wariors[l]->getName(), Wariors[l]->getGender(), Wariors[l]->getHP(), Wariors[l]->getXP(), Wariors[l]->getGold(), Wariors[l]->getStamina(), Wariors[l]->getLevel(), Wariors[l]->getKills(), Wariors[l]->getWeapons().size(), Wariors[l]->getUseableItems().size() , Wariors[l]->getWeapons(), Wariors[l]->getUseableItems());
                            // }
                            delete Wariors[attackNumber];
                            Wariors.erase(Wariors.begin() + attackNumber);
                            Wariors.shrink_to_fit();
                        }
                        break;
                    }
                }

                while(true)
                {
                    attackNumber = rand()%Wariors.size();
                    if(Wariors[attackNumber]->getHP() > 0)
                    {
                        centeredLine("Enemy #" + to_string(enemyCount) + " attacks " + Wariors[attackNumber]->getName() + "!");
                        enemy->getEnemyController()->Attack(Wariors[attackNumber]);
                        if(Wariors[attackNumber]->getHP() < 0)
                        {
                            prints("==================================");
                            cout << "       " << Wariors[attackNumber]->getName() << " is dead" << endl;
                            prints("==================================");
                            // string username;
                            // ofstream userRewrite("data/users.txt");
                            // ofstream user("data/users.txt" , ios::app);
                            // userRewrite << "";
                            // while (userList >> username)
                            // {
                            //     if (username == Wariors[attackNumber]->getName())
                            //     {
                            //         continue;
                            //     }
                            //     else
                            //     {
                            //         user << username << endl;
                            //     }
                            // }
                            // for (int l = 0; l < Wariors.size(); l++)
                            // {
                            //     userSave (Wariors[l]->getName(), Wariors[l]->getGender(), Wariors[l]->getHP(), Wariors[l]->getXP(), Wariors[l]->getGold(), Wariors[l]->getStamina(), Wariors[l]->getLevel(), Wariors[l]->getKills(), Wariors[l]->getWeapons().size(), Wariors[l]->getUseableItems().size() , Wariors[l]->getWeapons(), Wariors[l]->getUseableItems());
                            // }
                            delete Wariors[attackNumber];
                            Wariors.erase(Wariors.begin() + attackNumber);
                            Wariors.shrink_to_fit();
                        }
                        break;
                    }
                }
            }


        }

       }
    }

    prints("=============================================");
    centeredLine("All warriors have fallen.");
    prints("=============================================");
    // for (int l = 0; l < Wariors.size(); l++)
    // {
    //     userSave (Wariors[l]->getName(), Wariors[l]->getGender(), Wariors[l]->getHP(), Wariors[l]->getXP(), Wariors[l]->getGold(), Wariors[l]->getStamina(), Wariors[l]->getLevel(), Wariors[l]->getKills(), Wariors[l]->getWeapons().size(), Wariors[l]->getUseableItems().size() , Wariors[l]->getWeapons(), Wariors[l]->getUseableItems());
    // }
}

int CalculateHPForHuman(int level)
{
    return level*8 + 80;
}
int CalculateSTForHuman(int level)
{
    return level *10 + 70;
}

int CalculateDMPAforZombie(int level)
{
    int DMPA;
    DMPA = pow(level , 10/7) + 10;
    return DMPA;
}
int CalculateSTforZombie(int level)
{
    int ST;
    ST = level * 20 + 50;
    return ST;
}
int CalculateHPForZombie(int level)
{
    int HP;
    HP = pow(level , 4/3) * 20 + 50;
    return HP;
}
void userSave (string name, string gender, int hp, int xp, int gold, int stamina, int level, int kills, int weaponsNum, int usablesNum, vector<Weapon*> weapons, vector<UseableItems*> usable) {
    ofstream save ("data/" + name + ".txt");
    save << name << endl << gender << endl<< hp << endl << xp << endl << gold << endl << stamina << endl << level << endl << kills << endl << weaponsNum << endl << usablesNum << endl;
    for (int i = 0; i < weapons.size(); i++)
        save << weapons[i]->getName() << endl;
    for (int i = 0; i < usable.size(); i++)
        save << usable[i]->getName() << endl;
}
