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
#include <conio.h>
#include <unordered_map>
#include "OpenXLSX.hpp"
using namespace std;
using namespace OpenXLSX;
//______________________________________________________________________________________________________________________
struct user {
    string ID;
    string fullName;
    string phoneNumber;
    string password;
    string email;
    int indexUserInFile = 0;
    bool isBlocked = false;
};
const int colmID = 1, colmFullName = 2, colmPhoneNumber = 3, colmEmail = 4, colmPassword = 5, colmBlocked = 6, endRangeLoginMenuList = 6;
// key: userID, value: struct of this exact user
unordered_map <string, user> getUserData;
unordered_map <string, bool> registeredEmails;
//______________________________________________________________________________________________________________________
ostream& operator<<(ostream& out, user& inUser)
{
    cout << "ID: " << inUser.ID << "\n" << "Email: " << inUser.email << "\n" << "Full Name: " << inUser.fullName << "\n"
         << "Phone Number: " << inUser.phoneNumber << "\n" << "Password: " << inUser.password << "\n";
    return out;
}
//______________________________________________________________________________________________________________________
void printMainMenu()
{
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "Options of the main menu:-" << endl;
    cout << "--------------------------" << endl;
    cout << "1- Register." << endl;
    cout << "2- Login." << endl;
    cout << "3- Forget Password." << endl;
    cout << "4- Exit." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//______________________________________________________________________________________________________________________
void printLoginMenu()
{
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "Options of the login menu:-" << endl;
    cout << "---------------------------" << endl;
    cout << "1- Show Personal Data." << endl;
    cout << "2- Change Full Name." << endl;
    cout << "3- Change Phone Number." << endl;
    cout << "4- Change Email." << endl;
    cout << "5- Change Password." << endl;
    cout << "6- Return to the Main Menu." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//______________________________________________________________________________________________________________________
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
//______________________________________________________________________________________________________________________
string encryptPassword(const string& plainText) // At-bash Cipher
{
    string cipherText;
    char cipherLetter;
    for (auto i: plainText)
    {
        if (isupper(i))
        {
            cipherLetter = i + 25 - 2 * (i - 'A'); // equation to get new cipher letter
        }
        else if (islower(i))
        {
            cipherLetter = i + 25 - 2 * (i - 'a');
        }
        else
        {
            cipherLetter = i;
        }
        cipherText += cipherLetter;
    }
    return cipherText;
}
//______________________________________________________________________________________________________________________
string decryptPassword(const string& cipherText)
{
    string plainText;
    char plainLetter;
    for (auto i: cipherText)
    {
        if (isupper(i))
        {
            plainLetter = i - 25 + 2 * ('Z' - i); // equation to get new plain letter
        }
        else if (islower(i))
        {
            plainLetter = i - 25 + 2 * ('z' - i);
        }
        else
        {
            plainLetter = i;
        }
        plainText += plainLetter;
    }
    return plainText;
}
//______________________________________________________________________________________________________________________
void fetchXLSXFile()
{
    // get the user data already in file and populate to the map.
    user userProfile; XLDocument usersData;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");
    int numberOfUsers = workSheet.rowCount();

    for (int index = 2; index <= numberOfUsers; ++index)
    {

        userProfile.indexUserInFile = index;
        userProfile.ID = workSheet.cell(index, colmID).value().get<string>();
        userProfile.fullName = workSheet.cell(index, colmFullName).value().get<string>();
        userProfile.phoneNumber = workSheet.cell(index, colmPhoneNumber).value().get<string>();
        userProfile.email = workSheet.cell(index, colmEmail).value().get<string>();
        userProfile.password = workSheet.cell(index, colmPassword).value().get<string>();
        userProfile.password = decryptPassword(userProfile.password);
        userProfile.isBlocked = workSheet.cell(index, colmBlocked).value().get<bool>();

        getUserData.insert({ userProfile.ID,userProfile });
        registeredEmails.insert({ userProfile.email, true });
    }
    usersData.close();
}
//______________________________________________________________________________________________________________________
void updateXLSXFile(const int& indexUserInFile, const string& userID, const string& infoWantedToChange, const int& colm)
{
    // change the password in the map.
    user tempProfile = getUserData[userID];
    XLDocument usersData;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1"); // change the password in the file of the users.

    switch (colm)
    {
        case 2: {
            tempProfile.fullName = infoWantedToChange;
            workSheet.cell(indexUserInFile, colmFullName).value() = infoWantedToChange;
            break;
        }
        case 3: {
            tempProfile.phoneNumber = infoWantedToChange;
            workSheet.cell(indexUserInFile, colmPhoneNumber).value() = infoWantedToChange;
            break;
        }
        case 4: {
            // Edit the Key -> email, in the registeredEmails map
            auto oldEmail = registeredEmails.extract(tempProfile.email);
            oldEmail.key() = infoWantedToChange;
            registeredEmails.insert(move(oldEmail));

            // Edit the Email in the getUsersData map and the Excel file.
            tempProfile.email = infoWantedToChange;
            workSheet.cell(indexUserInFile, colmEmail).value() = infoWantedToChange;
            break;
        }
        case 5: {
            tempProfile.password = infoWantedToChange;
            workSheet.cell(indexUserInFile, colmPassword).value() = encryptPassword(infoWantedToChange);
            break;
        }
        default:
            break;
    }
    getUserData[userID] = tempProfile;
    usersData.save();
    usersData.close();
}
//______________________________________________________________________________________________________________________
void updateXLSXFile(const int& indexUserInFile, const string& userID, const bool& blockedMood)
{
    // change Blocked Mood in the map.
    user tempProfile = getUserData[userID];
    tempProfile.isBlocked = blockedMood;
    getUserData[userID] = tempProfile;

    // change the Blocked Mood in the file of the users.
    XLDocument usersData;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");

    workSheet.cell(indexUserInFile, colmBlocked).value() = blockedMood;

    usersData.save();
    usersData.close();
}
//______________________________________________________________________________________________________________________
bool isYesOrNo(const string& choice)
{
    bool isValidInput = true;
    if (choice.length() == 1)
    {
        if (choice == "y" || choice == "Y" || choice == "n" || choice == "N") return isValidInput;
    }
    return !isValidInput;
}
//______________________________________________________________________________________________________________________
void clearScreen()
{
    system("CLS");
    cout << flush;
    system("CLS");
}
//______________________________________________________________________________________________________________________
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
            if (choice == "n" || choice == "N") return !isWant;
        }
    }
    return isWant;
}
//______________________________________________________________________________________________________________________
string makeLowerCase(string line)
{
    for (int i = 0; i < line.length(); i++) line[i] = tolower(line[i]);
    return line;
}
//______________________________________________________________________________________________________________________
bool isvalidID(const string& ID)
{
    regex isValid("^[\\w\\.\\-\\#\\!\\%\\$\\&\\+\\*\\/\\=\\?\\^\\`\\{\\|\\}\\~]*$");
    return regex_match(ID, isValid);
}
//______________________________________________________________________________________________________________________
string getID()
{
    string ID;
    while (true)
    {
        cout << "ID/Username: ";
        getline(cin, ID);
        if (isvalidID(ID))
        {
            ID = makeLowerCase(ID);
            return ID;
        }
        else
        {
            cout << "Please enter a valid ID!" << endl;
            ID = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool isValidFullName(const string& fullName)
{
    regex isValid("^[a-zA-Z]+([ -]?[A-Za-z]*)+$");
    return regex_match(fullName, isValid);
}
//______________________________________________________________________________________________________________________
string getFullName()
{
    string fullName;
    while (true)
    {
        cout << "FullName: ";
        getline(cin, fullName);
        if (isValidFullName(fullName))
        {
            return fullName;
        }
        else
        {
            cout << "FullName is not valid please try again!" << endl;
            fullName = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool isValidEmail(const string& email)
{
    regex isValid("^\\w{1}([\\.\\-\\#\\!\\%\\$\\‘\\&\\+\\*\\/\\=\\?\\^\\_\\`\\{\\|\\}\\~]?\\w+){0,63}@\\w+([.-]?\\w+)*(\\.\\w{2,3})+$");
    return regex_match(email, isValid);
}
//______________________________________________________________________________________________________________________
string getEmail()
{
    string email;
    while (true)
    {
        cout<<"Email: ";
        getline(cin,email);
        if (isValidEmail(email))
        {
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
bool isValidPhoneNumber(const string& phoneNumber)
{
    regex isValid("^01[0125][0-9]{8}$");
    return regex_match(phoneNumber, isValid);
}
//______________________________________________________________________________________________________________________
string  getPhoneNumber()
{
    string phoneNumber;
    while (true)
    {
        cout<<"PhoneNumber: ";
        getline(cin,phoneNumber);
        if (isValidPhoneNumber(phoneNumber))
        {
            return phoneNumber;
        }
        else
        {
            cout<<"PhoneNumber is not valid please try again!" << endl;
            phoneNumber = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool checkUserChoice(const string& choice, const int& endRange)
{
    if (choice.length() == 1)
    {
        if (!isdigit(choice[0]))
        {
            return false;
        }
        int checkChoice = stoi(choice);
        if (checkChoice >= 1 && checkChoice <= endRange)
        {
            return true;
        }
    }
    return false;
}
//______________________________________________________________________________________________________________________
int getUserChoice(const int& endRange)
{
    string getChoice;
    int setChoice;
    bool isValidChoice = false;
    while (!isValidChoice)
    {
        cout << "Enter your choice from the list above: ";
        getChoice = "";
        while (getChoice.empty())
        {
            getline(cin, getChoice);
        }
        isValidChoice = checkUserChoice(getChoice, endRange);
        if (!isValidChoice)
        {
            cout << "The Choice you entered is not an option from the list,	Try again and make sure to enter a valid option from the list." << endl;
        }
    }
    cout << "----------------------------------------------------------------------------------------" << endl;
    setChoice = stoi(getChoice);
    return setChoice;
}
//______________________________________________________________________________________________________________________
bool isValidPassword(const string& password)
{
    regex passwordFormat("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#<>=?!+@$%^&*-]).{8,}$");
    bool strongPassword = regex_match(password, passwordFormat);
    return strongPassword;
}
//______________________________________________________________________________________________________________________
string getPassword(const string& additionalText = "")
{
    // please remove all text regarding what a valid password should contain and add it somewhere else bcz this used even for login // Yusuf B
    char tempChar; string password;
    cout << additionalText << "Password: ";
    for(int count = 0;;)
    { //infinite loop
        tempChar = getch(); //stores char typed in tempChar
        if(tempChar >= 32 && tempChar <= 126)
        { //check if tempChar is numeric , alphabet, special character
            //stores tempChar in pass
            password += tempChar;
            ++count;
            cout << "*" ;
        }
        if(tempChar == '\b' && count >= 1)
        { //if user typed backspace. count should be greater than 0.
            cout << "\b \b"; //rub the character behind the cursor.
            --count;
        }
        if(tempChar == '\r')
        { //if enter is pressed
            return password; //break the loop
        }
    }
}
//______________________________________________________________________________________________________________________
string getANewPassword(const string& oldPassword = "")
{
    string newPassword, repeatNewPassword;
    while(true)
    {
        cout << "The password must contain small letters (a,b ..etc), capital letters (A,B ..etc), numbers (0,1 ..etc),\n"
                "special characters (@,# ..etc) and be greater than 7 characters." << endl;
        newPassword = getPassword("Enter ");
        if (!isValidPassword(newPassword))
        {
            cout << "\n" << "The password Must follow the instructions format, try again." << endl;
            newPassword = "";
            continue;
        }
        cout << endl;
        repeatNewPassword = getPassword("Confirm ");
        if (newPassword == repeatNewPassword)
        {
            cout << "\n" << "Passwords Match Successfully!" << endl;
            if (!oldPassword.empty())
            {
                if (oldPassword == newPassword)
                {
                    cout << "\n" << "The new password must be different from the old one, Try again!" << endl;
                    newPassword = "";
                    continue;
                }
            }
            return newPassword;
        }
        else
        {
            cout << "The passwords doesn't match, Try again!" << endl;
            repeatNewPassword = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool doesIDExist(const string& inUsername)
{
    if (getUserData.count(inUsername))
    {
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
void userRegister()
{
    XLDocument usersData; user newUser, tempProfile;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");

    int indexUserInFile = workSheet.rowCount() + 1;
    string ID, fullName, phoneNumber, email, password;

    while(ID.empty())
    {
        ID = getID();
        if (doesIDExist(ID))
        {
            cout << "The ID is already exists for someone else, Try again with a different ID." << endl;
            ID = "";
        }
    }
    fullName = getFullName();
    phoneNumber = getPhoneNumber();
    while (email.empty())
    {
        email = getEmail();
        if (doesEmailExists(email))
        {
            cout << "The email is already exists for someone else, Try again with a different email." << endl;
            email = "";
        }
    }
    password = getANewPassword();

    newUser.indexUserInFile = indexUserInFile;
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
void showPersonalData(const string& ID)
{
    user userProfile = getUserData[ID];
    cout << "Your Personal Data:-" << endl;
    cout << "--------------------" << endl;
    cout << userProfile;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//______________________________________________________________________________________________________________________
void changeFullName(const string& ID)
{
    user userProfile = getUserData[ID];
    string tempName = userProfile.fullName;

    while(tempName == userProfile.fullName)
    {
        userProfile.fullName = getFullName();
        if (tempName == userProfile.fullName)
        {
            cout << "The new name must be different from the old one, Try again!" << endl;
        }
    }
    updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, userProfile.fullName, colmFullName);
    cout << "Changing the Full Name Done Successfully!" << endl;
}
//______________________________________________________________________________________________________________________
void changePhoneNumber(const string& ID)
{
    user userProfile = getUserData[ID];
    string tempPhoneNumber = userProfile.phoneNumber;

    while(tempPhoneNumber == userProfile.phoneNumber)
    {
        userProfile.phoneNumber = getPhoneNumber();
        if (tempPhoneNumber == userProfile.phoneNumber)
        {
            cout << "The new phone number must be different from the old one, Try again!" << endl;
        }
    }

    updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, userProfile.phoneNumber, colmPhoneNumber);
    cout << "Changing the Full Name Done Successfully!" << endl;
}
//______________________________________________________________________________________________________________________
void changeEmail(const string& ID)
{
    user userProfile = getUserData[ID];
    string tempEmail = userProfile.email;

    while(tempEmail == userProfile.email)
    {
        userProfile.email = getEmail();
        if (tempEmail == userProfile.email)
        {
            cout << "The new email must be different from the old one, Try again!" << endl;
        }
    }

    updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, userProfile.email, colmEmail);
    cout << "Changing the Email Done Successfully!" << endl;
}
//______________________________________________________________________________________________________________________
void changePassword(const string& ID, bool fromOTP = false)
{
    string newPassword, oldPassword;
    user userProfile = getUserData[ID];

    if (fromOTP)
    {
        cout << "Enter your new password: ";
        userProfile.password = getANewPassword();
        updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, userProfile.password, colmPassword);
    }
    else
    {
        cout << "\n";
        oldPassword = getPassword("Enter Your Old ");
        if (oldPassword == userProfile.password)
        {
            newPassword = getANewPassword(oldPassword);
            updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, newPassword, colmPassword);
            cout << "Password Changed Successfully!\n";
        }
        else
        {
            cout << "Password is not correct; you will be logged out due to security concerns!\n" << "Try again Later.\n";
        }
    }
}
//______________________________________________________________________________________________________________________
void executeLoginMenu(const int& choice, const string& ID)
{
    switch (choice)
    {
        case 1: {
            showPersonalData(ID);
            break;
        }
        case 2: {
            changeFullName(ID);
            break;
        }
        case 3: {
            changePhoneNumber(ID);
            break;
        }
        case 4: {
            changeEmail(ID);
            break;
        }
        case 5: {
            changePassword(ID);
            break;
        }
        default:
            break;
    }
}
//______________________________________________________________________________________________________________________
void userLogin()
{   // password is assumed to be the plain password.
    // return username if login is successful, else return ""
    int failedLoginPasswordAttempts = 0, userChoice = 0;
    string inUsername, inPassword;
    bool clrScreen;
    while (true)
    {
        cout << "Inorder to Log in please enter the following!\n";
        inUsername = getID();
        inPassword = getPassword();
        if (doesIDExist(inUsername))
        {
            user userProfile;
            userProfile = getUserData[inUsername];

            // dealing with password
            if (!userProfile.isBlocked)
            {
                if (inPassword == userProfile.password)
                {
                    cout << "\n" << "Successful Login, welcome back " << userProfile.ID << " your full name is " << userProfile.fullName << endl;
                    while(true)
                    {
                        printLoginMenu();
                        userChoice = getUserChoice(endRangeLoginMenuList);
                        if (userChoice != endRangeLoginMenuList)
                        {
                            executeLoginMenu(userChoice, userProfile.ID);
                            clrScreen = isClearScreen();
                            if (clrScreen)
                            {
                                clearScreen();
                            }
                        }
                        else
                        {
                            cout << "You will logout now!" << endl;
                            return;
                        }
                    }
                }
                else
                {
                    failedLoginPasswordAttempts += 1;
                    cout << "\n" << "Failed to login! Invalid Password!\n";

                    if (failedLoginPasswordAttempts >= 3)
                    {
                        cout << "You have been blocked from the system." << endl;
                        updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, true); //blocked mode = true
                        break;
                    }
                }
            }
            else
            {
                cout << "You are already blocked from the system\n";
                break;
            }
        }
        else
        {
            cout << "Username is not Found, Please try again later or Register with new account!\n";
            break;
        }
    }
}
//______________________________________________________________________________________________________________________
void authenticateOTPProcess(const string& otp, const string& userID)
{   // otp sent to user // Yusuf B
    string inOTP;
    while(inOTP.empty())
    {
        cout << "Please enter you OTP that you received on your email: ";
        getline (cin, inOTP);
    }
    if (inOTP == otp) changePassword(userID, true);
    else cout << "Your OTP is incorrect, failed forget password attempt;\n";
}
//______________________________________________________________________________________________________________________
void executeMainMenu(const int& choice)
{
    switch (choice)
    {
        case 1: {
            userRegister();
            break;
        }
        case 2: {
            userLogin();
            break;
        }
        case 3: {
//            authenticateOTPProcess();
            break;
        }
        default:
            break;
    }
}
//______________________________________________________________________________________________________________________