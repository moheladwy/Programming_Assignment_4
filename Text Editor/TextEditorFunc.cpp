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
    fstream theFile; bool checker = false;
    theFile.open(fileName.c_str(), ios::in);
    if (theFile.is_open())
    {
        checker = true;
    }
    theFile.close();
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
    bool isValidFile;
    string inputLine, secondFileName;
    secondFileName = getAValidFileName(" Second");
    isValidFile = checkValidFile(secondFileName);
    if (!isValidFile)
    {
        cout << "the file does not exist in the directory, I created for you.\n";
        file2.open(secondFileName.c_str(), ios::out);
        file2.close();
    }
    file.open(fileName.c_str(), ios::app);
    file2.open(secondFileName.c_str(), ios::in);
    while (getline(file2, inputLine))
    {
        file << inputLine << "\n";
    }
    file.close();
    file2.close();
    cout << "Merging files done.\n";
}
//____________________________________________________________________________________________
void countNumberOfWords(string fileName)
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
    if (numberOfWords == 0) {
        cout << "There is no words in this file.\n";
    }
    else {
        cout << "The number of Words in the file = " << numberOfWords << "\n";
    }
}
//____________________________________________________________________________________________
void countNumberOfLines(string fileName)
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
    cout << "The number of the Lines in the file = " << numberOfLines << "\n";
}
//____________________________________________________________________________________________
void countNumberOfCharacters(string fileName)
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
    cout << "The number of the characters in the file = " << numberOfCharacters << "\n";
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
void searchForWordInFile(string fileName, string searchWord)
{
    fstream file;
    string inputLine, word;
    bool checkWord = false;
    file.open(fileName.c_str(), ios::in);
    while (getline(file, inputLine))
    {
        stringstream strLine(inputLine);
        while (strLine >> word)
        {
            word = makeWordLowerCase(word);
            if (searchWord == word)
            {
                checkWord = true;
                break;
            }
        }
    }
    file.close();
    if (checkWord) {
        cout << "\n" << "the word exists in the file.\n";
    }
    else {
        cout << "\n" << "the word does not exist in the file.\n";
    }
}
//____________________________________________________________________________________________
// counting the number of times a word exists in a file. // very strict counter. // read only. // DONE - Yusuf Badr.
void countWordOccurences(string fileName, string searchWord) {
    fstream file;
    searchWord = makeWordLowerCase(searchWord);
    char letter;
    string word;
    int numberOfOccurences = 0;
    file.open(fileName, ios::in);
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
            numberOfOccurences += 1;
        }
        file.ignore(1);
    }
    file.close();
    cout << "The Number of the occurences of the word {" << searchWord << "} in the file = " << numberOfOccurences << "\n";
}
//____________________________________________________________________________________________
// DONE - Yusuf Badr.
void allFileToUpperCase(string fileName) {
    fstream originalFile, newFile;
    char letter;

    originalFile.open(fileName.c_str(), ios::in);
    newFile.open("newTemp.txt", ios::out);

    while (originalFile.peek() != EOF) {
        originalFile.get(letter);
        letter = toupper(letter);
        newFile << letter;
    }

    newFile.close();
    originalFile.close();

    remove(fileName.c_str());
    rename("newTemp.txt", fileName.c_str());
    cout << "The content of the file {" << fileName << "} have turned to upper case succefully.\n";
}
//____________________________________________________________________________________________
// DONE - Yusuf Badr.
void allFileToLowerCase(string fileName) {
    fstream originalFile, newFile;
    char letter;

    originalFile.open(fileName.c_str(), ios::in);
    newFile.open("newTemp.txt", ios::out);

    while (originalFile.peek() != EOF) {
        originalFile.get(letter);
        letter = tolower(letter);
        newFile << letter;
    }

    newFile.close();
    originalFile.close();

    remove(fileName.c_str());
    rename("newTemp.txt", fileName.c_str());
    cout << "The content of the file {" << fileName << "} have turned to lower case succefully.\n";
}
//____________________________________________________________________________________________
// converts the first letter of every word in the text file to capital letter. // DONE - Yusuf Badr.
void allFileToFirstCaps(string fileName) {
    fstream originalFile, newFile;
    char letter;

    originalFile.open(fileName.c_str(), ios::in);
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

    remove(fileName.c_str());
    rename("newTemp.txt", fileName.c_str());
    cout << "all words in the file {" << fileName << "} have turned to 1st caps (1st char of each word is capital) succefully.\n";
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
        cout << "Saved a copy as new file successfully!\n";
    }
    else {
        cout << "OK, saved original file only successfully!\n";
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
    cout << "###############################################\n";
    cout << "### write here or press Ctrl+Z+Enter to stop ###\n";
    cout << "###############################################\n";
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
    myFile.close();
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
    cout << "\n" << "The content of the file {" << fileName << "} have displayed succefully.\n";
}
//____________________________________________________________________________________________
void emptyFileContent(string fileName) //Done by Amr
{
    fstream myFile;
    myFile.open(fileName.c_str(), ios::trunc);
    myFile.close();
    cout << "\n" << "The content of the file {" << fileName << "} have cleared succefully.\n";
}
//____________________________________________________________________________________________
void encryptFileContent(string fileName) // Done by Amr.
{

    string line, newline;
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
        cout << "The content of the file {" << fileName << "} have encrypted succefully.\n";
    }
}
//____________________________________________________________________________________________
void decryptFileContent(string fileName) //Done by Amr
{

    string line, newline;
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
        cout << "The content of the file {" << fileName << "} have decrypted succefully.\n";
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
            break;
        }

        case 7: {
            countNumberOfWords(fileName);
            break;
        }

        case 8: {
            countNumberOfCharacters(fileName);
            break;
        }

        case 9: {
            countNumberOfLines(fileName);
            break;
        }

        case 10: {
            searchForWordInFile(fileName, searchWord);
            break;
        }

        case 11: {
            countWordOccurences(fileName, searchWord);
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
        cout << "Thanks for using our Text File Editor Program.\n";
    }
}
//____________________________________________________________________________________________
