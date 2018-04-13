#include <algorithm> 
#include <cctype>
#include <locale>
#include "models.h"


// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


bool personExits(Person &p)
{
   if(p.strExist(p.givenName) || p.strExist(p.surName))
      return true;
   else return false;
}


inline bool caseInsCharCompareN(char a, char b) {
   return(toupper(a) == toupper(b));
}
// inline bool caseInsCharCompareW(wchar_t a, wchar_t b) {
//    return(towupper(a) == towupper(b));
// }
bool caseInsCompare(const string& s1, const string& s2) {
   return((s1.size() == s2.size()) &&
          equal(s1.begin(), s1.end(), s2.begin(), caseInsCharCompareN));
}
// bool caseInsCompare(const wstring& s1, const wstring& s2) {
//    return((s1.size() == s2.size()) &&
//           equal(s1.begin(), s1.end(), s2.begin(), caseInsCharCompareW));
// }
