//____________________________________________________________________________________________
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Text Editor Application
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Ahmed
// Purpose: Allow the user to open text files with write and reading from.
// File: This is the CPP file that contain the algorithms of the functions.
//____________________________________________________________________________________________
#include <iostream>
#include <cctype>
#include <fstream>
#include <regex>
#include <string>
using namespace std;
//____________________________________________________________________________________________
// general Functions for the program that used many times in many functions.
//____________________________________________________________________________________________
bool isValidYesOrNo(const string &choice)
{
    bool isValidInput = true;
    if (choice == "Y" || choice == "y" || choice == "N" || choice == "n")
    {
        return isValidInput;
    }
    return !isValidInput;
}
//____________________________________________________________________________________________
bool isValidFile(const string &fileName)
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
bool isClearScreen()
{
    int isWant = false;
    string choice;
    while (!isWant)
    {
        cout << "Do you want to clear the screen before continue or not (y)|(n): ";
        getline(cin, choice);
        isWant = isValidYesOrNo(choice);
        if (!isWant)
        {
            cout << "Please enter a choice from (y) or (n) only, Try again.\n";
        }
        else
        {
            if (choice == "n" || choice == "N")
            {
                return !isWant;
            }
        }
    }
    return isWant;
}
//____________________________________________________________________________________________
bool isEmptyFile(const string &fileName)
{
    fstream file; string inputLine, word;
    file.open(fileName.c_str(), ios::in);
    getline(file, inputLine);
    stringstream strLine(inputLine);
    strLine >> word;
    file.close();
    if (word.empty())
    {
        return true;
    }
    return false;
}
//____________________________________________________________________________________________
bool isValidUserChoice(const string &choice)
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
        if (userChoice >= 1 && userChoice <= 16)
        {
            return true;
        }
    }
    return false;
}
//____________________________________________________________________________________________
int getUserChoice()
{
    string getChoice;
    int setChoice;
    bool isValidChoice = false;

    while (!isValidChoice)
    {
        getChoice = "";
        while (getChoice.empty())
        {
            cout << "Enter your choice from the list above from [1:16]: ";
            getline(cin, getChoice);
        }
        isValidChoice = isValidUserChoice(getChoice);
    }
    setChoice = stoi(getChoice);
    cout << "--------------------------------------------------------------------------------------" << endl;
    return setChoice;
}
//____________________________________________________________________________________________
void printMainMenu()
{
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "The options of the program:-" << endl;
    cout << "----------------------------" << endl;
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
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void printEndProgram()
{
    cout << "Thanks for using our Text File Editor Program." << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "Authors of the program:-" << endl;
    cout << "------------------------" << endl;
    cout << "1- Name: Mohamed Hussein Hassan Eladwy." << endl;
    cout << "2- Name: Yusuf Elsayed Abdelrahman Bdr." << endl;
    cout << "3- Name: Amr Khalied Elsayed Elhennawy." << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void clearScreen()
{
    system("CLS");
}
//____________________________________________________________________________________________
void createOriginalFile(const string &fileName) {
    fstream originalFile;
    originalFile.open(fileName.c_str(), ios::in);
    cout << "--------------------------------------------------------------------------------------" << endl;
    if (originalFile.is_open())
    {
        cout << "This file does indeed exists and will be used for your preferred operations.\n";
    }
    else
    {
        originalFile.open(fileName.c_str(), ios::out);
        cout << "This is a new file that have been created for you!\n";
    }
    originalFile.close();
}
//____________________________________________________________________________________________
string getValidFileName(const string &turn)
{
    string fileName; bool checker;
    regex isValid(R"(^[\w\-. ]+\.txt$)");
    // regex isValid("^[\\w\\-. ]+\\.txt$");
    while (true)
    {
        fileName = "";
        while (fileName.empty())
        {
            cout << "Enter the" << turn << " File Name: ";
            getline(cin, fileName);
        }
        checker = regex_match(fileName, isValid);
        if (checker)
        {
            return fileName;
        }
        else
        {
            cout << "Incorrect format.\n" << "Must contain only: letters, numbers, \'_\', \'-\', \'.\', \' \', followed by .txt\n";
        }
    }
}
//____________________________________________________________________________________________
string createTempOfOriginalFile(const string &originalFileName) {

    string tempFileName = "tempOfOriginal.txt";
    fstream newFile, oldFile;

    newFile.open(tempFileName.c_str(), ios::out);
    oldFile.open(originalFileName.c_str(), ios::in);

    if (newFile.is_open())
    {
        //copying the content from the old one.
        newFile << oldFile.rdbuf();
    }

    newFile.close();
    oldFile.close();

    return tempFileName;
}
//____________________________________________________________________________________________
string makeWordLowerCase(string word)
{
    for (char &letter : word)
    {
        letter = char(tolower(int (letter)));
    }
    return word;
}
//____________________________________________________________________________________________
string getWordForSearching()
{
    string word;
    while (word.empty())
    {
        cout << "Enter the word you want to search about in the file: ";
        getline(cin, word);
    }
    word = makeWordLowerCase(word);
    return word;
}
//____________________________________________________________________________________________
// Main Functions of the Program.
//____________________________________________________________________________________________
void addingContent(const string &fileName)
{
    string line;
    fstream myFile;
    bool emptyFile = isEmptyFile(fileName);

    cout << "######################################################" << endl;
    cout << "#### write here or press Enter+0000+Enter to stop ####" << endl;
    cout << "######################################################" << endl;

    myFile.open(fileName.c_str(), ios::app);

    if (!emptyFile)
    {
        myFile << " ";
    }

    while (true)
    {
        getline(cin, line);
        if (line == "0000")
        {
            break;
        }
        myFile << line << "\n";
    }
    myFile.close();

    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "text added successfully." << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void displayContent(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
        cout << "The file is empty, There is no content to display." << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
    else
    {
        string line;
        fstream myFile;

        myFile.open(fileName.c_str(), ios::in);

        cout << "The content of the file:-\n";
        cout << "-------------------------\n";

        while (getline(myFile, line))
        {
            cout << line << "\n";
        }
        myFile.close();

        cout << "--------------------------------------------------------------------------------------" << endl;
        cout << "The content of the file have displayed successfully." << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
}
//____________________________________________________________________________________________
void emptyFileContent(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
        cout << "This file does indeed empty!" << endl;
    }
    else
    {
        fstream myFile;
        myFile.open(fileName.c_str(), ios::out);
        myFile.close();

        cout << "The content of the file have cleared successfully." << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void encryptFileContent(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
        cout << "The file is empty, there is no content to encrypt!" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
    else
    {
        string line, newline;
        fstream myFile, newFile;

        myFile.open(fileName.c_str(), ios::in);
        newFile.open("newTemp.txt", ios::out);

        while (getline(myFile, line))
        {
            newline = "";
            for (char &letter : line)
            {
                letter++;
                newline += letter;
            }
            newFile << newline << "\n";
        }
        myFile.close();
        newFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
        cout << "The content of the file have encrypted and secured successfully." << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
}
//____________________________________________________________________________________________
void decryptFileContent(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
        cout << "The file is empty, there is no content to decrypt!" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
    else
    {
        string line, newline;
        fstream myFile, newFile;
        myFile.open(fileName.c_str(), ios::in);
        newFile.open("newTemp.txt", ios::out);

        while (getline(myFile, line))
        {
            newline = "";
            for (char &letter : line)
            {
                letter--;
                newline += letter;
            }
            newFile << newline << "\n";
        }
        myFile.close();
        newFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
        cout << "The content of the file have decrypted successfully." << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
}
//____________________________________________________________________________________________
void mergeAnotherFile(const string &fileName)
{
    fstream file1, file2;
    bool validFile;
    string inputLine, secondFileName;

    secondFileName = getValidFileName(" Second");
    validFile = isValidFile(secondFileName);
    if (!validFile)
    {
        cout << "The first file does not exist in the directory, I created for you with the Name that you entered." << endl;
        file2.open(secondFileName.c_str(), ios::out);
        file2.close();
    }

    file1.open(fileName.c_str(), ios::app);
    file2.open(secondFileName.c_str(), ios::in);

    file1 << " ";
    while (getline(file2, inputLine))
    {
        file1 << inputLine << "\n";
    }

    file1.close();
    file2.close();

    cout << "Merging files done." << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void countNumberOfWords(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
        cout << "The file is empty, There is no words in." << endl;
    }
    else
    {
        fstream file;
        int numberOfWords = 0;
        string inputLine, word;

        file.open(fileName.c_str(), ios::in);

        while (getline(file, inputLine))
        {
            stringstream strLine(inputLine);
            while (strLine >> word)
            {
                numberOfWords++;
            }
        }
        file.close();

        cout << "The number of Words in the file = " << numberOfWords << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void countNumberOfLines(const string &fileName)
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

    // because the default of Notepad text editor that any file starts the lines and the characters from 1 not 0 like words.
    if (numberOfLines == 0)
    {
        numberOfLines++;
    }
    cout << "The number of the Lines in the file = " << numberOfLines << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void countNumberOfCharacters(const string &fileName)
{
    fstream file;
    int numberOfCharacters = 0;

    file.open(fileName.c_str(), ios::in);

    file.get(); // Get the first char that is would be in any file.
    numberOfCharacters++;

    while (!file.eof() && !file.fail())
    {
        file.get();
        numberOfCharacters++;
    }
    file.close();

    cout << "The number of the characters in the file = " << numberOfCharacters << "\n";
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void searchForWordInFile(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
        cout << "The file is empty, There is no content to search in!" << endl;
    }
    else
    {
        fstream file;
        string inputLine, word, searchWord = getWordForSearching();
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

        if (checkWord)
        {
            cout << "the word {" << searchWord << "} exists in the file." << endl;
        }
        else
        {
            cout << "the word {" << searchWord << "} does not exist in the file." << endl;
        }
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void countWordOccurrences(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
        cout << "The file is empty, There is no content to count the occurrences of a word!" << endl;
    }
    else
    {
        fstream file;
        string word, inputLine, searchWord = getWordForSearching();
        int numberOfOccurrences = 0;

        file.open(fileName.c_str(), ios::in);
        // Eladwy: My way of the code is better dude.
        while(getline(file, inputLine))
        {
            stringstream strLine(inputLine);
            while (strLine >> word)
            {
                word = makeWordLowerCase(word);
                if (searchWord == word)
                {
                    numberOfOccurrences += 1;
                }
            }
        }

//        char letter;
//        while (!file.eof() && !file.fail())
//        {
//            word = "";
//            while (file.peek() != ' ' && file.peek() != '\n' && file.peek() != EOF)
//            {
//                file.get(letter);
//                if (isalpha(letter))
//                {
//                    letter = char(tolower(letter));
//                }
//                word += letter;
//            }
//            if (word == searchWord)
//            {
//                numberOfOccurrences += 1;
//            }
//            file.ignore(1);
//        }

        file.close();

        cout << "The Number of the occurrences of the word {" << searchWord << "} in the file = " << numberOfOccurrences << "\n";
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void allFileToUpperCase(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
         cout << "The file is empty, There is no content to turn to upper case!" << endl;
    }
    else
    {
        fstream originalFile, newFile;
        char letter;

        originalFile.open(fileName.c_str(), ios::in);
        newFile.open("newTemp.txt", ios::out);

        while (originalFile.peek() != EOF) {
            originalFile.get(letter);
            letter = char(toupper(letter));
            newFile << letter;
        }

        newFile.close();
        originalFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
        cout << "The content of the file have turned to upper case successfully." << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void allFileToLowerCase(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
        cout << "The file is empty, There is no content to turn to lower case!" << endl;
    }
    else
    {
        fstream originalFile, newFile;
        char letter;

        originalFile.open(fileName.c_str(), ios::in);
        newFile.open("newTemp.txt", ios::out);

        while (originalFile.peek() != EOF) {
            originalFile.get(letter);
            letter = char(tolower(letter));
            newFile << letter;
        }

        newFile.close();
        originalFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
        cout << "The content of the file have turned to lower case successfully." << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void allFileToFirstCaps(const string &fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (emptyFile)
    {
        cout << "The file is empty, There is no content to turn to 1st caps!" << endl;
    }
    else
    {
        fstream originalFile, newFile;
        string inputLine, word;

        originalFile.open(fileName.c_str(), ios::in);
        newFile.open("newTemp.txt", ios::out);

        // Eladwy: My way is better dude.
        while(getline(originalFile, inputLine))
        {
            stringstream strLine(inputLine);
            while (strLine >> word)
            {
                word = makeWordLowerCase(word);
                word[0] = char(toupper(word[0]));
                newFile << word << " ";
            }
            newFile << "\n";
        }

//        char letter, nextChar;
//        if (originalFile.peek() != EOF)
//        {
//            originalFile.get(letter);
//            letter = char (toupper(letter));
//            newFile << letter;
//        }
//        while (originalFile.peek() != EOF)
//        {
//            nextChar = char(originalFile.get());
//            if ((nextChar == ' ' or nextChar == '\n') and isalpha(originalFile.peek()))
//            {
//                originalFile.unget();
//                originalFile.get(letter);
//                newFile << letter;
//                originalFile.get(letter);
//                letter = char(toupper(letter));
//                newFile << letter;
//            }
//            else
//            {
//                originalFile.unget();
//                originalFile.get(letter);
//                // Eladwy: I made the rest of the word a lower case dude.
//                // bcz there is no need to call allFileToLowerCase function here.
//                letter = char(tolower(letter));
//                newFile << letter;
//            }
//        }

        newFile.close();
        originalFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
        cout << "all words in the file have turned to 1st caps successfully." << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void saveFile(const string &originalFileName, const string &tempOriginalFileName)
{
    // getting yes or no with defensive programming.
    fstream oldFile, newFile, tempFile;
    string choice;
    bool validInput = false;

    while (!validInput)
    {
        cout << "Would you like to save the current changes of this file? (y)|(n): ";
        getline(cin, choice);
        validInput = isValidYesOrNo(choice);
        if (!validInput)
        {
            cout << "Please enter a valid character, (y)|(n)." << endl;
        }
    }
    choice[0] = char(tolower(choice[0]));

    if (choice[0] == 'y')
    {

        oldFile.open(originalFileName.c_str(), ios::out);
        tempFile.open(tempOriginalFileName.c_str(), ios::in);

        if (oldFile.is_open())
        {
            //copying the content from the old one.
            oldFile << tempFile.rdbuf();
        }

        oldFile.close();
        tempFile.close();
        cout << "Changes Saved!" << endl;
    }
    else if (choice[0] == 'n')
    {
        cout << "Changes not saved!" << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
    // ------

    // getting yes or no with defensive programming.
    choice = "";
    validInput = false;
    while (!validInput)
    {
        cout << "Would you like to save the file changes as a file with a different name? (y)|(n): ";
        getline(cin, choice);
        validInput = isValidYesOrNo(choice);
        if (!validInput)
        {
            cout << "Please enter a valid character, (y)|(n)." << endl;
        }
    }
    choice[0] = char(tolower(choice[0]));

    if (choice[0] == 'y')
    {
        string newFileName = getValidFileName(" other new");
        while (newFileName == originalFileName)
        {
            cout << "The new name should be different from the old one." << endl;
            newFileName = getValidFileName(" other new");
        }

        newFile.open(newFileName.c_str(), ios::out);
        oldFile.open(tempOriginalFileName.c_str(), ios::in);

        if (newFile.is_open())
        {
            //copying the content from the old one.
            newFile << oldFile.rdbuf();
        }

        newFile.close();
        oldFile.close();

        cout << "Saved a copy as new file successfully!" << endl;
    }
    else if (choice[0] == 'n')
    {
        cout << "OK." << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void executeUserChoice(int choice, const string &fileName, const string &originalFileName)
{
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
            searchForWordInFile(fileName);
            break;
        }

        case 11: {
            countWordOccurrences(fileName);
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
            saveFile(originalFileName, fileName);
            break;
        }

        default:
            break;
        }
}
//____________________________________________________________________________________________