#include <Windows.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <regex>
using namespace std;
//____________________________________________________________________________________________
bool checkFileName(string fileName)
{
    regex isValid("[a-zA-Z0-9()]+(.txt)");
    return regex_match(fileName, isValid);
}
//____________________________________________________________________________________________
string getFileName(string turn)
{
    string fileName; bool checker; 
    while (true)
    {
        fileName = "";
        while (fileName.empty())
        {
            cout << "Enter the " << turn << " File Name : ";
            cin >> fileName;
            cin.clear();
        }
        checker = checkFileName(fileName);
        if (checker)
        {
            break;
        }
        else
        {
            cout << "Wrong Name of Text File it should be {(letters, numbers or both).txt}, Try again." << endl;
        }
    }

    return fileName;
}
//____________________________________________________________________________________________
bool checkValidFile(string fileName)
{
    fstream outfile; bool checker = true;
    outfile.open(fileName.c_str(), ios::in);
    if (outfile.fail())
    {
        checker = false;
    }
    outfile.close();
    return checker;
}
//____________________________________________________________________________________________
void mainMenu()
{
    cout << "1.  Add new text to the end of the file." << endl;
    cout << "2.  Display the content of the file." << endl;
    cout << "3.  Empty the file." << endl;
    cout << "4.  Encrypt the file content." << endl;
    cout << "5.  Decrypt the file content." << endl;
    cout << "6.  Merge another file." << endl;
    cout << "7.  Count the number of words in the file." << endl;
    cout << "8.  Count the number of characters in the file." << endl;
    cout << "9.  Count the number of lines in the file." << endl;
    cout << "10. Search for a word in the file." << endl;
    cout << "11. Count the number of times a word exists in the file." << endl;
    cout << "12. Turn the file content to upper case." << endl;
    cout << "13. Turn the file content to lower case." << endl;
    cout << "14. Turn file content to 1st caps (1st char of each word is capital)." << endl;
    cout << "15. Save." << endl;
    cout << "16. Exit." << endl;
}
//____________________________________________________________________________________________
void clearScreen()
{
    system("CLS");
    cout << flush;
    system("CLS");
}
//____________________________________________________________________________________________
void mergeAnotherFile(fstream& file)
{
    fstream file2;
    string secondFileName = getFileName("Second");
    file2.open(secondFileName.c_str(), ios::in);
    file << file2.rdbuf();
    file2.close();
}
//____________________________________________________________________________________________
int countNumberOfWords(fstream& file)
{
    int numberOfWords = 0; char inputWord[30];
    /*firstLetter = file.get();
    if (firstLetter == ' ')
    {
        numberOfWords = 0;
    }*/
    file.getline(inputWord, 30, ' ');
    while (isspace(cin.peek())) cin.ignore(' ');

    while (!file.eof())
    {
        ++numberOfWords;
        file.getline(inputWord, 30, ' ');
    }

    return numberOfWords;
}
//____________________________________________________________________________________________
int countNumberOfLines(fstream& file)
{
    char inputLine[100]; int numberOfLines = 0;
    file.getline(inputLine, 100, '\n');
    while (!file.eof())
    {
        ++numberOfLines;
        file.getline(inputLine, 100, '\n');
    }
    return numberOfLines;
}
//____________________________________________________________________________________________
int countNumberOfCharacters(fstream& file) 
{
    int numberOfCharacters = 0;
    file.get();
    while (!file.eof())
    {
        numberOfCharacters++;
        file.get();
    }
    return numberOfCharacters;
}
//____________________________________________________________________________________________
string makeWordLowerCase(string word)
{
    for (int index = 0; index < word.size(); index++)
    {
        word[index] = tolower(word[index]);
    }
    return word;
}
//____________________________________________________________________________________________
string getWordForSearching()
{
    string word;
    word = "";
    while (word.empty())
    {
        cout << "Enter the word you want to search about in the file: ";
        cin >> word;
        cin.clear();
    }
    word = makeWordLowerCase(word);
    return word;
}
//____________________________________________________________________________________________
void searchForWordInFile()
{

}