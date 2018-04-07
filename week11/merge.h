/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   <Your Name>   
* Summary: 
*
************************************************************************/
#include <list>
#include <cassert>
   
using namespace std;

/************************************************************************
 * Declarations
 ************************************************************************/

template<class T>
void mergeSort(list< list<T> > &data);

template<class T>
void splitList(list< list<T> > &data, list< list<T> > &l1, list< list<T> > &l2);

template<class T>
void mergeList( list<T> &data,  list<T> &l1,  list<T>  &l2);

template<class T>
void mergeList(list< list<T> > &data, list< list<T> > &l1, list< list<T> > &l2);

void displayList(list<int> &data);

void displayListList(list<list<int> > &data);

/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
void mergeSort(list<int> &data)
{
   displayList(data);
	list< list<int> > *tmpData = new list< list<int> >();

   //Split data into a list of sorted sub-lists
   for(list<int>::iterator it = data.begin();
   it != data.end();
   it++)
   {
      int tmpInt = *it;
	   if(!tmpData->empty() && *it >= tmpData->back().back() )
	   {
         int tmpSubInt = tmpData->back().back();
		   // list<int> tmpList = tmpData->back();
		   tmpData->back().push_back(*it);
	   }else{
		   int tmpInt = *it;
		   list<int> tmpList1 = list<int>(1, tmpInt);
		   tmpData->push_back( tmpList1 );
	   }
      // displayListList(*tmpData);
   }
   
   displayList(data);

   displayListList(*tmpData);
   mergeSort(*tmpData);


   //convert *tmpData into data
   int newDataSize = tmpData->size();
   assert(tmpData->size() == 1);
   data.clear();
   data = tmpData->front();
}

template<class T>
void mergeSort(list< list<T> > &data)
{
	list< list<T> > list1;
	list< list<T> > list2;
//	list< list<int> >::iterator it1 = subList->begin();

   int newDataSize = data.size();
   displayListList(data);
	while(data.size() > 1)
	{
       newDataSize = data.size();
		splitList(data,list1,list2);
		mergeList(data,list1,list2);
       newDataSize = data.size();
    displayListList(data);
	}
    displayListList(data);
    newDataSize = data.size();
}

void displayList(list<int> &data)
{
   // cout << "list: ";
   // list<int>::iterator lIt = data.begin();
   // while(lIt != data.end())
   // {
   //    cout << *lIt << " ";
   //    ++lIt;
   // }
   // cout << endl;
}

void displayListList(list<list<int> > &data)
{
   // cout << "display data:\n";
   // list<list<int> >::iterator llIt = data.begin();
   // while(llIt != data.end())
   // {
   //    displayList(*llIt);
   //    ++llIt;
   // }
   // cout << endl << endl;
}


template<class T>
void splitList(list< list<T> > &data, list< list<T> > &l1, list< list<T> > &l2)
{
	l1.clear();
	l2.clear();
	list< list<T> > *listPtr = &l1;
	for(list< list<int> >::iterator it = data.begin();
			it != data.end();
			++it)
	{
		listPtr->push_back(*it);
		if(listPtr == &l1)
			listPtr = &l2;
		else
			listPtr = &l1;
	}
	data.clear();
}



template<class T>
void mergeList(list< list<T> > &data, list< list<T> > &l1, list< list<T> > &l2)
{
	list< list<int> >::iterator itL1 = l1.begin();
	list< list<int> >::iterator itL2 = l2.begin();
	while(itL1 != l1.end() && itL2 != l2.end() )
	{
      int dSize = data.size();
      list<int> newDataList = list<int>();
		mergeList(newDataList,*itL1, *itL2);
      data.push_back(newDataList);
      ++itL1;
      ++itL2;
	}
   // TODO: merge rest of l1 or l2 node lists.
	while(itL2 != l2.end())
	{
		data.push_back(*itL2);
		++itL2;
	}
	while(itL1 != l1.end())
	{
		data.push_back(*itL1);
		++itL1;
	}

}


template<class T>
void mergeList( list<T> &data,  list<T> &l1,  list<T>  &l2)
{
	list<int>::iterator itL1 = l1.begin();
	list<int>::iterator itL2 = l2.begin();
	//Merge most of the values
	while(itL1 != l1.end() && itL2 != l2.end() )
	{
		if(*itL1 <= *itL2){
			data.push_back(*itL1);
			++itL1;
		}else{
			data.push_back(*itL2);
			++itL2;
		}
      list<int>::iterator dataIt = data.begin();
      *dataIt;
	}

	//Add the rest of the values that weren't already merged.
	if(itL1 == l1.end())
	{
		data.splice(
				data.end(), 	//Position in destination list to add after
				l2,				//List source
				itL2,			//Position in source to begin
				l2.end()		//Position in source to end
		);
	}else{
		data.splice(
				data.end(), 	//Position in destination list to add after
				l1,				//List source
				itL1,			//Position in source to begin
				l1.end()		//Position in source to end
		);
	}



}
















