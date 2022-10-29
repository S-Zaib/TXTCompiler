#include <iostream>
#include <string>
#include "Header.h"
using namespace std;


int main()
{
	string expression;
	cout << "Enter Expression: ";
	getline(cin, expression);
	string nig = postfixer(expression);
	string nig2 = prefixer(expression);
	cout << "Postfix: " << nig << endl;
	cout << "Prefix: " << nig2 << endl;
	cout << "POST TO INFIX: " << infixer(nig) << endl;
	cout << "PRE TO INFIX: " << infixer(nig2) << endl;
	return 0;
}
