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
// key: userID, value: struct of this exact user
unordered_map <string, user> getUserData;
//___________________________________________________________________________________________________
// operator overloading for struct, you can modify to allow for direct output of each user in the Excel file
ostream& operator<< (ostream& out, user inUser){
    out << ",Full Name: " << inUser.fullName << " ,Phone Number: " << inUser.phoneNumber << " ,Email: " << inUser.email << " ,Password: " << inUser.password;
    return out;
}
//___________________________________________________________________________________________________
string encryptPassword(const string& plainText) { // Atbash Cipher
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
string decryptPassword(const string& cipherText) {
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
    user userProfile;
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
string getPassword(string type)
{
    char tempChar; string password;
    cout << "The password must contain small letters (a,b ..etc), capital letters (A,B ..etc), numbers (0,1 ..etc), special characters (@,# ..etc) and be greater than 7 characters." << endl;
    while (true)
    {
        cout << "Enter the" << type << " password that follow the instructions above: ";
        for(int count = 0;;) //infinite loop
        {
            tempChar = getch(); //stores char typed in tempChar
            if(tempChar >= 32 && tempChar <= 126)//
                //check if tempChar is numeric , alphabet, special character
            {
                //stores tempChar in pass
                password += tempChar;
                ++count;
                cout << "*" ;
            }
            if(tempChar == '\b' && count >= 1) //if user typed backspace
                //count should be greater than 0.
            {
                cout << "\b \b"; //rub the character behind the cursor.
                --count;
            }
            if(tempChar == '\r') //if enter is pressed
            {
                //null means end of string.
                password += '\0';
                break; //break the loop
            }
        }
        if (!isValidPassword(password))
        {
            cout << "The password must contain small letters (a,b ..etc), capital letters (A,B ..etc), numbers (0,1 ..etc), special characters (@,# ..etc) and be greater than 7 characters." << endl;
            cout << "The password Must follow the above instructions, try again." << endl;
            password = "";
        }
        else
        {
            return password;
        }
    }
}
//___________________________________________________________________________________________________
void userLogin() {// parameter password is assumed to be the plain password
    cout << "Inorder to Log in please enter the following\n";
    cout << "Username: ";
    string username;
    getline(cin, username);
    cout << "\nPassword: ";




//    while (true){
//
//    }
//    tempChar = getch(); //stores char typed in tempChar
//    if(tempChar >= 32 && tempChar <= 126)
//        //check if tempChar is numeric , alphabet, special character
//    {
//        //stores tempChar in pass
//        firstPassword += tempChar;
//        ++letterPassword1;
//        cout << "*" ;
//    }
//    if(tempChar == '\b' && letterPassword1 >= 1) //if user typed backspace
//        //letterPassword1 should be greater than 0.
//    {
//        cout << "\b \b"; //rub the character behind the cursor.
//        --letterPassword1;
//    }
//    if(tempChar == '\r') //if enter is pressed
//    {
//        //null means end of string.
//        firstPassword += '\0';
//        break; //break the loop
//    }
}

void userRegister(string& ID, string& fullName, string& phoneNumber, string& email)
{
    XLDocument usersData; user newUser;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");
    int indexUserInFile = workSheet.rowCount();
    string firstPassword, repeatedPassword;
    while(true)
    {
        firstPassword = getPassword(" first");
        repeatedPassword = getPassword(" repeated");
        if (firstPassword == repeatedPassword)
        {
            cout << "Passwords Match Successfully!" << endl;
            break;
        }
        else
        {
            cout << "The passwords doesn't match, Try again!" << endl;
        }
    }

    newUser.indexUserInFile = indexUserInFile + 1;
    newUser.ID = ID;
    newUser.fullName = fullName;
    newUser.phoneNumber = phoneNumber;
    newUser.email = email;
    newUser.password = firstPassword;

    getUserData.insert({ID, newUser});

    workSheet.cell(indexUserInFile, colmID).value() = ID;
    workSheet.cell(indexUserInFile, colmFullName).value() = fullName;
    workSheet.cell(indexUserInFile, colmPhoneNumber).value() = phoneNumber;
    workSheet.cell(indexUserInFile, colmEmail).value() = email;
    workSheet.cell(indexUserInFile, colmPassword).value() = encryptPassword(firstPassword); // Encrypting the firstPassword that will be stored in the file.

    usersData.save();
    usersData.close();
}
//___________________________________________________________________________________________________
string userLogin(string ID, string password){ // parameter password is assumed to be the plain password.
    return "";
}
//___________________________________________________________________________________________________
bool isValidEmail(string email)// Done by amr
{
    regex isValid("^\\w{1}([\\.\\-\\#\\!\\%\\$\\‘\\&\\+\\*\\/\\=\\?\\^\\_\\`\\{\\|\\}\\~]?\\w+){0,63}@\\w+([.-]?\\w+)*(\\.\\w{2,3})+$");
    return regex_match(email, isValid);
}
//___________________________________________________________________________________________________
string getEmail()
{
    string email;
    while (true)
    {
        cout<<"Email: ";
        getline(cin,email);
        if (isValidEmail(email)){
            return email;
            cout<<"\nEmail has been added successfully";
            break;
        }
        else
        {
            cout<<"\nEmail is not valid please try again\n\n";
        }
    }
}
//___________________________________________________________________________________________________
bool isValidPhoneNumber(string phoneNumber)// Done by amr
{
    regex isValid("^01[0125][0-9]{8}$");
    return regex_match(phoneNumber, isValid);
}
//___________________________________________________________________________________________________
string  getPhoneNumber() // Done by amr
{
string phoneNumber;
while (true)
{
cout<<"PhoneNumber: ";
getline(cin,phoneNumber);
if (isValidPhoneNumber(phoneNumber)){
// return phoneNumber;
cout<<"\nPhoneNumber has been added successfully";
break;
}
else
{
cout<<"\nPhoneNumber is not valid please try again\n\n";
}
}
}
//___________________________________________________________________________________________________
