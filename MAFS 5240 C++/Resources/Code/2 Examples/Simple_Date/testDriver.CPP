#include <iostream>
#include "date.h"

using namespace std;

int main()
{
   const int MAXDAYS = 160;
   Date d(10, 13, 2008);

   for (int loop = 1; loop <= MAXDAYS; loop++) {
      d.print();
      d.nextDay();
   }

   cout << endl;
   return 0;
}