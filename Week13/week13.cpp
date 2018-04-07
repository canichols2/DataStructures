#include "person.h"
#include "interfaces.h"
#include "bst.h"
#include <iostream>
#include <fstream>
// #include <ifstream>

int main(char const *argv[])
{
   Person *pPtr;
   BST<Person> arr;
   char filename[50];
   if(argv)
   {
      // filename = argv[0];
      strcpy(filename,argv[0]); 
   }
   else
   {
      cout << "filename: ";
      cin >> filename;
   }

   try
   {
      ifstream file(filename);
      int level;
      string type;
      string data;
      while (file >> level >> type)
      {
         switch (level)
         {
         case 0:
            if(type[1]=='I')
            {
               pPtr = new Person();
               arr.insert(pPtr);
            }
         case 1:
            break;
         case 2:
            break;
         default:
            break;
         }
      }
   }
   catch (const std::exception&)
   {
      
   }






   return 0;
}
