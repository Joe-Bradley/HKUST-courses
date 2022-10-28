#include <iostream>
#include <string>

using namespace std;

// return plural version of word if ctr isn't 1
string make_plural(size_t ctr, const string &word,
                               const string &ending)
{
    return (ctr == 1) ? word : word + ending;
}

int main () {
	string sword("word"), sresult;
	const string send("s");
	sresult = make_plural(2, sword, send);
	sword = "";
	cout << sresult << endl;
	return 0;
}