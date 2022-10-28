#ifndef Rational_H
#define Rational_H

class Rational {
public:
   Rational(int = 0, int = 1);  // default constructor
   Rational operator+(const Rational &);
   Rational operator-(const Rational &);
   Rational operator*(const Rational &);
   Rational operator/(Rational &);
   void printRational(void);
   void printRationalAsFloating(void);
private:
   int numerator;
   int denominator;

   void reduction(void);   // utility function
};

#endif
