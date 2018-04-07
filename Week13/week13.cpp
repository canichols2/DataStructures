
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>         // for strcmp
#include <iomanip> 
#include "person.h"
#include "interfaces.h"
#include "bst.h"
#include "vector.h"
#include <iostream>
#include <fstream>
// #include <ifstream>

//Prototypes:
int extractInt(string str);

int main(int argc, char const *argv[])
{
   Person     *PersonPointer;
   FamilyUnit *FamilyPointer;
   Vector<FamilyUnit> FAMS = Vector<FamilyUnit>(100);
   Vector<Person>     INDI = Vector<Person>(150);
   char filename[50];
   if(argc)
   {
      // filename = argv[0];
      strcpy(filename,argv[1]); 
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
      string zeroLevelType;
      string firstLevelType;
      string secondLevelType;
      while (file >> level >> type)
      {
         // string data = 
         getline(file,data);
         switch (level)
         {
         case 0:
            if(type[0] == '@' && type[1] == 'I')
            {
               int index = extractInt(type);
               INDI[index] = Person();
               PersonPointer = &INDI[index];
               zeroLevelType = "INDI";
            }
            if(type[0] == '@' && type[1] == 'F')
            {
               int index = extractInt(type);
               FAMS[index] = FamilyUnit();
               FamilyPointer = &FAMS[index];
               zeroLevelType = "FAMS";
            }
            break;
         case 1:
            firstLevelType = type;
         case 2:
            secondLevelType = type;
         case 3:
            // thirdLevelType = level;
            if(zeroLevelType  == "FAMS")break;
            if(firstLevelType == "NOTE")break;
            if(firstLevelType == "NAME" && secondLevelType == "GIVN")
               PersonPointer->givenName = data;
            if(firstLevelType == "NAME" && secondLevelType == "SURN")
               PersonPointer->surName = data;
            if(firstLevelType == "BIRT" && secondLevelType == "DATE")
            {
               PersonPointer->setDate(data);
            }
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


int extractInt(string str)
{
   string newStr="";
   int out = atoi (str.c_str());
   for (int i = 0; i < str.length(); i++)
   {
      if(isdigit(str[i]))
         newStr += str[i];
   }
   return stoi(newStr);
}