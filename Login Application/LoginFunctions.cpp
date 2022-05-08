// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application.
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Ahmed
// Purpose: .......
// File: This is the CPP file that contain the algorithms of the functions.
//___________________________________________________________________________________________________
#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <Windows.h>
using namespace std;
//___________________________________________________________________________________________________
void printMainMenu()
{
	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "1- Register." << endl;
	cout << "2- Login." << endl;
	cout << "3- Change Password." << endl;
	cout << "4- Forget Password." << endl;
	cout << "----------------------------------------------------------------------------------------" << endl;
}
//___________________________________________________________________________________________________
bool checkValidYesOrNo(string choice)
{
	bool isValidInput = true;
	if (choice.length() == 1) {
		switch (choice[0]) {
		case 'y':
		case 'Y':
			return isValidInput;
		case 'n':
		case 'N':
			return isValidInput;
		default:
			break;
		}
	}
	return !isValidInput;
}
//___________________________________________________________________________________________________
void printEndApp()
{
	cout << "Thanks for using our Login System Application." << endl;
	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "Authors of the Application:-" << endl;
	cout << "----------------------------" << endl;
	cout << "1- Name: Mohamed Hussein Hassan Eladwy. ID: 20210335." << endl;
	cout << "2- Name: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502." << endl;
	cout << "3- Name: Amr Khalied Elsayed Elhennawy. ID: 20210274." << endl;
	cout << "----------------------------------------------------------------------------------------" << endl;
}
//___________________________________________________________________________________________________
void clearScreen()
{
	system("CLS");
	cout << flush;
	system("CLS");
}
//___________________________________________________________________________________________________
bool isClearScreen()
{
	int isWant = false;
	string choice = "";
	while (!isWant)
	{
		cout << "Do you want to clear the screen before continue or not (y)|(n): ";
		getline(cin, choice);
		isWant = checkValidYesOrNo(choice);
		if (!isWant)
		{
			cout << "Please enter a choice from (y) or (n) only, Try again.\n";
		}
		else
		{
			if (choice == "n" || choice == "N")
			{
				return !isWant;
			}
		}
	}
	return isWant;
}
//___________________________________________________________________________________________________
string makeLowerCase(string line)
{
	for (int i = 0; i < line.length(); i++) {
		line[i] = tolower(line[i]);
	}
	return line;
}
//___________________________________________________________________________________________________
bool checkUserChoice(string choice)
{
	if (choice.length() == 1) {
		if (!isdigit(choice[0]))
		{
			return false;
		}
		int checkChoice = stoi(choice);
		if (checkChoice >= 1 && checkChoice <= 4) {
			return true;
		}
	}
	return false;
}
//___________________________________________________________________________________________________
int getUserChoice()
{
	string getChoice;
	int setChoice;
	bool isValidChoice = false;
	while (!isValidChoice) {
		cout << "Enter your choice from the list above [1:4]: ";
		getChoice = "";
		while (getChoice.empty()) {
			getline(cin, getChoice);
		}
		isValidChoice = checkUserChoice(getChoice);
		if (!isValidChoice) {
			cout << "The Choice you entered is not an option from the list,\
					 Try again and make sure to enter a valid option from the list." << endl;
		}
	}
	cout << "----------------------------------------------------------------------------------------" << endl;
	setChoice = stoi(getChoice);
	return setChoice;
}
//___________________________________________________________________________________________________