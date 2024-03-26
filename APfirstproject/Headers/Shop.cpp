#include<string>
#include<windows.h>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Shop.h"
#include <vector>

using namespace std;



    //Functions for printing
        void printS(string s)
        {
            for(int i = 0 ; i < s.size() ; i++)
            {
                cout << s[i];
                Sleep(1);
            }
            cout << endl << endl;
        }
        void prints(string s)
        {
            for(int i = 0 ; i < s.size() ; i++)
            {
                cout << s[i];
                Sleep(1);
            }
            cout << endl << endl;
        }
    //=======================

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
        prints("======================== Weapons =========================");
		
		for(int i = 0 ; i < availableWeapons.size() ; i++)
        {
			cout<< i+1 << ". " << availableWeapons[i]->getName() << "   Price: " << availableWeapons[i]->getPrice()  << "   Damage: " << availableWeapons[i]->getDamagePerAttack() << "    NeededSTPA: " << availableWeapons[i]->getNeededStaminaPerAttack() << endl;
            Sleep(10);
		}
        prints("==========================================================");
        printS("===================== Useable Items ====================");
		
		for(int i = 0 ; i < availableUseables.size() ; i++)
        {
			cout << i+1 + availableWeapons.size() << ". " << availableUseables[i]->getName() << "    Price: " << availableUseables[i]->getPrice() << "     HealinPower: " << availableUseables[i]->getHealingPower() << "    Energy:" << availableUseables[i]->getEnergy() << endl;
            Sleep(10);
		}
         prints("=========================================================");
    }

   

    void Shop::BuyItem(MainCharacter* player)
    {

        int ChosenNumber;
        
        while(true)
        {
            cout << "Your Wealth is: " << player->getGold() << endl;
            ShowItems();
            prints("===Please enter the number of the Item you wanna buy(Enter zero if you'd like to exit this shop)===");

            cin >> ChosenNumber;
            if(ChosenNumber <= availableWeapons.size() && ChosenNumber > 0)
            {
                if(availableWeapons[ChosenNumber-1] != nullptr)
                {
                    if(dynamic_cast<PermenantWeapon*>(availableWeapons[ChosenNumber-1]) != NULL)
                    {
                        for(int i = 0 ; i < player->getWeapons().size() ; i++)
                        {
                            if(dynamic_cast<PermenantWeapon*>(player->getWeapons()[i]) != NULL)
                            {
                                delete player->getWeapons()[i];
                                player->getWeapons().erase(player->getWeapons().begin() + i);
                                break;
                            }
                        }
                    }
                    player->addWeapon(availableWeapons[ChosenNumber-1]);
                    player->setGold(player->getGold() - availableWeapons[ChosenNumber-1]->getPrice());
                }
                else{

                    cout << "Passing null ptr so" << endl;
                    delete availableWeapons[ChosenNumber-1];
                    availableWeapons.erase(availableWeapons.begin() + ChosenNumber-1);
                }

                for(int i = ChosenNumber ; i < availableWeapons.size() ; )
                {
                    delete availableWeapons[i];
                    availableWeapons.erase(availableWeapons.begin() + ChosenNumber);
                }
                for(int i = 0 , k = 0  ; i < ChosenNumber-1-k ;k++ )
                {
                    delete availableWeapons[i];  
                    availableWeapons.erase(availableWeapons.begin() + 0);
                }
                for(int i = 0 ; i < availableUseables.size() ; )
                {
                    delete availableUseables[i];
                    availableUseables.erase(availableUseables.begin() + 0);
                    
                }
                return;
			}
			else if(ChosenNumber > availableWeapons.size() && ChosenNumber <= availableWeapons.size() + availableUseables.size()){
				if(availableUseables[ChosenNumber-1-availableWeapons.size()] != nullptr)
                {
                    player->addUseableItems(availableUseables[ChosenNumber-1-availableWeapons.size()]);
                    player->setGold(player->getGold() - availableUseables[ChosenNumber-1-availableWeapons.size()]->getPrice());
                }
                else
                {
                    cout << "Passing was failed so" << endl; 
                }
                for(int i = ChosenNumber-availableWeapons.size() ; i < availableUseables.size() ; )
                {
                    delete availableUseables[i];
                    availableUseables.erase(availableUseables.begin() + ChosenNumber-availableWeapons.size());
                }
                
                for(int i = 0 , j = 0  ; i < ChosenNumber - 1 - availableWeapons.size() - j ; j++)
                {
                    delete availableUseables[i];
                    availableUseables.erase(availableUseables.begin() + 0);
                }
                for(int i = 0 ; i < availableWeapons.size() ; )
                {
                    delete availableWeapons[i];
                    availableWeapons.erase(availableWeapons.begin() + 0 );
                }
                return;
			}
			else if(ChosenNumber==0){
                return;
                
			}
        }
            

    }

    void Shop::setWeapon(vector<Weapon*> wep)
    {
        availableWeapons = wep;
    }

    void Shop::setUsableItems(vector<UseableItems*> usa)
    {
       availableUseables = usa; 
    }
