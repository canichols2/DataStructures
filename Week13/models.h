#ifndef prsn
#define prsn

#include <stdio.h>
#include "interfaces.h"
#include "deque.h"
#include "list.h"
#include <string>
using namespace std;


/******************************
 * Person Class
 ******************************/
class Person 
{
   public:
   Person(int gen=1, int fam= -1):generation(gen),familyIndex(fam){}
   ~Person(){}
   tm birthdate;
   string year;
   string month;
   string day;
   string givenName;
   string surName;
   int familyIndex;
   int generation;
   Deque<Person> parents;
   void setDate(string date)
   {
      tm tim;
      char loc_month[10];
      sscanf(date.c_str(), "%d %s %d",&tim.tm_mday,loc_month,&tim.tm_year);
      tim.tm_mon = intMonth(loc_month);
      birthdate = tim;
   }
   int intMonth(){
      return intMonth(this->month);
   }
   int intMonth(string month){
      if(month == "JAN") return 1;
      if(month == "FEB") return 2;
      if(month == "MAR") return 3;
      if(month == "APR") return 4;
      if(month == "MAY") return 5;
      if(month == "JUN") return 6;
      if(month == "JUL") return 7;
      if(month == "AUG") return 8;
      if(month == "SEP") return 9;
      if(month == "OCT") return 10;
      if(month == "NOV") return 11;
      if(month == "DEC") return 12;
      return 0;
   }
   bool operator<=(Person &rhs){
      if(*this == rhs || *this < rhs)
         return true;
      return false;
   }
   bool operator==(Person &rhs){return (strEql(surName,rhs.surName) && strEql(givenName,rhs.givenName) &&  birthdate.tm_year == rhs.birthdate.tm_year && birthdate.tm_mon == rhs.birthdate.tm_mon &&  birthdate.tm_mday == rhs.birthdate.tm_mday);};
   bool operator>=(Person &rhs){return !(*this < rhs);  }
   bool operator!=(Person &rhs){return !(*this == rhs); }
   bool  operator<(Person &rhs){
      
      if(strLT(surName,rhs.surName))
         return true;
      else if (strEql(surName,rhs.surName) && strLT(givenName,rhs.givenName))
         return true;
      else if (strEql(surName,rhs.surName) && strLT(givenName,rhs.givenName) &&  birthdate.tm_year < rhs.birthdate.tm_year)
         return true;
      else if (strEql(surName,rhs.surName) && strLT(givenName,rhs.givenName) &&  birthdate.tm_year == rhs.birthdate.tm_year && birthdate.tm_mon < rhs.birthdate.tm_mon)
         return true;
      else if (strEql(surName,rhs.surName) && strLT(givenName,rhs.givenName) &&  birthdate.tm_year == rhs.birthdate.tm_year && birthdate.tm_mon == rhs.birthdate.tm_mon &&  birthdate.tm_mday < rhs.birthdate.tm_mday)
         return true;
      return false;
   }
   bool  operator>(Person &rhs){return !(*this < rhs) && !(*this == rhs);}

   bool strExist(string &str)
   {
      return /*str != NULL && */ str != "";
   }


   bool strEql(string str1, string str2)
   {
      if (strExist(str1) && strExist(str2))
         if(str1 == str2)
            return true;
         else
            return false;
      else
      {
         return true;
      }
   }
   bool strLT(string str1, string str2)
   {
      if (strExist(str1) && strExist(str2))
         if(str1 < str2)
            return true;
         else
            return false;
      else
      {
         return true;
      }
   }
   //External Declaration
   string toString() const;
   void addParent()
   {

   }
   void addChild()
   {

   }
   friend ostream &operator<<( ostream &out, const Person &P ) { 
         out << P.toString();
         return out;            
      }

};

string Person::toString() const
{
   string output = givenName;
   if(givenName != "" && surName != "") output += " ";
   output += surName;
   if(birthdate.tm_year)
      output += ", b. "+ to_string(birthdate.tm_year) + " ";
   if(birthdate.tm_mday) 
      output += "" + to_string(birthdate.tm_mday) + " ";
   if(birthdate.tm_mon)
      output += "" + to_string(birthdate.tm_mon) + " ";
   return output;

}


template <class T>
class fakePointer
{
   public:
   T *obj;
   fakePointer(){}
   fakePointer(T &obj)
   {
      this->obj = &obj;
   }
   ~fakePointer(){}
   bool operator==(fakePointer &rhs)const {return *(obj) == *(rhs.obj);}
   bool operator>=(fakePointer &rhs)const {return *(obj) >= *(rhs.obj);}
   bool operator<=(fakePointer &rhs)const {return *(obj) <= *(rhs.obj);}
   bool operator!=(fakePointer &rhs)const {return *(obj) != *(rhs.obj);}
   bool  operator<(fakePointer &rhs)const {return *(obj) <  *(rhs.obj);}
   bool  operator>(fakePointer &rhs)const {return *(obj) >  *(rhs.obj);}
   friend ostream &operator<<( ostream &out, const fakePointer<T> &P ) { 
         out << *(P.obj);
         return out;            
      }
   void operator= (T &rhs)
   {
      obj = &rhs;
   }
   T& operator*()
   {
      return *obj;
   }
};


// class ParentLevel:public Printable
// {
//    public:
//    int level;
//    ParentLevel(int l = 1):level(l){}
//    ~ParentLevel(){}
//    string toString()
//    {
//       string               output = "Parents:";
//            if(level == 2)  output = "Grandparents:";
//       else if(level == 3)  output = "Great Grandparents:";
//       else if(level == 4)  output = "2nd Great Grandparents:";
//       else if(level == 5)  output = "3rd Great Grandparents:";
//       else if(level == 6)  output = "4th Great Grandparents:";
//       else if(level == 7)  output = "5th Great Grandparents:";
//       return output;
//    }
// };

class FamilyUnit
{
   public:
   List<int> Parents;
   List<int> Children;
   FamilyUnit(){
      Parents = List<int>();
      Children = List<int>();
   }
   ~FamilyUnit(){}
   void addParent(int p){
      Parents.push_back(p);
   }
   void addChild(int c){
      Children.push_back(c);
   }
      
};
#endif //prsn