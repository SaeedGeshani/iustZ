#pragma once
#include<string>
using namespace std;

class Items{
	protected:
		string Name;
		int Price;
	public:
		//constructor
		
		Items();
		Items(string name, int price);

		//getter and setter
	    void setName(string name);
    	
    	string getName();
    	
	   void setPrice(int price);
    	
    	
    	int getPrice();
    	
	//operator overloading:
	bool operator==(Items other);
};