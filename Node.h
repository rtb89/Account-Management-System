//Name:Rachana_T_Bhatia
//Course: 16:332:503, PM for Financial Applications and Numerical Computing
//Header file for Node class-Friend class of StockAccount :Account management systme: Date Apr_27_2015


# include <cstdlib>
# include <string>   

 #ifndef LISTNODE_H
 # define LISTNODE_H  

using namespace std;                  
 class StockAccount;   //Pre-definiing the class
 
 class Node            //Defining a class Node
 {
	 
 friend class StockAccount; // make StockAccount class a friend class

 public:
	Node(string& info1, int& info2)                //Constructore function
		:stockSym(info1), stockNumber(info2)        //Initiallizer for Itemname and itemno.
 {
  this->leftptr=0;         //Setting the previous pointer of the current node to zero
  this->rightptr=0;       //Setting the next pointer of the current node to zero
 }
	        
 private:
    string stockSym;                 // string data of the node for storing stock symbol
    int stockNumber;                 //interger data type to store Number of Stocks
    Node *leftptr;                   // Pointer to a node
	Node *rightptr;                 // Pointer to a node


 }; // end class Node
  #endif