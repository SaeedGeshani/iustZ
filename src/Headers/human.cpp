#include<string>
#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<ctime>
#include "human.h"
#include "ThrowableWeapon.h"
#include "ConsoleUI.h"
#include <thread>
#include <chrono>
#include<cstdlib>
using namespace std;

int CalculateHPForHuman(int);
int CalculateSTForHuman(int);


//Enemy/////////////////////////////////////////////////////////////////////////////
    //Getter and Setter=====================
    void HumanEnemy::setHumanEnemyModel(EnemyModel* humanenemymodel)
    {
        Enemymodel = humanenemymodel;
    }
    EnemyModel* HumanEnemy::getHumanEnemyModel()
    {
        return Enemymodel;
    }
    void HumanEnemy::setHumanEnemyView(EnemyView* humanenemyview)
    {
        Enemyview = humanenemyview;
    }
    EnemyView* HumanEnemy::getHumanEnemyView()
    {
        return Enemyview;
    }
    void HumanEnemy::setHumanEnemyController(EnemyController* humanenemycontroller)
    {
        Enemycontroller = humanenemycontroller;
    }
    EnemyController* HumanEnemy::getHumanEnemyController()
    {
        return Enemycontroller;
    }
    //Constructor==============================
    HumanEnemy::HumanEnemy() = default;
    HumanEnemy::HumanEnemy(EnemyModel* humanenemymodel , EnemyView* humanenemyview , EnemyController* humanenemycontroller)
    {
        Enemymodel = humanenemymodel;
        Enemyview = humanenemyview;
        Enemycontroller = humanenemycontroller;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyModel//////////////////////////////////////////////////////////////////////////////////////////////////

    //Setter & Getters ==========================
    // void EnemyModel::setEnemyWeapons(vector<Weapon*> enemyweapon)
    // {
    //     EnemyWeapons = enemyweapon;
    // }

    // vector<Weapon*> EnemyModel::getEnemyWeapons()
    // {
    //     return EnemyWeapons;
    // }

    // void EnemyModel::setEnemyUseableItems(vector<UseableItems*> enemyuseableitem)
    // {
    //     EnemyUseableItems = enemyuseableitem;
    // }

    // vector<UseableItems*> EnemyModel:: getEnemyUseableItems()
    // {
    //     return EnemyUseableItems;
    // }

    void HumanEnemyModel::setNeededStaminaPerAttack(int neededstperattack)
    {
        if(neededstperattack < 0)
        {
            cout << "The enemy can't attack the player." << endl;
        }
        else{
            neededStaminaPerAttack = neededstperattack;
        }
    }
    int HumanEnemyModel::getNeededStaminaPerAttack()
    {
        return neededStaminaPerAttack;
    }
    void HumanEnemyModel::setLevel(int level)
    {
        Level = level;
    }
    int HumanEnemyModel::getLevel()
    {
        return Level;
    }
    void HumanEnemyModel::setName(std::string name)
    {
        Name = name;
    }
    std::string HumanEnemyModel::getName()
    {
        return Name;
    }
    void HumanEnemyModel::setHP(int hp)
    {
        HP = hp;
    }
    int HumanEnemyModel::getHP()
    {
        return HP;
    }
    void HumanEnemyModel::setDamagePerAttack(int damageperattack)
    {
        DamagePerAttack = damageperattack;
    }
    int HumanEnemyModel::getDamagePerAttack()
    {
        return DamagePerAttack;
    }
    void HumanEnemyModel::setStamina(int stamina)
    {
        Stamina = stamina;
    }
    int HumanEnemyModel::getStamina()
    {
        return Stamina;
    }
    //=========================================
    //Constructor==============================
    HumanEnemyModel::HumanEnemyModel() = default;
    HumanEnemyModel::HumanEnemyModel(string name , int hp , int stamina , int damageperattack , int level , int zarib)
    {
        Name = name;
        HP = hp;
        Stamina = stamina;
        DamagePerAttack = damageperattack;
        Level = level;
        Zarib = zarib;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyView/////////////////////////////////////////////////////////////////////////////////////////
 
    //Setter and Getters=========================
    void HumanEnemyView::setHumanEnemyModel(EnemyModel* humanenemymodel)
    {
        Enemymodel = humanenemymodel;
    }
    EnemyModel* HumanEnemyView::getHumanEnemyModel()
    {
        return Enemymodel;
    }
    //Constructors===============================
    HumanEnemyView::HumanEnemyView() = default;
    HumanEnemyView::HumanEnemyView(EnemyModel* humanenemymodel)
    {
       Enemymodel = humanenemymodel;
    }

    //Functions==================================
    void HumanEnemyView::ShowHumanEnemyInfo()
    {
        cout << "Here is status of enemy : " << endl;
        cout << "Enemy's Name: " << Enemymodel->getName() << endl;
        cout << "Enemy's HP : " << Enemymodel->getHP() << endl;
        cout << "Enemy's Stamina: " << Enemymodel->getStamina() << endl;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyController/////////////////////////////////////////////////////////////////////////////////////////



    //Constructor======================
    HumanEnemyController::HumanEnemyController() = default;
    HumanEnemyController::HumanEnemyController(EnemyModel* humanenemymodel)
    {
        Enemymodel = humanenemymodel;
    }
    //Setter and Getters===============
    void HumanEnemyController::setHumanEnemyModel(EnemyModel* humanenemymodel)
    {
        Enemymodel = humanenemymodel;
    }
    EnemyModel* HumanEnemyController::getHumanEnemyModel()
    {
        return Enemymodel;
    }
    //Functions=========================
    void HumanEnemyController::WeaponAttack(MainCharacter*player , int number)
    {
        const int hpBefore = player->getHP();
        const int baseDamage = (Enemymodel->getEnemyWeapons()[number]->getDamagePerAttack() + player->getLevel()*4) * Enemymodel->getZarib()/2;
        const int defenseValue = 0;
        const int finalDamage = baseDamage;

        player->setHP(player->getHP() - finalDamage);
        Enemymodel->setStamina(Enemymodel->getStamina() - Enemymodel->getEnemyWeapons()[number]->getNeededStaminaPerAttack());

        ui::LogAttack(
            Enemymodel->getName(),
            player->getName(),
            Enemymodel->getEnemyWeapons()[number]->getName(),
            baseDamage,
            defenseValue,
            finalDamage,
            hpBefore,
            player->getHP());

        if(dynamic_cast<ThrowableWeapon*>(Enemymodel->getEnemyWeapons()[number]) != NULL)
        {
            delete Enemymodel->EnemyWeapons[number];
            Enemymodel->EnemyWeapons.erase(Enemymodel->EnemyWeapons.begin() + number);
        }
    }

    void HumanEnemyController::useItems(int number)
    {
        cout << "===========================================" << endl;
        cout << "          Enemy is using: " << Enemymodel->getEnemyUseableItems()[number]->getName() <<endl;
        cout << "===========================================" << endl;
        cout << "Added ST: " << Enemymodel->getEnemyUseableItems()[number]->getEnergy() << endl;
        cout << "Added HP: " << Enemymodel->getEnemyUseableItems()[number]->getHealingPower() <<endl;
        Enemymodel->setStamina(Enemymodel->getStamina() + Enemymodel->getEnemyUseableItems()[number]->getEnergy());
        Enemymodel->setHP(Enemymodel->getHP() + Enemymodel->getEnemyUseableItems()[number]->getHealingPower());
        delete Enemymodel->EnemyUseableItems[number];
        Enemymodel->EnemyUseableItems.erase(Enemymodel->EnemyUseableItems.begin() + number);
        bool checkToDelete = false;
        this_thread::sleep_for(chrono::seconds(5));
        system("cls");
    }

    void HumanEnemyController::Attack(MainCharacter* player)
    {
        int MaxHP = CalculateHPForHuman(player->getLevel());
        int MaxST = CalculateSTForHuman(player->getLevel());
        bool checkGone = false;
        switch (CheckHealth(MaxHP))
        {
        case Low:
            switch (CheckStamina(MaxST))
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                ///////
                if(Enemymodel->getHP() <= 0)
                {
                    break;
                }
                while(Enemymodel->getHP() < (0.7)*(MaxHP) || Enemymodel->getStamina() < (0.7)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
                        cout << "==========Low  low ===Using item===" <<endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                checkGone = false;
                srand(time(0));
                int random1;
               if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random1 = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random1 ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random1 ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "========================================" << endl;
                    cout << " Enemy Couldn't use Weapon cause Stamina" << endl;
                    cout << "========================================" << endl;
                }
                break;
                }
                break;
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////
                if(Enemymodel->getHP() <= 0)
                {
                    break;
                }
                while(Enemymodel->getHP() < (0.5)*(MaxHP) || Enemymodel->getStamina() < (0.5)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
                        cout << "=====Low average=====Using Item======" << endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                checkGone = false;
                srand(time(0));
                if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random1 = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random1; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random1 ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "========================================" << endl;
                    cout << " Enemy Couldn't use Weapon cause Stamina" << endl;
                    cout << "========================================" << endl;
                }
                break;
                }

                break;
            default:
            //FIRST CODE
                if(Enemymodel->getHP() <= 0)
                    {
                        break;
                    }
             while(Enemymodel->getHP() < (0.7)*(MaxHP) || Enemymodel->getStamina() < (0.7)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
                        cout << "=====Low high=====Using Item====" << endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }

            //SECOND PART
            checkGone = false;
                srand(time(0));
                int random;
                if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "=================================" << endl;
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                    cout << "=================================" << endl;
                }
                break;
                }
                break;
            }
            break;
        case Average:
            switch (CheckStamina(MaxST))
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                /////// 
                if(Enemymodel->getHP() <= 0)
                {
                    break;
                }
                while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
                        cout << "====Average low====Using Item====" << endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }
                ///////
                //use an item to attack ;
                /////// 
                checkGone = false;
                srand(time(0));
                int random;
                if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "=================================" << endl;
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                    cout << "=================================" << endl;
                }
                break;
                }
                break;
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////
                if(Enemymodel->getHP() <= 0)
                {
                    break;
                }
                while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
                        cout << "====Average average ======Using Item" << endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }
                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                checkGone = false;
                srand(time(0));
                random;
               if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP())
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack()&& Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "=================================" << endl;
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                    cout << "=================================" << endl;
                }
                break;
                }
                break;
            default:
            //FIRST PART
            if(Enemymodel->getHP() <= 0)
                {
                    break;
                }
            while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
                        cout <<"===== Average high====Using Item====" << endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }
            //SECONDPART
            checkGone = false;
                srand(time(0));
                random;

                if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "=================================" << endl;
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                    cout << "=================================" << endl;
                }
                break;
                }
                
            }
            break;

        case High:
            switch (CheckStamina(MaxST))
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                ///////  
                if(Enemymodel->getHP() <= 0)
                {
                    break;
                }
                while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
                        cout << "======High low=====Using Item====" << endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }
                ///////
                //use an item to attack ;
                ///////
                checkGone = false;
                srand(time(0));
                int random;
                if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "=================================" << endl;
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                    cout << "=================================" << endl;
                }
                break;
                }
                break;
            case average:
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////
                if(Enemymodel->getHP() <= 0)
                {
                    break;
                }
                while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
                        cout << "=====High average===== Using Item" << endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                checkGone = false;
                srand(time(0));
                random;
                if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack()&& Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "=================================" << endl;
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                    cout << "=================================" << endl;
                }
                break;
                }
                break;
            default:
            //FIRTPART
            if(Enemymodel->getHP() <= 0)
                {
                    break;
                }
            while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
                        cout <<"=====High high==== Using Item====" << endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }

            //SECONDPART
            checkGone = false;
                srand(time(0));
                random ;
               if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "=================================" << endl;
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                    cout << "=================================" << endl;
                }
                break;
                }
                break;
            }
            break;

        default:

        //FIRTPART
        if(Enemymodel->getHP() <= 0)
                {
                    break;
                }
        while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyWeapons().size() > 0)
                    {
                        cout <<" ANYTHING ELSE" << endl;
                        useItems(0);
                    }
                    else{

                        break;
                    }
                    
                }
        //SECONDPART
         checkGone = false;
                srand(time(0));
                int random;
               if(Enemymodel->getEnemyWeapons().size() > 0)
                {
                    random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                    {
                        WeaponAttack(player , i);
                        checkGone = true;
                        break;
                    }
                }

                if(!checkGone)
                {
                    for(int i = 0 ; i < random ; i++)
                    {
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack() && Enemymodel->getHP() > 0)
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone && Enemymodel->getHP() > 0)
                {
                    cout << "=================================" << endl;
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                    cout << "=================================" << endl;
                }
                break;
                }
            break;
        }
        
        //if((humanenemymodel->getStamina() - humanenemymodel->getNeededStaminaPerAttack()) > 0)
        //{
        //player->setHP(player->getHP() - humanenemymodel->getDamagePerAttack());
        //humanenemymodel->setStamina(humanenemymodel->getStamina() - humanenemymodel->getNeededStaminaPerAttack());
        //}
        //else{
        //    cout << "Enemy Doesn't have enough Energy to attack" << endl;
        //}
    }



    int HumanEnemyController::CheckHealth(int maxHP){
        //*************add percent of Health , now it is just a number between 0 to 100 ;*****************
        if (Enemymodel->getHP() <= maxHP/10){
            return 0 ;
        }
        else if (Enemymodel->getHP()>maxHP/10 && Enemymodel->getHP()<=maxHP/2){
            return 50 ;
        }
        else if (Enemymodel->getHP()<=maxHP && Enemymodel->getHP()>maxHP/2){
            return 100 ;
        }
        return -1;
    }
    int HumanEnemyController::CheckStamina(int maxST){
        //*************add percent of Health , now it is just a number between 0 to 100 ;*****************
        if (Enemymodel->getStamina() <= maxST/10){
            return 0 ;
        }
        else if (Enemymodel->getStamina()>maxST/10 && Enemymodel->getStamina()<=maxST/2){
            return 50 ;
        }
        else if (Enemymodel->getStamina()<=maxST && Enemymodel->getStamina()>maxST/2){
            return 100 ;
        }

        return -1;
    }

