#include "Rational.cpp"
#include "Rational.h"
#include <iostream>

using namespace std;

int main()
{
   Rational c(1,3), d(7,8), x;

   c.printRational();
   cout << " + ";
   d.printRational();
   x = c + d;
   cout << " = ";
   x.printRational();
   cout << endl;
   x.printRational();
   cout << " = ";
   x.printRationalAsFloating();
   cout << endl << endl;

   c.printRational();
   cout << " - ";
   d.printRational();
   x = c - d;
   cout << " = ";
   x.printRational();
   cout << endl;
   x.printRational();
   cout << " = ";
   x.printRationalAsFloating();
   cout << endl << endl;

   c.printRational();
   cout << " x ";
   d.printRational();
   x = c * d;
   cout << " = ";
   x.printRational();
   cout << endl;
   x.printRational();
   cout << " = ";
   x.printRationalAsFloating();
   cout << endl << endl;

   c.printRational();
   cout << " / ";
   d.printRational();
   x = c / d;
   cout << " = ";
   x.printRational();
   cout << endl;
   x.printRational();
   cout << " = ";
   x.printRationalAsFloating();
   cout << endl;

   return 0;
}


