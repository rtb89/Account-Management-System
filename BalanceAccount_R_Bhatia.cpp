//Name:Rachana_T_Bhatia
//Course: 16:332:503, PM for Financial Applications and Numerical Computing
//CPP file for Derived class Balance Account :Account management systme: Date Apr_27_2015


# include "BalanceAccount_R_Bhatia.h"
//# include "Account_R_Bhatia.h";
#include <fstream>  //includes the file functions
#include <iostream>
using namespace std;
#include <iomanip>  // includes the fuction prototype setprecision, static_cast
#include <time.h>   // includes the function prototype for time(0) 
#include <cstdlib>  //includes the function prototype of rand()
#include <fstream>  //includes the file functions
#include <cmath>   //includes math fuctuin sqrt and abs
#include <string>

//Constructor function
BalanceAccount::BalanceAccount():Account()
{
	amountType='\0'; //Initiallize the private data
    Amount=0.0  ;
}

BalanceAccount::~BalanceAccount()        //Destructor
{  
}

void BalanceAccount::depositMoney()
{  
   	cout <<"\nEnter the amount to be deposited:    $";
	cin >> Amount;
	Amount=((Amount>0)?Amount:0);     //Set the negative amount value to zero
	time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
     timeinfo = localtime(&seconds);
     cout<<"Amount deposited at the current local time :"<<asctime(timeinfo); 
	amountType= "Deposit";
   Account:cashBalance=Account::cashBalance+Amount; //Update the cashbalance with the deposited amount

//Update the transaction file
ofstream accountFile("bank_transaction_history.txt",ios::app);
 if(!accountFile)
	 {  cerr<<"File could not be opened"<<endl;
	 exit(1);
	 }
accountFile<<left<<setw(12)<<amountType<<setw(20)<<showpoint<<Amount<<setw(20)<<right<<asctime(timeinfo)<<"\n";
 
 }

//return cash balance
double BalanceAccount::getCashBalance()
{
	return Account::cashBalance;
}


//Function to withdraw money
void BalanceAccount::withdrawMoney()
{  
	
   	cout <<"\nEnter the amount to be withdrawn:   $";
	cin >> Amount;
	Amount=((Amount>0)?Amount:0);  //Discard the negative amount value
	time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
     timeinfo = localtime(&seconds);
    	amountType= "Withdraw";
	if(Amount>Account::cashBalance)
		cerr<<"Not suffecient amount in the account"<<endl;
	else
	{
      
    Account::cashBalance=Account::cashBalance-Amount;
	cout<<"Withdrawal successful at the current local time :  "<<asctime(timeinfo); 
      ofstream accountFile("bank_transaction_history.txt",ios::app);
	   if(!accountFile)
	 {  cerr<<"File could not be opened"<<endl;
	 exit(1);
	 }
   accountFile <<left<<setw(12)<< amountType <<setw(20)<<showpoint<<Amount<<setw(20)<<right<< asctime(timeinfo)<<"\n";
 }
}

//override the pure virtual function
 void BalanceAccount::printHistory() const
{  string type;
double amount;
string datetime1;
string datetime2;
string datetime3;
string datetime4;
string datetime5;
cout<<"\nAccount Statement:\n\n";
ifstream myFile("bank_transaction_history.txt",ios::in);
while(myFile>>type>>amount>>datetime1>>datetime2>>datetime3>>datetime4>>datetime5)
cout<<"\n"<<setw(12)<<type<<"\t"<<amount<<"\t"<<datetime1<<" "<<datetime2<<" "<<datetime3<<" "<<datetime4<<" "<<datetime5;
}//end of function
 