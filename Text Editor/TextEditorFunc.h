//____________________________________________________________________________________________
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Text Editor Application
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Aly
// Purpose: Allow the user to open text files with write and reading from.
// File: This is the Header file that contain the prototype of the Functions and its parameters. 
//____________________________________________________________________________________________
#pragma once
using namespace std;
//____________________________________________________________________________________________
// general Functions for the program that used many times in many functions.
//____________________________________________________________________________________________
bool isValidYesOrNo(const string &choice);
bool isValidFile(const string &fileName);
bool isValidUserChoice(const string &choice);
bool isEmptyFile(const string &fileName);
bool isClearScreen();

int getUserChoice();

void printMainMenu();
void printEndProgram();
void createOriginalFile(const string &fileName);
void clearScreen();

string getValidFileName(const string &turn);
string createTempOfOriginalFile(const string &originalFileName);
string makeWordLowerCase(string word); 
string getWordForSearching();
//____________________________________________________________________________________________
// Main Functions of the Program.
//____________________________________________________________________________________________
void addingContent(const string &fileName);
void displayContent(const string &fileName);
void emptyFileContent(const string &fileName);
void encryptFileContent(const string &fileName);
void decryptFileContent(const string &fileName);
void mergeAnotherFile(const string &fileName);
void countNumberOfWords(const string &fileName);
void countNumberOfCharacters(const string &fileName);
void countNumberOfLines(const string &fileName);
void searchForWordInFile(const string &fileName);
void countWordOccurrences(const string &fileName);
void allFileToUpperCase(const string &fileName);
void allFileToLowerCase(const string &fileName);
void allFileToFirstCaps(const string &fileName);
void saveFile(const string &originalFileName, const string &tempOriginalFileName);
void executeUserChoice(int choice, const string &fileName, const string &originalFileName);
//____________________________________________________________________________________________