#ifndef WHOLE
#define WHOLE
#include <iostream>
#include "list.h"        // for LIST
using namespace std;

/***********************************
 * WholeNumber class
 * used to hide the implementation.
 * Uses linked lists to have infinate sized ints.
 * *********************************/
class WholeNumber
{
   private:
      List<int> number;
      int val(ListIterator<int> it){
         if(it != NULL)
            return *it;
         return 0;
      }
   public:
      WholeNumber(){
         number.push_back(0);
      }
      WholeNumber(int num){
         number.push_back(num);
      }
      WholeNumber(const WholeNumber& num){
         //calls list assignment operator
         number = num.number;
      }

      /**********************
       * Whole Number += Operator overload
       * Used to add one whole number to another
       * ****/
      WholeNumber& operator+=(WholeNumber& rhs){
         ListIterator<int> itLhs = number.rbegin();
         ListIterator<int> itRhs = rhs.number.rbegin();
         List<int> newList = List<int>();
         int over = 0;
         while(itLhs != NULL || itRhs != NULL){
            int total = val(itLhs) + val(itRhs) + over;
            over = total / 1000;
            int newTotal = total % 1000;
            newList.push_front(newTotal);
            itLhs--;itRhs--;
         }
         if(over > 0){
            // make new node
            newList.push_front(over);
         }
         number = newList;
         return *this;
      }
      WholeNumber& operator=( WholeNumber& rhs){
         number = rhs.number;
         return *this;
      }
      WholeNumber operator+( WholeNumber& rhs){
         WholeNumber tmp = *this;
         tmp += rhs;
         return tmp;
      }
      friend ostream& operator << (ostream& out,const  WholeNumber &rhs);
};

/**********************************
 * OSTREAM Extraction Operator Overload
 * used to cout the whole number as a string.
 * ********************************/
ostream& operator << (ostream& out,const  WholeNumber &rhs)
{ 
   WholeNumber tmp = WholeNumber(rhs); 
   ListIterator<int> it = tmp.number.begin();
   //Display the first set without leading 0's
   out << *it;
   it++;
   if(it != NULL)
      out<<",";
   while (it != NULL){
      if(*it < 100) 
         out << 0;
      if(*it < 10) 
         out << 0;
      out << *it;
      it++;
      if(it != NULL)
         out<<",";
   }

   return out;
}
#endif