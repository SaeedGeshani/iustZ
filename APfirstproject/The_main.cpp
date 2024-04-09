#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<ctime>
#include<stdlib.h>
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
void leaderboard (int level, int xp);
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
        a = new Batarang(40 , 15 , "Batrang" , 75);
        if(a != nullptr)
        {
            break;
        }
        delete a;
    }
	
    while(true)
    {
        b = new Blaster(20 , 10 , "Blaster" , 50);
        if(b != nullptr)
        {
            break;
        }
        delete b;
    }
	
    while(true)
    {
        c = new Katana(30 , 15 , "Katana" , 100);
        if(c != nullptr)
        {
            break;
        }
        delete c;
    }

	
    while(true)
    {
        d = new grenade(75 , 50 , "Grenade" , 120);
        if(d != nullptr)
        {
            break;
        }
        delete d;
    }
	
    while(true)
    {
        e = new Egg(20 , 20 , "Egg" , 20 , 10);
        if(e != nullptr)
        {
            break;
        }
        delete e;
    }
	
    while(true)
    {
        f = new WheyProtein(15 , 30 , "Whey Protein" , 50 , 10);
        if(f != nullptr)
        {
            break;
        }
        delete f;
    }

	vector<Weapon*> wp{a, b, c, d};
	vector<UseableItems*> itms{e, f};
	srand(time(0));
	vector<Weapon*> outputweapon;
	vector<UseableItems*> outputusable;
	for(int i=0;i<4;i++){
		if(rand()%2 == 0){
			outputweapon.push_back(wp[i]);
		}	
        else{
            delete wp[i];
        }
	}
	for(int i=0;i<2;i++){
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

	
	printS("Enter gender of the Warior:(male - female) ");
	getline(cin , gender);
	while(gender != "male" && gender != "female")
	{
        prints("Invalid Input try again: ");
		getline(cin , gender);
	}

	Warior.setName(name);	
	Warior.setGender(gender);
    cout << endl;
    prints("===============================================");
    cout << endl;
    printS("KING Summoned you");
    printS("===This gift is given from the King to you to buy your Weapons to continue:===");
    cout << endl;
    printS("===== Here you are:" );
    cout << endl << endl;
    printS("Now you have 1000 G");
    Warior.setGold(1000);
    prints("================================================");

    printS("==========Here is the section of that you shold pick one glorious Permenant Weapon ==============");
    cout << endl;
    int ChosenWeapon;
    do{
        printS("==Now you should pick up a powerful permenant weapon which will be with you till the end of the war :==");
	    printS("plese pick up one weapon: ");
        cout << endl;

	    cout << "1.Katana" << endl << "2.Blaster" << endl;

        printS("Katana(100 G)(Damage : 20) (NeededStamina : 15)");
        printS("Blaster(75 G) (Damage : 15) (Needed Stamina : 10)");

	    
	    cin >> ChosenWeapon;

        if(ChosenWeapon == 1)
        {
        	Katana* yourkat = new Katana(40 , 15 , "Katana" , 100);
            Warior.setGold(Warior.getGold()-yourkat->getPrice());
            Warior.addWeapon(yourkat);
        }
        else if(ChosenWeapon == 2)
        {
        	Blaster* yourblast = new Blaster(15 , 10 , "Blaster" , 75);
            Warior.setGold(Warior.getGold()-yourblast->getPrice());
            Warior.addWeapon(yourblast);

        }

        else{

            cout << "You entered invalid number so enter true one" << endl;
        }
	
    }while(ChosenWeapon != 1 && ChosenWeapon != 2 );

    prints("==============================================");
    cout << endl;

    printS("========================== GIFT ===========================");
    printS("===== Now we will give you somthing that you can heal yourself and give your muscular body a litle bit Energy so take them and put in your Inventory");
    printS("The first one is WheyPowder it helps you to get Stamina(50) and heal your body(10) you will have two:");
    WheyProtein* ptr1WheyPowder = new WheyProtein(50 , 10   , "Whey Powder" , 30, 0);
    WheyProtein* ptr2WheyPowder = new WheyProtein(50 , 10   , "Whey Powder" , 30, 0);
    Warior.addUseableItems(ptr1WheyPowder);
    Warior.addUseableItems(ptr2WheyPowder);

    Warior.setLevel(1);
    Warior.setHP(100);
    Warior.setStamina(100);
    Warior.setXP(0);
    
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
    makingNewcharacter();
    int Difficulty;
    while(true)
    {
        printS("Choose your game Difficulty : (1 , 2 , 3)");
        cin >> Difficulty;
        if(Difficulty == 1 || Difficulty == 2 || Difficulty == 3)
        {
            break;
        }
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

            Zombie* enemy = Enemyhouse.makeZombie();

            while(Warior.getHP() > 0 && enemy->getEnemyModel()->getHP() > 0)
            {

                while(true)
                {
                    cout << "LEVEL" << Warior.getLevel() << endl;
                    prints("================== Danger ===============");
                    printS("Enemy is against you what you want to do?");
                    cout << "1.Fight" << endl << "2.use Inventory" << endl;

                    cout << "==Warior's HP: " << Warior.getHP() << "     ==Warior's ST: " << Warior.getStamina() << endl;
                    cout << "==Enemy's HP: " << enemy->getEnemyModel()->getHP() << "         ==Enmey's DMPA: " << enemy->getEnemyModel()->getDamagePerAttack() << endl;
                    int input;
                    cin >> input;
                

                    if(input == 1)
                    {
                        
                        
                        while(true)
                        {
                            printS("=========Choose a Weapon========= (0 = exit)");
                            Warior.showCharacterWeapons();
                            cin >> input;
                            if(input <= Warior.getWeapons().size() && input >= 1)
                            {
                                Warior.Attack(enemy , Warior.getWeapons()[input-1]);
                                enemy->getEnemyController()->Attack(&Warior);
                                break;
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
                            printS("=========Choose Item=========  (0 = exit) ");
                            Warior.showCharacterUsableItems();
                            cin >> input;

                            if(input >= 1 && input <= Warior.getUseableItems().size())
                            {
                                Warior.useItem(input);
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

            if(Warior.getHP() < 0)
            {
                prints("=============================");
                cout << "         YOU ARE DEAD        " << endl;
                prints("=============================");
            }
            else if(enemy->getEnemyModel()->getHP() < 0)
            {
                prints("========================");
                cout << "       ENEMY IS DEAD     " << endl;
                prints("========================");
                Warior.setGold(Warior.getGold() + 50);
                Warior.setXP(Warior.getXP() + 100);
                delete enemy;
                Warior.CalculateLevel();
            }
        }
    }

    
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
