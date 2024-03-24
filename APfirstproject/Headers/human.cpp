#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<ctime>
#include "human.h"
using namespace std;


//Enemy/////////////////////////////////////////////////////////////////////////////
    //Getter and Setter=====================
    void HumanEnemy::setHumanEnemyModel(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }
    HumanEnemyModel* HumanEnemy::getHumanEnemyModel()
    {
        return humanenemymodel;
    }
    void HumanEnemy::setHumanEnemyView(HumanEnemyView* humanenemyview)
    {
        this->humanenemyview = humanenemyview;
    }
    HumanEnemyView* HumanEnemy::getHumanEnemyView()
    {
        return humanenemyview;
    }
    void HumanEnemy::setHumanEnemyController(HumanEnemyController* humanenemycontroller)
    {
        this->humanenemycontroller = humanenemycontroller;
    }
    HumanEnemyController* HumanEnemy::getHumanEnemyController()
    {
        return humanenemycontroller;
    }
    //Constructor==============================
    HumanEnemy::HumanEnemy() = default;
    HumanEnemy::HumanEnemy(HumanEnemyModel* humanenemymodel , HumanEnemyView* humanenemyview , HumanEnemyController* humanenemycontroller)
    {
        this->humanenemymodel = humanenemymodel;
        this->humanenemyview = humanenemyview;
        this->humanenemycontroller = humanenemycontroller;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyModel//////////////////////////////////////////////////////////////////////////////////////////////////

    //Setter & Getters ==========================
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
    void HumanEnemyView::setHumanEnemyModel(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }
    HumanEnemyModel* HumanEnemyView::getHumanEnemyModel()
    {
        return humanenemymodel;
    }
    //Constructors===============================
    HumanEnemyView::HumanEnemyView() = default;
    HumanEnemyView::HumanEnemyView(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }

    //Functions==================================
    void HumanEnemyView::ShowHumanEnemyInfo()
    {
        cout << "Here is status of enemy : " << endl;
        cout << "Enemy's Name: " << humanenemymodel->getName() << endl;
        cout << "Enemy's HP : " << humanenemymodel->getHP() << endl;
        cout << "Enemy's Stamina: " << humanenemymodel->getStamina() << endl;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//EnemyController/////////////////////////////////////////////////////////////////////////////////////////



    //Constructor======================
    HumanEnemyController::HumanEnemyController() = default;
    HumanEnemyController::HumanEnemyController(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }
    //Setter and Getters===============
    void HumanEnemyController::setHumanEnemyModel(HumanEnemyModel* humanenemymodel)
    {
        this->humanenemymodel = humanenemymodel;
    }
    HumanEnemyModel* HumanEnemyController::getHumanEnemyModel()
    {
        return humanenemymodel;
    }
    //Functions=========================
    void HumanEnemyController::Attack(MainCharacter* player)
    {

        switch (CheckHealth(player))
        {
        case Low:
            ///////
            //use an item to heal or more than one , Hp is under 10 percent ;
            ///////
            switch (CheckStamina(player))
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                ///////  

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                break;
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                break;
            default:
                break;
            }
            break;
        case Average:
            ///////
            //use an item to heal , Hp is under 50 percent ;
            ///////
            switch (CheckStamina(player))
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                /////// 

                ///////
                //use an item to attack ;
                /////// 
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                break;
            default:
                break;
            }
            break;
        case High:
            switch (CheckStamina(player))
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                ///////  

                ///////
                //use an item to attack ;
                ///////
            case average:
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////

                ///////
                //use an item to attack and set stamina and DamagePerAttack of that weapon and use the comment code below ;
                ///////
                break;
            default:
                break;
            }
            break;
        default:
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
    int HumanEnemyController::CheckHealth(MainCharacter* player){
        //*************add percent of Health , now it is just a number between 0 to 100 ;*****************
        if (player->getHP() <= 10){
            return 0 ;
        }
        else if (player->getHP()>10 && player->getHP()<=50){
            return 50 ;
        }
        else if (player->getHP()<=100 && player->getHP()>50){
            return 100 ;
        }
    }
    int HumanEnemyController::CheckStamina(MainCharacter* player){
        //*************add percent of Health , now it is just a number between 0 to 100 ;*****************
        if (player->getStamina() <= 10){
            return 0 ;
        }
        else if (player->getStamina()>10 && player->getStamina()<=50){
            return 50 ;
        }
        else if (player->getStamina()<=100 && player->getStamina()>50){
            return 100 ;
        }
    }

//HumanEnemyFactory///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Constructor========================
    HumanEnemyFactory::HumanEnemyFactory() = default;
    HumanEnemyFactory::HumanEnemyFactory(int humanenemylevel)
    {
        HumanEnemyLevel = humanenemylevel;
    }
    //Setter and Getters=================
    void HumanEnemyFactory::setHumanEnemyLevel(int humanenemylevel)
    {
        HumanEnemyLevel = humanenemylevel;
    }
    int HumanEnemyFactory::getHumanEnemyLevel()
    {
        return HumanEnemyLevel;
    }
    Zombie* HumanEnemyFactory::makeZombie()
    {
        ZombieModel* zombiemodel = new ZombieModel("Zombie", CalculateHPForZombie(HumanEnemyLevel) , CalculateSTforZombie(HumanEnemyLevel) , CalculateDMPAforZombie(HumanEnemyLevel) , HumanEnemyLevel); 
        ZombieView* zombieview = new ZombieView(zombiemodel);      
        ZombieController* zombiecontroller = new ZombieController(zombiemodel);
        Zombie* zombie = new Zombie(zombiemodel , zombieview , zombiecontroller);
        return zombie;
        
    }
