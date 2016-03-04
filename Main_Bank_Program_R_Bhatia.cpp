//Name:Rachana_T_Bhatia
//Course: 16:332:503, PM for Financial Applications and Numerical Computing
//Main function:Account management systme: Date Apr_27_2015
#include <iostream>
using namespace std;
#include <string.h>
# include "BalanceAccount_R_Bhatia.h"
# include "stockAccount_R_Bhatia.h"
#include <iomanip>  // includes the fuction prototype setprecision, static_cast
#include <fstream>  //includes the file functions
#include <string>

//Function to call the Balance account transactions
void bankAccountOptions(BalanceAccount *bAccount){
	while(true){
		cout << "\n\n******Bank Account*******" << endl;
		cout << "Please select an option:" << endl;
		cout << "1- View account balance" << endl;
		cout << "2- Deposit money" << endl;
		cout << "3- Withdraw money" << endl;
		cout << "4- Print out history" << endl;
		cout << "5- Return to previous menu" << endl;
		cout << endl << endl << "Please select one of the above options: ";
		int menuSelection = 0;
		cin >> menuSelection; //Input the choice of operation

		switch(menuSelection){
		case 1: //view balane
			{cout<<"The balance in your account:   $";
			cout<<bAccount->getCashBalance();
			
	        break;}
		case 2: //deposit money
			bAccount->depositMoney();

			break;
		case 3:	//withdraw money
			bAccount->withdrawMoney();
			break;
		case 4: //View transaction history
			cout<<"Your Transaction History:"<<endl;
			bAccount->printHistory();
			break;
		case 5: //return to the main
			return;
			break;
		
		default: //return to the main
			return;
			break;
		}
	}
}


//Function to call transaction of the stock portfolio

void stockAccountOptions(StockAccount *sAccount){
	while(true){
		cout << "\n\n*****Stock Portfolio Account*****" << endl;
		cout << "Please select an option:" << endl;
		cout << "1. Display the price for a stock symbol" << endl;
		cout << "2. Display the current portfolio" << endl;
		cout << "3. Buy shares" << endl;
		cout << "4. Sell shares " << endl;
		cout << "5. View a graph for the portfolio value " << endl;
		cout << "6. View transaction history " << endl;
		cout << "7. Return to previous menu " << endl;
		cout << endl << "option: ";
		int menuSelection = 0;
		cin >> menuSelection;

		switch(menuSelection){
		case 1: // Display the price per share of the particular share randomly from one of the result text files
			{double price;
			string symb;
				cout<<"\nEnter the symbol of the stock\n";
				cin>> symb;
			    price=sAccount->stockPrice(symb);
				if (price==0.0) cout<< "\nShare symbol not found in the list\n";
				else cout<< "\nPer Share Price of "<<symb<<" is: $"<<price<<endl<<endl;
			
	        break;}
		case 2:  //Display the portfolio
			sAccount->displayPortfolio();
			break;
		case 3:	//Buy Share
			sAccount->buyShare();
			break;
		case 4:  //Sell Share
			sAccount->sellShare();
			break;
    	case 5: //View Graph
			sAccount->viewPortfolioGraph();
			break;
		case 6:
			cout<<"Your Transaction History:"<<endl;
			sAccount->printHistory();
			break;
		
		default:  //return to the main
			return;
			break;
		}
	}
}

 int main()
 {  
	 double initialBalance=10000;
	 // Update the cash balance text file with the intial balance and header if opening for the first time

	ifstream myFile("cash_balance.txt");
     if(myFile.fail()) {

		ofstream accountFile("cash_balance.txt",ios::out);
          accountFile<<setw(20)<<left<<"Second_1990"<<setw(18)<<left<<"Portfolio_value"<<setw(18)<<left<<"Cash_Balance"<<endl;
		  accountFile<<setw(20)<<left<<00000000<<setw(18)<<left<<initialBalance<<setw(18)<<left<<initialBalance<<endl;
	 }

	BalanceAccount acc;	
	StockAccount stk;
	
	string symb;
	int menuSelection = 0;
	cout << "Welcome to the Account Management System:" <<endl;
		cout << "Please select an account to access:" <<endl;
		cout << "1- Stock Portfolio Account" << endl << "2- Bank Account" << endl << "3- Exit" << endl;
		cin >> menuSelection;
	while(menuSelection<4) {
		
		
		switch(menuSelection){
		case(1):  //Stock Transactions

			{	stockAccountOptions(&stk);  //Calling the function for Stock Transactions
				break;
			}

		case(2): //Bank Transaction
		     {   
				 bankAccountOptions(&acc);  //Calling the function for Account Transactions
				 break;
			 }

		case(3):  //Exit
			{    //Update the Cash balance text file with the current portfolio and cash balance
				stk.updateCashPortfolio(); 
			    return 0;
			    break;
			}
		default:  //Exit
			//Update the Cash balance text file with the current portfolio and cash balance
			stk.updateCashPortfolio();
			exit(1);
		}
	

		cout << "\nWelcome to the Account Management System:" <<endl;
		cout << "Please select an account to access:" <<endl;
		cout << "1- Stock Portfolio Account" << endl << "2- Bank Account" << endl << "3- Exit" << endl;
		cin >> menuSelection;
	}
			return 0;
 }
	
 
 