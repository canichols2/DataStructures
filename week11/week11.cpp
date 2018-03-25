/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
* Author:
*    Cody Nichols
* Summary: 
*
************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>
#include <vector>
#include <cstring>         // for strcmp
#include <iomanip>         // for SETW
#include "heap.h"
#include "merge.h"

using namespace std;

/**********************************************************************
 * MAIN
 * Gets the sort type and filename from the command line. If the sort type
 * or filename are not entered on the command line, the user will be
 * prompted for the sort type and/or filename.
 * Call the appropriate sort to sort the data contained in the vector or
 * linked list and display the sorted data to the console.
 ***********************************************************************/
int main(int argc, const char* argv[])
{
   char sortType[10];
   char fileName[50];
   if (argc == 1)
   {
      cout << "Which sort merge or heap? ";
      cin >> sortType;
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }
   else if (argc == 2)
   {
      strcpy(sortType,argv[1]);
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }
   else if (argc == 3)
   {
      strcpy(sortType,argv[1]);    
      strcpy(fileName,argv[2]);
   }
   
   if (strcmp(sortType, "heap") == 0)
   {
         // TO DO: read the file into a vector
      vector<int> vect;
      int tmp = 0;             // Adding an empty object into position 0 of vector
      vect.push_back(tmp);     // Will allow me to use 1-N instead of 0-N
      ifstream file(fileName);

      while (file >> tmp)
      {
         vect.push_back(tmp);
      } 
         //        call your heapsort passing the vector as a parameter
      heapSort(vect);
         //        output the sorted vector to the console.
      int size = vect.size();
      for(int i = 1; i < size ;i++)
      {
         cout << setw(3) << vect[i];
         if(i % 10 == 0)
            cout << endl;
      }
   }
   else if (strcmp(sortType, "merge") == 0)
   {
         // TO DO: read the file into a linked list
         //        call your natural merge sort
         //        output the sorted linked list to the console.
         list<int> list1;
         int tmp = 0;
         ifstream file(fileName);
         while(file >> tmp)
         {
            list1.push_back(tmp);
         }

         mergeSort(list1);

         int size = list1.size();
         list<int>::iterator it = list1.begin();
         for(int i = 1; i <= size ;i++)
         {
            cout << setw(3) << *it;
            ++it;
            if(i % 10 == 0)
               cout << endl;
         }

         // cout << "sorted list: ";
         // for(list<int>::iterator it = list1.begin();
         //       it != list1.end();
         //       it++)
         //       {
         //          cout << *it << " ";
         //       }
         // cout << endl;

   }
   else
   {
      cout << "\nInvalid sort name - must be 'heap' or 'merge'" << endl;
   }
   
   return 0;
}
