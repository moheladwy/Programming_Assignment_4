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
#include <unordered_set>
#include "OpenXLSX.hpp"
using namespace std;
using namespace OpenXLSX;
//______________________________________________________________________________________________________________________
struct user
{
    // Struct of User Profile Data.
    string ID;
    string fullName;
    string phoneNumber;
    string password;
    string email;
    int indexUserInFile = 0;
    bool isBlocked = false;
};
const int colmID = 1, colmFullName = 2, colmPhoneNumber = 3, colmEmail = 4, colmPassword = 5, colmBlocked = 6, endLoginMenu = 6;
unordered_map<string, user> database;         // key: userID, value: struct of this exact user
unordered_set<string> registeredEmails;       // Value: Emails of the users from the struct.
unordered_set<string> registeredPhoneNumbers; // Value: Phone Numbers of the users from the struct.
//______________________________________________________________________________________________________________________
// Overload the << operator to be able to print the struct in simple way.
ostream &operator<<(ostream &out, user &inUser)
{
    cout << "ID: " << inUser.ID << "\n"
         << "Email: " << inUser.email << "\n"
         << "Full Name: " << inUser.fullName << "\n"
         << "Phone Number: " << inUser.phoneNumber << "\n"
         << "Password: " << inUser.password << "\n";
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
    cout << "3- Exit." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//______________________________________________________________________________________________________________________
void printLoginMenu()
{
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "Options of the login menu:-" << endl;
    cout << "---------------------------" << endl;
    cout << "1- Show Your Personal Data." << endl;
    cout << "2- Change Full Name." << endl;
    cout << "3- Change Phone Number." << endl;
    cout << "4- Change Email." << endl;
    cout << "5- Change Password." << endl;
    cout << "6- Logout." << endl;
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
void encryptPassword(string &plainText) // At-bash Cipher
{
    for (char &i : plainText)
    {
        if (isupper(i))
        {
            i = i + 25 - 2 * (i - 'A'); // equation to get new cipher letter
        }
        else if (islower(i))
        {
            i = i + 25 - 2 * (i - 'a');
        }
    }
}
//______________________________________________________________________________________________________________________
void decryptPassword(string &cipherText)
{
    for (auto &i : cipherText)
    {
        if (isupper(i))
        {
            i = i - 25 + 2 * ('Z' - i); // equation to get new plain letter
        }
        else if (islower(i))
        {
            i = i - 25 + 2 * ('z' - i);
        }
    }
}
//______________________________________________________________________________________________________________________
void fetchXLSXFile()
{
    // get the user data already in file and populate to the map.
    user userProfile;
    XLDocument usersData;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");
    int numberOfUsers = workSheet.rowCount();

    for (int index = 2; index <= numberOfUsers; ++index)
    {
        // Load the Full Data of the User in the Struct.
        userProfile.indexUserInFile = index;
        userProfile.ID = workSheet.cell(index, colmID).value().get<string>();
        userProfile.fullName = workSheet.cell(index, colmFullName).value().get<string>();
        userProfile.phoneNumber = workSheet.cell(index, colmPhoneNumber).value().get<string>();
        userProfile.email = workSheet.cell(index, colmEmail).value().get<string>();
        userProfile.password = workSheet.cell(index, colmPassword).value().get<string>();
        decryptPassword(userProfile.password);
        userProfile.isBlocked = workSheet.cell(index, colmBlocked).value().get<bool>();

        // Load the Struct of the User Profile in the map.
        database.insert({userProfile.ID, userProfile});
        // Load the email and the phone number of the user in the set.
        registeredEmails.insert(userProfile.email);
        registeredPhoneNumbers.insert(userProfile.phoneNumber);
    }
    usersData.close();
}
//______________________________________________________________________________________________________________________
void updateXLSXFile(const int &indexUserInFile, const string &userID, string &infoWantedToChange, const int &colm)
{
    user tempProfile = database[userID];
    XLDocument usersData;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");

    switch (colm)
    {
    case 2:
    {
        tempProfile.fullName = infoWantedToChange;
        workSheet.cell(indexUserInFile, colmFullName).value() = infoWantedToChange;
        break;
    }
    case 3:
    {
        // Edit the Value -> Phone Number, in the registeredPhoneNumbers set
        auto oldPhoneNumber = registeredPhoneNumbers.extract(tempProfile.phoneNumber);
        oldPhoneNumber.value() = infoWantedToChange;
        registeredPhoneNumbers.insert(move(oldPhoneNumber));

        // Edit the Phone Number in the getUsersData map and the Excel file.
        tempProfile.phoneNumber = infoWantedToChange;
        workSheet.cell(indexUserInFile, colmPhoneNumber).value() = infoWantedToChange;
        break;
    }
    case 4:
    {
        // Edit the Value -> email, in the registeredEmails set
        auto oldEmail = registeredEmails.extract(tempProfile.email);
        oldEmail.value() = infoWantedToChange;
        registeredEmails.insert(move(oldEmail));

        // Edit the Email in the getUsersData map and the Excel file.
        tempProfile.email = infoWantedToChange;
        workSheet.cell(indexUserInFile, colmEmail).value() = infoWantedToChange;
        break;
    }
    case 5:
    {
        tempProfile.password = infoWantedToChange;
        encryptPassword(infoWantedToChange);
        workSheet.cell(indexUserInFile, colmPassword).value() = infoWantedToChange;
        break;
    }
    default:
        break;
    }
    database[userID] = tempProfile;
    usersData.save();
    usersData.close();
}
//______________________________________________________________________________________________________________________
void updateXLSXFile(const int &indexUserInFile, const string &userID, const bool &blockedMood)
{
    // change Blocked Mood in the map.
    user tempProfile = database[userID];
    tempProfile.isBlocked = blockedMood;
    database[userID] = tempProfile;

    // change the Blocked Mood in the file of the users.
    XLDocument usersData;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");

    workSheet.cell(indexUserInFile, colmBlocked).value() = blockedMood;

    usersData.save();
    usersData.close();
}
//______________________________________________________________________________________________________________________
bool isYesOrNo(const string &choice)
{
    bool isValidInput = true;
    if (choice.length() == 1)
    {
        if (choice == "y" || choice == "Y" || choice == "n" || choice == "N")
            return isValidInput;
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
            if (choice == "n" || choice == "N")
                return !isWant;
        }
    }
    return isWant;
}
//______________________________________________________________________________________________________________________
void makeLowerCase(string &line)
{
    for (char &letter : line)
        letter = tolower(letter);
}
//______________________________________________________________________________________________________________________
bool isvalidID(const string &ID)
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
            makeLowerCase(ID);
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
bool isValidFullName(const string &fullName)
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
bool isValidEmail(const string &email)
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
        cout << "Email: ";
        getline(cin, email);
        if (isValidEmail(email))
        {
            makeLowerCase(email);
            return email;
        }
        else
        {
            cout << "Email is not valid please try again!" << endl;
            email = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool isValidPhoneNumber(const string &phoneNumber)
{
    regex isValid("^01[0125][0-9]{8}$");
    return regex_match(phoneNumber, isValid);
}
//______________________________________________________________________________________________________________________
string getPhoneNumber()
{
    string phoneNumber;
    while (true)
    {
        cout << "PhoneNumber: ";
        getline(cin, phoneNumber);
        if (isValidPhoneNumber(phoneNumber))
        {
            return phoneNumber;
        }
        else
        {
            cout << "PhoneNumber is not valid please try again!" << endl;
            phoneNumber = "";
        }
    }
}
//______________________________________________________________________________________________________________________
bool isValidChoice(const string &choice, const int &endRange)
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
int getUserChoice(const int &endRange)
{
    string getChoice;
    int setChoice;
    bool validChoice = false;
    while (!validChoice)
    {
        cout << "Enter your choice from the list above: ";
        getChoice = "";
        while (getChoice.empty())
        {
            getline(cin, getChoice);
        }
        validChoice = isValidChoice(getChoice, endRange);
        if (!validChoice)
        {
            cout << "The Choice you entered is not an option from the list,	Try again and make sure to enter a valid option from the list." << endl;
        }
    }
    cout << "----------------------------------------------------------------------------------------" << endl;
    setChoice = stoi(getChoice);
    return setChoice;
}
//______________________________________________________________________________________________________________________
bool isValidPassword(const string &password)
{
    regex passwordFormat("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#<>=?!+@$%^&*-]).{8,256}$");
    return regex_match(password, passwordFormat);
}
//______________________________________________________________________________________________________________________
string getPassword(const string &additionalText = "")
{
    char tempChar;
    string password;
    cout << additionalText << "Password: ";
    for (int count = 0;;)
    {
        tempChar = char(getch());                        // getch() function returns an int, so we convert it to char.
        if (int(tempChar) >= 32 && int(tempChar) <= 126) // check if tempChar is numeric , alphabet, special character.
        {
            // stores tempChar in password.
            password += tempChar;
            ++count;
            cout << "*";
        }
        else if (tempChar == '\b' && count >= 1) // if user typed backspace. count should be greater than 0.
        {
            cout << "\b \b"; // rub the character behind the cursor.
            --count;
        }
        else if (tempChar == '\r') // if Enter is pressed
        {
            cout << endl;
            return password; // return the Password.
        }
    }
}
//______________________________________________________________________________________________________________________
string getANewPassword(const string &oldPassword = "")
{
    string newPassword, repeatNewPassword;
    while (true)
    {
        cout << "--------------------------------------------------------" << endl;
        cout << "The password must contain:" << endl;
        cout << "--------------------------" << endl;
        cout << "1- Small letters (a, b ..etc)." << endl;
        cout << "2- Capital letters (A, B ..etc)." << endl;
        cout << "3- Numbers (0, 1 ..etc)." << endl;
        cout << "4- Special characters(@, #..etc)." << endl;
        cout << "5- Be 8 or more characters and less that 256 characters." << endl;
        cout << "--------------------------------------------------------" << endl;
        newPassword = getPassword("Enter ");
        if (!isValidPassword(newPassword))
        {
            cout << "The password Must follow the instructions format, try again." << endl;
            newPassword = "";
            continue;
        }
        repeatNewPassword = getPassword("Confirm ");
        if (newPassword == repeatNewPassword)
        {
            if (!oldPassword.empty())
            {
                if (oldPassword == newPassword)
                {
                    cout << "The new password must be different from the old one, Try again!" << endl;
                    newPassword = "";
                    continue;
                }
            }
            cout << "Passwords Match Successfully!" << endl;
            return newPassword;
        }
        else
        {
            cout << "The passwords doesn't match, Try again!" << endl;
        }
    }
}
//______________________________________________________________________________________________________________________
void Register()
{
    XLDocument usersData;
    user newUser, tempProfile;
    usersData.open("usersData.xlsx");
    auto workSheet = usersData.workbook().worksheet("Sheet1");

    int indexUserInFile = workSheet.rowCount() + 1; // The Place of the new user in the file.
    string ID, fullName, phoneNumber, email, password;

    fullName = getFullName();

    while (ID.empty())
    {
        ID = getID();
        if (database.count(ID))
        {
            cout << "The ID is already exists for someone else, Try again with a different ID." << endl;
            ID = "";
        }
    }
    while (phoneNumber.empty())
    {
        phoneNumber = getPhoneNumber();
        if (registeredPhoneNumbers.count(phoneNumber))
        {
            cout << "The phone number is already exists for someone else, Try again with a different phone number." << endl;
            phoneNumber = "";
        }
    }
    while (email.empty())
    {
        email = getEmail();
        if (registeredEmails.count(email))
        {
            cout << "The email is already exists for someone else, Try again with a different email." << endl;
            email = "";
        }
    }
    password = getANewPassword();

    // Store the Data of the User in the map and sets.
    newUser.indexUserInFile = indexUserInFile;
    newUser.ID = ID;
    newUser.fullName = fullName;
    newUser.phoneNumber = phoneNumber;
    newUser.email = email;
    newUser.password = password;
    newUser.isBlocked = false;

    database.insert({ID, newUser});
    registeredEmails.insert(email);
    registeredPhoneNumbers.insert(phoneNumber);
    encryptPassword(password); // Encrypting the password that will be stored in the file.

    // Store the Data of the User in the Excel File.
    workSheet.cell(indexUserInFile, colmID).value() = ID;
    workSheet.cell(indexUserInFile, colmFullName).value() = fullName;
    workSheet.cell(indexUserInFile, colmPhoneNumber).value() = phoneNumber;
    workSheet.cell(indexUserInFile, colmEmail).value() = email;
    workSheet.cell(indexUserInFile, colmPassword).value() = password;
    workSheet.cell(indexUserInFile, colmBlocked).value() = false;

    usersData.save();
    usersData.close();

    cout << "You have been registered successfully to the system, You can login now." << endl;
}
//______________________________________________________________________________________________________________________
void showPersonalData(const string &ID)
{
    user userProfile = database[ID];
    cout << "Your Personal Data:-" << endl;
    cout << "--------------------" << endl;
    cout << userProfile;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//______________________________________________________________________________________________________________________
void changeFullName(const string &ID)
{
    user userProfile = database[ID];
    string tempName = userProfile.fullName;

    while (tempName == userProfile.fullName)
    {
        userProfile.fullName = getFullName();
        if (tempName == userProfile.fullName)
        {
            cout << "The new name must be different from the old one, Try again!" << endl;
        }
    }
    // Update the new full name in the file and the map.
    updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, userProfile.fullName, colmFullName);
    cout << "Changing the Full Name Done Successfully!" << endl;
}
//______________________________________________________________________________________________________________________
void changePhoneNumber(const string &ID)
{
    user userProfile = database[ID];
    string tempPhoneNumber = userProfile.phoneNumber;

    while (tempPhoneNumber == userProfile.phoneNumber)
    {
        userProfile.phoneNumber = getPhoneNumber();
        if (tempPhoneNumber == userProfile.phoneNumber)
        {
            cout << "The new phone number must be different from the old one, Try again!" << endl;
        }
    }
    // Update the phone number in the file, map and set.
    updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, userProfile.phoneNumber, colmPhoneNumber);
    cout << "Changing the Full Name Done Successfully!" << endl;
}
//______________________________________________________________________________________________________________________
void changeEmail(const string &ID)
{
    user userProfile = database[ID];
    string tempEmail = userProfile.email;

    while (tempEmail == userProfile.email)
    {
        userProfile.email = getEmail();
        if (tempEmail == userProfile.email)
        {
            cout << "The new email must be different from the old one, Try again!" << endl;
        }
    }
    // Update the new email in the file, map and set.
    updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, userProfile.email, colmEmail);
    cout << "Changing the Email Done Successfully!" << endl;
}
//______________________________________________________________________________________________________________________
void changePassword(const string &ID)
{
    string newPassword, oldPassword;
    user userProfile = database[ID];
    int nTry = 0;

    cout << "You have 3 trails only to enter the password." << endl;
    while (nTry < 3)
    {
        oldPassword = getPassword("Enter Your Old ");
        if (oldPassword == userProfile.password)
        {
            newPassword = getANewPassword(oldPassword);
            // Update the new password in the file and the map.
            updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, newPassword, colmPassword);
            cout << "Password Changed Successfully!\n";
            break;
        }
        else
        {
            nTry++;
            if (nTry == 3)
            {
                cout << "Password is not correct; you will be logged out due to security concerns! Try again Later." << endl;
            }
            else
            {
                cout << "Password is not correct; you have " << 3 - nTry << "trails left, try again!" << endl;
            }
        }
    }
}
//______________________________________________________________________________________________________________________
void executeLoginMenu(const int &choice, const string &ID)
{
    switch (choice)
    {
    case 1:
    {
        showPersonalData(ID);
        break;
    }
    case 2:
    {
        changeFullName(ID);
        break;
    }
    case 3:
    {
        changePhoneNumber(ID);
        break;
    }
    case 4:
    {
        changeEmail(ID);
        break;
    }
    case 5:
    {
        changePassword(ID);
        break;
    }
    default:
        break;
    }
}
//______________________________________________________________________________________________________________________
void Login()
{
    string inUsername, inPassword;
    while (true) // 1st while loop.
    {
        cout << "Inorder to Log in please enter the following!" << endl;
        inUsername = getID();
        inPassword = getPassword();

        if (database.count(inUsername)) // 1st if.
        {
            user userProfile;
            userProfile = database[inUsername];
            int failedLoginPasswordAttempts = 0, userChoice;

            // dealing with password
            if (!userProfile.isBlocked) // 2nd if.
            {
                if (inPassword == userProfile.password) // 3rd if.
                {

                    cout << "Successful Login, welcome back " << userProfile.ID << " your full name is " << userProfile.fullName << endl;
                    while (true) // 2nd while loop. for getting user choices from the login menu.
                    {

                        printLoginMenu();
                        userChoice = getUserChoice(endLoginMenu);

                        // if the user doesn't want to log out.
                        if (userChoice != endLoginMenu) // 1st if for the 2nd while loop.
                        {
                            executeLoginMenu(userChoice, userProfile.ID);
                            if (isClearScreen()) // 2nd if for the 2nd while loop.
                            {
                                clearScreen();
                            }
                        }

                        else // for 1st if of the 2nd while loop.
                        {
                            cout << "You will logout now!" << endl;
                            cout << "----------------------------------------------------------------------------------------" << endl;
                            return; // close the login function.
                        }
                    }
                }

                else // for the 3rd if.
                {
                    failedLoginPasswordAttempts += 1;
                    cout << "Failed to login! Invalid Password!" << endl;
                    cout << "----------------------------------------------------------------------------------------" << endl;

                    if (failedLoginPasswordAttempts >= 3)
                    {
                        cout << "You have been blocked from the system." << endl;
                        cout << "----------------------------------------------------------------------------------------" << endl;
                        updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, true); // blocked mode = true
                        break;                                                             // for the 1st while loop.
                    }
                }
            }

            else // for the 2nd if.
            {
                cout << "You are already blocked from the system" << endl;
                cout << "----------------------------------------------------------------------------------------" << endl;
                break; // for the 1st while loop.
            }
        }

        else // for the 1st if.
        {
            cout << "Username is not Found, Please try again later or Register with new account!" << endl;
            cout << "----------------------------------------------------------------------------------------" << endl;
            break; // for the 1st while loop.
        }
    }
}
//______________________________________________________________________________________________________________________
void executeMainMenu(const int &choice)
{
    if (choice == 1)
        Register();
    else
        Login();
}
//______________________________________________________________________________________________________________________