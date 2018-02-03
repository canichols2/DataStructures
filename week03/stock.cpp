/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"   // for Dollars defined in StockTransaction
using namespace std;

struct transaction{
   int count;
   Dollars price;
   Dollars difference;
};
// declare Methods
string getWord(istream& in);
string getNum(string str);
void displayCopy(Queue<transaction> b,Queue<transaction> s);

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
      << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";
   string inputString;
   string option,countString,valueString;
   Queue<transaction> buyQueue = Queue<transaction>();
   Queue<transaction> sellQueue = Queue<transaction>();
   for(;;){
      option = "";
      cout << "> ";
      cin >> option;
      if(option == "buy" )
      {
         transaction newTran;
         cin >> newTran.count;
         cin >> newTran.price;
         buyQueue.push(newTran);
      }
      else if(option == "sell" )
      {
         int toSell;
         Dollars price;
         cin >> toSell;
         cin >> price;
         while(toSell){
            transaction &B = buyQueue.front();
            if(toSell < B.count){
               transaction S;
               S.price = price;
               S.count = toSell;
               B.count -= toSell;
               S.difference += (S.price*toSell)-(B.price*toSell);
               toSell=0;
               sellQueue.push(S);
            }
            else if(toSell == B.count){
               transaction S;
               S.price = price;
               S.count = toSell;
               S.difference += (S.price*toSell)-(B.price*B.count);
               buyQueue.pop();
               toSell=0;
               sellQueue.push(S);

            }else if(toSell > B.count){
               transaction S;
               S.price = price;
               S.difference += (S.price*B.count)-(B.price*B.count);
               buyQueue.pop();
               toSell -= B.count;
               S.count = B.count;
               sellQueue.push(S);
            }
         }

      }
      else if(option == "display" )
      {
         displayCopy(buyQueue,sellQueue);
      }
      else if(option == "quit" ) 
      {
         break; 
      }
   }

}
string getWord(istream& in) 
{
    char c;
    string word;
    while( !in.eof() ) 
    {
        c = in.get();
        if( c == ' ' || c == '\t' || c == '\n' ) break;
        word += c;
    }
    return word;
}

string getNum(string str){
   string outString="";
   char money = '$';
   char decimal = '.';
   for (int i = 0;i < str.length();i++){
      if(str[i] != money && str[i] != decimal) outString += str[i];
   }
   return outString;
}

void displayCopy(Queue<transaction> b,Queue<transaction> s)
{
   if(!b.empty())
   cout << "Currently held:\n";
   //for each in bought
   while(!b.empty()){
      cout << "\tBought " << b.front().count << " shares at " << b.front().price << endl;
      b.pop();
   }
   Dollars proceeds = 0;
   if(!s.empty()){
      cout << "Sell History:\n";
   }
   //for each in sold
   while(!s.empty()){
      cout << "\tSold " << s.front().count << " shares at " << s.front().price << " for a profit of " << s.front().difference << endl;
      proceeds +=  s.front().difference;
      s.pop();
   }
   cout << "Proceeds: " << proceeds << endl;
}
