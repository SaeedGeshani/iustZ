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




//[dkqwbjfvaejkeakjvnkjnekjvnksjn.lvknlaknvlkasnlkvnlnvksavlklsnvlknslkvnlsknvlknri jpwepwmvw   piwj[gojepek/kmfkwpjvo  jwkw]]

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




//87777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777



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

                //===========================================================================================================



while(humanenemymodel->getHP() < (0.4)*((70 + humanenemymodel->getLevel()*10)))
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

