#include <iostream>
#include <string>
#include <fstream>
#include "TextEditorFunc.h"
using namespace std;
// only main menu and calls to functions in TextEditorFunc.cpp should be here
// no function definitions of function bodies should be present in this file

int main()
{

	cout << "Welcome to our Text File Editor!\n";
	cout << "Please enter the filename that you want to deal with below\n";
	string originalFileName = getAValidFileName();
	createOriginalFile(originalFileName);
	string tempOriginalFileName = createTempOfOriginalFile(originalFileName);
	int userChoice;
	while (true) {
		printMainMenu();
		userChoice = getUserChoice();
		if (userChoice != 16) {
			executeUserChoice(userChoice, tempOriginalFileName, originalFileName);
			clearScreen();
		}
		else {
			cout << "Thanks for using our Text File Editor Program.\n";
			break;
		}
	}
	return 0;
}