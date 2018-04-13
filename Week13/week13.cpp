
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>         // for strcmp
#include <iomanip> 
#include "models.h"
#include "interfaces.h"
#include "bst.h"
#include "vector.h"
#include "helpers.h"
#include <iostream>
#include <fstream>
// #include <ifstream>

//Prototypes:
int extractInt(string str);

int main(int argc, char const *argv[])
{

   Person     *PersonPointer;
   FamilyUnit *FamilyPointer;
   // Vector<FamilyUnit> FAMS = Vector<FamilyUnit>(100);
   // Vector<Person>     INDI = Vector<Person>(150);
   FamilyUnit FAMS[100] ;
   Person     INDI[150] ;
   int lastPerson;
   int lastFamily;
   BST<fakePointer<Person> > orderedPeople;

   //Get Filename
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


   //Open GED file
   //Read in values
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
         trim(data);
         switch (level)
         {
         case 0:
            if(type[0] == '@' && type[1] == 'I')
            {
               int index = extractInt(type);
               INDI[index] = Person();
               PersonPointer = &INDI[index];
               zeroLevelType = "INDI";
               if(index > lastPerson)
                  lastPerson = index;
            }
            if(type[0] == '@' && type[1] == 'F')
            {
               int index = extractInt(type);
               FAMS[index] = FamilyUnit();
               FamilyPointer = &FAMS[index];
               zeroLevelType = "FAMS";
               if(index > lastFamily)
                  lastFamily = index;
            }
            break;
         case 1:
            firstLevelType = type;
         case 2:
            secondLevelType = type;
         case 3:
            // thirdLevelType = level;
            if(zeroLevelType  == "INDI")
            {
               if(firstLevelType == "FAMC")
               {
                  PersonPointer->familyIndex = extractInt(data);
               }
               if(firstLevelType == "NAME")
               {
                  if(secondLevelType == "GIVN")
                     PersonPointer->givenName = (data);
                  if(secondLevelType == "SURN")
                     PersonPointer->surName = (data);
               }
               if(firstLevelType == "BIRT")
               {
                  if(secondLevelType == "DATE")
                  {
                     //FIXME: fix SetDate function for dates without month/day
                     PersonPointer->setDate(data);
                  }
               }
            }
            if(zeroLevelType == "FAMS"){
               if(firstLevelType == "HUSB" || firstLevelType == "WIFE")
               {//Parents
                  FamilyPointer->addParent(extractInt(data));
               }
               if(firstLevelType == "CHIL")
               {
                  FamilyPointer->addChild(extractInt(data));
               }
            }
            break;
         default:
            break;
         }
      }
      file.close();
   //END Open GED file
   //Read in values




      ofstream outFile;
      outFile.open("sorted.dat ");

      //add vector of persons to ordered list (bst?)
      for(int i = 1;i <= lastPerson;  i++)
      {
         fakePointer<Person> fPPer = fakePointer<Person>(INDI[i]);
         if(personExits( *(fPPer.obj) )/*TODO: Check if vector actually has an object*/)
         {
            orderedPeople.insert( fPPer );
         }
      }

      



      //Write Ordered to outfile
      for(
         BSTIterator<fakePointer<Person> > it = orderedPeople.begin();
         it != orderedPeople.end();
         it++
      )
      {
         // outFile << (*it).obj->toString() << endl;
         outFile << *it << endl;
      }
      outFile.close();


      Deque<Person> pDeck;
      int curGen = -1;

      INDI[1].generation = 0;
      pDeck.push_back( INDI[1] );
         /* // temp output */ //ofstream outFile2; outFile2.open("pedigree.txt");

       while (!pDeck.empty() )
       {
          fakePointer<Person> curPer = pDeck.front();
         int curFamIndex = (*curPer).familyIndex;
         //Output
         switch((*curPer).generation)
         {
            case 0:
               cout << "The Ancestors of " << (*curPer).givenName << " " << (*curPer).surName << ":\n";
               break;
            case 1:
               if ((*curPer).generation != curGen)
                  cout << "Parents:\n";
               break;
            case 2:
               if ((*curPer).generation != curGen)
                  cout << "Grandarents:\n";
               break;
            case 3:
               if ((*curPer).generation != curGen)
                  cout << "Great Grandarents:\n";
               break;
            case 4:
               if ((*curPer).generation != curGen)
                  cout << "2nd Great Grandarents:\n";
               break;
            case 5:
               if ((*curPer).generation != curGen)
                  cout << "3rd Great Grandarents:\n";
               break;
            case 6:
               if ((*curPer).generation != curGen)
                  cout << "4th Great Grandarents:\n";
               break;
            case 7:
               if ((*curPer).generation != curGen)
                  cout << "5th Great Grandarents:\n";
               break;
               
         }
         //End Output

          curGen = (*curPer).generation;
         if(curGen != 0)
            cout << "\t"<< *curPer << endl;
         if(curFamIndex >= 0)
         {
            FamilyUnit *family = &(FAMS[curFamIndex]);
            ListIterator<int> curPar = family->Parents.begin();
            while (curPar != NULL)
            {
               INDI[(*curPar)].generation = (*curPer).generation + 1;
               pDeck.push_back( INDI[(*curPar)] );
               curPar++;
            } 
         }
         pDeck.pop_front();

       }
         // outFile2.close();

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