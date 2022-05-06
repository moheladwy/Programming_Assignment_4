/*
FCAI – Programming 1 – 2022 - Assignment 4
Program Name: Text Editor Application
Last Modification Date: xx/05/2022
Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
Teaching Assistant: Eng.Hagar Aly
Purpose: Allow the user to open text files with write and reading from.
File: This is the Application File that contain the main algorithem of the program.
*/

#include <iostream>
#include <string>
#include <fstream>
#include "TextEditorFunc.h"
// #include "TextEditorFunc.cpp"

/* 
Please Eng.Hagar Uncomment the apove #include "TextEditorFunc.cpp" if You are using Microsoft Visual Studio Code (the blue one) for Compiling the Files. 
(MS VSC => work on files in the same Folder not in project). and the files won't compile if you don't do that.

if You are using Clion, Code Blocks or Microsoft Visual Studio (the purple one) leave it as it is (commented).
(All of them work on Files in a project not like MS VSC in the same folder) and the files won't compile if You are Uncommented it.
*/

using namespace std;

int main()
{
	cout << "Welcome to our Text File Editor!\n";
	cout << "Please enter the filename that you want to deal with below.\n";

	string originalFileName = getAValidFileName("");
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
			printEndProgram();
			remove(tempOriginalFileName.c_str());
			isOpen = false;
		}
	}
	return 0;
}