/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "whole.h"       // for WholeNumber class
using namespace std;

WholeNumber fib(int);


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers

   //Create a linked list
   // List<WholeNumber> list = List<WholeNumber>();
   // list.push_back(WholeNumber(1));
   List<WholeNumber> list = List<WholeNumber>();
   list.push_back(WholeNumber(1));
   

   for(int i = 0; i < number; i++){
      //get end of list
      ListIterator<WholeNumber> it = list.begin();
      cout << "\t"<< *it << endl;
      if(list.size() > 1)
      {
         WholeNumber tmp1 = *(it++);
         list.push_front(tmp1 + *it);
         list.remove(list.rbegin());
      }
      else
      {
         list.push_front(*it);
      }
   }
   
   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   
   // your code to display the <number>th Fibonacci number
   cout << "\t" << fib(number)<<endl;

}

WholeNumber fib(int n)
{
   List<WholeNumber> list = List<WholeNumber>();
   list.push_back(WholeNumber(1));

   for(int i = 1; i < n; i++){
      ListIterator<WholeNumber> it = list.begin();
      if(list.size() > 1)
      {
         WholeNumber tmp1 = *(it++);
         list.push_front(tmp1 + *it);
         list.remove(list.rbegin());
      }
      else
      {
         list.push_front(*it);
      }
   }
   
   return *(list.begin());
}