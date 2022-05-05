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
			cout << "Thanks for using our Text File Editor Program." << endl;
			cout << "--------------------------------------------------------------------------------------" << endl;
			cout << "Authors of the program:-" << endl;
			cout << "------------------------" << endl;
			cout << "1- Name: Mohamed Hussein Hassan Eladwy. ID: 20210335." << endl;
			cout << "2- Name: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502." << endl;
			cout << "3- Name: Amr Khalied Elsayed Elhennawy. ID: 20210274." << endl;
			cout << "--------------------------------------------------------------------------------------" << endl;
			remove(tempOriginalFileName.c_str());
			isOpen = false;
		}
	}
	return 0;
}