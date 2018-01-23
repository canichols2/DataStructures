/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Cody Nichols
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream> // for ISTREAM and COUT
#include <string>   // for STRING
#include <cstring>  // for isChar
#include <ctype.h>  // for isChar
#include <cassert>  // for ASSERT
#include "stack.h"  // for STACK
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string &infix)
{
   string postfix;
   Stack<char> opStack;
   char topToken,
       c;
   const string BLANK = " ";

   for (int i = 0; i < infix.length(); i++)
   {
      c = infix[i];
      switch (c)
      {
      case ' ':
         break;
      case '(':
         opStack.push(c);
         break;
      case ')':
         for (;;)
         {
            assert(!opStack.empty());
            topToken = opStack.top();
            opStack.pop();
            if (topToken == '(')
               break;
            postfix.append(BLANK + topToken);
         }
         break;
      case '^':
      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
         for (;;)
         {
            if (opStack.empty() ||
                opStack.top() == '(' ||
                (c == '^') ||
                ((c == '*' || c == '/' || c == '%') && (opStack.top() == '+' || opStack.top() == '-') && (opStack.top() != '^'))

            )
            {
               opStack.push(c);
               break;
            }
            else
            {
               topToken = opStack.top();
               opStack.pop();
               postfix.append(BLANK + topToken);
            }
         }
         break;
      default:
         postfix.append(BLANK + c);
         for (;;)
         {
            char n = infix[i + 1];
            if (!isalnum(n) && n != '.')
               break;
            i++;
            c = infix[i];
            postfix.append(1, c);
         }
      }
   }
   for (;;)
   {
      if (opStack.empty())
         break;
      topToken = opStack.top();
      opStack.pop();
      if (topToken != '(')
      {
         postfix.append(BLANK + topToken);
      }
      else
      {
         cout << " *** Error in infix expression ** \n";
         break;
      }
   }
   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl
              << endl;
      }
   } while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string &postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   } while (input != "quit");
}
