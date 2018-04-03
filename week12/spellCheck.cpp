/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "spellCheck.h"
#include "hash.h"
#include "list.h"
#include "bst.h"
using namespace std;






class strHash: public Hash<string>
{
public:
   strHash(int cap=300):Hash<string>(cap){}
   strHash(const strHash &rhs):Hash<string>(rhs){}

   int hash(const string & str) const
   {
      // this one uses prime numbers which i heard is a good idea
      // // This yeilded the lowest maximum length on any one bucket (lowest maximum I could get was 42 in any trial.)
      // //  and the lowest empty slots. (only based on capacity, higher capacity higher empty slots)
      int prime = 17;
      return (int)str.length() * ( (int)str[0] + prime * (int)str[str.length()-1] ) / prime % capacity();

      //this is a bit cleaner, but still doesn't give any benefit
      int hash = 13; //prime number
      for(int i = 0; i < str.length(); i++)
      {
         hash = hash * 31 + str[i];
      }
      return hash % capacity();
      // First attempt got too convoluded and didn't give any extra benefit
      return ( ( (int)str[0] + (int)str[ str.length() -1]) * str.length() ) % capacity();
   }
};

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   BST<string> misspelled;
   strHash SH;
   ifstream dict("dictionary.txt");
   string word;
   while(dict >> word )
   {
      SH.insert(word);
   }
   // SH.display();   

   string filename;
   cout << "What file do you want to check?\n";
   cin >> filename;


   ifstream pass(filename.c_str());
   while(pass >> word)
   {
      string data = word;
      for(int i =0; i < data.length(); i++)
      {
         data[i] = tolower(data[i]);
         data[i];
         // it.tolower();
      }
      
      // transform(data.begin(), data.end(), data.begin(), ::tolower);
      if(!SH.find(data))
      {
         if(misspelled.find(word) == NULL)
            misspelled.insert(word);
      }
   }
   if(misspelled.size() == 0)
   {
      cout << "File contains no spelling errors\n";
      return;
   }
   cout << "Misspelled: " ;
   for(BSTIterator<string> it = misspelled.begin(); it != misspelled.end(); )
   {
      /* code */
      cout << *it;
      it++;
      if(it != NULL)
         cout << ", ";
   }
}


