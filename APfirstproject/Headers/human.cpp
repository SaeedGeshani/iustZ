#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<ctime>
#include "human.h"
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
            cout << "The enemy can't attack on player." << endl;
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
    HumanEnemyModel::HumanEnemyModel(string name , int hp , int stamina , int damageperattack , int level)
    {
        Name = name;
        HP = hp;
        Stamina = stamina;
        DamagePerAttack = damageperattack;
        Level = level;
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
        player->setHP(player->getHP() - Enemymodel->getEnemyWeapons()[number]->getDamagePerAttack());
        Enemymodel->setStamina(Enemymodel->getStamina() - Enemymodel->getEnemyWeapons()[number]->getNeededStaminaPerAttack());
        if(dynamic_cast<ThrowableWeapon*>(Enemymodel->getEnemyWeapons()[number]) != NULL)
        {
            delete Enemymodel->getEnemyWeapons()[number];
            Enemymodel->getEnemyWeapons().erase(Enemymodel->getEnemyWeapons().begin() + number);
        }
    }

    void HumanEnemyController::useItems(int number)
    {
        Enemymodel->setStamina(Enemymodel->getStamina() + Enemymodel->getEnemyUseableItems()[number]->getEnergy());
        Enemymodel->setHP(Enemymodel->getHP() + Enemymodel->getEnemyUseableItems()[number]->getHealingPower());
        delete Enemymodel->getEnemyUseableItems()[number];
        Enemymodel->getEnemyUseableItems().erase(Enemymodel->getEnemyUseableItems().begin() + number);
    }

    void HumanEnemyController::Attack(MainCharacter* player)
    {
        int MaxHP = CalculateHPForHuman(player->getLevel());
        int MaxST = CalculateSTForHuman(player->getLevel());
        bool checkGone = false;
        switch (CheckHealth())
        {
        case Low:
            switch (CheckStamina())
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                ///////
                
                while(Enemymodel->getHP() < (0.7)*(MaxHP) || Enemymodel->getStamina() < (0.7)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random1 = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random1 ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                }

                break;
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////
                while(Enemymodel->getHP() < (0.5)*(MaxHP) || Enemymodel->getStamina() < (0.5)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random1 = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random1 ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                }


                break;
            default:
            //FIRST CODE
             while(Enemymodel->getHP() < (0.7)*(MaxHP) || Enemymodel->getStamina() < (0.7)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                }


                break;
            }
            break;
        case Average:
            switch (CheckStamina())
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                /////// 
                while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                }
                break;
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////
                while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                }
                break;
            default:
            //FIRST PART
            while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                }
                break;
            }
            break;

        case High:
            switch (CheckStamina())
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                ///////  
                while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random = rand()%Enemymodel->getEnemyWeapons().size();
                
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                }
                break;
            case average:
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////
                while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                }
                break;
            default:
            //FIRTPART
            while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
                }
                break;
            }
            break;

        default:

        //FIRTPART
        while(Enemymodel->getHP() < (0.6)*(MaxHP) || Enemymodel->getStamina() < (0.6)*(MaxST))
                {
                    if(Enemymodel->getEnemyUseableItems().size() > 0)
                    {
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
                random = rand()%Enemymodel->getEnemyWeapons().size();
                for(int i = random ; i < Enemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
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
                        if(Enemymodel->getStamina() > Enemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(player , i);
                            checkGone = true;
                            break;
                        }
                    }
                }

                if(!checkGone)
                {
                    cout << "Couldn't use Weapon cause Stamina" << endl;
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



    int HumanEnemyController::CheckHealth(){
        //*************add percent of Health , now it is just a number between 0 to 100 ;*****************
        if (Enemymodel->getHP() <= 10){
            return 0 ;
        }
        else if (Enemymodel->getHP()>10 && Enemymodel->getHP()<=50){
            return 50 ;
        }
        else if (Enemymodel->getHP()<=100 && Enemymodel->getHP()>50){
            return 100 ;
        }
        return -1;
    }
    int HumanEnemyController::CheckStamina(){
        //*************add percent of Health , now it is just a number between 0 to 100 ;*****************
        if (Enemymodel->getStamina() <= 10){
            return 0 ;
        }
        else if (Enemymodel->getStamina()>10 && Enemymodel->getStamina()<=50){
            return 50 ;
        }
        else if (Enemymodel->getStamina()<=100 && Enemymodel->getStamina()>50){
            return 100 ;
        }

        return -1;
    }

