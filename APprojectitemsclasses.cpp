#include <iostream>
using namespace std;
class Item{
	protected:
		string name;
		int price;	
	public:
		string getName(){
			return name;
		}
		int getPrice(){
			return price;
		}
		void setName(string Name){
			name = Name;
		}
		void setPrice(int Price){
			price =Price;
		}
		bool operator==(Item other){
			if(other.getName()== name && other.getPrice()==price){
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
	public:
		void setDamagePerAttack(int dpa){
			damagePerAttack = dpa;
		}
		int getDamagePerAttack(){
			return damagePerAttack;
		}
		virtual void weaponAttack(Enemy currentEnemy) =0;
};
class UsableItems: public Item{
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
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
		}
};
class Shuriken: public ColdWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
			for(int i=0;i<mainCharacter.getWeapons().size();i++){
				if(dynamic_cast<Shuriken*>(mainCharacter.getWeapons()[i]) != NULL){
					mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
					break;
				}
			}
		}
};
class Batarang: public ColdWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
			for(int i=0;i<mainCharacter.getWeapons().size();i++){
				if(dynamic_cast<Batarang*>(mainCharacter.getWeapons()[i]) != NULL){
					mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
					break;
				}
			}
		}
};
class Trident : public ColdWeapon,PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
		}
};
class Spear: public ColdWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
			for(int i=0;i<mainCharacter.getWeapons().size();i++){
				if(dynamic_cast<Spear*>(mainCharacter.getWeapons()[i]) != NULL){
					mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
					break;
				}
			}
		}
};
class FlameThrower: public Hotweapon, PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
		}
};
class Blaster: public HotWeapon, PermanentWeapoon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
		}
};
class LightSaber: public HotWeapon, PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
		}
};
class ElderWand: public ColdWeapon, PermanentWeapon{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
		}
};
class Grenade: public HotWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
			for(int i=0;i<mainCharacter.getWeapons().size();i++){
				if(dynamic_cast<Grenade*>(mainCharacter.getWeapons()[i]) != NULL){
					mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
					break;
				}
			}
		}
};
class CapsShield: public ColdWeapon, ThrowableItem{
	public:
		void weaponAttack(Enemy currentEnemy) override{
			currentEnemy.setHP(currentEnemy.getHP()-damagePerAttack);
			for(int i=0;i<mainCharacter.getWeapons().size();i++){
				if(dynamic_cast<CapsShield*>(mainCharacter.getWeapons()[i]) != NULL){
					mainCharacter.getWeapons().erase(mainCharacter.getWeapons().begin()+ i);
					break;
				}
			}
		}
};



