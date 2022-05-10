//___________________________________________________________________________________________________
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application.
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Ahmed
// Purpose: .......
// File: This is the CPP file that contain the algorithms of the functions.
//___________________________________________________________________________________________________
#include <iostream>
#include <regex>
#include <string>
#include <cctype>
#include <conio.h>
#include <unordered_map>
#include <windows.h>
#include "OpenXLSX.hpp"
using namespace std;
using namespace OpenXLSX;
//___________________________________________________________________________________________________
// code practices:
/*
 * There is a struct as you can see below.
 * Since the  user ID is unique to each user, we will identify each user of the struct by the username:
 * please note that userID is CASE-SENSITIVE
 * e.g. user <userID>;
 *      <userID>.email = "test@email.com"
 * below is another example
 * e.g. user ahmedAdam;
 *      ahmedAdam.email = "test2@email.com"
*/
//___________________________________________________________________________________________________
struct user {
    string ID;
    string fullName;
    string phoneNumber;
    string password;
    string email;
    int indexUserInFile;
};

const int colmID = 1, colmFullName = 2, colmPhoneNumber = 3, colmEmail = 4, colmPassword = 5;
user userProfile;
// key: userID, value: struct of this exact user
unordered_map <string, user> getUserData;
//___________________________________________________________________________________________________
// operator overloading for struct, you can modify to allow for direct output of each user in the Excel file
ostream& operator<< (ostream& out, user inUser){
    out << ",Full Name: " << inUser.fullName << " ,Phone Number: " << inUser.phoneNumber << " ,Email: " << inUser.email << " ,Password: " << inUser.password;
    return out;
}
//___________________________________________________________________________________________________
string encryptPassword(string& plainText) { // Atbash Cipher
    string cipherText;
    char cipherLetter;
    for (auto i: plainText){
        if (isupper(i)){
            cipherLetter = i + 25 - 2 * (i - 'A'); // equation to get new cipher letter
        } else if (islower(i)) {
            cipherLetter = i + 25 - 2 * (i - 'a');
        } else {
            cipherLetter = i;
        }
        cipherText += cipherLetter;
    }
    return cipherText;
}
//___________________________________________________________________________________________________
string decryptPassword(string& cipherText) {
    string plainText;
    char plainLetter;
    for (auto i: cipherText){
        if (isupper(i)){
            plainLetter = i - 25 + 2 * ('Z' - i); // equation to get new plain letter
        } else if (islower(i)) {
            plainLetter = i - 25 + 2 * ('z' - i);
        } else {
            plainLetter = i;
        }
        plainText += plainLetter;
    }
    return plainText;
}
//___________________________________________________________________________________________________
//===== to be done =====
void fetchXLSXFile(){
    // get the user data already in file and populate to the map.
    XLDocument usersData;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");
    int numberOfUsers = workSheet.rowCount();
    for (int index = 2; index <= numberOfUsers; ++index) {
        userProfile.indexUserInFile = index;
        userProfile.ID = workSheet.cell(index,colmID).value().get<string>();
        userProfile.fullName = workSheet.cell(index,colmFullName).value().get<string>();
        userProfile.phoneNumber = workSheet.cell(index,colmPhoneNumber).value().get<string>();
        userProfile.email = workSheet.cell(index,colmEmail).value().get<string>();
        userProfile.password = workSheet.cell(index,colmPassword).value().get<string>();
        userProfile.password = decryptPassword(userProfile.password);
        getUserData.insert({userProfile.ID,userProfile});
    }
    usersData.close();
    for (auto itr = getUserData.begin(); itr != getUserData.end(); itr++) {
        cout << "ID: " << itr->first << " " << itr->second << "\n";
    }
}
//___________________________________________________________________________________________________
void updateXLSXFile(int& indexUserInFile, string& newPassword, string& userID){
    // changes made in unordered map should be updated to xlsx file directly.

    // change the password in the map.
    user tempProfile = getUserData[userID];
    tempProfile.password = newPassword;
    getUserData[userID] = tempProfile;

    // change the password in the file of the users.
    XLDocument usersData;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");
    workSheet.cell(indexUserInFile,colmPassword).value() = encryptPassword(newPassword);
    usersData.save();
    usersData.close();
}
//___________________________________________________________________________________________________
void printMainMenu()
{
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "1- Register." << endl;
    cout << "2- Login." << endl;
    cout << "3- Change Password." << endl;
    cout << "4- Forget Password." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//___________________________________________________________________________________________________
bool isYesOrNo(string& choice)
{
    bool isValidInput = true;
    if (choice.length() == 1) {
        if (choice == "y" || choice == "Y" || choice == "n" || choice == "N") return isValidInput;
        }
    return !isValidInput;
}
//___________________________________________________________________________________________________
void printEndApp()
{
    cout << "Thanks for using our Login System Application." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "Authors of the Application:-" << endl;
    cout << "----------------------------" << endl;
    cout << "1- Name: Mohamed Hussein Hassan Eladwy. ID: 20210335." << endl;
    cout << "2- Name: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502." << endl;
    cout << "3- Name: Amr Khalied Elsayed Elhennawy. ID: 20210274." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//___________________________________________________________________________________________________
void clearScreen()
{
    Sleep(60000);
    system("CLS");
    cout << flush;
    system("CLS");
}
//___________________________________________________________________________________________________
bool isClearScreen()
{
    int isWant = false;
    string choice;
    while (!isWant)
    {
        cout << "Do you want to clear the screen before continue or not (y)|(n): ";
        getline(cin, choice);
        isWant = isYesOrNo(choice);
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
//___________________________________________________________________________________________________
string makeLowerCase(string line)
{
    for (int i = 0; i < line.length(); i++) line[i] = tolower(line[i]);
    return line;
}
//___________________________________________________________________________________________________
bool checkUserChoice(string choice)
{
    if (choice.length() == 1) {
        if (!isdigit(choice[0]))
        {
            return false;
        }
        int checkChoice = stoi(choice);
        if (checkChoice >= 1 && checkChoice <= 4) {
            return true;
        }
    }
    return false;
}
//___________________________________________________________________________________________________
int getUserChoice()
{
    string getChoice;
    int setChoice;
    bool isValidChoice = false;
    while (!isValidChoice) {
        cout << "Enter your choice from the list above [1:4]: ";
        getChoice = "";
        while (getChoice.empty()) {
            getline(cin, getChoice);
        }
        isValidChoice = checkUserChoice(getChoice);
        if (!isValidChoice) {
            cout << "The Choice you entered is not an option from the list,	Try again and make sure to enter a valid option from the list." << endl;
        }
    }
    cout << "----------------------------------------------------------------------------------------" << endl;
    setChoice = stoi(getChoice);
    return setChoice;
}
//___________________________________________________________________________________________________
bool isValidPassword(string& password)
{
    regex passwordFormat("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#<>=?!+@$%^&*-]).{8,}$");
    bool strongPassword = regex_match(password, passwordFormat);
    return strongPassword;
}
//___________________________________________________________________________________________________
string getPassword()
{
    first:
    cout << "The password must contain small letters, capital letters, numbers, special characters and be greater than 7 characters." << endl;
    cout << "Enter a password that follow the instructions above: ";
    char tempChar; string firstPassword, repeatedPassword;
    for(int letterPassword1 = 0;;) //infinite loop
    {
        tempChar = getch(); //stores char typed in tempChar
        if(tempChar >= 32 && tempChar <= 126)
            //check if tempChar is numeric , alphabet, special character
        {
            //stores tempChar in pass
            firstPassword += tempChar;
            ++letterPassword1;
            cout << "*" ;
        }
        if(tempChar == '\b' && letterPassword1 >= 1) //if user typed backspace
            //letterPassword1 should be greater than 0.
        {
            cout << "\b \b"; //rub the character behind the cursor.
            --letterPassword1;
        }
        if(tempChar == '\r') //if enter is pressed
        {
            //null means end of string.
            firstPassword += '\0';
            break; //break the loop
        }
    }
    if (!isValidPassword(firstPassword))
    {
        cout << endl << "The password Must follow the above instructions, try again." << endl;
        goto first;
    }
    else
    {
        second:
        cout << endl << "Enter the Password again to confirm the first one: ";
        for(int letterPassword2 = 0;;) //infinite loop
        {
            tempChar = getch(); //stores char typed in tempChar
            if(tempChar >= 32 && tempChar <= 126)
                //check if tempChar is numeric , alphabet, special character
            {
                //stores tempChar in pass
                repeatedPassword += tempChar;
                ++letterPassword2;
                cout << "*" ;
            }
            if(tempChar == '\b' && letterPassword2 >= 1) //if user typed backspace
                //letterPassword2 should be greater than 0.
            {
                cout << "\b \b"; //rub the character behind the cursor.
                --letterPassword2;
            }
            if(tempChar == '\r') //if enter is pressed
            {
                //null means end of string.
                repeatedPassword += '\0';
                break; //break the loop
            }
        }
        if (repeatedPassword == firstPassword)
        {
            return firstPassword;
        }
        else
        {
            cout << endl << "The Password doesn't match with the first one, Try again." << endl;
            goto second;
        }
    }
}
//___________________________________________________________________________________________________
void userRegister(string& ID, string& fullName, string& phoneNumber, string& email)
{
    XLDocument usersData; user newUser;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");
    int indexUserInFile = workSheet.rowCount();
    string password = getPassword();

    newUser.indexUserInFile = indexUserInFile + 1;
    newUser.ID = ID;
    newUser.fullName = fullName;
    newUser.phoneNumber = phoneNumber;
    newUser.email = email;
    newUser.password = password;

    getUserData.insert({ID, newUser});

    workSheet.cell(indexUserInFile, colmID).value() = ID;
    workSheet.cell(indexUserInFile, colmFullName).value() = fullName;
    workSheet.cell(indexUserInFile, colmPhoneNumber).value() = phoneNumber;
    workSheet.cell(indexUserInFile, colmEmail).value() = email;
    workSheet.cell(indexUserInFile, colmPassword).value() = encryptPassword(password); // Encrypting the password that will be stored in the file.

    usersData.save();
    usersData.close();
}
//___________________________________________________________________________________________________
string userLogin(string ID, string password){ // parameter password is assumed to be the plain password.
    return "";
}
//___________________________________________________________________________________________________