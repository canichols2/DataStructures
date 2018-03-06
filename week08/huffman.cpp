/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Cody Nichols
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/
#include <string>
#include "pair.h"
#include "list.h"
#include <iostream>
#include <fstream>
#include "huffman.h"       // for HUFFMAN() prototype
using namespace std;
void readTree(BinaryNode<Pair<float,string> >* node,string huffStr);
// template <class T>
// ostream & operator << (ostream & out, const BinaryNode <Pair<float,string> >* & rhs);
// ostream & operator << (ostream & out, const Pair<float,string> & rhs);

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(string fileName)
{
      huff huffObj;
   float tmpF;
   string tmpS;
   ifstream file(fileName.c_str());
   while(file>>tmpS>>tmpF)
   {
      //I created a new insert to sort as it's inserting.
      huffObj.rInsertOrdered( new BinaryNode<Pair<float,string> >(  Pair<float,string>(tmpF,tmpS))  );
      // cout << huffObj <<endl;
      
   }
   
   //TODO Call huffObj. Create Tree...
   huffObj.createTree();

   huffObj.readTree();
//    readTree(sortedNodes.front(),"");

   return;
}




