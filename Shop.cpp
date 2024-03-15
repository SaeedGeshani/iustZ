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



int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);



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
