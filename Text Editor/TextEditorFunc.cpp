#include <Windows.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
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
void mergeAnotherFile(string fileName)
{
    fstream file, file2;
    string inputLine, secondFileName = getFileName("Second");
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
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}
//____________________________________________________________________________________________
// counting the number of times a word exists in a file // very strict counter
int countWordOccurences(string filename, string searchWord){ // read only
    fstream file;
    file.open(filename, ios::in);
    searchWord = makeWordLowerCase(searchWord);
    char letter;
    int counter = 0;
    while (!file.eof() && !file.fail()) {
        string word;
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
// open and closing file done in the function
void allFileToUpperCase(string filename) { // read and write
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
// open and closing file done in the function
void allFileToLowerCase(string filename) { // read and write
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
// converts the first letter of every word in the text file to capital letter
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
    while (originalFile.peek() != EOF) {
        char nextChar = originalFile.get();
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
bool checkUserChoice(string choice) // Done. By Mohamed.
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
void save(fstream& file) // Almost Done By Mohamed.
{
    file.flush();
}
//____________________________________________________________________________________________
void addingContent(string fileName) //Done by Amr
{
  string line;
  fstream myFile;
  myFile.open(fileName.c_str(), ios::app);
  cout << "##################" << "\n";
  cout << "### write here ###" << "\n";
  cout << "##################" << "\n";
  while (true)
  {
     getline(cin, line);
     if(cin.eof())
      {
        cout << "\n" << "text added." << "\n";
        break;
      }
      myFile << line << "\n";
 
  }
}
//__________________________________________________________________________________________
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
//_________________________________________________________________________________________
void emptyFileContent(string fileName) //Done by Amr
{
    fstream myFile;
    myFile.open(fileName.c_str(), ios::trunc);
    myFile.close();
}
//__________________________________________________________________________________________
void encryptFileContent(string fileName) //Done by Amr
{

    string  line,newline;
    int stage1,stage2;
    fstream myfile(fileName.c_str(),ios::in);
    fstream newfile("newTemp.txt",ios::out);
  if (myfile.is_open())
  {
      while (getline(myfile,line))
      {
        newline="";
        for (int i = 0; i < line.length(); i++)
        {
        if (isupper(line[i]))
        {           
          stage1 = line[i] - 28;
          stage2 = 127 - stage2;
        }
        else if (islower(line[i]))
        {
            stage1 = line[i] - 60;
            stage2= 159 - stage2;
        }
        else if (isspace(line[i]))
        {
            stage2 = ' ';
        }
        
         cout<<char(stage2);
         newline+=char(stage2);
        }
        newfile<< newline<<"\n";
        cout<<endl;
      }
       myfile.close();
       newfile.close();
      remove(fileName.c_str());
      rename("newTemp.txt", fileName.c_str());
     
  }
  
}
//___________________________________________________________________
void decryptingFileContent(string fileName) //Done by Amr
{

    string  line,newline;
    int stage1,stage2;
    fstream myfile(fileName.c_str(),ios::in);
    fstream newfile("newTemp.txt",ios::out);
  if (myfile.is_open())
  {
      while (getline(myfile,line))
      {
        newline="";
        for (int i = 0; i < line.length(); i++)
        {
        if (isupper(line[i]))
        {           
          stage1 = 127 - line[i];
          stage2 = stage1 + 28;
        }
        else if (islower(line[i]))
        {
            stage1 = 159-line[i];
            stage2= stage1 + 60;
        }
        else if (isspace(line[i]))
        {
            stage2 = ' ';
        }
        
         cout<<char(stage2);
         newline+=char(stage2);
        }
        newfile<< newline<<"\n";
        cout<<endl;
      }
       myfile.close();
       newfile.close();
      remove(fileName.c_str());
      rename("newTemp.txt", fileName.c_str());
     
  }
  
}