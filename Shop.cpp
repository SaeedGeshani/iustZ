#include<string>
#include<iostream>
#include<vector>
using namespace std;


class Items{
protected:
    int Price;
    string Name;

public:
    int getPrice()
    {
        return Price;
    }

    string getName()
    {
        return Name;
    }
};

class MainCharacter{
protected:
    int Gold;
    vector<Items*>Inventory;

public:
    int getGold()
    {
        return Gold;
    }

    void addInventory(Items* item)
    {
        Inventory.push_back(item);
    }
    
};

class constItem : public Items{};
class ThrowableItems : public Items{};
class UseableItems : public Items{};
class HotWeapon : public Items{};
class ColdWeapon : public Items{};
class Grenade : public ThrowableItems , public HotWeapon{};
class AK_47 : public HotWeapon , public constItem{};
class wheyProtein : public UseableItems{};
class Egg : public UseableItems{};
class Katana : public ColdWeapon , public constItem{};

class Shop{
private:
    string Name;
    int Level;
    vector<vector<Items*>> items;
    vector<ThrowableItems*> ptrThrowableItems;
    vector<UseableItems*> ptrUseableItems; 
    vector<HotWeapon*> ptrHotWeapon;
    vector<ColdWeapon*> ptrColdWeapon;
    vector<constItem*> ptrConstItem;
    MainCharacter consumer;
    

public:
    Shop(string name , int level)
    {
        Grenade grenade;
        AK_47 ak_47;
        wheyProtein wheyprotein;
        Egg egg;
        Katana katana;
        Name = name;
        Level = level;
        
        ptrThrowableItems.push_back(&grenade);
        ptrHotWeapon.push_back(&grenade);
        ptrHotWeapon.push_back(&ak_47);
        ptrConstItem.push_back(&ak_47);
        ptrUseableItems.push_back(&wheyprotein);
        ptrUseableItems.push_back(&egg);
        ptrColdWeapon.push_back(&katana);
        ptrConstItem.push_back(&katana);
        
    }

    void operator+=(ThrowableItems* ThroOBJ)
    {
        ptrThrowableItems.push_back(ThroOBJ);
    }
    void operator+=(UseableItems* UseOBJ)
    {
        ptrUseableItems.push_back(UseOBJ);
    }
    void operator+=(HotWeapon* HotOBJ)
    {
        ptrHotWeapon.push_back(HotOBJ);
    }
    void operator+=(ColdWeapon* ColdOBJ)
    {
        ptrColdWeapon.push_back(ColdOBJ);
    }

    vector<ThrowableItems*> getThrowableItems()
    {
        return ptrThrowableItems;
    }
    vector<UseableItems*> getUseableItems()
    {
        return ptrUseableItems;
    }
    vector<HotWeapon*> getHotItems()
    {
        return ptrHotWeapon;
    }
    vector<ColdWeapon*> getColdItems()
    {
        return ptrColdWeapon;
    }


    void buyItem(string NameOfItem)
    {
        for(int i = 0 ; i < items.size() ; i++)
        {
            for(int j = 0 ; j < items[i].size() ; j++)
            {
                if(items[i][j]->getName() == NameOfItem)
                {
                    if(consumer.getGold() >= items[i][j]->getPrice())
                    {
                        consumer.addInventory(items[i][j]);
                        break;
                    }
                }
            }
        }

        cout << "These is more than your currency" << endl;
    }
    
};



