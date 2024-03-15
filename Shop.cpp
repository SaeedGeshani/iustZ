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

using namespace std;

//Global Objects And Variables==============================
    static MainCharacter Warior;
    Shop Store;
    EnemyFactory Enemyhouse;
//==========================================================


int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);



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

	cout << "===============Section of making your dream wariror===============" << endl;
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
        cout << endl <<"==Now you should pick up a powerful permenant weeapon which will be with you till the end of the war :==" << endl;
	    cout << endl <<"plese pick up one weapon: " << endl;
	    cout << "1.Katana" << endl << "2.Ak_47" << endl << "3.Knife" << endl;
	
	    cout << endl <<"Katana(100 G)(Damage : 20) (NeededStamina : 15)" << endl;
	    cout << endl <<"Ak_47(75 G) (Damage : 15) (Needed Stamina : 10)" << endl;
	    cout << endl <<"Knife(50 G) (Damage : 10) (NeededStamina : 5)" << endl;

	    
	    cin >> ChosenWeapon;

        if(ChosenWeapon == 1)
        {
            Warior.setGold(900);
            PermenantWeapon* Katana = new PermenantWeapon(20 , 15 , 1 , "Katana" , 100);
            Warior.addWeapon(Katana);
        }
        else if(ChosenWeapon == 2)
        {
            Warior.setGold(925);
            PermenantWeapon* Ak_47 = new PermenantWeapon(15 , 10 , 1 , "Ak_47" , 75);
            Warior.addWeapon(Ak_47);
        }
        else if(ChosenWeapon == 3)
        {
            Warior.setGold(950);
            PermenantWeapon* Knife = new PermenantWeapon(10 , 5 , 1 , "Knife" , 50);
            Warior.addWeapon(Knife);
        }
        else{

            cout << "You entered invalid number so enter true one" << endl;
        }
	
    }while(ChosenWeapon != 1 && ChosenWeapon != 2 && ChosenWeapon != 3);

    cout << endl << "===== Now we will give you somthing that you can heal yourself and give your muscular body a litle bit Energy so give them and put in your Inventory" << endl;
    cout << endl << "The first one is WheyPowder it helps you to get Stamina(20) and heal your body(10) you will have two:" << endl;
    UseableItems* ptr1WheyPowder = new UseableItems(20 , 20 , 1 , "Healing" , "WheyPowder" , 30);
    UseableItems* ptr2WheyPowder = new UseableItems(20 , 20 , 1 , "Healing" , "WheyPowder" , 30);
    Warior.addUseableItems(ptr1WheyPowder);
    Warior.addUseableItems(ptr2WheyPowder);

    Warior.setLevel(1);
    Warior.setHP(100);
    Warior.setStamina(100);
    Warior.setXP(0);
    
}

//Making Game ready to Starting the story
void makeGameplayReady()
{
    Store.setLevel(1);
    Store.setName("BlackMarket");
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
            Store.BuyItem(&Warior);
        }
        else{

            Zombie* enemy = Enemyhouse.makeZombie();
            while(Warior.getHP() > 0 && enemy->getEnemyModel()->getHP() > 0)
            {
                cout << "enemy is against you what you want to do?" << endl;
                cout << "1.Fight" << endl << "2.use Inventory" << endl;
                int input;
                cin >> input;

                if(input == 1)
                {
                    cout << "Which Weapon you wanna use?" << endl;
                    Warior.showCharacterWeapons();
                    cin >> input;
                        Warior.Attack(enemy , Warior.getWeapons()[input-1]);
                        enemy->getEnemyController()->Attack(&Warior);
                } 
                else if(input == 2)
                {
                    Warior.showCharacterUsableItems();
                    cin >> input;

                    Warior.useItem(input);
                }
            }
            if(Warior.getHP() < 0)
            {
                cout << " YOU ARE DEAD" << endl;
                Warior.setGold(Warior.getGold() + 100);
            }
            else if(enemy->getEnemyModel()->getHP() < 0)
            {
                cout << endl << "ENEMY IS DEAD" << endl;
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
    ST = pow(level , 7/5) + 80;
    return ST;
}
int CalculateHPForZombie(int level)
{
    int HP;
    HP = pow(level , 4/3) * 50 + 100;
    return HP;
}
