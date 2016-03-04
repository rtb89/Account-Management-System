//Name:Rachana_T_Bhatia
//Course: 16:332:503, PM for Financial Applications and Numerical Computing
//Header file for abstract class Account :Account management systme: Date Apr_27_2015


#include <iostream>
using namespace std;


#ifndef ACCOUNT
#define ACCOUNT

 class Account   //Abstract class defenition

 { 
 public:
 Account(); //Constructor function
  virtual void printHistory() const=0; //Pure virtual function to ve overridden by all derived class


 protected:
 static double cashBalance;  //Static data member
  
 };
#endif;

 //End of class defenition

 

	 