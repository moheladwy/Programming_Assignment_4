#include <Windows.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream> 
#include <regex>
#include <string>
using namespace std;

//____________________________________________________________________________________________
bool checkValidYesOrNo(string choice)
{
    bool isValidInput = true;
    if (choice.length() == 1) {
        switch (choice[0]) {
        case 'y':
        case 'Y':
            return isValidInput;
        case 'n':
        case 'N':
            return isValidInput;
        default:
            break;
        }
    }
    return !isValidInput;
}
//____________________________________________________________________________________________
string getAValidFileName(string turn = "")
{
    string fileName; bool checker;
    regex isValid("^[\\w\\-. ]+\\.txt$"); // Done. by Yusuf
    while (true)
    {
        fileName = "";
        while (fileName.empty())
        {
            cout << "Enter the" << turn << " file Name: ";
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
void clearScreen()
{
    system("CLS");
    cout << flush;
    system("CLS");
}
//____________________________________________________________________________________________
bool isClearScreen()
{
    int isWant = false;
    string choice = "";
    while (!isWant)
    {
        cout << "Do you want to clear the screen before continue or not (y)|(n): ";
        getline(cin, choice);
        isWant = checkValidYesOrNo(choice);
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
bool isEmptyFile(string fileName)
{
    fstream file;
    file.open(fileName.c_str(), ios::in);
    string inputLine, word = "";
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
void createOriginalFile(string fileName) {
    fstream originalFile;
    originalFile.open(fileName.c_str(), ios::in);
    cout << "--------------------------------------------------------------------------------------" << endl;
    if (originalFile.is_open()) {
        cout << "This file does indeed exists and will be used for your preferred operations.\n";
    }
    else {
        originalFile.open(fileName.c_str(), ios::out);
        cout << "This is a new file that have been created for you!\n";
    }
    originalFile.close();
}
//____________________________________________________________________________________________
string createTempOfOriginalFile(string originalFileName) {

    string tempFileName = "tempOfOriginal.txt";
    fstream newFile;
    fstream oldFile;
    newFile.open(tempFileName.c_str(), ios::out);
    oldFile.open(originalFileName.c_str(), ios::in);

    if (newFile.is_open()) {
        //copying the content from the old one.
        newFile << oldFile.rdbuf();
    }

    newFile.close();
    oldFile.close();

    return tempFileName;
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
        cout << "the file does not exist in the directory, I created for you with the Name that you entered.\n";
        file2.open(secondFileName.c_str(), ios::out);
        file2.close();
    }
    file.open(fileName.c_str(), ios::app);
    file2.open(secondFileName.c_str(), ios::in);
    while (getline(file2, inputLine))
    {
        file << " " << inputLine << "\n";
    }
    file.close();
    file2.close();
    cout << "Merging files done.\n";
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void countNumberOfWords(string fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile) {
        fstream file;
        int numberOfWords = 0;
        string inputLine, word;
        file.open(fileName.c_str(), ios::in);
        while (getline(file, inputLine)) {
            stringstream strLine(inputLine);
            while (strLine >> word) {
                numberOfWords++;
            }
        }
        file.close();
        cout << "The number of Words in the file = " << numberOfWords << endl;
    }
    else {
        cout << "The file is empty, There is no content in it." << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void countNumberOfLines(string fileName)
{
    fstream file;
    int numberOfLines = 0;
    string inputLine;
    file.open(fileName.c_str(), ios::in);
    while (getline(file, inputLine)) {
        numberOfLines++;
    }
    file.close();
    // because the defult of Notepad text editor that any file starts the lines and the characters from 1 not 0 like words.
    if (numberOfLines == 0) {
        cout << "The number of the Lines in the file = " << ++numberOfLines << "\n";
    }
    else {
        cout << "The number of the Lines in the file = " << numberOfLines << "\n";
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void countNumberOfCharacters(string fileName)
{
    fstream file;
    file.open(fileName.c_str(), ios::in);
    int numberOfCharacters = 0;
    file.get();
    numberOfCharacters++;
    while (!file.eof() && !file.fail()) {
        file.get();
        numberOfCharacters++;
    }
    file.close();
    cout << "The number of the characters in the file = " << numberOfCharacters << "\n";
    cout << "--------------------------------------------------------------------------------------" << endl;
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
void searchForWordInFile(string fileName)
{
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile) {
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
        if (checkWord) {
            cout << "the word {" << searchWord << "} exists in the file.\n";
        }
        else {
            cout << "the word {" << searchWord << "} does not exist in the file or the file empty.\n";
        }
    }
    else {
        cout << "The file is empty, There is no content to search in!" << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
// counting the number of times a word exists in a file. // very strict counter. // read only. // DONE - Yusuf Badr.
void countWordOccurences(string fileName) 
{
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile) {
        fstream file;
        char letter;
        string word, searchWord = getWordForSearching();
        searchWord = makeWordLowerCase(searchWord);
        int numberOfOccurences = 0;
        file.open(fileName.c_str(), ios::in);
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
    else {
        cout << "The file is empty, There is no content to count the occurences of a word!" << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
// DONE - Yusuf Badr.
void allFileToUpperCase(string fileName) {
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile) {
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
        cout << "The content of the file have turned to upper case succefully.\n";
    }
    else {
        cout << "The file is empty, There is no content to turn to upper case!" << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
// DONE - Yusuf Badr.
void allFileToLowerCase(string fileName) {
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile)
    {
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
        cout << "The content of the file have turned to lower case succefully.\n";
    }
    else {
        cout << "The file is empty, There is no content to turn to lower case!" << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
// converts the first letter of every word in the text file to capital letter. // DONE - Yusuf Badr.
void allFileToFirstCaps(string fileName) {
    // allFileToLowerCase(fileName);
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile)
    {
        fstream originalFile, newFile;
        char letter, nextChar;

        originalFile.open(fileName.c_str(), ios::in);
        newFile.open("newTemp.txt", ios::out);

        if (originalFile.peek() != EOF) {
            originalFile.get(letter);
            letter = toupper(letter);
            newFile << letter;
        }
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
                // Eladwy: I maked the rest of the word a lower case dude. 
                // bcz there is no need to call allFileToLowerCase function here.
                letter = tolower(letter); 
                newFile << letter;
            }
        }

        newFile.close();
        originalFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
        cout << "all words in the file have turned to 1st caps (1st char of each word is capital) successfully.\n";
    }
    else
    {
        cout << "The file is empty, There is no content to turn to 1st caps!" << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
// DONE - Yusuf Badr.
void saveFile(string originalFileName, string tempOriginalFileName) {

    // getting yes or no with defensive programming.
    fstream oldFile, newFile, tempFile;
    string choice = "";
    bool validInput = false;
    while (!validInput) {
        cout << "Would you like to save the current changes of this file? (y)|(n):\n";
        getline(cin, choice);
        validInput = checkValidYesOrNo(choice);
        if (!validInput)
        {
            cout << "Please enter a valid character, \"y\" or \"n\"\n";
        }
    }
    choice[0] = tolower(choice[0]);

    if (choice[0] == 'y') {

        oldFile.open(originalFileName.c_str(), ios::out);
        tempFile.open(tempOriginalFileName.c_str(), ios::in);

        if (oldFile.is_open()) {
            //copying the content from the old one.
            oldFile << tempFile.rdbuf();
        }

        oldFile.close();
        tempFile.close();
        cout << "Changes Saved!\n";
    }
    else if (choice[0] == 'n') {
        cout << "Changes not saved!\n";
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
    // ------

    // getting yes or no with defensive programming.
    choice = "";
    validInput = false;
    while (!validInput) {
        cout << "Would you like to save the file changes as a file with a different name? (y)|(n):\n";
        getline(cin, choice);
        validInput = checkValidYesOrNo(choice);
        if (!validInput)
        {
            cout << "Please enter a valid character, \"y\" or \"n\"\n";
        }
    }
    choice[0] = tolower(choice[0]);

    if (choice[0] == 'y') {
        string newFileName = getAValidFileName(" other new");
        while (newFileName == originalFileName) {
            cout << "The new name should be different from the old one.\n";
            newFileName = getAValidFileName(" other new");
        }

        newFile.open(newFileName.c_str(), ios::out);
        oldFile.open(tempOriginalFileName.c_str(), ios::in);

        if (newFile.is_open()) {
            //copying the content from the old one.
            newFile << oldFile.rdbuf();
        }

        newFile.close();
        oldFile.close();
        cout << "Saved a copy as new file successfully!\n";
    }
    else if (choice[0] == 'n') {
        cout << "OK.\n";
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
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
        if (userChoice >= 1 && userChoice <= 16)
        {
            return true;
        }
    }
    return false;
}
//____________________________________________________________________________________________
int getUserChoice() // Done By Mohamed.
{
    string getChoice;
    int setChoice;
    bool isValidChoice = false;

    while (!isValidChoice)
    {
        getChoice = "";
        while (getChoice.empty())
        {
            cout << "Enter your choice from the list above from [1:16] ya user ya habeby: ";
            getline(cin, getChoice);
        }
        isValidChoice = checkUserChoice(getChoice);
    }
    setChoice = stoi(getChoice);
    cout << "--------------------------------------------------------------------------------------" << endl;
    return setChoice;
}
//____________________________________________________________________________________________
void addingContent(string fileName) //Done by Amr.
{
    string line;
    fstream myFile;
    myFile.open(fileName.c_str(), ios::app);
    cout << "######################################################\n";
    cout << "### write here or press Enter+0000+Enter to stop ###\n";
    cout << "######################################################\n";
    while (true)
    {
        getline(cin, line);
        if (line == "0000")
        {
            break;
        }
        myFile << line << "\n";
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "text added succesfully.\n";
    cout << "--------------------------------------------------------------------------------------" << endl;
    myFile.close();
}
//____________________________________________________________________________________________
void displayContent(string fileName) //Done by Amr
{
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile) {
        string line;
        fstream myFile;
        myFile.open(fileName.c_str(), ios::in);
        cout << "The Content of the File:-\n";
        cout << "-------------------------\n";
        while (getline(myFile, line))
        {
            cout << line << "\n";
        }

        myFile.close();
        cout << "--------------------------------------------------------------------------------------" << endl;
        cout << "The content of the file have displayed succefully.\n";
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
    else {
        cout << "The file is empty, There is no content to display." << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
}
//____________________________________________________________________________________________
void emptyFileContent(string fileName) //Done by Amr
{
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile) {
        fstream myFile;
        myFile.open(fileName.c_str(), ios::out);
        myFile.close();
        cout << "The content of the file have cleared succefully.\n";
    }
    else {
        cout << "This file does indeed empty!" << endl;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}
//____________________________________________________________________________________________
void encryptFileContent(string fileName) // Done by Amr.
{

    string line, newline;
    fstream myFile, newFile;
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile)
    {
        myFile.open(fileName.c_str(), ios::in);
        newFile.open("newTemp.txt", ios::out);
        while (getline(myFile, line))
        {
            newline = "";
            for (int i = 0; i < line.length(); i++)
            {
                line[i]++;
                newline += line[i];
            }
            newFile << newline << "\n";
        }
        myFile.close();
        newFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
        cout << "The content of the file have encrypted succefully.\n";
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
    else
    {
        cout << "The file is empty, there is no content to encrypt!" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
}
//____________________________________________________________________________________________
void decryptFileContent(string fileName) //Done by Amr
{

    string line, newline;
    fstream myFile, newFile;
    bool emptyFile = isEmptyFile(fileName);
    if (!emptyFile)
    {
        myFile.open(fileName.c_str(), ios::in);
        newFile.open("newTemp.txt", ios::out);

        while (getline(myFile, line))
        {
            newline = "";
            for (int i = 0; i < line.length(); i++)
            {
                line[i]--;
                newline += line[i];
            }
            newFile << newline << "\n";
        }
        myFile.close();
        newFile.close();

        remove(fileName.c_str());
        rename("newTemp.txt", fileName.c_str());
        cout << "The content of the file have decrypted succefully.\n";
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
    else
    {
        cout << "The file is empty, there is no content to decrypt!" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
}
//____________________________________________________________________________________________
void executeUserChoice(int choice, string fileName, string originalFileName) // Done - Eladwy.
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
            countWordOccurences(fileName);
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