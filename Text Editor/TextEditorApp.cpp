#include <iostream>
#include <string>
#include <fstream>
#include "TextEditorFunc.h"
using namespace std;

int main()
{
	cout << "Eladwy tests his functions and they are working correct dudes.(~_~)";
	int numLines, numWords, numChars;
	string wordWanted;
	bool checker;

	numLines = countNumberOfLines("test3.txt");
	cout << "The number of the Lines in the file = " << numLines << "\n";

	numWords = countNumberOfWords("test3.txt");
	cout << "The number of the Words in the file = " << numWords << "\n";

	numChars = countNumberOfCharacters("test3.txt");
	cout << "The number of the chars in the file = " << numChars << "\n";

	wordWanted = getWordForSearching();
	checker = searchForWordInFile("test3.txt", wordWanted);
	if (checker)
	{
		cout << "\n" << "the word exists in the file.\n";
	}
	else
	{
		cout << "\n" << "the word does not exist in the file.\n";
	}
	cout << "Counting is done bro.\n";

	fstream file;
	file.open("test3.txt", ios::app);
	mergeAnotherFile(file);
	file.close();
	cout << "Merging the files is done.\n";

	return 0;
}