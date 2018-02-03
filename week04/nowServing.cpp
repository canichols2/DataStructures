/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   string command;
   string csClass;
   string name;
   int min;
   int curMin=0;
   struct student { student(){name="";csClass="";min=1;} student(string n,string c, int m){name = n;csClass = c; min = m;} string name; string csClass; int min; };
   student currentStudent;
   Deque<student> queue;
   do
   {
      cout << "<"<< curMin++ << "> ";
      cin  >> command;

      try
      {
         if (command == "!!")
         {
            cin >> csClass >> name >> min;
            queue.push_front(student(name,csClass,min) );
         }
         else if (command == "none")
         {
            // Do nothing
         }
         else if (command == "finished")
         {
            break;
         }
         else
         {
            csClass = command;
            cin >> name >> min;
            queue.push_front(student(name,csClass,min) );
         }
         //TODO: Decrement current student time
         currentStudent.min--;
         //TODO: if current studnet time up, remove and grab new student.
         if(currentStudent.min <= 0 && queue.size()){
            currentStudent=queue.front();
            queue.pop_front();
         }
         if(currentStudent.min > 0){
            //TODO: output the current student
            cout << "\tCurrently serving " << currentStudent.name << " for class "<<currentStudent.csClass<<". Time left: "<< currentStudent.min<<endl;
         }
      }
      catch (const char * e)
      {
         cout << '\t' << e << endl;
      }
   }
   while (command != "!");

   // end
   cout << "End of simulation\n";
}


