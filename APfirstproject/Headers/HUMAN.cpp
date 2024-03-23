#include "HUMAN.h"
#include<iostream>
using namespace std;



int CalculateDMPAforHuman(int level)
{
    int DMPA;
    DMPA = pow(level , 10/7) + 10;
    return DMPA;
}
int CalculateSTforHuman(int level)
{
    int ST;
    ST = level * 20 + 50;
    return ST;
}
int CalculateHPForHuman(int level)
{
    int HP;
    HP = pow(level , 4/3) * 20 + 50;
    return HP;
}


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
        if(hp > 70 + Level*10)
        {
            HP = 70 + Level*10;
        }
        else{

            HP = hp;
        }
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
        if(stamina > 80 + 8*Level)
        {
            Stamina = 80 + Level*8;
        }
        else{

            Stamina = stamina;
        }
    }
    int HumanEnemyModel::getStamina()
    {
        return Stamina;
    }
    //=========================================

    void HumanEnemyModel::setEnemyUsableItems(vector<UseableItems*> useableitems)
    {
        UsableEN = useableitems;
    }

    vector<UseableItems*> HumanEnemyModel::getEnemyUseableItems()
    {
        return UsableEN;
    }

    void HumanEnemyModel::setEnemyWeapons(vector<Weapon*> weps)
    {
        WeaponsEN = weps;
    }

    vector<Weapon*> HumanEnemyModel::getEnemyWeapons()
    {
        return WeaponsEN;
    }

    //Constructor==============================
    HumanEnemyModel::HumanEnemyModel() = default;
    HumanEnemyModel::HumanEnemyModel(string name , int hp , int stamina , int damageperattack , int level)
    :EnemyModel(name , hp , stamina , damageperattack , level)
    {
        
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
    void HumanEnemyController::UseItem(int column)
    {
        humanenemymodel->setHP(humanenemymodel->getHP() + humanenemymodel->getEnemyUseableItems()[column]->getHealingPower());
        humanenemymodel->setStamina(humanenemymodel->getStamina() + humanenemymodel->getEnemyUseableItems()[column]->getEnergy());
        delete humanenemymodel->getEnemyUseableItems()[column];
        humanenemymodel->getEnemyUseableItems().erase(humanenemymodel->getEnemyUseableItems().begin() + column);
    }

    void HumanEnemyController::WeaponAttack(int numberOfWeapon , MainCharacter* player)
    {
        if(humanenemymodel->getStamina() > humanenemymodel->getEnemyWeapons()[numberOfWeapon]->getNeededStaminaPerAttack())
        {
            humanenemymodel->setStamina(humanenemymodel->getStamina() - humanenemymodel->getEnemyWeapons()[numberOfWeapon]->getNeededStaminaPerAttack());
            player->setHP(player->getHP() - humanenemymodel->getEnemyWeapons()[numberOfWeapon]->getDamagePerAttack());
            if(dynamic_cast<ThrowableWeapon*>(humanenemymodel->getEnemyWeapons()[numberOfWeapon]) != NULL)
            {
                delete humanenemymodel->getEnemyWeapons()[numberOfWeapon];
                humanenemymodel->getEnemyWeapons().erase(humanenemymodel->getEnemyWeapons().begin() + numberOfWeapon);
                humanenemymodel->getEnemyWeapons().shrink_to_fit();
            }
        }
        else{

            cout << "=========================================================" << endl;
            cout << "Not enough energy for humanenemy to attack (weapon attck)" << endl;
            cout << "=========================================================" <<endl;
        }
        
    }

       void HumanEnemyController::Attack(MainCharacter* player)
    {   bool checkgone = false;
            int randomGunNumber;

        switch (CheckHealth())
        {
            
        case Low:
            switch (CheckStamina())
            {
            case low:
                ///////
                //use an item to generate stamina or more than one , Stamina is under 10 percent ;
                ///////
                while(humanenemymodel->getHP() < (0.7)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.7)*(80 + humanenemymodel->getLevel()*8))
                {
                    if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }
                    
                }  

                ///////
                //use an item to attack ;
                ///////
                
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
                }




                break;
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////
                while(humanenemymodel->getHP() < (0.5)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.5)*(80 + humanenemymodel->getLevel()*8))
                {
                  if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }  
                }

                ///////
                //use an item to attack ;
                ///////
                checkgone = false;
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
                }



                break;
            default:

            //aaaaaaaaaaaaaaaaaaaaaaa
                while(humanenemymodel->getHP() < (0.5)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.5)*(80 + humanenemymodel->getLevel()*8))
                {
                  if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }  
                }
            //aaaaaaaaaaaaaaaaaaaaaaa
                checkgone = false;
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
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
                while(humanenemymodel->getHP() < (0.5)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.5)*(80 + humanenemymodel->getLevel()*8))
                {
                  if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }  
                }
                ///////
                //use an item to attack ;
                /////// 
                checkgone = false;
               
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
                }



            break;
            case average:  
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////
                while(humanenemymodel->getHP() < (0.5)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.5)*(80 + humanenemymodel->getLevel()*8))
                {
                  if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }  
                }
                ///////
                //use an item to attack ;
                ///////
                checkgone = false;
                
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
                }



                break;
            default:
            //aaaaaaaaaaaaaaaaaa
            while(humanenemymodel->getHP() < (0.5)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.5)*(80 + humanenemymodel->getLevel()*8))
                {
                  if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }  
                }
            //pppppppppppppppp
            checkgone = false;
                
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
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
                while(humanenemymodel->getHP() < (0.5)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.5)*(80 + humanenemymodel->getLevel()*8))
                {
                  if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }  
                }
                ///////
                //use an item to attack ;
                ///////
                checkgone = false;
                
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
                }



            break;
            case average:
                ///////
                //use an item to generate stamina , stamina is under 50 percent ;
                ///////
                while(humanenemymodel->getHP() < (0.5)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.5)*(80 + humanenemymodel->getLevel()*8))
                {
                  if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }  
                }
                ///////
                //use an item to attack ;
                ///////
                checkgone = false;
               
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
                }



            break;
            default:

            //aaaaaaaaaaaaaaaaaaaaaaaaaaaa
            while(humanenemymodel->getHP() < (0.5)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.5)*(80 + humanenemymodel->getLevel()*8))
                {
                  if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }  
                }
            //ddddddddddddddddddddddddddddd
            checkgone = false;
               
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
                }



                break;
            }

            break;

        default:
            //aaaaaaaaaaaaaaaaaaaaaa
            while(humanenemymodel->getHP() < (0.5)*(70 + humanenemymodel->getLevel()*10) || humanenemymodel->getStamina() < (0.5)*(80 + humanenemymodel->getLevel()*8))
                {
                  if(humanenemymodel->getHP() != (70 + humanenemymodel->getLevel()*10) && humanenemymodel->getStamina() != (80 + humanenemymodel->getLevel()*8))
                    {
                        if(humanenemymodel->getEnemyUseableItems().size() > 0)
                        {
                            UseItem(0);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else{
                        break;
                    }  
                }
            //aaaaaaaaaaaaaaaaaaaaaaaa
            bool checkgone = false;
                int randomGunNumber;
                randomGunNumber = rand() % humanenemymodel->getEnemyWeapons().size();
                for(int i = randomGunNumber ; i < humanenemymodel->getEnemyWeapons().size() ; i++)
                {
                    if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                    {
                        WeaponAttack(i , player);
                        checkgone = true;
                        break;
                    }
                }
                if(!checkgone)
                {
                    for(int i = 0 ; i < randomGunNumber ; i++)
                    {
                        if(humanenemymodel->getStamina() >= humanenemymodel->getEnemyWeapons()[i]->getNeededStaminaPerAttack())
                        {
                            WeaponAttack(i , player);
                            checkgone = true;
                            break;
                        }
                    }
                }
                if(!checkgone)
                {
                    cout << "=====================================================" << endl;
                    cout << "Not enough energy for humanenemy to use any weapon :)" << endl;
                    cout << "=====================================================" << endl;
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
        if (humanenemymodel->getHP() <= (0.1)*(70 + humanenemymodel->getLevel()*10)){
            return 0 ;
        }
        else if (humanenemymodel->getHP()>(0.1)*(70 + humanenemymodel->getLevel()*10) && humanenemymodel->getHP()<=(0.5)*(70 + humanenemymodel->getLevel()*10)){
            return 50 ;
        }
        else if (humanenemymodel->getHP()<=(70 + humanenemymodel->getLevel()*10) && humanenemymodel->getHP()>(0.5)*(70 + humanenemymodel->getLevel()*10)){
            return 100 ;
        }
        return -1;
    }
    int HumanEnemyController::CheckStamina(){
        //*************add percent of Health , now it is just a number between 0 to 100 ;*****************
        if (humanenemymodel->getStamina() <= (0.1)*(80 + humanenemymodel->getLevel()*8)){
            return 0 ;
        }
        else if (humanenemymodel->getStamina()>10 && humanenemymodel->getStamina() <= (0.5)*(80 + humanenemymodel->getLevel()*8)){
            return 50 ;
        }
        else if (humanenemymodel->getStamina()<=(80 + humanenemymodel->getLevel()*8) && humanenemymodel->getStamina()>(0.5)*(80 + humanenemymodel->getLevel()*8)){
            return 100 ;
        }
        return -1;
    }

// //HumanEnemyFactory///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //Constructor========================
//     HumanEnemyFactory::HumanEnemyFactory() = default;
//     HumanEnemyFactory::HumanEnemyFactory(int humanenemylevel)
//     {
//         HumanEnemyLevel = humanenemylevel;
//     }
//     //Setter and Getters=================
//     void HumanEnemyFactory::setHumanEnemyLevel(int humanenemylevel)
//     {
//         HumanEnemyLevel = humanenemylevel;
//     }
//     int HumanEnemyFactory::getHumanEnemyLevel()
//     {
//         return HumanEnemyLevel;
//     }
//     Zombie* HumanEnemyFactory::makeZombie()
//     {
//         ZombieModel* zombiemodel = new ZombieModel("Zombie", CalculateHPForZombie(HumanEnemyLevel) , CalculateSTforZombie(HumanEnemyLevel) , CalculateDMPAforZombie(HumanEnemyLevel) , HumanEnemyLevel); 
//         ZombieView* zombieview = new ZombieView(zombiemodel);      
//         ZombieController* zombiecontroller = new ZombieController(zombiemodel);
//         Zombie* zombie = new Zombie(zombiemodel , zombieview , zombiecontroller);
//         return zombie;
        
//     }
