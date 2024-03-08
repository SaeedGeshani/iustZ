#include<iostream>
#include<vector>
using namespace std;

class MainCharacter {

protected :
    string Name;
    string Gender;
    int Level;
    int Age;
    int Health;
    int Stamina;
    int Exp;
    int Gold ;
    //ColdWeapon CLWeapon;
    //HotWeapon HTWeapon;
    //vector<ThrowableItems> THItems;
    //vector<UseableItems> USItems;
public :
    MainCharacter () {
        Name = "Player" ;
        Age = 18 ;
        Gender = "Male" ; 
        Level = 1 ;
        Health = 500 ;
        Stamina = 100 ;
        Exp = 0 ;
        Gold = 500 ;      
    } ;

    MainCharacter (string name , int age , string gender) {
        Name = name ;
        Age = age ;
        Gender = gender ; 
        Level = 1 ;
        Health = 500 ;
        Stamina = 100 ;
        Exp = 0 ;
        Gold = 500 ;
    } ;
    string getName () {
        return Name ;
    }
    string getGender () {
        return Gender ;
    }
    int getAge () {
        return Age ;
    }
    int getHealth () {
        return Health ;
    }
    int getStamina () {
        return Stamina ;
    }
    int getExp () {
        return Exp ;
    }
    int getGold () {
        return Gold ;
    }
    virtual int calculateEpx (int Level , int Exp) {
        while (Exp >= Level*10){
            Exp = Exp - (Level*10) ;
            Level++ ;
        }
    }
};

int main(){ 

        return 0;
}
