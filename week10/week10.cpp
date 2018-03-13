/***********************************************************************
* Program:
*    Week 10, Map
*    Brother Helfrich, CS 235
* Author:
*    Cody Nicho.s
* Summary: 
*    Enter a txt file name
*    This will count the occurances of each word
*    then outpot to console the top 100.
************************************************************************/
#include <iostream>    // for CIN and COUT
#include <string>      // for STRING
#include <fstream>
#include "bst.h"
#include <algorithm>
#include <iomanip>
// #include ""
#include <map>
using namespace std;
string sanatize(string);
int main()
{
   string fileName;
   map<string,int> WordMap;
   

   cout << "Enter filename: ";
   cin >> fileName;
   ifstream file(fileName.c_str());
   string word;
   while(file >> word )
   {
      word = sanatize(word);
      if(word != "")
      {
         map<string,int>::iterator it = WordMap.find(word);
         if(it != WordMap.end())
         {//Key already exists.
            WordMap[word] = WordMap[word] + 1;
         }
         else
         {//Key does not exist, create it.
            WordMap[word] = 1;
         }

      }
   }

   // Binary Search Tree for calculated values
   BST<pair<int,string> >  words;
   //Add all values from map to BST.

   for(
      map<string,int>::iterator it = WordMap.begin();
      it != WordMap.end();
      it++
   )
   {
      words.insert(make_pair(it->second,it->first));
   }

   //Display top 100 values.
   BSTIterator<pair<int,string> > it = words.rbegin();
   for (int i = 0;i<100;i++)
   {
      if(it != NULL)
         cout << setw(23) << (*it).second <<" = " << (*it).first << endl;
      --it;
   }



   return 0;
}


string sanatize(string word)
{
   //remove punctuation
   string clean;
   string punc = "!:';()#.$,/";
   for(auto it = word.begin();it != word.end();it++)
   {
       string::iterator found = find(punc.begin(),punc.end(),(*it));
       if(found == punc.end())
         clean+=*it;
   }
   word = clean;


   //lowercase word
   transform(word.begin(), word.end(), word.begin(), ::tolower);
   // // This is an interesting expression. 
   // //I'll have to use it sometime
   // for_each(word.begin(), word.end(),[](char & c) {
   //    c = tolower(c);
   // });

   return word;
}