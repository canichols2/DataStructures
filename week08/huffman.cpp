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
// void readTree(BinaryNode<Pair<float,string> >* node,string huffStr);

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
      huffObj.rInsertOrdered( new BinaryNode<Pair<float,string> >(  Pair<float,string>(tmpF,tmpS))  );
   }
   huffObj.createTree();
   huffObj.readTree();

   return;
}




