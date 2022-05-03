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
	int userChoice, isOpen = true;
	while (isOpen) {
		printMainMenu();
		userChoice = getUserChoice();
		if (userChoice != 16) {
			executeUserChoice(userChoice, tempOriginalFileName, originalFileName);
			if (isClearScreen())
			{
				clearScreen();
			}
		}
		else {
			cout << "Thanks for using our Text File Editor Program.\n";
			isOpen = false;
		}
	}
	return 0;
}