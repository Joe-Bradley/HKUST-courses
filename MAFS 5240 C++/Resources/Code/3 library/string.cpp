#include <string>
#include <iostream>

int main( )
{
   using namespace std;

   // Default Constructor
   string str1;
   cout << "string str1;" << endl;
   if (str1.empty ( ) )
      cout << "The string str1 is empty." << endl;
   else
      cout << "The string str1 is not empty." << endl;
   cout << endl;

   // Initialize str2 as a copy of the string literal
   string str2 ( "How Do You Do?" );
   cout << "string str2 ( \"How Do You Do?\" );" << endl;
   cout << "str2: " << str2 << endl;
   cout << endl;

   // Initialize str3 as a copy of str2
   string str3 ( str2 );
   cout << "string str3 ( str2 );" << endl;
   cout << "str3: " << str3 << endl;
   cout << endl;

   // Initialize str4 with 5 copies of character '9'
   string str4 ( 5, '9' );
   cout << "string str4 ( 5, '9' );" << endl;
   cout << "str4: " << str4 << endl;
   cout << endl;

   // Initialize str5 with part of str 2
   string str5 ( str2 , 7 , 5 );
   cout << "string str5 ( str2 , 7 , 5 );";
   cout << "str5: " << str5 << endl;
   cout << endl;

   // Initializes str6b from str6a range of characters
   string str6a ( "Hello World" );
   string str6b ( str6a.begin ( ) + 6 , str6a.end ( ) );
   cout << "string str6a ( \"Hello World\" );\n"
	       "string str6b ( str6a.begin ( ) + 6 , str6a.end ( ) );" << endl;;
   cout << "str6b: " << str6b << endl;
   cout << endl;

   // String I/O
   string s1, s2, s3;
   cout << "Input: ";
   cin >> s1 >> s2 >> s3;
   cout << "1st word: " << s1 << endl;
   cout << "2nd word: " << s2 << endl;
   cout << "3rd word: " << s3 << endl;
   cout << endl;

   // String I/O - getline
   string line;
   cout << "Input line: " << endl;
   //cin.ignore(1000,'\n');
   getline (cin, line);
   cout << line << endl;


}
