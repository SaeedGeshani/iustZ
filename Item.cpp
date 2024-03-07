#include <iostream>
using namespace std;
class Item{
	protected:
		string Name;
		int Price;	
	public:
		string getName(){
			return Name;
		}
		int getPrice(){
			return Price;
		}
		void setName(string name){
			Name = name;
		}
		void setPrice(int price){
			Price = price;
		}
		bool operator==(Item other){
			if(other.getName()== Name && other.getPrice() == Price){
				return true;
			}
			else{
				return false;
			}
		}
		
};

class Weapon: public Item{
	protected:
		int damagePerAttack;
		int neededStamina;
	public:
		void setDamagePerAttack(int dpa){
			damagePerAttack = dpa;
		}
		int getDamagePerAttack(){
			return damagePerAttack;
		}
		void setNeededS(int ns){
			neededStamina = ns;
		}
		int getNeededS(){
			return neededStamina;
		}
		virtual void weaponAttack(Enemy currentEnemy) = 0;
};
class UsableItems: public Item{
	protected:
		int addedHP;
		int AddedStamina;
	public:
		void setAddedHP(int ahp){
			addedHP = ahp;
		}
		int getAddedHP(){
			return addedHP;
			
		}
		void setAddedStamina(int ast){
			AddedStamina = ast;
		}
		int getAddedStamina(){
			return AddedStamina;
		}
		virtual void HPandStincreaser() = 0;

		};
class WheyProtein: public UsableItems{
	public :
		void HPandStincreaser() override{
			mainCharacter.setHP(mainCharacter.getHP()+addedHP);
			mainCharacter.setStamina(mainCharacter.getStamina()+AddedStamina);
			for(int i=0;i<mainCharacter.getUsableItems().size();i++){
					if(dynamic_cast<WheyProtein*>(mainCharacter.getUsableItems()[i]) != NULL){
						mainCharacter.getUsableItems().erase(mainCharacter.getUsableItems().begin()+ i);
						break;
					}
				}
		}
};
class Egg : public UsableItems{
	public :
		void HPandStincreaser() override{
			mainCharacter.setHP(mainCharacter.getHP()+addedHP);
			mainCharacter.setStamina(mainCharacter.getStamina()+AddedStamina);
			for(int i=0;i<mainCharacter.getUsableItems().size();i++){
					if(dynamic_cast<WheyProtein*>(mainCharacter.getUsableItems()[i]) != NULL){
						mainCharacter.getUsableItems().erase(mainCharacter.getUsableItems().begin()+ i);
						break;
					}
				}
		}
};
class HotWeapon: public Weapon{
};
class ColdWeapon: public Weapon{
};
class ThrowableItem: public Weapon{
};
class PermanentWeapon : public Weapon{
};
class Katana : public ColdWeapon,PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Shuriken: public ColdWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				for(int i=0;i<mainCharacter.getWeapons().size();i++){
					if(dynamic_cast<Shuriken*>(mainCharacter.getWeapons()[i]) != NULL){
						mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
						break;
					}
				}
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Batarang: public ColdWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				for(int i=0;i<mainCharacter.getWeapons().size();i++){
					if(dynamic_cast<Batarang*>(mainCharacter.getWeapons()[i]) != NULL){
						mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
						break;
					}
				}
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Trident : public ColdWeapon,PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Spear: public ColdWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				for(int i=0;i<mainCharacter.getWeapons().size();i++){
					if(dynamic_cast<Spear*>(mainCharacter.getWeapons()[i]) != NULL){
						mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
						break;
					}
				}
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class FlameThrower: public Hotweapon, PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Blaster: public HotWeapon, PermanentWeapoon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class LightSaber: public HotWeapon, PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class ElderWand: public ColdWeapon, PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Grenade: public HotWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				for(int i=0;i<mainCharacter.getWeapons().size();i++){
					if(dynamic_cast<Grenade*>(mainCharacter.getWeapons()[i]) != NULL){
						mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
						break;
					}
				}
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class CapsShield: public ColdWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				for(int i=0;i<mainCharacter.getWeapons().size();i++){
					if(dynamic_cast<CapsShield*>(mainCharacter.getWeapons()[i]) != NULL){
						mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
						break;
					}
				}
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};
class Mjolnir: public ColdWeapon, PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			if(mainCharacter.getStamina()>=neededStamina){
				currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
				currentEnemy.setStamina(currentEnemy.getStamina()-damagePerAttack/4);
				mainCharacter.setStamina(mainCharacter.getStamina()- neededStamina);
			}
			else{
				cout<<"this weapon requires more Stamina!"<<endl;
			}

		}
};



