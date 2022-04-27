#include <Windows.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;
//____________________________________________________________________________________________
bool checkFileName(string fileName)
{
    regex isValid("^[\\w\\-. ]+\\.txt$");
    return regex_match(fileName, isValid);
}
//____________________________________________________________________________________________
string getFileName(string turn = "")
{
    string fileName; bool checker;
    while (true)
    {
        fileName = "";
        while (fileName.empty())
        {
            cout << "Enter the " << turn << " file Name: ";
            getline(cin, fileName);
        }
        checker = checkFileName(fileName);
        if (checker)
        {
            return fileName;
        }
        else
        {
            cout << "Wrong Name of Text File it should be {(letters, numbers or both).txt}, Try again." << endl;
        }
    }
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
int countNumberOfWords(string fileName)
{
    fstream file;
    file.open(fileName.c_str(), ios::in);
    int numberOfWords = 0; 
    string inputLine;
    while (getline(file, inputLine))
    {
        stringstream strLine(inputLine);
        string word;
        while (strLine >> word)
        {
            numberOfWords++;
        }
    }
    file.close();
    return numberOfWords;
}
//____________________________________________________________________________________________
int countNumberOfLines(string fileName)
{
    fstream file;
    int numberOfLines = 0;
    file.open(fileName.c_str(), ios::in);
    string inputLine;
    while (getline(file, inputLine))
    {
        numberOfLines++;
    }
    file.close();
    return numberOfLines;
}
//____________________________________________________________________________________________
int countNumberOfCharacters(string fileName)
{
    fstream file;
    file.open(fileName.c_str(), ios::in);
    int numberOfCharacters = 0;
    file.get();
    while (!file.eof() && !file.fail())
    {
        numberOfCharacters++;
        file.get();
    }
    file.close();
    return numberOfCharacters + 1;
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
        getline(cin, word);
    }
    word = makeWordLowerCase(word);
    return word;
}
//____________________________________________________________________________________________
bool searchForWordInFile(string fileName, string wordWanted)
{
    fstream file;
    file.open(fileName.c_str(), ios::in);
    string inputLine, word;
    while (getline(file, inputLine))
    {
        stringstream s(inputLine);
        while (s >> word)
        {
            word = makeWordLowerCase(word);
            if (wordWanted == word)
            {
                return true;
            }
        }
    }
    file.close();
    return false;
}