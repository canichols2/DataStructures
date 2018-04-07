#include "interfaces.h"
#include "deque.h"
#include <string>
using namespace std;


/******************************
 * Person Class
 ******************************/
class Person : public Printable
{
   public:
   Person(int gen=1):generation(gen){}
   ~Person(){}
   string year;
   string month;
   string day;
   string givenName;
   string surName;
   int generation;
   Deque<Person> parents;
   int intMonth(){
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
   bool operator==(Person &rhs){return (surName == rhs.surName && givenName == rhs.givenName &&  atoi(year.c_str()) == atoi(rhs.year.c_str()) && intMonth() == rhs.intMonth() &&  atoi(day.c_str()) == atoi(rhs.day.c_str()));};
   bool operator>=(Person &rhs){return !(*this < rhs);  }
   bool operator!=(Person &rhs){return !(*this == rhs); }
   bool  operator<(Person &rhs){
      if(surName < rhs.surName)
         return true;
      if(surName == rhs.surName && givenName < rhs.givenName)
         return true;
      if(surName == rhs.surName && givenName == rhs.givenName &&  atoi(year.c_str()) == atoi(rhs.year.c_str()))
         return true;
      if(surName == rhs.surName && givenName == rhs.givenName &&  atoi(year.c_str()) == atoi(rhs.year.c_str()) && intMonth() < rhs.intMonth())
         return true;
      if(surName == rhs.surName && givenName == rhs.givenName &&  atoi(year.c_str()) == atoi(rhs.year.c_str()) && intMonth() == rhs.intMonth() &&  atoi(day.c_str()) < atoi(rhs.day.c_str()))
         return true;
   }
   bool  operator>(Person &rhs){return!(*this < rhs) && !(*this == rhs);}

   //External Declaration
   string toString();
   void addParent(

   );
   void addChild();
};

string Person::toString()
{
   string output = givenName;
   if(givenName != "" && surName != "") output += " ";
   output += surName;
   if(year != ""){
      output += ", b. ";
      if(day != "") output += day + " ";
      if(month != "") output += month + " ";
      output += year;
   }
   return output;
}




class ParentLevel:public Printable
{
   public:
   int level;
   ParentLevel(int l = 1):level(l){}
   ~ParentLevel(){}
   string toString()
   {
      string               output = "Parents:";
           if(level == 2)  output = "Grandparents:";
      else if(level == 3)  output = "Great Grandparents:";
      else if(level == 4)  output = "2nd Great Grandparents:";
      else if(level == 5)  output = "3rd Great Grandparents:";
      else if(level == 6)  output = "4th Great Grandparents:";
      else if(level == 7)  output = "5th Great Grandparents:";
      return output;
   }
}