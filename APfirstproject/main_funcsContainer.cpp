#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<ctime>
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
    EnemyFactory Enemyhouse;
//==========================================================


int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);

Shop* randomShopGenerator(){
	Shop* randomStore = new Shop;
	Batarang* a = new Batarang(40 , 10 , "Batrang" , 50);
	Blaster* b = new Blaster(50 , 10 , "Blaster" , 100);
	Katana* c = new Katana(80 , 5 , "Katana" , 75);
	grenade* d = new grenade(200 , 50 , "Grenade" , 50);
	Egg* e = new Egg(20 , 50 , "Egg" , 10 , 5);
	WheyProtein* f = new WheyProtein(40 , 100 , "Whey Protein" , 50 , 10);
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

// void showItemsOfShop(Shop Market)
// {
//     cout << "Weapons: " << endl << "==================================" << endl;
//     for(int i = 0 ; i < Market.getWeapon().size() ; i++)
//     {
//         cout << i+1 << "_ " << Market.getWeapon()[i]->getName() << endl;
//     }
//     cout << endl << "=================================";
//     cout << "UseableItems: " << endl;
//     for(int i = 0 ; i < Market.getUseableItem().size() ; i++)
//     {
//         cout << i + Market.getWeapon().size()+1 << "_ " << Market.getUseableItem()[i]->getType() << endl;
//     }
//     cout << "===================================" << endl;
// }
// void buyitemFromShop(Shop Market , int numberOfProduct , string classNameOfProduct , MainCharacter Player)
// {
// 	showItemsOfShop(Market);
//     if(numberOfProduct > Market.getUseableItem().size() || numberOfProduct <= 0)
//     {
//         cout << "Invalid input" << endl;
//     }
//     else{

//         if(numberOfProduct <= Market.getWeapon().size())
//         {
//             if(Player.getGold() >= Market.getWeapon()[numberOfProduct - 1]->getPrice())
//             {
//                 Player.addWeapon(Market.getWeapon()[numberOfProduct-1]);
//             }
//             else{

//                 cout << "your currency is not enough" << endl;
//             }
//         }
//         else{

//             if(Player.getGold() >= Market.getUseableItem()[numberOfProduct - 1 - Market.getWeapon().size()]->getPrice())
//             {
//                 Player.addUseableItems(Market.getUseableItem()[numberOfProduct -1 - Market.getWeapon().size()]);
//             }
//             else{

//                 cout <<"your currency is not enough" << endl;
//             }
//         }
//     }
// }


void makingNewcharacter()
{
	string name;
	int age;
	string gender;

	cout << "===============Section of making your dreamy wariror===============" << endl;
	cout << "Enter name of the Warior :" << endl;
	getline(cin , name);

	
	cout << "Enter gender of the Warior:(male - female) "  << endl;
	getline(cin , gender);
	while(gender != "male" && gender != "female")
	{
		cout << "Invalid Input try again: " << endl;
		getline(cin , gender);
	}

	Warior.setName(name);	
	Warior.setGender(gender);

    cout << endl << "===This gift is given from the King to you to buy your Weapons to continue:===" << endl << endl;
    cout << endl << "===== Here you are:" << endl << endl <<"Now you have 1000 G" << endl << endl;
    Warior.setGold(1000);
    
    int ChosenWeapon;
    do{
        cout << endl <<"==Now you should pick up a powerful permenant weapon which will be with you till the end of the war :==" << endl;
	    cout << endl <<"plese pick up one weapon: " << endl;
	    cout << "1.Katana" << endl << "2.Blaster" << endl;
	
	    cout << endl <<"Katana(100 G)(Damage : 20) (NeededStamina : 15)" << endl;
	    cout << endl <<"Blaster(75 G) (Damage : 15) (Needed Stamina : 10)" << endl;

	    
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

    cout << endl << "===== Now we will give you somthing that you can heal yourself and give your muscular body a litle bit Energy so take them and put in your Inventory" << endl;
    cout << endl << "The first one is WheyPowder it helps you to get Stamina(20) and heal your body(10) you will have two:" << endl;
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
void makeGameplayReady()
{
//    Store.setLevel(1);
//    Store.setName("BlackMarket");
    Enemyhouse.setEnemyLevel(1);

}

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
    return -1;
}



int main()
{
    makingNewcharacter();
    makeGameplayReady();


    bool checkStatus;
    
    while(Warior.getHP() > 0)
    {
        checkStatus = randomShuffle(1 , 1);

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
                    cout << "enemy is against you what you want to do?" << endl;
                    cout << "1.Fight" << endl << "2.use Inventory" << endl;
                    int input;
                    cin >> input;
                

                    if(input == 1)
                    {
                        
                        
                        while(true)
                        {
                            cout << "Which Weapon you wanna use?" << endl;
                            Warior.showCharacterWeapons();
                            cin >> input;
                            if(input <= Warior.getWeapons().size() && input >= 1)
                            {
                                Warior.Attack(enemy , Warior.getWeapons()[input-1]);
                                enemy->getEnemyController()->Attack(&Warior);
                                break;
                            }
                        }
                        
                        break;
                    } 

                    else if(input == 2)
                    {
                        while(true)
                        {
                            cout << "which item you wanna choose? " << endl;
                            Warior.showCharacterUsableItems();
                            cin >> input;

                            if(input >= 1 && input <= Warior.getUseableItems().size())
                            {
                                Warior.useItem(input);
                                break;
                            }
                        }
                        break;
                    }
                }
                
                
            }

            if(Warior.getHP() < 0)
            {
                cout << " YOU ARE DEAD" << endl;
            }
            else if(enemy->getEnemyModel()->getHP() < 0)
            {
                cout << endl << "ENEMY IS DEAD" << endl;
                Warior.setGold(Warior.getGold() + 100);
                delete enemy;
            }
        }
    }

    
}

int CalculateDMPAforZombie(int level)
{
    int DMPA;
    DMPA = pow(level , 8/7) + 10;
    return DMPA;
}
int CalculateSTforZombie(int level)
{
    int ST;
    ST = pow(level , 7/5) + 50;
    return ST;
}
int CalculateHPForZombie(int level)
{
    int HP;
    HP = pow(level , 4/3) * 50 + 50;
    return HP;
}