#include<string>
#include<windows.h>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Shop.h"
#include <vector>
#include <thread>

using namespace std;



    //Functions for printing
        void printS(string s)
        {
            for(int i = 0 ; i < s.size() ; i++)
            {
                cout << s[i];
                Sleep(0);
            }
            cout << endl << endl;
        }
        void prints(string s)
        {
            for(int i = 0 ; i < s.size() ; i++)
            {
                cout << s[i];
                Sleep(0);
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

    bool Shop::isFirst(string name , MainCharacter* player , int place)
    {
        if(place < player->getUseableItems().size())
        {
            for(int i = 0 ; i < place ; i++)
            {
                if(player->getUseableItems()[i]->getName() == name)
                {
                    return false;
                }
            }
        }

        if(place < player->getWeapons().size())
        {
            for(int i = 0 ; i < place ; i++)
            {
                if(player->getWeapons()[i]->getName() == name)
                {
                    return false;
                }
            }
        }

        return true;
    }
    
  
    int Shop::numberInInventory(string name , MainCharacter* player)
    {
        int counter = 0;
        for(int i = 0 ; i < player->getUseableItems().size() ; i++)
        {
            if(player->getUseableItems()[i]->getName() == name)
            {
                counter++;
            }
        }
        for(int i = 0 ; i < player->getWeapons().size() ; i++)
        {
            if(player->getWeapons()[i]->getName() == name)
            {
                counter++;
            }
        }
        
        return counter;
    }

    void Shop::showDetailOfInventory(MainCharacter* player)
    {
        cout << "====================UsableItems======================" << endl;
        for(int i = 0 ; i < player->getUseableItems().size() ; i++)
        {
            if(isFirst(player->getUseableItems()[i]->getName() , player , i))
            {
                int NUM = numberInInventory(player->getUseableItems()[i]->getName() , player);
                cout << player->getUseableItems()[i]->getName() << "  x" << NUM << endl;
            }
        }
        cout << "=====================================================" << endl;
        cout << "=======================Weapons=======================" << endl;
        for(int i = 0 ; i < player->getWeapons().size() ; i++)
        {
            if(isFirst(player->getWeapons()[i]->getName() , player , i))
            {
                int NUM = numberInInventory(player->getWeapons()[i]->getName() , player);
                cout << player->getWeapons()[i]->getName() << "  x" << NUM << endl;
            }
        }
        cout << "=====================================================" << endl << endl;
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

        prints("==========================================================");
        printS("===================== Weapons ====================");
		
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
        int rr = 1;
        while(true)
        {
        	if(rr==1){
        		prints("you have made it to an item shop on your way!");
            	
			}
			else{
				prints("How about another item?");
			}
        	prints("Here are the items you already have in your inventory: ");
            showDetailOfInventory(player);
            cout << "Your Wealth is: " << player->getGold() <<" G"<< endl;
            this_thread::sleep_for(chrono::seconds(3));
            prints("And here are available items in this shop: ");
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
                    
                    if(player->getGold() >= availableWeapons[ChosenNumber-1]->getPrice()){
                    	
                    	player->addWeapon(availableWeapons[ChosenNumber-1]);
                    	player->setGold(player->getGold() - availableWeapons[ChosenNumber-1]->getPrice());
                    	system("cls");
                    	
					}
					else{
						prints("Not enough gold to afford the item!");
						rr--;
						this_thread::sleep_for(chrono::seconds(2));
						system("cls");
						continue;
					}
                    
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
                	if(player->getGold() >= availableUseables[ChosenNumber-1-availableWeapons.size()]->getPrice()){
                		player->addUseableItems(availableUseables[ChosenNumber-1-availableWeapons.size()]);
                    	player->setGold(player->getGold() - availableUseables[ChosenNumber-1-availableWeapons.size()]->getPrice());
                    	system("cls");
					}
					else{
						prints("Not enough gold to afford the item!");
						rr--;
						this_thread::sleep_for(chrono::seconds(2));
						system("cls");
						continue;
					}
                    
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
