/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   /****
    * Open the file
    */
   ifstream myHandFile;
   myHandFile.open("/home/cs235e/week05/hand.txt\n");
   if(!myHandFile){
      myHandFile.open("hand.txt");
      if(!myHandFile){
         cerr << "neither '/home/cs235e/week05/hand.txt' nor 'hand.txt' could be opened\n";
         return;
      }
   }

   /***********
    * Read the file in
    ************/
   Set<Card> theirHand  =  Set<Card>();
   Set<Card> myHand     =  Set<Card>();
   while (!myHandFile.eof()){
      Card temp;
      myHandFile >> temp;
      theirHand.insert(temp);
   }
   Card guess = "blank";
   char temp[128] = "blank";
   int index = -1;
   for(int i=0;i<5;i++){
      cout << "Round " << i + 1 << ": ";
      // cin.ignore(1000,'\n');
      cin >> temp;
      guess = temp;
      index = theirHand.find(guess);
      cout << "Guess:"<<guess<<"\nTheirHand:"<<*theirHand.begin()<<endl;
      if(index < 0){
         cout << "\tGo Fish!" << endl;
      }else{
         cout << "\tYou got a match!\n";
         theirHand.erase(index);
         myHand.insert(guess);
      }
   }
   cout << "You have "<<myHand.size()<< "matches!\n";
   cout << "The remaining cards:";
   for(
      SetIterator<Card> it = theirHand.begin(); 
      it != theirHand.end(); 
      ++it
   ){
      if(*it == *theirHand.begin())
         cout <<" "<< *it;
      else
         cout << ", "<< *it;
   }



   return ;
}
