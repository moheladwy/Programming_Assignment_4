#pragma once
/*
This the Functions that we will work on it.
amr have the functions [1:5]
eladwy have the functions [6:10]
bdr have the functions [11:15]
*/
using namespace std;
//____________________________________________________________________________________________

string getAValidFileName(string turn = ""); //DONE
//____________________________________________________________________________________________


// NOTE: Must be removed as it is a function used only once in the getAValidFileName() function
// therefore it should not be included in the file. - Yusuf Badr
//bool checkFileName(string fileName); // Done.
//____________________________________________________________________________________________

bool checkValidFile(string fileName); // Done.
//____________________________________________________________________________________________

void printMainMenu(); // DONE
//____________________________________________________________________________________________

bool checkUserChoice(string choice); // Done.
//____________________________________________________________________________________________

int getUserChoice(); // Done.
//____________________________________________________________________________________________

void executeUserChoice(int choice);
//____________________________________________________________________________________________

void addingContent(string fileName); //Done
//____________________________________________________________________________________________

void displayContent(string fileName); //Done
//____________________________________________________________________________________________

void emptyFileContent(string fileName); //Done
//____________________________________________________________________________________________

void encryptFileContent(); //Done
//____________________________________________________________________________________________

void decryptingFileContent(); //Done
//____________________________________________________________________________________________

void mergeAnotherFile(string fileName); // Done.
//____________________________________________________________________________________________

int countNumberOfWords(string fileName); // Done.
//____________________________________________________________________________________________

int countNumberOfCharacters(string fileName); // Done.
//____________________________________________________________________________________________

int countNumberOfLines(string fileName); // Done.
//____________________________________________________________________________________________

string makeWordLowerCase(string word); // Done.
//____________________________________________________________________________________________
 
string getWordForSearching(); // Done.
//____________________________________________________________________________________________

bool searchForWordInFile(string fileName, string wordWanted); // Done.
//____________________________________________________________________________________________

int countWordOccurences(string filename, string searchWord); // DONE - Yusuf Badr
//____________________________________________________________________________________________

void allFileToUpperCase(string filename); // DONE - Yusuf Badr
//____________________________________________________________________________________________

void allFileToLowerCase(string filename); // DONE - Yusuf Badr
//____________________________________________________________________________________________

void allFileToFirstCaps(string filename); //DONE - Yusuf Badr
//____________________________________________________________________________________________



/*
consider deleting - no need for this function - Yusuf Badr

void save(fstream& file); // Almost Done.
//____________________________________________________________________________________________
*/


void saveFile(string existingFileName); //DONE - Yusuf Badr

void clearScreen(); //Done.
//____________________________________________________________________________________________