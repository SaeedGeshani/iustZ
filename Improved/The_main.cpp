#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<stdlib.h>
#include <thread>
#include "Headers/Items.h"
#include "Headers/Items.cpp"
#include "Headers/EnemyFactory.h"
#include "Headers/EnemyFactory.cpp"
#include "Headers/Zombie.h"
#include "Headers/Zombie.cpp"
#include "Headers/Enemy.h"
#include "Headers/Enemy.cpp"
#include "Headers/MainCharacter.h"
#include "Headers/MainCharacter.cpp"
#include "Headers/Shop.h"
#include "Headers/Shop.cpp"
#include "Headers/UseableItems.h"
#include "Headers/UseableItems.cpp"
#include "Headers/PermenantWeapon.h"
#include "Headers/PermenantWeapon.cpp"
#include "Headers/ThrowableWeapon.h"
#include "Headers/ThrowableWeapon.cpp"
#include "Headers/Weapon.h"
#include "Headers/Weapon.cpp"
#include "Headers/ColdWeapon.h"
#include "Headers/ColdWeapon.cpp"
#include "Headers/HotWeapon.h"
#include "Headers/HotWeapon.cpp"
#include "Headers/Batarang.h"
#include "Headers/Batarang.cpp"
#include "Headers/Katana.h"
#include "Headers/Katana.cpp"
#include "Headers/grenade.h"
#include "Headers/grenade.cpp"
#include "Headers/Egg.h"
#include "Headers/Egg.cpp"
#include "Headers/WheyProtein.h"
#include "Headers/WheyProtein.cpp"
#include "Headers/Blaster.h"
#include "Headers/Blaster.cpp"
#include "Headers/human.h"
#include "Headers/human.cpp"
#include "Headers/KratosBlades.h"
#include "Headers/KratosBlades.cpp"
#include "Headers/EnergyDrink.h"
#include "Headers/EnergyDrink.cpp"
#include "Headers/shuriken.h"
#include "Headers/shuriken.cpp"
#include "Headers/Spear.h"
#include "Headers/Spear.cpp"
#include "Headers/XPpotion.h"
#include "Headers/XPpotion.cpp"
#include "Headers/Mjolnir.h"
#include "Headers/Mjolnir.cpp"
#include "Headers/MiniGun.h"
#include "Headers/MiniGun.cpp"
#include "Headers/RocketLauncher.h"
#include "Headers/RocketLauncher.cpp"

using namespace std;

//Global Objects And Variables==============================
    static MainCharacter Warior;
    Shop* Store;
    EnemyFactory Enemyhouse(&Warior);
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

    if(Warior.getUseableItems().size() <= 0)
    {
        for(int i = 0 ; i < Warior.getWeapons().size() ; i++)
        {
            if(Warior.getStamina() > Warior.getWeapons()[i]->getNeededStaminaPerAttack())
            {
                check = true;
            }
        }
    }
    else{

        return true;
    }
    
    return check;
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

	prints("===============Section of making your dreamy wariror===============");
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

	Warior.setName(name);	
	Warior.setGender(gender);
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
    Warior.setGold(1000);
    this_thread::sleep_for(chrono::seconds(33));
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
            Warior.setGold(Warior.getGold()-yourkat->getPrice());
            Warior.addWeapon(yourkat);
        }
        else if(ChosenWeapon == 2)
        {
        	Blaster* yourblast = new Blaster(35 , 10 , "Blaster" , 200);
            Warior.setGold(Warior.getGold()-yourblast->getPrice());
            Warior.addWeapon(yourblast);

        }
        else if(ChosenWeapon == 3)
        {
        	KratosBlades* yourblades = new KratosBlades(25 , 15 , "Kratos Blades" , 150 );
            Warior.setGold(Warior.getGold()-yourblades->getPrice());
            Warior.addWeapon(yourblades);

        }
        else if(ChosenWeapon == 4)
        {
        	MiniGun* yourmini = new MiniGun(55 , 30 , "MiniGun" , 600 );
            Warior.setGold(Warior.getGold()-yourmini->getPrice());
            Warior.addWeapon(yourmini);

        }
        else if(ChosenWeapon == 5)
        {
        	Mjolnir* yourmjo = new Mjolnir(25 , 20 , "Mjolnir" , 130 );
            Warior.setGold(Warior.getGold()-yourmjo->getPrice());
            Warior.addWeapon(yourmjo);

        }
        else if(ChosenWeapon == 6)
        {
        	RocketLauncher* yourrock = new RocketLauncher(110 , 40 , "Rocket Launcher" , 1000);
            Warior.setGold(Warior.getGold()-yourrock->getPrice());
            Warior.addWeapon(yourrock);

        }

        else{
        	
            cout << "You entered an invalid number! So enter a valid input" << endl;
			this_thread::sleep_for(chrono::seconds(3));
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
    Warior.addUseableItems(ptr1WheyPowder);
    Warior.addUseableItems(ptr2WheyPowder);

    Warior.setLevel(1);
    Warior.setHP(100);
    Warior.setStamina(100);
    Warior.setXP(0);
    this_thread::sleep_for(chrono::seconds(7));
    system("cls");
    
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



int main()
{
    Enemy* enemy;
    makingNewcharacter();
    int Difficulty;
    while(true)
    {
        printS("Choose your game Difficulty : (1 , 2 , 3)");
        cin >> Difficulty;
        if(Difficulty == 1 || Difficulty == 2 || Difficulty == 3)
        {
			system("cls");
            break;
            
        }
        system("cls");
    }
    

    bool checkStatus;
    
    while(Warior.getHP() > 0)
    {
        checkStatus = randomShuffle(Difficulty , Warior.getLevel());

        if(checkStatus)
        {
            Store = randomShopGenerator();
            Store->BuyItem(&Warior);
            delete Store;
        }

        else{

            int Whichenemy = rand()%2;

            if(Whichenemy == 0)
            {
                enemy = Enemyhouse.makeZombie();
            }
            else if(Whichenemy == 1) 
            {
                enemy = Enemyhouse.makeHuman();
            }

            while(Warior.getHP() > 0 && enemy->getEnemyModel()->getHP() > 0 && checkContinue())
            {

                while(true)
                {
                    system("cls");
                    cout << "LEVEL" << Warior.getLevel() << endl;
                    prints("================== Danger ===============");
                    printS("Enemy is against you. What do you want to do?");
                    cout << "Enemy race: ";
                    if(enemy->getEnemyModel()->getName() == "Human")
                    {
                        cout << "Human" << endl;
                    }
                    else if(enemy->getEnemyModel()->getName() == "Zombie")                    
                    {
                        cout << "Zombie" << endl;       
                    }

                    cout << "1.Fight" << endl << "2.use Inventory" << endl;

                    cout << "==Warior's HP: " << Warior.getHP() << "     ==Warior's ST: " << Warior.getStamina() << endl;
                    cout << "==Enemy's HP: " << enemy->getEnemyModel()->getHP();
                    if(enemy->getEnemyModel()->getName() == "Human")
                    {
                        cout << "         ==Enmey's DMPA: " << "Depending on Weapon";
                    }
                    else{

                        cout << "         ==Enmey's DMPA: " << enemy->getEnemyModel()->getDamagePerAttack();
                    }
                    cout <<  "     ==Enemy's ST: " << enemy->getEnemyModel()->getStamina() << endl;
                    int input;
                    cin >> input;
                

                    if(input == 1)
                    {
                        
                        
                        while(true)
                        {	system("cls");
                            printS("=========Choose a Weapon========= (0 = exit)");
                            Warior.showCharacterWeapons();
                            cin >> input;
                            
                            
                            if(input <= Warior.getWeapons().size() && input >= 1)
                            {
                                if(Warior.getStamina() > Warior.getWeapons()[input-1]->getNeededStaminaPerAttack())
                                {
                                    Warior.Attack(enemy , Warior.getWeapons()[input-1]);
                                    enemy->getEnemyController()->Attack(&Warior);
                                    this_thread::sleep_for(chrono::seconds(10));
                                    system("cls");
                                    break;
                                }

                                prints("Your Warior doesn't have enough stamina to use this weapon");
                            }
                            else if(input == 0)
                            {
                                break;
                            }
                        }
                        
                        break;
                    } 

                    else if(input == 2)
                    {
                        while(true)
                        {	
                        	system("cls");
                            printS("=========Choose Item=========  (0 = exit) ");
                            Warior.showCharacterUsableItems();
                            cin >> input;

                            if(input >= 1 && input <= Warior.getUseableItems().size())
                            {
                                Warior.useItem(input);
                                Warior.CalculateLevel();
                                break;
                            }
                            else if(input == 0)
                            {
                                break;
                            }
                        }
                        break;
                    }
                }
                
                
            }

            if(Warior.getHP() < 0 || !checkContinue())
            {
            	system("cls");
                prints("=============================");
                cout << "         YOU ARE DEAD        " << endl;
                prints("=============================");
            }
            else if(enemy->getEnemyModel()->getHP() < 0)
            {
            	system("cls");
                prints("===========================");
                cout << "       ENEMY IS DEAD     " << endl;
                prints("===========================");
                Sleep(100);
                Warior.setGold(Warior.getGold() + 50);
                Warior.setXP(Warior.getXP() + 100);
                if(enemy->getEnemyModel()->getName() == "Human")
                {
                	system("cls");
                    cout << "==========================" << endl;
                    cout << "Inventory Of Enemy Looted" << endl;
                    cout << "==========================" << endl;
                    Warior.getEnemyUseableItems(enemy->getEnemyModel()->getEnemyUseableItems());
                    Warior.getEnemyWeapons(enemy->getEnemyModel()->getEnemyWeapons());

                }
                delete enemy;
                Warior.CalculateLevel();
            }
        }
    }

    
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