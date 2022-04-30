#include <Windows.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
using namespace std;
//____________________________________________________________________________________________
string getAValidFileName(string turn = "")
{
    string fileName; bool checker;
    regex isValid("^[\\w\\-. ]+\\.txt$"); // Done. by Eladwy.
    while (true)
    {
        fileName = "";
        while (fileName.empty())
        {
            cout << "Enter the" << turn << " file Name:\n";
            getline(cin, fileName);
        }
        checker = regex_match(fileName, isValid);
        if (checker)
        {
            return fileName;
        }
        else
        {
            cout << "Incorrect format\n" << "Must contain only: letters, numbers, \'_\', \'-\', \'.\', \' \', followed by .txt\n" << endl;
        }
    }
}
//____________________________________________________________________________________________
bool checkValidFile(string fileName)
{
    fstream outfile; bool checker = false;
    outfile.open(fileName.c_str(), ios::in);
    if (outfile.is_open())
    {
        checker = true;
    }
    outfile.close();
    return checker;
}
//____________________________________________________________________________________________
void printMainMenu()
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
void mergeAnotherFile(string fileName)
{
    fstream file, file2;
    string inputLine, secondFileName = getAValidFileName(" Second");
    file.open(fileName.c_str(), ios::app);
    file2.open(secondFileName.c_str(), ios::in);
    while (getline(file2, inputLine))
    {
        file << inputLine << "\n";
    }
    file.close();
    file2.close();
}
//____________________________________________________________________________________________
int countNumberOfWords(string fileName)
{
    fstream file;
    file.open(fileName.c_str(), ios::in);
    int numberOfWords = 0;
    string inputLine, word;
    while (getline(file, inputLine))
    {
        stringstream strLine(inputLine);
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
    string inputLine;
    file.open(fileName.c_str(), ios::in);
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
    numberOfCharacters++;
    while (!file.eof() && !file.fail())
    {
        numberOfCharacters++;
        file.get();
    }
    file.close();
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
    string word = "";
    while (word.empty())
    {
        cout << "Enter the word you want to search about in the file: ";
        getline(cin, word);
    }
    word = makeWordLowerCase(word);
    return word;
}
//____________________________________________________________________________________________
bool searchForWordInFile(string fileName, string searchWord)
{
    fstream file;
    string inputLine, word;
    file.open(fileName.c_str(), ios::in);
    while (getline(file, inputLine))
    {
        stringstream strLine(inputLine);
        while (strLine >> word)
        {
            word = makeWordLowerCase(word);
            if (searchWord == word)
            {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}
//____________________________________________________________________________________________
// counting the number of times a word exists in a file. // very strict counter. // read only. // DONE - Yusuf Badr.
int countWordOccurences(string filename, string searchWord) {
    fstream file;
    searchWord = makeWordLowerCase(searchWord);
    char letter;
    string word;
    int counter = 0;
    file.open(filename, ios::in);
    while (!file.eof() && !file.fail()) {
        word = "";
        while (file.peek() != ' ' && file.peek() != '\n' && file.peek() != EOF) {
            file.get(letter);
            if (isalpha(letter)) {
                letter = tolower(letter);
            }
            word += letter;
        }
        if (word == searchWord) {
            counter += 1;
        }
        file.ignore(1);
    }
    file.close();
    return counter;
}
//____________________________________________________________________________________________
// open and closing file done in the function. // read and write. // DONE - Yusuf Badr.
void allFileToUpperCase(string filename) {
    fstream originalFile, newFile;
    char letter;

    originalFile.open(filename.c_str(), ios::in);
    newFile.open("newTemp.txt", ios::out);

    while (originalFile.peek() != EOF) {
        originalFile.get(letter);
        letter = toupper(letter);
        newFile << letter;
    }

    newFile.close();
    originalFile.close();

    remove(filename.c_str());
    rename("newTemp.txt", filename.c_str());
}
//____________________________________________________________________________________________
// open and closing file done in the function. // read and write. // DONE - Yusuf Badr.
void allFileToLowerCase(string filename) {
    fstream originalFile, newFile;
    char letter;

    originalFile.open(filename.c_str(), ios::in);
    newFile.open("newTemp.txt", ios::out);

    while (originalFile.peek() != EOF) {
        originalFile.get(letter);
        letter = tolower(letter);
        newFile << letter;
    }

    newFile.close();
    originalFile.close();

    remove(filename.c_str());
    rename("newTemp.txt", filename.c_str());
}
//____________________________________________________________________________________________
// converts the first letter of every word in the text file to capital letter. // DONE - Yusuf Badr.
void allFileToFirstCaps(string filename) {
    fstream originalFile, newFile;
    char letter;

    originalFile.open(filename.c_str(), ios::in);
    newFile.open("newTemp.txt", ios::out);

    if (originalFile.peek() != EOF) {
        originalFile.get(letter);
        letter = toupper(letter);
        newFile << letter;
    }
    char nextChar;
    while (originalFile.peek() != EOF) {
        nextChar = originalFile.get();
        if ((nextChar == ' ' or nextChar == '\n') and isalpha(originalFile.peek())) {
            originalFile.unget();
            originalFile.get(letter);
            newFile << letter;
            originalFile.get(letter);
            letter = toupper(letter);
            newFile << letter;
        }
        else {
            originalFile.unget();
            originalFile.get(letter);
            newFile << letter;
        }
    }

    newFile.close();
    originalFile.close();

    remove(filename.c_str());
    rename("newTemp.txt", filename.c_str());
}
//____________________________________________________________________________________________
// DONE - Yusuf Badr.
void saveFile(string existingFileName) {
    string choice = "";
    // getting yes or no with defensive programming.
    bool validInput = false;
    while (!validInput) {
        cout << "Would you like to save the file AGAIN with a different name (y)|(n): ";
        getline(cin, choice);

        if (choice.length() == 1) {
            switch (choice[0]) {
            case 'y':
            case 'Y':
                validInput = true;
                break;
            case 'n':
            case 'N':
                validInput = true;
                break;
            default:
                cout << "invalid character try again.\n";
            }
        }
        else {
            cout << "Please enter one CHARACTER y/n\n";
        }
    }

    choice[0] = tolower(choice[0]);
    if (choice[0] == 'y') {
        string newFileName = getAValidFileName(" other new");
        while (newFileName == existingFileName) {
            cout << "The new name should be different from the old one.\n";
            newFileName = getAValidFileName(" other new");
        }

        fstream newFile;
        fstream oldFile;
        newFile.open(newFileName.c_str(), ios::out);
        oldFile.open(existingFileName.c_str(), ios::in);

        if (newFile.is_open()) {
            //copying the content from the old one.
            newFile << oldFile.rdbuf();
        }

        newFile.close();
        oldFile.close();
        cout << "Saved a copy as new file successfully!";
    }
    else {
        cout << "OK, saved original file only successfully!";
    }
}
//____________________________________________________________________________________________
bool checkUserChoice(string choice) // Done. // By Mohamed.
{
    if ((choice.length() == 1 || choice.length() == 2))
    {
        // check if all the letters in the input is digit. 
        for (auto letter : choice)
        {
            if (!isdigit(letter))
            {
                return false;
            }
        }

        // check the range of the user choice. 
        int userChoice = stoi(choice);
        if (userChoice > 0 && userChoice < 17)
        {
            return true;
        }
    }

    return false;
}
//____________________________________________________________________________________________
int getUserChoice() // Done By Mohamed.
{
    string getChoice = "";
    int setChoice;
    bool checker = true;

    while (checker)
    {
        while (getChoice.empty())
        {
            cout << "Enter your choice from the list above from [1:16] ya user ya habeby: ";
            getline(cin, getChoice);
        }

        checker = checkUserChoice(getChoice);
    }

    setChoice = stoi(getChoice);
    return setChoice;
}
//____________________________________________________________________________________________
void addingContent(string fileName) //Done by Amr.
{
    string line;
    fstream myFile;
    myFile.open(fileName.c_str(), ios::app);
    cout << "##################\n";
    cout << "### write here ###\n";
    cout << "##################\n";
    while (true)
    {
        getline(cin, line);
        if (cin.eof())
        {
            cout << "\n" << "text added.\n";
            break;
        }
        myFile << line << "\n";
    }
}
//____________________________________________________________________________________________
void displayContent(string fileName) //Done by Amr
{
    string line;
    fstream myFile;
    myFile.open(fileName.c_str(), ios::in);
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            cout << line << "\n";
        }

        myFile.close();
    }
}
//____________________________________________________________________________________________
void emptyFileContent(string fileName) //Done by Amr
{
    fstream myFile;
    myFile.open(fileName.c_str(), ios::trunc);
    myFile.close();
}
//____________________________________________________________________________________________
void encryptFileContent(string fileName) // Done by Amr.
{

    string line, newline;
    int stage1, stage2;
    fstream myFile;
    fstream newFile;

    myFile.open(fileName.c_str(), ios::in);
    newFile.open("newTemp.txt", ios::out);

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            newline = "";
            for (int i = 0; i < line.length(); i++)
            {
                line[i]++;
                cout << line[i];
                newline += line[i];
            }
            newFile << newline << "\n";
            cout << "\n"; // Why are you printing the new line amr ?? (Q:from Mohamed)
        }
        myFile.close();
        newFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
    }
}
//____________________________________________________________________________________________
void decryptFileContent(string fileName) //Done by Amr
{

    string line, newline;
    int stage1, stage2;
    fstream myFile;
    fstream newFile;

    myFile.open(fileName.c_str(), ios::in);
    newFile.open("newTemp.txt", ios::out);

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            newline = "";
            for (int i = 0; i < line.length(); i++)
            {
                line[i]--;
                cout << line[i];
                newline += line[i];
            }
            newFile << newline << "\n";
            cout << "\n"; // Why are you printing the new line amr ?? (Q:from Mohamed)
        }
        myFile.close();
        newFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
    }
}
//____________________________________________________________________________________________
void executeUserChoice(int choice, string fileName, string searchWord) // Done - Eladwy.
{
    if (choice != 16) {
        switch (choice) {

        case 1: {
            addingContent(fileName);
            break;
        }

        case 2: {
            displayContent(fileName);
            break;
        }

        case 3: {
            emptyFileContent(fileName);
            break;
        }

        case 4: {
            encryptFileContent(fileName);
            break;
        }

        case 5: {
            decryptFileContent(fileName);
            break;
        }

        case 6: {
            mergeAnotherFile(fileName);
            cout << "Merging files is done.\n";
            break;
        }

        case 7: {
            int numberOfWords = countNumberOfWords(fileName);
            cout << "The number of the Words in the file = " << numberOfWords << "\n";
            break;
        }

        case 8: {
            int numberOfChars = countNumberOfCharacters(fileName);
            cout << "The number of the characters in the file = " << numberOfChars << "\n";
            break;
        }

        case 9: {
            int numberOfLines = countNumberOfLines(fileName);
            cout << "The number of the Lines in the file = " << numberOfLines << "\n";
            break;
        }

        case 10: {
            bool checkWord = searchForWordInFile(fileName, searchWord);
            if (checkWord) {
                cout << "\n" << "the word exists in the file.\n";
            }
            else {
                cout << "\n" << "the word does not exist in the file.\n";
            }
            break;
        }

        case 11: {
            int numberOfOccurences = countWordOccurences(fileName, searchWord);
            cout << "The Number of the occurences of the word {" << searchWord << "} in the file = " << numberOfOccurences << "\n";
            break;
        }

        case 12: {
            allFileToUpperCase(fileName);
            break;
        }

        case 13: {
            allFileToLowerCase(fileName);
            break;
        }

        case 14: {
            allFileToFirstCaps(fileName);
            break;
        }

        case 15: {
            saveFile(fileName);
            break;
        }

        default:
            break;
        }
    }
    else {
        cout << "Thanks for using our Text File Program.\n";
    }
}
//____________________________________________________________________________________________