#include<string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Shop.h"
#include <vector>

using namespace std;


    Shop::Shop() = default;
    //Setter & Getters=================
    vector<UseableItems*> & Shop::getUseableItem()
    {
        return availableUseables;
    }
    vector<Weapon*> & Shop::getWeapon()
    {
        return availableWeapons;
    }
  

    void Shop::ShowItems()
    {
//        cout << "Here are the ThrowableWeapons: ========"<< endl;
//        cout << "1.Batrang" << endl;
//        cout << "2.Grenade" << endl;
//        cout << "3.TNT" << endl;
//        cout << "And these are UsableItems and Healers: ========" << endl;
//        cout << "4.WheyProtein" << endl;
//        cout << "5.Egg" << endl;
//        cout << "6.Peace Herbal Tea" << endl;
		cout<<"Here are available weapons on this market: "<<endl;
		for(int i=0;i<availableWeapons.size();i++){
			cout<<i+1<<". "<<availableWeapons[i]->getName()<<endl;
		}
		cout<<"Here are available usable items on this market: "<<endl;
		for(int i=0;i<availableUseables.size();i++){
			cout<<i+1+availableWeapons.size()<<". "<<availableUseables[i]->getName()<<endl;
		}
    }

    void Shop::BuyItem(MainCharacter* player)
    {
        this->ShowItems();

        int ChosenNumber;
        
        do{
            cout << "Please enter the number of the Item you wanna buy(Enter zero if you'd like to exit this shop)" << endl;
            cin >> ChosenNumber;
            if(ChosenNumber<= availableWeapons.size()){
            	player->addWeapon(availableWeapons[ChosenNumber-1]);
			}
			else if(ChosenNumber>availableWeapons.size() && ChosenNumber<= availableWeapons.size()+availableUseables.size()){
				player->addUseableItems(availableUseables[ChosenNumber-1-availableWeapons.size()]);
			}
			else if(ChosenNumber==0){
                return;
			}
            
        }while(ChosenNumber < 0 || ChosenNumber > availableWeapons.size()+availableUseables.size() );
    }


