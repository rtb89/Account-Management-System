//Name:Rachana_T_Bhatia
//Course: 16:332:503, PM for Financial Applications and Numerical Computing
//CPP file for Derived class Stock Account :Account management systme: Date Apr_27_2015

# include "stockAccount_R_Bhatia.h" 
# include "Node.h"
#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"        //Include the mex header file
#include <iomanip>  // includes the fuction prototype setprecision, static_cast
#include <time.h>   // includes the function prototype for time(0) 
#include <cstdlib>  //includes the function prototype of rand()
#include <fstream>  //includes the file functions
#include <iostream>
using namespace std;
#include <engine.h>   //Include the matlab engine header file

//constructor Function-initialize the linked list from the transaction history
StockAccount::StockAccount():Account()
{ string s,t,sec;        //Variables to store the data from the transaction file
int n;
double p,v,pValue;
bool updated=false;
	myHead=NULL;myTail=NULL;
	mySize=0; //set the size of the linked list as 0
	//Create the linked list of shares from the Transaction history
	 ifstream myFile("stock_transaction_history.txt ",ios::in);
     if(myFile.fail()) //To check if the stock transaction File already exists
	 {
		ofstream accountFile("stock_transaction_history.txt ",ios::out);
        accountFile<<left<<setw(14)<<"Stock_symbol"<<setw(14)<<"No_of_Shares"<<setw(13)<<"Transaction"<<setw(17)<<"Price_per_Share"<<setw(12)<<"Total_Value"<<setw(15)<<"Time(Seconds)"<<endl;
		
	 }

//Creating a linked list from the previously saved Transaction History
	 myFile.seekg(87);       //put the pointer in the text file to the second line to read data
	 while(myFile>>s>>n>>t>>p>>v>>sec) //read the data from the text file until eof
	 { 
		 //if there is already data in the linked list, add the new read data to the node with the same Stock Symbol 
		 if (mySize!=0) 
	         { 	Node *currentNode;
               currentNode=myHead;
              while (currentNode!=0) 
               {   if (currentNode->stockSym==s) 
                  {   if (t=="Purchase")
			     currentNode->stockNumber=currentNode->stockNumber+n;
		         else { currentNode->stockNumber=currentNode->stockNumber-n; 
			         if (currentNode->stockNumber == 0) {removeNode(s);}
			      }
		      updated=true; 
		   }
            currentNode=currentNode->rightptr;
         }
      	}
//If there doesn't exist any node with the same symbol , then add the new node
   if ((mySize==0 ) || (updated==false))
   {    Node *newnode = getnewNode(s,n);      //get a new node using te utility function
	if (mySize==0)                //adding the node to the empty list
    myHead=myTail=newnode;
	else
    {	 
	  newnode->leftptr=myTail;
	  myTail->rightptr=newnode;
	  myTail=newnode;
     }
mySize++; //Increment the size of the linked list
   }
  }

}

StockAccount::~StockAccount()                                //Destructor to delete all the new nodes created
{  if (mySize !=0) {
	cout<< "\nDistroying Nodes";
	Node *currentNode;
	Node *tempNode;
	currentNode= myHead;

	while (currentNode!=0)                  // delete remaining nodes
	{
	tempNode=currentNode;
	cout<< "\n"<<tempNode-> stockSym<<"\t"<< tempNode->stockNumber;
	currentNode=currentNode->rightptr;              //Traversing through linked nodes till the end of the list
	delete tempNode;                          //delete the node
	--mySize;                                //decrease the size of the list after each deletion
	 }
}
cout<<"\nAll Nodes Destroyed\n";
}

//Function to get the stockPrice from the Results_1 & Result_2 text file 
double StockAccount::stockPrice(string sym)
{
int i=0;
	string date,vSym;  
	double vPrice;
	 srand(time(0));  //Set the current time as seed
	 int A= rand()%2; //Variable A randomly gets the value 0 or 1
    if(A==0) 
//Read the Result_1.txt file if value of A is 0
	  { ifstream stockFile("Results_1.txt", ios::in);
	         if(!stockFile)
	            {  cerr<<"File could not be opened"<<endl;
	              exit(1);
	            }
	       while(stockFile>>vSym>>vPrice>>date)
		   { if (sym==vSym) 
		      { return vPrice;}
		   }
	}
	//Read the second file otherwise
	else  { ifstream stockFile("Results_2.txt", ios::in);
		       if(!stockFile)
	             {  cerr<<"File could not be opened"<<endl;
	              exit(1);
	              }
			 while(stockFile>>vSym>>vPrice>>date)
          	 { if (sym==vSym) 
			      {return vPrice;}
		     }
	      }
	cout <<"\nError: Stock price could not be found\n";
	
}

// Function to buy shares
void StockAccount::buyShare()
{  bool updated=false;
   double price, maxPrice,totalAmount;
   int numberofShares;
   string symb;
   cout<<"\nEnter the symbol of the stock to be purchased:    ";
   cin >> symb;
   price=stockPrice(symb);   //Get the value of stock price using the function
   // Displaysplay error message if the Stock doesn't exist in result file
   if (price==0.0) { cerr<< "\nTransaction Failed-Share not available for purchase\n"; return;}

   cout<<"\nEnter the maximum price per share willing to pay:  $ ";  //Get the maximum price
   cin >> maxPrice;
   //Display the Error message when the actual price of share is greater than the expected price
      if (maxPrice<price) 
   { cerr<< "\nTransaction Failed-Price Per Share of "<<symb<<", $ "<<price<< " is greater than the expected share price\n"; 
             return;}  

     cout<<"\nEnter the number of shares willing to purchase:  ";
	 cin >> numberofShares;
   totalAmount= numberofShares*price; //Calculate the total value of the shares to purchase
   //Display the error message if the total price is greater than the available balance in account
   if (totalAmount > Account::cashBalance)
   { cout<<"\nTransaction Failed-Shares cann't be puchased as insuffecient balance in the account\n";
     return;}

  // Calculate the cashbalance buy deducting the amount spent on purchasing the share
   Account::cashBalance=Account::cashBalance-totalAmount;
   
 //Update the information of stock purchase in the Linked list
    if (mySize!=0) 
	{ 	Node *currentNode;
   currentNode=myHead;
   //Update the excisting node of the linked list with the same stock symbol by adding the number of shares purchased
   while (currentNode!=0) 
   {   if (currentNode->stockSym==symb) 
   { currentNode->stockNumber=currentNode->stockNumber+numberofShares;  updated=true;}
   currentNode=currentNode->rightptr;
   }
	}
	//If there is no node with the current stock symbol, then add a new node
   if ((mySize==0 ) || (updated==false))
   {
    Node *newnode = getnewNode(symb,numberofShares);      //get a new node using te utility function
	if (mySize==0)                //adding the node to the empty list
    myHead=myTail=newnode;
	
	else
  {	 
	  newnode->leftptr=myTail;
	  myTail->rightptr=newnode;
	  myTail=newnode;
  }
mySize++;  //Increase the size of the linked list
   } //Linked list updated

    time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
    timeinfo = localtime(&seconds);
   // cout<<"The current local time and date is:"<<asctime(timeinfo); 
	string aType= "Purchase";
//Update the Transaction History file with the purchase transcation
ofstream accountFile("stock_transaction_history.txt ",ios::app);
accountFile<<left<<setw(14)<<symb<<setw(14)<<numberofShares<<setw(13)<<aType<<setw(17)<<price<<setw(11)<<totalAmount<<setw(20)<<seconds<<endl;
 //Output the Result
 cout<<"\n****Transaction Successfull**\n";
 cout<<numberofShares<<" of "<<symb<<" Shares purchased succesfully at a per share "<<price<<endl;
 cout<<"Amount Deducted from account "<<totalAmount<<" at "<<asctime(timeinfo)<<endl;
}
 
void StockAccount::sellShare()
{  bool updated=false;
   double price, minPrice ,totalAmount;
   int numberofShares;
   string symb;
   // If the portfolio has no shares then display the error output
   if (mySize==0) 
   { cout <<"\nSorry: No share available for sell in the portfolio account\n"; return;}
   std::cout<<"\nEnter the symbol of the stock willing to sell\n";
   std::cin >> symb;
   price=stockPrice(symb);
   if (price==0.0) { cerr<< "\nSorry.Transaction Failed.Share not available for selling\n"; return;}

    cout<<"\nEnter the minimum selling price per share:  $ ";
   cin >> minPrice;
   if (minPrice>price) { cerr<< "\nSorry.Current price Per Share of "<<symb<<", $"<<price<< " is less than the expected share selling price\n"; 
             return;}
   	  	
	Node *currentNode;
   currentNode=myHead;
   while (currentNode!=0) 
   {   if (currentNode->stockSym==symb) 
   { updated=true;break;}
   currentNode=currentNode->rightptr;
   }
   // Check if the particular share is in the portfolio
	 if (updated==false)
	{ cout<<"\nSorry: This Share can't be sold as it is not available in the portfolio account\n"; return;}

    cout<<"\nEnter the number of shares willing to sell:  ";
	cin >> numberofShares;
	//Check if there is suffecient number of share willing to sell
	if (currentNode->stockNumber < numberofShares)
	{ cout<<"\nSorry:Transaction Failed. Number of shares available is not enough\n"; return;
	}
    
	
   currentNode->stockNumber=currentNode->stockNumber-numberofShares;
   totalAmount= numberofShares*price; 
    Account::cashBalance=Account::cashBalance+totalAmount;
	//If the total number of shares is 0 after the sell , then remove the node corresponding to that share through the utility function
   if (currentNode->stockNumber == 0) {removeNode(symb);}  
 
   time_t seconds;
    seconds = time(NULL);
   tm * timeinfo;
   timeinfo = localtime(&seconds);
   string aType= "Sell";
	
  //Update the Transaction history with the current transaction details
ofstream accountFile("stock_transaction_history.txt ",ios::app);
accountFile<<left<<setw(14)<<symb<<setw(14)<<numberofShares<<setw(13)<<aType<<setw(17)<<price<<setw(11)<<totalAmount<<setw(20)<<seconds<<endl;

  //Output the Result
 cout<<"\n****Transaction Successfull**\n";
 cout<<numberofShares<<" of "<<symb<<" Shares sold succesfully at a per share "<<price<<endl;
 cout<<"\nAmount added to the account "<<totalAmount<<" at "<<asctime(timeinfo)<<endl;
}

//Pure virtual  function overriden
//To print the history of transaction from the Transaction history text file
void StockAccount::printHistory() const
{  string s,t,sec;
   int n;
   double p,v;
cout<<"\n**************************Stock Transaction History****************************\n\n";
cout<<left<<setw(13)<<"Stock_symbol"<<setw(13)<<"No_of_Shares"<<setw(12)<<"Transaction"<<setw(17)<<"Price_per_Share"<<setw(12)<<"Total_Value"<<setw(15)<<"Time(Seconds)\n";
ifstream myFile1("stock_transaction_history.txt",ios::in);
if(!myFile1)
	 {  cerr<<"File could not be opened"<<endl;
	 exit(1);
	 }
myFile1.seekg(87);
//cout<<myFile1.tellg();
while(myFile1>>s>>n>>t>>p>>v>>sec)
  {  cout<<left<<setw(13)<<s<<setw(13)<<n<<setw(12)<<t<<setw(17)<<p<<setw(12)<<v<<setw(15)<<sec<<endl;
  }
}//end of function

//Function to display the current total portfolio and cash balance
void StockAccount::displayPortfolio()
{
double p, v,totalValue;
cout<<"\nCash_Balance =  $ "<<Account::cashBalance<<endl;

Node * currentNode= myHead;
totalValue=0.0;
if (mySize==0)
    {cout<<"\nNo shares available in the porfolio account\n";}
else
{
     while (currentNode!=0) 
    {   cout<<setw(18)<<left<<"CompanySymbol"<<setw(18)<<"Number"<<setw(18)<<"PricePerShare"<<setw(18)<<right<<"TotalValue\n";
        p=stockPrice(currentNode->stockSym);  //Price per share of the Stock
        v=p*currentNode->stockNumber;   //Value of the portfolio cooresponding to a particular share 
        totalValue=totalValue + v;  //Calcualte the portfolio value corresponding to all shares in account
       //display the price and total current value of the shares
		cout<<setw(18)<<left<<currentNode->stockSym<<setw(18)<<currentNode->stockNumber<<setw(18)<<p<<setw(18)<<right<<v<<endl;
        currentNode=currentNode->rightptr;

    }
}
cout<<"\nTotal Portfolio value:  $"<<totalValue+Account::cashBalance<<endl;
}//end of function

//Function to update the text file with the Cash balance and totalpotfolio value 
void StockAccount::updateCashPortfolio()
{    time_t seconds;
    seconds = time(NULL);
	double p, v,totalValue,totalPortfolioValue;
Node * currentNode= myHead;
totalValue=0.0;
//Traversing through the linked list
while (currentNode!=0) 
{
p=stockPrice(currentNode->stockSym);  //Price per share of the Stock
v=p*currentNode->stockNumber;   //Value of the portfolio of the
totalValue=totalValue + v;
currentNode=currentNode->rightptr;
}
totalPortfolioValue=totalValue+Account::cashBalance;
cout<<"\nTotal Portfolio value:  $"<<totalValue+Account::cashBalance<<endl;

// Update the cash_balance_text file
	ofstream myFile1("cash_balance.txt",ios::app);
     if(!myFile1)
	 {  cerr<<"File could not be opened"<<endl;
	 exit(1);
	 }
	 myFile1<<setw(20)<<left<<seconds<<setw(18)<<left<<totalPortfolioValue<<setw(18)<<left<<Account::cashBalance<<endl;
}

//Plot the graph of portfolio value as a function of time using matlab engine
 void StockAccount::viewPortfolioGraph()
 {   engine *ep;                           //Declaring Pointer to the engine
		ep = engOpen(NULL);
		if (ep == NULL)
		{
			std::cout << "Error: Not Found"<< endl;
	             exit(1);
		}
	 
	 int size=0;
 double data1,data2, data3, a[50],b[50];   //defining array to store the value of portfoli and time refernce  from cash_balance text file
 double refData1=1430030204 ; //define the refernce time in seconds
 //read the data from the text file
	 ifstream myFile1("cash_balance.txt",ios::in);
     if(!myFile1)
	 {  cerr<<"File could not be opened"<<endl;
	 exit(1);
	 }
	 myFile1.seekg(87);
	while(myFile1>>data1>>data2>>data3)
	{  	a[size]=data1-refData1;  // Input the relative time in seconds in array a
		b[size]=data2;  //Input the portfolio value in b
		size++;
		cout<<data1<<"\t"<<data2;
	}
	if (size!=0)//If the text file is not empty
 {
	 mxArray *mxa;     //declaring "matrix array" data type which is recognized by both C++ and matlab 
	mxArray *mxb;      //declaring "matrix array" data type which is recognized by both C++ and matlab 
	mxa = mxCreateDoubleMatrix(1, size, mxREAL);     //Allocate the space to matrix array
	mxb = mxCreateDoubleMatrix(1, size, mxREAL);    //Allocate the space 
	memcpy((void *) mxGetPr(mxa), (void *)a, sizeof(double)*size);   //copy the content of array "a" to matrix array mxa
	memcpy((void *) mxGetPr(mxb), (void *)b, sizeof(double)*size);  //copy the content of array "a" to matrix array mxa
	engPutVariable(ep, "a", mxa);  //Put the matrix array to variable "a" in Matlab engine
	engPutVariable(ep, "b", mxb);   //Put the matrix array to variable "b" in Matlab engine
	//engEvalString (ep, "xlim([1430030204  1430040204]);" );
	engEvalString(ep, "plot(a,b);") ;  //plotting the value stored in variable a & b
	//Lable the graph
    engEvalString(ep, "xlabel('Time(seconds_1990)'),ylabel('Portfolio_Value'),title('Plot of Variation in Portfolio value with time');") ; 
	//10 seconds of pause to view the graph wondow in Matlab before closing the engine
   engEvalString(ep, "pause(10.0);");  
	
  engClose(ep);  //Close the matlab engine
 }
 return ; //indiacates a successful termination

 }
  
//Utility functions 

// Function to get a new node
Node * StockAccount::getnewNode(string &s,int &am)
 {  return new Node(s,am);       //return a new node
 }

//function to remove a Node with the the stock symbol value
void StockAccount::removeNode(string &sym)
 {
	 if (mySize==0) cout <<"\nThe item no. doesn't excist as the List is Empty\n";
	 else{ Node *currentNode;
   currentNode=myHead;
   while (currentNode!=0) 
   {   if (currentNode->stockSym==sym) //searching the node corresponding to the input item number
       {  if (currentNode==myHead)         // Check the condition if the corresponding node is the first node of the list
              {  Node *temp1Node=myHead;
                if (myTail==myHead)
	            myTail=myHead=0;
               else 
				   myHead=myHead->rightptr;
				myHead->leftptr=0;
             delete temp1Node;
              --mySize;
			 return ;
         }
	   else if (currentNode==myTail) // Check the condition if the corresponding node is the last node of the list
	   {
		   Node *temp2Node=myTail;
		   myTail=myTail->leftptr;
		   myTail->rightptr=0;
               delete temp2Node;
                 --mySize;
			return ;
       }

	   else 
	   {
		  Node *tempNode = currentNode;
		  currentNode->leftptr->rightptr=currentNode->rightptr;
		  currentNode->rightptr->leftptr=currentNode->leftptr;
          delete tempNode;
         --mySize;
		  return;
        }
   }
   currentNode=currentNode->rightptr;
	 }
   cout<<"\nItem not deleted as it doesn't exist in the list\n";

 }
}

