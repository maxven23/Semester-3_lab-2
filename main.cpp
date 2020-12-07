#pragma once
#include "num4.h"


int main(void) {
	string input;
	string type;
	int size;

	cout << "Enter your String:  ";
	getline(cin, input );
	cout << endl;

	cout << "Enter your the Type of pagination: ('words' or 'letters')  ";
	getline(cin, type);
	cout << endl;

	cout << "Enter the number of elements on one page:  ";
	cin >> size;
	cout << endl;

	IDictionary<string, int>* Dict = alphabetPtr(input, size, type);
	
	cout << endl << endl;
	Dict->Tree->printTree();


	cout << endl << endl;

	return 0;
}