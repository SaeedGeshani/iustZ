#include<string>
#include "MainCharacter.h"
#include "Weapon.h"
#include "Shop.h"
#include <vector>
#include <thread>

using namespace std;


const int SHOP_UI_WIDTH = 92;

string shopCenteredText(const string& text, int width = SHOP_UI_WIDTH)
{
    if(static_cast<int>(text.size()) >= width)
    {
        return text;
    }
    int padding = (width - static_cast<int>(text.size())) / 2;
    return string(padding, ' ') + text;
}

void shopCenteredLine(const string& text = "")
{
    cout << shopCenteredText(text) << endl;
}

void shopDivider(char fill = '=', int width = 58)
{
    shopCenteredLine(string(width, fill));
}

void shopHeader(const string& title)
{
    shopDivider();
    shopCenteredLine(" " + title);
    shopDivider();
}

    //Functions for printing
        void printS(const string& s)
        {
            shopCenteredLine(s);
        }
        void prints(const string& s)
        {
            shopCenteredLine(s);
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
        shopHeader("Inventory: Usable Items");
        for(int i = 0 ; i < player->getUseableItems().size() ; i++)
        {
            if(isFirst(player->getUseableItems()[i]->getName() , player , i))
            {
                int NUM = numberInInventory(player->getUseableItems()[i]->getName() , player);
                shopCenteredLine(player->getUseableItems()[i]->getName() + "  x" + to_string(NUM));
            }
        }
        shopDivider();
        shopHeader("Inventory: Weapons");
        for(int i = 0 ; i < player->getWeapons().size() ; i++)
        {
            if(isFirst(player->getWeapons()[i]->getName() , player , i))
            {
                int NUM = numberInInventory(player->getWeapons()[i]->getName() , player);
                shopCenteredLine(player->getWeapons()[i]->getName() + "  x" + to_string(NUM));
            }
        }
        shopDivider();
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

        shopHeader("Shop Weapons");
		
		for(int i = 0 ; i < availableWeapons.size() ; i++)
        {
            shopCenteredLine(to_string(i + 1) + ". " + availableWeapons[i]->getName() + " | Price: " + to_string(availableWeapons[i]->getPrice()) + " | Damage: " + to_string(availableWeapons[i]->getDamagePerAttack()) + " | Needed STPA: " + to_string(availableWeapons[i]->getNeededStaminaPerAttack()));
		}
        shopHeader("Shop Usable Items");
		
		for(int i = 0 ; i < availableUseables.size() ; i++)
        {
            shopCenteredLine(to_string(i + 1 + static_cast<int>(availableWeapons.size())) + ". " + availableUseables[i]->getName() + " | Price: " + to_string(availableUseables[i]->getPrice()) + " | Heal: " + to_string(availableUseables[i]->getHealingPower()) + " | Energy: " + to_string(availableUseables[i]->getEnergy()));
		}
         shopDivider();
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
            shopCenteredLine("Gold: " + to_string(player->getGold()) + " G");
            this_thread::sleep_for(chrono::milliseconds(1200));
            printS("Available items in this shop:");
            ShowItems();
            

            shopDivider('-');
            cout << shopCenteredText("Select item number (0 to exit): ");
            cin >> ChosenNumber;
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
                    	system("cls");
                    	
					}
					else{
						prints("Not enough gold to afford the item!");
						rr--;
						this_thread::sleep_for(chrono::milliseconds(900));
						system("cls");
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
                    	system("cls");
					}
					else{
						prints("Not enough gold to afford the item!");
						rr--;
						this_thread::sleep_for(chrono::milliseconds(900));
						system("cls");
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
				system("cls");
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
