# Account-Management-System
#The Account Management System Program have Inherited class structure with the Account Class as Abstract Base class 
#It has a static protected data cashBalance whose instance gets updated with all the member function of the inherited class as well and pure virtual function printHistory which would be overridden by all derived classes. The cpp file initialize the static data variable and define the constructor function of the class which take the value of Cash Balance from the “cash_balance.txt” file by placing the pointer at 20 bytes from the end of the file.(using seekg function)
#There are two derived classes.

#BalanceAccount Class has two private data types for storing the amount type and amount value for deposit and sell. It has the public member functions depositMoney() (for Depositing Money), withdrawMoney()  (for Withdrawing Money), that update the value of the cashBalance variable and write the transaction details in the “bank_transaction_history.txt” file. Function getCashBalance() returns the updated cashBalance value. printHistory() (Pure virtual inherited function) function read the data stored in the “bank_transaction_history.txt” and display it on the screen.

#StockAccount class uses a double linked list for storing all the shares in the portfolio. It uses a friend class node to form the linked list. Each node contains two data type: Stock symbol & no. of stocks
#The constructor function creates the “stock_transaction_history.txt " file if it doesn’t exist already by putting the header title. It then reads the transaction history and create a doubly linked list by adding new nodes (through getnewNode() fn) for new stock symbol or updating the node that already has the same stock symbol. The number of stocks the read data from the file are added / subtracted to number of stocks of the node with same stock symbol based on the Transaction type (ie. Purchase or sell). While updating the nodes it also checks if the number of shares has become zero and thus remove that node from the linked list by private utility function removeNode(). 

#The destructor function deletes all nodes of the linked list.

#stockPrice() function returns the price per share of the stock symbol from the either of the two results text file. This is done through randomly choosing a number through rand() fn and taking the modulus with 2. The result is either 0 or 1. Based on this Results1.txt or Results2.txt file is chosen to get the price per share.

#buyShare() fn checks for the various criteria to facilitate the share purchase. If all criteria are met, a new node is added or existing node is updated in the linked list. Total amount of the share purchase value is deducted from the available cashBalance. "stock_transaction_history.txt" is updated with the transaction details and printed on the screen as well.
#sellShare() function does a similar thing as the above fn but also remove that node from the linked list if the number of shares after subtraction become zero through private utility function removeNode(). 

#printHistory() prints the transaction history by reading the "stock_transaction_history.txt" file till eof. It ignores the header line by positing the pointer at 87 bytes position using seekg() fn. 

#displayPortfolio() calculates the portfolio value of all the existing shares on the linked list by taking the current price per share randomly from of the results text file added with the total cashBalance.
#updateCashPortfolio() fn updates the “cash_balance.txt” file with the time(in seconds since 1990), the current total portfolio value & cashBalance. It is called only from the main function when the program exit.
#viewPortfolioGraph() fn displays the graph of the total portfolio value with respect to the time reference. The“cash_balance.txt” file is read and the time & portfolio values are stored in arrays which are the passed to mxArrays variables also recognized by matlab. 

#The main file defines two function each for stock account transaction and balance account transaction. It also creates the “cash_balance.txt”
#If it doesn’t exist already by placing the header line and a line with the initial cash balance of $10000. This value is read in the constructor fn of the base class Account.

#The program generates three text file
#•	  “cash_balance.txt”
#•	  "stock_transaction_history.txt"
#•	  “bank_transaction_history.txt”
