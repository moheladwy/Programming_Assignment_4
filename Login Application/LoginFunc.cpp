//______________________________________________________________________________________________________________________
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application.
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Ahmed
// Purpose: .......
// File: This is the CPP file that contain the algorithms of the functions.
//______________________________________________________________________________________________________________________
#include <iostream>
#include <regex>
#include <string>
#include <cctype>
#include <cstring>
#include <conio.h>
#include <unordered_map>
#include <windows.h>
#include <optional>
#include "OpenXLSX.hpp"
using namespace std;
using namespace OpenXLSX;
//______________________________________________________________________________________________________________________
/*
 * code practices:
 * There is a struct as you can see below.
 * Since the  user ID is unique to each user, we will identify each user of the struct by the username:
 * please note that userID is CASE-SENSITIVE
 * e.g. user <userID>;
 *      <userID>.email = "test@email.com"
 * below is another example
 * e.g. user ahmedAdam;
 *      ahmedAdam.email = "test2@email.com"
*/
//______________________________________________________________________________________________________________________
struct user {
    string ID;
    string fullName;
    string phoneNumber;
    string password;
    string email;
    int indexUserInFile;
    bool isBlocked;
};
// NEED TO BE DONE : make logged in by deafult false;
const int colmID = 1, colmFullName = 2, colmPhoneNumber = 3, colmEmail = 4, colmPassword = 5, colmBlocked = 6;
// key: userID, value: struct of this exact user
unordered_map <string, user> getUserData;
unordered_map <string, bool> registeredEmails;
//______________________________________________________________________________________________________________________
string makeLowerCase(string line) {
    for (int i = 0; i < line.length(); i++) line[i] = tolower(line[i]);
    return line;
}
//______________________________________________________________________________________________________________________
bool isValidEmail(string& email) {
    regex isValid("^\\w{1}([\\.\\-\\#\\!\\%\\$\\‘\\&\\+\\*\\/\\=\\?\\^\\_\\`\\{\\|\\}\\~]?\\w+){0,63}@\\w+([.-]?\\w+)*(\\.\\w{2,3})+$");
    return regex_match(email, isValid);
}
//______________________________________________________________________________________________________________________
string getEmail() {
    string email;
    while (true)
    {
        cout<<"Email: ";
        getline(cin,email);
        if (isValidEmail(email)){
            email = makeLowerCase(email);
            return email;
        }
        else
        {
            cout<<"Email is not valid please try again!" << endl;
            email = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool isValidPhoneNumber(string& phoneNumber) {
    regex isValid("^01[0125][0-9]{8}$");
    return regex_match(phoneNumber, isValid);
}
//______________________________________________________________________________________________________________________
string  getPhoneNumber() {
    string phoneNumber;
    while (true)
    {
        cout<<"PhoneNumber: ";
        getline(cin,phoneNumber);
        if (isValidPhoneNumber(phoneNumber)) {
            return phoneNumber;
        }
        else {
            cout<<"PhoneNumber is not valid please try again!" << endl;
            phoneNumber = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool isValidFullName(string& fullName) {
    regex isValid("^[a-zA-Z]+[ -]?[A-Za-z]*$");
    return regex_match(fullName, isValid);
}
//______________________________________________________________________________________________________________________
string getFullName() {
    string fullName;
    while (true) {
        cout << "FullName: ";
        getline(cin, fullName);
        if (isValidFullName(fullName)) {
            return fullName;
        }
        else {
            cout << "FullName is not valid please try again!" << endl;
            fullName = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool isvalidID(string& ID) {
    regex isValid("^[\\w\\.\\-\\#\\!\\%\\$\\&\\+\\*\\/\\=\\?\\^\\`\\{\\|\\}\\~]*$");
    return regex_match(ID, isValid);
}
//______________________________________________________________________________________________________________________
string getID() {
    string ID;
    while (true) {
        cout<<"ID/Username: ";
        getline(cin,ID);
        if (isvalidID(ID)) {
            ID = makeLowerCase(ID);
            return ID;
        }
        else {
            cout<<"Please enter a valid ID!" << endl;
            ID = "";
        }
    }
}
//______________________________________________________________________________________________________________________
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
//______________________________________________________________________________________________________________________
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
//______________________________________________________________________________________________________________________
void fetchXLSXFile() {
    // get the user data already in file and populate to the map.
    user userProfile; XLDocument usersData;
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
        userProfile.isBlocked = workSheet.cell(index,colmBlocked).value().get<bool>();

        getUserData.insert({userProfile.ID,userProfile});
        registeredEmails.insert({userProfile.email, true});
    }
}
//______________________________________________________________________________________________________________________
void updateXLSXFile(const int& indexUserInFile, const string& userID, const string& newPassword) { // rev with hussein - YB
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
//______________________________________________________________________________________________________________________
void updateXLSXFile(const int& indexUserInFile, const string& userID, const bool& blockedMood ) { // rev with hussein -YB
    // change Blocked Mood in the map.
    user tempProfile = getUserData[userID];
    tempProfile.isBlocked = blockedMood;
    getUserData[userID] = tempProfile;

    // change the Blocked Mood in the file of the users.
    XLDocument usersData;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");

    workSheet.cell(indexUserInFile,colmBlocked).value() = blockedMood;

    usersData.save();
    usersData.close();
}
//______________________________________________________________________________________________________________________
void printMainMenu() {
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "1- Register." << endl;
    cout << "2- Login." << endl;
    cout << "3- Forget Password." << endl;
    cout << "4- Exit." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//______________________________________________________________________________________________________________________
bool isYesOrNo(string& choice) {
    bool isValidInput = true;
    if (choice.length() == 1) {
        if (choice == "y" || choice == "Y" || choice == "n" || choice == "N") return isValidInput;
        }
    return !isValidInput;
}
//______________________________________________________________________________________________________________________
void printEndApp() {
    cout << "Thanks for using our Login System Application." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "Authors of the Application:-" << endl;
    cout << "----------------------------" << endl;
    cout << "1- Name: Mohamed Hussein Hassan Eladwy. ID: 20210335." << endl;
    cout << "2- Name: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502." << endl;
    cout << "3- Name: Amr Khalied Elsayed Elhennawy. ID: 20210274." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//______________________________________________________________________________________________________________________
void clearScreen() {
    Sleep(60000);
    system("CLS");
    cout << flush;
    system("CLS");
}
//______________________________________________________________________________________________________________________
bool isClearScreen() {
    int isWant = false;
    string choice;
    while (!isWant) {
        cout << "Do you want to clear the screen before continue or not (y)|(n): ";
        getline(cin, choice);
        isWant = isYesOrNo(choice);
        if (!isWant) {
            cout << "Please enter a choice from (y) or (n) only, Try again.\n";
        }
        else {
            if (choice == "n" || choice == "N") {
                return !isWant;
            }
        }
    }
    return isWant;
}
//______________________________________________________________________________________________________________________
bool checkUserChoice(string choice) {
    if (choice.length() == 1) {
        if (!isdigit(choice[0])) {
            return false;
        }
        int checkChoice = stoi(choice);
        if (checkChoice >= 1 && checkChoice <= 4) {
            return true;
        }
    }
    return false;
}
//______________________________________________________________________________________________________________________
int getUserChoice() {
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
//______________________________________________________________________________________________________________________
bool isValidPassword(string& password) {
    regex passwordFormat("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#<>=?!+@$%^&*-]).{8,}$");
    bool strongPassword = regex_match(password, passwordFormat);
    return strongPassword;
}
//______________________________________________________________________________________________________________________
string getPassword(const string& additionalText = "") {
    // please remove all text regarding what a valid password should contain and add it somewhere else bcz this used even for login // Yusuf B
    char tempChar; string password;
    cout << additionalText <<"Password: ";
    for(int count = 0;;) { //infinite loop
        tempChar = getch(); //stores char typed in tempChar
        if(tempChar >= 32 && tempChar <= 126) { //check if tempChar is numeric , alphabet, special character
            //stores tempChar in pass
            password += tempChar;
            ++count;
            cout << "*" ;
        }
        if(tempChar == '\b' && count >= 1) { //if user typed backspace. count should be greater than 0.
            cout << "\b \b"; //rub the character behind the cursor.
            --count;
        }
        if(tempChar == '\r') { //if enter is pressed
            return password; //break the loop
        }
    }
}
//______________________________________________________________________________________________________________________
string getANewPassword() {
    string firstPassword, repeatedPassword;
    while(true) {
        cout << "\nThe password must contain small letters (a,b ..etc), capital letters (A,B ..etc), numbers (0,1 ..etc),\n"
                "special characters (@,# ..etc) and be greater than 7 characters." << endl;
        firstPassword = getPassword("Enter ");
        if (!isValidPassword(firstPassword)){
            cout << "The password Must follow the instructions format, try again." << endl;
            firstPassword = "";
            continue;
        }
        repeatedPassword = getPassword("Confirm ");
        if (firstPassword == repeatedPassword) {
            cout << "Passwords Match Successfully!" << endl;
            return firstPassword;
        }
        else {
            cout << "The passwords doesn't match, Try again!" << endl;
            repeatedPassword = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool doesIDExist(const string& inUsername) {
    if (getUserData.count(inUsername)) {
        return true;
    }
    return false;
}
//______________________________________________________________________________________________________________________
bool doesEmailExists(const string& email)
{
    if (registeredEmails.count(email))
    {
        return true;
    }
    return false;
}
//______________________________________________________________________________________________________________________
void userRegister() {
    XLDocument usersData; user newUser, tempProfile;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");

    int indexUserInFile = workSheet.rowCount();
    string ID, fullName, phoneNumber, email, password;

    while(ID.empty()) {
        ID = getID();
        if (doesIDExist(ID)) {
            cout << "The ID is already exists for someone else, Try again with a different ID." << endl;
            ID = "";
        }
    }
    fullName = getFullName();
    phoneNumber = getPhoneNumber();
    while (email.empty()) {
        email = getEmail();
        if (doesEmailExists(email)) {
            cout << "The email is already exists for someone else, Try again with a different email." << endl;
            email = "";
        }
    }
    password = getANewPassword();

    newUser.indexUserInFile = indexUserInFile + 1;
    newUser.ID = ID;
    newUser.fullName = fullName;
    newUser.phoneNumber = phoneNumber;
    newUser.email = email;
    newUser.password = password;
    newUser.isBlocked = false;

    getUserData.insert({ID, newUser});
    registeredEmails.insert({email, true});

    workSheet.cell(indexUserInFile, colmID).value() = ID;
    workSheet.cell(indexUserInFile, colmFullName).value() = fullName;
    workSheet.cell(indexUserInFile, colmPhoneNumber).value() = phoneNumber;
    workSheet.cell(indexUserInFile, colmEmail).value() = email;
    workSheet.cell(indexUserInFile, colmPassword).value() = encryptPassword(password); // Encrypting the password that will be stored in the file.
    workSheet.cell(indexUserInFile, colmBlocked).value() = false;

    usersData.save();
    usersData.close();
}
//______________________________________________________________________________________________________________________
string userLogin() { // password is assumed to be the plain password.
    // return username if login is successful, else return ""
    int failedLoginPasswordAttempts = 0;
    while (true) {
        cout << "Inorder to Log in please enter the following\n";
        string inUsername = getID();
        string inPassword = getPassword();
        if (doesIDExist(inUsername)) {
            user userProfile;
            userProfile = getUserData[inUsername];

            // dealing with password
            if (!userProfile.isBlocked) {
                if (inPassword == userProfile.password) {
                    cout << "Successful Login, welcome back " << userProfile.ID << " your full name is " << userProfile.fullName << endl;
                    return userProfile.ID;

                }
                else {
                    failedLoginPasswordAttempts += 1;
                    cout << "Failed to login! Invalid Password!\n";

                    if (failedLoginPasswordAttempts >= 3) {
                        cout << "You have been blocked from the system." << endl;
                        updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, true); //blocked mode = true
                        break;
                    }
                }
            }
            else {
                cout << "You are already blocked from the system\n";
                break;
            }
        }
        else {
            cout << "Username is not Found; Please try again later!\n";
            break;
        }
    }
    return "";
}
//______________________________________________________________________________________________________________________
void changePassword(){
    string loggedInUsername = userLogin();
    if (loggedInUsername.length() != 0){
        // therefore username stored in loggedInUsername has successfully signed in
        user userProfile = getUserData[loggedInUsername];
        cout << "Enter your old Password below\n";
        string oldPassword = getPassword("Enter Old ");
        if (oldPassword == userProfile.password){
            string newPassword = getANewPassword();
            updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, newPassword);
            cout << "\nPassword Changed Successfully!\n";
        } else {
            cout << "Password does not match; you will be logged out due to security concerns!" << "\nTry again Later\n";
        }
    }
}
//______________________________________________________________________________________________________________________