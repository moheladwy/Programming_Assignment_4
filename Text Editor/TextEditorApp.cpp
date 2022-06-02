//____________________________________________________________________________________________
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Text Editor Application
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Aly
// Purpose: Allow the user to open text files with write and reading from.
// File: This is the Application File that contain the main algorithm of the program.
//____________________________________________________________________________________________
#include <iostream>
#include <string>
#include "TextEditorFunc.h"
using namespace std;
//____________________________________________________________________________________________
int main()
{
	cout << "Welcome to our Text File Editor!\n";
	cout << "Please enter the filename that you want to deal with below.\n";

	string originalFileName = getValidFileName("");
	createOriginalFile(originalFileName);
	string tempOriginalFileName = createTempOfOriginalFile(originalFileName);
	
	int userChoice, isOpen = true;
	while (isOpen)
    {
		printMainMenu();
		userChoice = getUserChoice();
	
		if (userChoice != 16)
        {
			executeUserChoice(userChoice, tempOriginalFileName, originalFileName);
			if (isClearScreen())
			{
				clearScreen();
			}
		}
		else
        {
			printEndProgram();
			remove(tempOriginalFileName.c_str());
			isOpen = false;
		}
	}

	return 0;
}
//____________________________________________________________________________________________