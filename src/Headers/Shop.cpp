#include<string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Shop.h"
#include <vector>
#include <thread>
#include "ConsoleUI.h"

using namespace std;


namespace {
//Functions for printing
        void printS(const string& s)
        {
            ui::centeredLine(s);
        }
        void prints(const string& s)
        {
            ui::centeredLine(s);
        }
    //=======================
}

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

    bool Shop::isFirst(const string& name , MainCharacter* player , int place)
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
    
  
    int Shop::numberInInventory(const string& name , MainCharacter* player)
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
        ui::drawHeader("Inventory: Usable Items");
        for(int i = 0 ; i < player->getUseableItems().size() ; i++)
        {
            if(isFirst(player->getUseableItems()[i]->getName() , player , i))
            {
                int NUM = numberInInventory(player->getUseableItems()[i]->getName() , player);
                ui::centeredLine(player->getUseableItems()[i]->getName() + "  x" + to_string(NUM));
            }
        }
        ui::drawDivider();
        ui::drawHeader("Inventory: Weapons");
        for(int i = 0 ; i < player->getWeapons().size() ; i++)
        {
            if(isFirst(player->getWeapons()[i]->getName() , player , i))
            {
                int NUM = numberInInventory(player->getWeapons()[i]->getName() , player);
                ui::centeredLine(player->getWeapons()[i]->getName() + "  x" + to_string(NUM));
            }
        }
        ui::drawDivider();
        cout << endl;
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

        ui::drawHeader("Shop Weapons");
		
		for(int i = 0 ; i < availableWeapons.size() ; i++)
        {
            ui::centeredLine(to_string(i + 1) + ". " + availableWeapons[i]->getName() + " | Price: " + to_string(availableWeapons[i]->getPrice()) + " | Damage: " + to_string(availableWeapons[i]->getDamagePerAttack()) + " | Needed STPA: " + to_string(availableWeapons[i]->getNeededStaminaPerAttack()));
		}
        ui::drawHeader("Shop Usable Items");
		
		for(int i = 0 ; i < availableUseables.size() ; i++)
        {
            ui::centeredLine(to_string(i + 1 + static_cast<int>(availableWeapons.size())) + ". " + availableUseables[i]->getName() + " | Price: " + to_string(availableUseables[i]->getPrice()) + " | Heal: " + to_string(availableUseables[i]->getHealingPower()) + " | Energy: " + to_string(availableUseables[i]->getEnergy()));
		}
         ui::drawDivider();
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
        	// prints("Here are the items you already have in your inventory: ");
            showDetailOfInventory(player);
            ui::centeredLine("Gold: " + to_string(player->getGold()) + " G");
            this_thread::sleep_for(chrono::milliseconds(1200));
            printS("Available items in this shop:");
            ShowItems();
            

            ui::drawFooter("Select an item number (0 to exit)");
            ChosenNumber = ui::readIntInRange(ui::centeredText("> "), 0, static_cast<int>(availableWeapons.size() + availableUseables.size()));
            if(ChosenNumber <= availableWeapons.size() && ChosenNumber > 0)
            {
                if(availableWeapons[ChosenNumber-1] != nullptr)
                {
                    
                    
                    if(player->getGold() >= availableWeapons[ChosenNumber-1]->getPrice()){
                    	
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
                    	ui::clearScreen();
                    	
					}
					else{
						prints("Not enough gold to afford the item!");
						rr--;
						this_thread::sleep_for(chrono::milliseconds(900));
						ui::clearScreen();
						continue;
					}
                    
                }
                else{

                    cout << "Passing null ptr so" << endl;
                    delete availableWeapons[ChosenNumber-1];
                    availableWeapons.erase(availableWeapons.begin() + ChosenNumber-1);
                }

                // for(int i = ChosenNumber ; i < availableWeapons.size() ; )
                // {
                //     delete availableWeapons[i];
                //     availableWeapons.erase(availableWeapons.begin() + ChosenNumber);
                // }
                // for(int i = 0 , k = 0  ; i < ChosenNumber-1-k ;k++ )
                // {
                //     delete availableWeapons[i];  
                //     availableWeapons.erase(availableWeapons.begin() + 0);
                // }
                // for(int i = 0 ; i < availableUseables.size() ; )
                // {
                //     delete availableUseables[i];
                //     availableUseables.erase(availableUseables.begin() + 0);
                    
                // }
                return;
			}
			else if(ChosenNumber > availableWeapons.size() && ChosenNumber <= availableWeapons.size() + availableUseables.size()){
				if(availableUseables[ChosenNumber-1-availableWeapons.size()] != nullptr)
                {
                	if(player->getGold() >= availableUseables[ChosenNumber-1-availableWeapons.size()]->getPrice()){
                		player->addUseableItems(availableUseables[ChosenNumber-1-availableWeapons.size()]);
                    	player->setGold(player->getGold() - availableUseables[ChosenNumber-1-availableWeapons.size()]->getPrice());
                    	ui::clearScreen();
					}
					else{
						prints("Not enough gold to afford the item!");
						rr--;
						this_thread::sleep_for(chrono::milliseconds(900));
						ui::clearScreen();
						continue;
					}
                    
                }
                else
                {
                    cout << "Passing was failed so" << endl; 
                }
                // for(int i = ChosenNumber-availableWeapons.size() ; i < availableUseables.size() ; )
                // {
                //     delete availableUseables[i];
                //     availableUseables.erase(availableUseables.begin() + ChosenNumber-availableWeapons.size());
                // }
                
                // for(int i = 0 , j = 0  ; i < ChosenNumber - 1 - availableWeapons.size() - j ; j++)
                // {
                //     delete availableUseables[i];
                //     availableUseables.erase(availableUseables.begin() + 0);
                // }
                // for(int i = 0 ; i < availableWeapons.size() ; )
                // {
                //     delete availableWeapons[i];
                //     availableWeapons.erase(availableWeapons.begin() + 0 );
                // }
                return;
			}
			else if(ChosenNumber==0){
				ui::clearScreen();
                return;
                
			}
        }
            

    }

    void Shop::setWeapon(const vector<Weapon*>& wep)
    {
        availableWeapons = wep;
    }

    void Shop::setUsableItems(const vector<UseableItems*>& usa)
    {
       availableUseables = usa; 
    }
