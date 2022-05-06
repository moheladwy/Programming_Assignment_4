// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Text Editor Application
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Aly
// Purpose: Allow the user to open text files with write and reading from.
// File: This is the Header file that contain the prototype of the Functions and its parameters. 

#pragma once
using namespace std;
//____________________________________________________________________________________________
// general Functions for the program that used many times in many different functions.
string getAValidFileName(string turn); 
bool checkValidFile(string fileName); 
void printMainMenu(); 
void printEndProgram();
bool checkUserChoice(string choice); 
int getUserChoice(); 
bool isEmptyFile(string fileName); 
void executeUserChoice(int choice, string fileName, string originalFileName); 
void createOriginalFile(string fileName); 
void clearScreen();
bool isClearScreen();
string createTempOfOriginalFile(string originalFileName);
string makeWordLowerCase(string word); 
string getWordForSearching();
//____________________________________________________________________________________________
// Amr Khalied Elsayed Elhennawy Functions from 1 to 5.
void addingContent(string fileName);
void displayContent(string fileName);
void emptyFileContent(string fileName);
void encryptFileContent(string fileName);
void decryptFileContent(string fileName);
//____________________________________________________________________________________________
// Mohamed Hussein Hassan Eladwy Functions from 6 to 10.
void mergeAnotherFile(string fileName); 
void countNumberOfWords(string fileName); 
void countNumberOfCharacters(string fileName); 
void countNumberOfLines(string fileName);  
void searchForWordInFile(string fileName); 
//____________________________________________________________________________________________
// Yusuf Elsayed Abdelrahman Bdr Functions from 11 to 15.
void countWordOccurences(string filename); 
void allFileToUpperCase(string filename); 
void allFileToLowerCase(string filename); 
void allFileToFirstCaps(string filename); 
void saveFile(string originalFileName, string tempOriginalFileName); 
//____________________________________________________________________________________________