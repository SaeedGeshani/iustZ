#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
#include<cmath>

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






//    {
//        damagePerAttack = damageperattack;
//        neededStaminaPerAttack = neededstaminaperattack;
//        Level = level;
//        Type = type;
//        Name = name;
//    }
    //==============================================
    //Attack function===============================
//    virtual void Attack(MainCharacter* Player , Enemy* zombie) override
//    {
//        if(Player->getStamina() >= neededStaminaPerAttack)
//        {
//            zombie->setHP(zombie->getHP() - damagePerAttack);
//            Player->setStamina(Player->getStamina() - neededStaminaPerAttack);
//
//            for(int i = 0 ; i < Player->getWeapons().size() ; i++)
//            {
//                if(Player->getWeapons()[i] == this)
//                {
//                    Player->getWeapons().erase(Player->getWeapons().begin() + i);
//                    break;
//                }
//            }
//        }
//        else{
//
//            cout << "your stamina is less than gun's needed stamina and you will die soon :)";
//        }
//    }

int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);




void showItemsOfShop(Shop Market)
{
    cout << "Weapons: " << endl << "==================================" << endl;
    for(int i = 0 ; i < Market.getWeapon().size() ; i++)
    {
        cout << i+1 << "_ " << Market.getWeapon()[i]->getType() << endl;
    }
    cout << endl << "=================================";
    cout << "UseableItems: " << endl;
    for(int i = 0 ; i < Market.getUseableItem().size() ; i++)
    {
        cout << i + Market.getWeapon().size()+1 << "_ " << Market.getUseableItem()[i]->getType() << endl;
    }
    cout << "===================================" << endl;
}
void buyitemFromShop(Shop Market, MainCharacter* mychar)
{
	showItemsOfShop(Market);
	cout<<"Enter the number of the item you would like to purchase"<<endl;
	int firstInput;
	cin>>firstInput;
	if(firstInput<=Market.getWeapon().size() && firstInput > 0){
		if(mychar->getGold()>= Market.getWeapon()[firstInput-1]->getPrice()){
			mychar->addWeapon(Market.getWeapon()[firstInput-1]);
			mychar->setGold(mychar->getGold()- Market.getWeapon()[firstInput-1]->getPrice());	
		}
		else{
			cout<<"Not enough gold!"<<endl;
			buyitemFromShop(Market, mychar);
		}
			
	}
	else if(firstInput>Market.getWeapon().size() && firstInput<= (Market.getUseableItem().size() + Market.getWeapon().size())){
		if(mychar->getGold()>= Market.getWeapon()[firstInput-1-Market.getWeapon().size()]->getPrice()){
			mychar->addUseableItems(Market.getUseableItem()[firstInput-1-Market.getWeapon().size()]);
			mychar->setGold(mychar->getGold()-Market.getWeapon()[firstInput-1-Market.getWeapon().size()]->getPrice());
		}
		else{
			cout<<"Not enough gold!"<<endl;
			buyitemFromShop(Market, mychar);
		}
			
	} 
	else{
		cout<<"invalid input! Try again"<<endl;
		buyitemFromShop(Market, mychar);
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
	
	cout << "==Now you should pick up a powerful permenant weapon wich will be with you till the end of the war :==" << endl;
	cout << "plese pick up one weapon: " << endl;
	cout << "1.Katana" << endl << "2.Ak_47" << endl << "3.Knife" << endl;
	
	cout << "Katana(High needestamina and High damageAerAttack)" << endl;
	cout << "Ak_47(Low needed stamina and Low damagePerAttack)" << endl;
	cout << "Knife(Balanced)" << endl;
	string ChosenWeapon;
	cin >> ChosenWeapon;
	

}

int main()
{
	MainCharacter Batman("Batman", 100, 100, 100, "Male", 100);
	EnemyModel croc("Killer Croc", 100 , 200, 20 , 10);
    EnemyController crocController = EnemyController(&croc);
    EnemyView crocView = EnemyView(&croc);
    Enemy RealCroc = Enemy(&croc , &crocView , &crocController);
	ThrowableWeapon Batarang(5,5,1,"Batarang", 50 );
	Shop Market{"OK" , 10};
	Market.addWeapon(&Batarang);
	cout<<Market.getWeapon().size()<<endl;
	buyitemFromShop(Market, &Batman);
	cout<<RealCroc.getEnemyModel()->getHP()<<"  "<<Batman.getGold()<<endl<<"========="<<endl;
	Batman.Attack(&RealCroc , &Batarang);
	cout<<RealCroc.getEnemyModel()->getHP()<<"  "<<Batman.getGold()<<endl<<"========="<<endl;
	return 0;
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
