#include <iostream>
#include "Rational.h"

using namespace std;

Rational::Rational(int n, int d)
{
   numerator = n;
   denominator = d;
}

Rational Rational::operator+(const Rational &a)
{
   Rational t;

   t.numerator = a.numerator * denominator + a.denominator * numerator;
   t.denominator = a.denominator * denominator;
   t.reduction();

   return t;
}

Rational Rational::operator-(const Rational &s)
{
   Rational t;

   t.numerator = s.denominator * numerator - denominator * s.numerator;
   t.denominator = s.denominator * denominator;
   t.reduction();

   return t;
}

Rational Rational::operator*(const Rational &m)
{
   Rational t;

   t.numerator = m.numerator * numerator;
   t.denominator = m.denominator * denominator;
   t.reduction();

   return t;
}

Rational Rational::operator/(Rational &v)
{
   Rational t;

   t.numerator = v.denominator * numerator;
   t.denominator = denominator * v.numerator;
   t.reduction();

   return t;
}

void Rational::printRational(void)
{
   if (denominator == 0)
      cout << "\nDIVIDE BY ZERO ERROR!!!" << endl;
   else if (numerator == 0)
      cout << 0;
   else
      cout << numerator << "/" << denominator;
}

void Rational::printRationalAsFloating(void) 
   {  cout << (float) numerator / denominator; }

void Rational::reduction(void)
{
   int largest = numerator > denominator ? numerator : denominator;

   int gcd = 0;  // greatest common divisor

   for (int loop = 2; loop <= largest; loop++)
       if (numerator % loop == 0 && denominator % loop == 0)
          gcd = loop;

   if (gcd != 0) {
      numerator /= gcd;
      denominator /= gcd;
   }
}
