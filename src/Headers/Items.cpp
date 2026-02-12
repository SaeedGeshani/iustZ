#include "Items.h"
#include<string>
using namespace std;


		//constructor
		
		Items::Items()= default;
		Items::Items(string name, int price){
			Name = name;
			Price = price;
		} 
		//getter and setter
	    void Items::setName(string name)
    	{		
       		Name = name;
    	}
    	string Items::getName()
    	{
        	return Name;
    	}	
	   void Items::setPrice(int price)
    	{
        	Price = price;
    	}
    	int Items::getPrice()
    	{
        	return Price;
    	}
	//operator overloading:
	bool Items::operator==(Items other){
		if(other.getName()==Name && other.getPrice()==Price){
			return true;
		}
		else{
			return false;
		}
	}

