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
   // List< // A Sorted List of
   //    BinaryNode< //Binary Nodes of
   //       Pair<    //of Pair's of
   //          float,//Floats and
   //          string//Strings
   //          > 
   //       >*
   //    > sortedNodes = List<BinaryNode<Pair<float,string> >*>();
   // List<Pair<float,string> > sortedThings = List<Pair<float,string> >();
   float tmpF;
   string tmpS;
   ifstream file(fileName.c_str());
   while(file>>tmpS>>tmpF)
   {
      //I created a new insert to sort as it's inserting.
      huffObj.insertOrdered( new BinaryNode<Pair<float,string> >(  Pair<float,string>(tmpF,tmpS))  );
      // ListIterator<BinaryNode<Pair<float,string> >*> it = sortedNodes.begin();
      // cout << huffObj <<endl;
      // while(it != NULL){
      //    cout << *it << endl;
      //    it++;
      // }
   }
   //for each Node in List
      //Until there is only one left to sort into the tree
   //pop Node off onto tmp* variable.
   //Pop next Node off onto tmp2* variable
   //make new node 
      //with addition of 2 floats and an empty string
      //With both tmp* and tmp2* nodes as children
      //Smaller on left
   //rInsertOrdered back onto list
   
   //TODO Call huffObj. Create Tree...
   huffObj.createTree();

   //set key values
      //Read through each node, starting with the left side
      //Write all values into some variable
      //using "key = 1101" format
   huffObj.readTree();
//    readTree(sortedNodes.front(),"");

   return;
}


/**********************
 * Recursively read through a Node tree
 * cout when you reach the end of the tree
 * str = 11101
 * ******************/
// void readTree(BinaryNode<Pair<float,string> >* node,string huffStr){
//    if(node->pLeft != NULL && node->pRight != NULL){
//       readTree(node->pLeft,huffStr +"0");
//       readTree(node->pRight,huffStr +"1");
//    }else{
//       cout << node->data.second << " = " << huffStr<<endl;
//    }
// }


