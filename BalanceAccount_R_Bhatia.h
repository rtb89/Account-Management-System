//Name:Rachana_T_Bhatia
//Course: 16:332:503, PM for Financial Applications and Numerical Computing
//Header file for Derived class Balance Account :Account management systme: Date Apr_27_2015

#include "Account_R_Bhatia.h"
#include <time.h>
#include <fstream>  //includes the file functions

#ifndef BALANCEACCOUNT
#define BALANCEACCOUNT

//Define the derived class BalanceAccount inherited Publicly from abstract class account
 class BalanceAccount :public Account  
 { 

 public:
   BalanceAccount(); //Constructor Function
 ~BalanceAccount();  //Destructor Function
 void depositMoney();  //Function prototype for Deposit Money
 void withdrawMoney();  // Function prototype for Withdraw Money 
  virtual void printHistory() const;  //Pure virtual inherited function
 double getCashBalance();  // Function prototype for getting the available cash Balance

 private:
	  string amountType;                 // string data of the node
      double Amount;                       //interger data type to store item number
	
    };

#endif;






