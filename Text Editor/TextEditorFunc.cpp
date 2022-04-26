#include <Windows.h>
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;
//____________________________________________________________________________________________
string getFileName()
{
    string fileName;
    while (true)
    {
        fileName = "";
        while (fileName.empty())
        {
            cout << "Enter the File Name: ";
            cin >> fileName;
            cin.clear();
        }
        break;
        /*if (checkFileName(fileName))
        {
            break;
        }
        else
        {
            cout << "Wrong Name of the File, Try again.";
        }*/
    }

    return fileName;
}
//____________________________________________________________________________________________
bool checkFileName(string fileName)
{
    regex isValid("[a-zA-Z0-9(){}#$%~`@^&_-=+,';\t]+[.][(txt)]");
    return regex_match(fileName, isValid);
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
string getSecondFileName()
{
    string fileName;
    while (true)
    {
        fileName = "";
        while (fileName.empty())
        {
            cout << "Enter the Second File Name: ";
            cin >> fileName;
            cin.clear();
        }
        break;
        /*if (checkFileName(fileName))
        {
            break;
        }
        else
        {
            cout << "Wrong Name of the File, Try again.";
        }*/
    }

    return fileName;
}
//____________________________________________________________________________________________
void mergeAnotherFile(fstream& file)
{
    fstream file2;
    string secondFileName = getSecondFileName();
    file2.open(secondFileName.c_str(), ios::in);
    file.put(file2.get());
    while (!file2.eof())
    {
        if (file2.get() != EOF)
        {
            file.put(file2.get());
        }
    }
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