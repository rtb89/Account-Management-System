//Name:Rachana_T_Bhatia
//Course: 16:332:503, PM for Financial Applications and Numerical Computing
//CPP file for Derived class Stock Account :Account management systme: Date Apr_27_2015

#include "Account_R_Bhatia.h"
#include "Node.h"

#ifndef STOCKACCOUNT
#define STOCKACCOUNT

//Define the derived class StockAccount inherited Publicly from abstract class account

 class StockAccount :public Account   
 { 
 public:
   StockAccount();  //Constructor Function
   ~StockAccount(); //Destructor function destroying all the nodes of the linked list
   double stockPrice(string);  //Function protype for returning the price per share
   void displayPortfolio();   //Function protype for displaying the portfolio
   virtual void printHistory() const;  
   void buyShare();   //Function protype for buying shares
   void sellShare();    //Function protype for selling the shares
  void viewPortfolioGraph();   //Function protype for viewing the graph
  void updateCashPortfolio();   //Function protype for updating the text file 


 private:

    Node* myHead;
	Node* myTail ;                     // string data of the node
    int mySize;                      //interger data type to store item number
	//Utility Functions
	Node* getnewNode(string &, int &);
	void removeNode(string &);
  
  };

#endif;

