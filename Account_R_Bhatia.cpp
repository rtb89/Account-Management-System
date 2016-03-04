//Name:Rachana_T_Bhatia
//Course: 16:332:503, PM for Financial Applications and Numerical Computing
//CPP file for abstract data class:Account management systme: Date Apr_27_2015


#include "Account_R_Bhatia.h"
#include <fstream>  //includes the file functions
#include <iostream>
using namespace std;


//Constructor Function
Account::Account()
{
	 ifstream myFile1("cash_balance.txt",ios::in);
	 if(!myFile1)
	 {  cerr<<"File could not be opened"<<endl;
	 exit(1);
	 }
	myFile1.seekg(-20,ios::end);   //set the pointer 38 bytes from the end of the file
	 myFile1>>cashBalance;  //Read the last saved value*/
	
}
//Initializing the static data
double Account::cashBalance=0.0; //Initialize the 