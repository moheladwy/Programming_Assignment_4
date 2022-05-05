/*
FCAI – Programming 1 – 2022 - Assignment 4
Program Name: Text Editor Application
Last Modification Date: xx/05/2022
Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
Teaching Assistant: Eng.Hagar Aly
Purpose: Allow the user to open text files with write and reading from.
File: This is the Header file that contain the prototype of the Functions and its parameters. 
*/

#pragma once
using namespace std;
//____________________________________________________________________________________________

string getAValidFileName(string turn); 
//____________________________________________________________________________________________

bool checkValidFile(string fileName); 
//____________________________________________________________________________________________

void printMainMenu(); 
//____________________________________________________________________________________________

bool checkUserChoice(string choice); 
//____________________________________________________________________________________________

int getUserChoice(); 
//____________________________________________________________________________________________

bool isEmptyFile(string fileName); 
//____________________________________________________________________________________________

void executeUserChoice(int choice, string fileName, string originalFileName); 
//____________________________________________________________________________________________

void addingContent(string fileName);
//____________________________________________________________________________________________

void displayContent(string fileName);
//____________________________________________________________________________________________

void emptyFileContent(string fileName);
//____________________________________________________________________________________________

void encryptFileContent(string fileName);
//____________________________________________________________________________________________

void decryptFileContent(string fileName);
//____________________________________________________________________________________________

void mergeAnotherFile(string fileName); 
//____________________________________________________________________________________________

void countNumberOfWords(string fileName); 
//____________________________________________________________________________________________

void countNumberOfCharacters(string fileName); 
//____________________________________________________________________________________________

void countNumberOfLines(string fileName); 
//____________________________________________________________________________________________

string makeWordLowerCase(string word); 
//____________________________________________________________________________________________

string getWordForSearching(); 
//____________________________________________________________________________________________

void searchForWordInFile(string fileName); 
//____________________________________________________________________________________________

void countWordOccurences(string filename); 
//____________________________________________________________________________________________

void allFileToUpperCase(string filename); 
//____________________________________________________________________________________________

void allFileToLowerCase(string filename); 
//____________________________________________________________________________________________

void allFileToFirstCaps(string filename); 
//____________________________________________________________________________________________

void saveFile(string originalFileName, string tempOriginalFileName); 
//____________________________________________________________________________________________

void createOriginalFile(string fileName); 
//____________________________________________________________________________________________

void clearScreen();
//____________________________________________________________________________________________

bool isClearScreen();
//____________________________________________________________________________________________

string createTempOfOriginalFile(string originalFileName);
//____________________________________________________________________________________________