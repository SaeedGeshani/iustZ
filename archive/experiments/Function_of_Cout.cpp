#include<iostream>
#include<string>
#include<windows.h>
using namespace std;

void printS(string s)
{
    for(int i = 0 ; i < s.size() ; i++)
    {
        cout << s[i];
        Sleep(20);
    }
}

int main()
{
    printS("Hello My name is Saeed Geshani");  
    return 0;
}