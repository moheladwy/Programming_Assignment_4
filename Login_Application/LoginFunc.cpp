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
struct user {   // Struct of User Profile Data.
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
unordered_map <string, user> getUserData; // The ID the Key and struct of the userProfile is the Value.
unordered_map <string, bool> registeredEmails; // The Email is the Key and the True(bool type) is the value(unused value).
//______________________________________________________________________________________________________________________
ostream& operator<<(ostream& out, user& inUser) // Overload the << operator to be able to print the struct in simple way.
{
    cout << "ID: " << inUser.ID << "\n" ;
    cout << "Email: " << inUser.email << "\n" ;
    cout << "Full Name: " << inUser.fullName << "\n";
    cout << "Phone Number: " << inUser.phoneNumber << "\n";
    cout << "Password: " << inUser.password << "\n";
    return out;
}
//______________________________________________________________________________________________________________________
void printMainMenu()
{
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "Choose one of the next main menu options:-" << endl;
    cout << "------------------------------------------" << endl;
    cout << "1- Register." << endl;
    cout << "2- Login." << endl;
    cout << "3- Exit." << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
}
//______________________________________________________________________________________________________________________
void printLoginMenu()
{
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "Choose one of the next login menu options:-" << endl;
    cout << "-------------------------------------------" << endl;
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
string encryptPassword(const string& plainText) // At-bash Cipher
{
    string cipherText;
    char cipherLetter;
    for (auto i: plainText)
    {
        if (isupper(i))
        {
            cipherLetter = char(int(i) + 25 - 2 * (i - 'A')); // equation to get new cipher letter
        }
        else if (islower(i))
        {
            cipherLetter = char(int(i) + 25 - 2 * (i - 'a'));
        }
        else
        {
            cipherLetter = char(int(i) + 1);
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
            plainLetter = i - 1;
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
    unsigned int numberOfUsers = workSheet.rowCount();

    for (int rowNumber = 2; rowNumber <= numberOfUsers; ++rowNumber)
    {
        // Load the Full Data of the User in the Struct.
        userProfile.indexUserInFile = rowNumber;
        userProfile.ID = workSheet.cell(rowNumber, colmID).value().get<string>();
        userProfile.fullName = workSheet.cell(rowNumber, colmFullName).value().get<string>();
        userProfile.phoneNumber = workSheet.cell(rowNumber, colmPhoneNumber).value().get<string>();
        userProfile.email = workSheet.cell(rowNumber, colmEmail).value().get<string>();
        userProfile.password = workSheet.cell(rowNumber, colmPassword).value().get<string>();
        userProfile.password = decryptPassword(userProfile.password);
        userProfile.isBlocked = workSheet.cell(rowNumber, colmBlocked).value().get<bool>();

        // Load the Struct of the User Profile in the map.
        getUserData.insert({ userProfile.ID,userProfile });
        registeredEmails.insert({ userProfile.email, true });
    }
    usersData.close();
}
//______________________________________________________________________________________________________________________
void updateXLSXFile(const int& indexUserInFile, const string& userID, const string& infoWantedToChange, const int& colm)
{
    // change the password in the map.
    user tempProfile = getUserData[userID]; XLDocument usersData;
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
    if (choice.length() == 1)
    {
        if (choice == "y" || choice == "Y" || choice == "n" || choice == "N") return true;
    }
    return false;
}
//______________________________________________________________________________________________________________________
void clearScreen()
{
    system("CLS");
    cout << flush;
    system("CLS");
}
//______________________________________________________________________________________________________________________
bool isWantClearScreen()
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
            cout << "Please enter a choice from (y) or (n) only, Try again." << endl;
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
    for (int i = 0; i < line.length(); i++) line[i] = char(tolower(line[i]));
    return line;
}
//______________________________________________________________________________________________________________________
bool isvalidID(const string& ID)
{
    regex isValid("^[\\w\\.\\-\\#\\!\\%\\$\\&\\+\\*\\/\\=\\?\\^\\`\\{\\|\\}\\~]+$");
    return regex_match(ID, isValid);
}
//______________________________________________________________________________________________________________________
string getID()
{
    string ID;
    while (true)
    {
        cout << "The ID/Username must be Unique and have no spaces." << endl;
        cout << "ID/Username: ";
        getline(cin, ID);
        if (isvalidID(ID))
        {
            ID = makeLowerCase(ID);
            return ID;
        }
        else
        {
            cout << "Please enter a valid ID that follows the instructions!" << endl;
        }
    }
}
//______________________________________________________________________________________________________________________
bool isValidFullName(const string& fullName)
{
    regex isValid("^[A-Z][a-zA-Z]+([ -]?[A-Za-z]*)+$");
    return regex_match(fullName, isValid);
}
//______________________________________________________________________________________________________________________
string getFullName()
{
    string fullName;
    while (true)
    {
        cout << "The Full Name must be 1st Caps and have no Numbers." << endl;
        cout << "FullName: ";
        getline(cin, fullName);
        if (isValidFullName(fullName))
        {
            return fullName;
        }
        else
        {
            cout << "FullName is not valid please follow the instructions and try again!" << endl;
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
        cout << "The Email must start with a letter not (Special characters, dots or spaces) ";
        cout << "and be 63 character before (@) after the (@) You can not have dot after (@) like (@.) ";
        cout << "and can not have 2 of dots like (..) and must end the email with a letter" << endl;
        cout << "Email: ";
        getline(cin,email);
        if (isValidEmail(email))
        {
            email = makeLowerCase(email);
            return email;
        }
        else
        {
            cout << "Email is not valid please follow the instructions and try again!" << endl;
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
        cout << "The Phone Number must start with 01 and followed by (0, 1, 2 or 5) then only anther 8 Numbers after that." << endl;
        cout<<"PhoneNumber: ";
        getline(cin,phoneNumber);
        if (isValidPhoneNumber(phoneNumber))
        {
            return phoneNumber;
        }
        else
        {
            cout<<"PhoneNumber is not valid please follow the instructions and try again!" << endl;
        }
    }
}
//______________________________________________________________________________________________________________________
bool isValidUserChoice(const string& choice, const int& endRange)
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
        isValidChoice = isValidUserChoice(getChoice, endRange);
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
    regex strongPasswordFormat("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#<>=?!+@$%^&*-]).{8,}$");
    return regex_match(password, strongPasswordFormat);
}
//______________________________________________________________________________________________________________________
string getPassword(const string& additionalText = "")
{
    char tempChar; string password;
    cout << additionalText << "Password: ";
    for(int count = 0;;)
    {
        tempChar = char(getch()); // getch() function returns an int, so we convert it to char.
        if(int(tempChar) >= 32 && int(tempChar) <= 126) // check if tempChar is numeric , alphabet, special character.
        {
            // stores tempChar in password.
            password += tempChar;
            ++count;
            cout << "*" ;
        }
        else if(tempChar == '\b' && count >= 1) // if user typed backspace. count should be greater than 0.
        {
            cout << "\b \b"; // rub the character behind the cursor.
            --count;
        }
        else if(tempChar == '\r') // if Enter is pressed
        {
            return password; // return the Password.
        }
    }
}
//______________________________________________________________________________________________________________________
string getNewPassword(const string& oldPassword = "")
{
    string newPassword, repeatNewPassword;
    while(true)
    {
        cout << "The password must contain small letters (a,b ..etc), capital letters (A,B ..etc), numbers (0,1 ..etc),";
        cout << "special characters (@,# ..etc) and be greater than 7 characters." << endl;
        newPassword = getPassword("Enter ");
        if (!isValidPassword(newPassword))
        {
            cout << "\n" << "The password must follow the instructions format, try again." << endl;
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
                    continue;
                }
            }
            return newPassword;
        }
        else
        {
            cout << "\n" << "The passwords doesn't match, Try again!" << endl;
        }
    }
}
//______________________________________________________________________________________________________________________
bool isIDExist(const string& inUsername)
{
    if (getUserData.count(inUsername)) // Check if the Key is Unique (Exists ones) in the map.
    {
        return true;
    }
    return false;
}
//______________________________________________________________________________________________________________________
bool isEmailExists(const string& email)
{
    if (registeredEmails.count(email)) // Check if the Key is Unique (Exists ones) in the map.
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

    int indexUserInFile = workSheet.rowCount() + 1; // The Place of the new user in the file.
    string ID, fullName, phoneNumber, email, password;

    while(ID.empty())
    {
        ID = getID(); // Get the ID from the User.
        if (isIDExist(ID))
        {
            cout << "The ID is already exists for someone else, Try again with a different ID." << endl;
            ID = "";
        }
    }

    fullName = getFullName();
    phoneNumber = getPhoneNumber();

    while (email.empty())
    {
        email = getEmail(); //Get the Email from the User.
        if (isEmailExists(email))
        {
            cout << "The email is already exists for someone else, Try again with a different email." << endl;
            email = "";
        }
    }
    password = getNewPassword();

    // Store the Data of the User in the map.
    newUser.indexUserInFile = indexUserInFile;
    newUser.ID = ID;
    newUser.fullName = fullName;
    newUser.phoneNumber = phoneNumber;
    newUser.email = email;
    newUser.password = password;
    newUser.isBlocked = false;

    getUserData.insert({ID, newUser});
    registeredEmails.insert({email, true});

    // Store the Data of the User in the Excel File.
    workSheet.cell(indexUserInFile, colmID).value() = ID;
    workSheet.cell(indexUserInFile, colmFullName).value() = fullName;
    workSheet.cell(indexUserInFile, colmPhoneNumber).value() = phoneNumber;
    workSheet.cell(indexUserInFile, colmEmail).value() = email;
    workSheet.cell(indexUserInFile, colmPassword).value() = encryptPassword(password); // Encrypting the password that will be stored in the file.
    workSheet.cell(indexUserInFile, colmBlocked).value() = false;

    usersData.save();
    usersData.close();

    cout << "You have been registered successfully to the system, You can login now if you want." << endl;
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
    // Update the new full name in the file and the map.
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

    // Update the phone number in the file and the map.
    updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, userProfile.phoneNumber, colmPhoneNumber);
    cout << "Changing the Phone Number Done Successfully!" << endl;
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

    // Update the new email in the file and the maps.
    updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, userProfile.email, colmEmail);
    cout << "Changing the Email Done Successfully!" << endl;
}
//______________________________________________________________________________________________________________________
void changePassword(const string& ID)
{
    string newPassword, oldPassword;
    user userProfile = getUserData[ID];

    while(true)
    {
        cout << endl;
        oldPassword = getPassword("Enter Your Old ");
        if (oldPassword == userProfile.password)
        {
            newPassword = getNewPassword(oldPassword);
            // Update the new password in the file and the map.
            updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, newPassword, colmPassword);
            cout << "Password Changed Successfully!\n";
            break;
        }
        else
        {
            cout << "Password is not correct, Try again!" << endl;
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
{
    string inUsername, inPassword;
    while (true) // 1st while loop.
    {
        cout << "Inorder to Log in please enter the following!\n";
        inUsername = getID();
        inPassword = getPassword();

        if (isIDExist(inUsername)) // 1st if.
        {
            user userProfile;
            userProfile = getUserData[inUsername];
            int failedLoginPasswordAttempts = 0, userChoice;

            // dealing with password
            if (!userProfile.isBlocked) // 2nd if.
            {
                if (inPassword == userProfile.password) // 3rd if.
                {

                    cout << "\n" << "Successful Login, welcome back " << userProfile.ID << " your full name is " << userProfile.fullName << endl;
                    while(true) // 2nd while loop. for getting user choices from the login menu.
                    {

                        printLoginMenu();
                        userChoice = getUserChoice(endRangeLoginMenuList);

                        // if the user doesn't want to log out.
                        if (userChoice != endRangeLoginMenuList) // 1st if for the 2nd while loop.
                        {
                            executeLoginMenu(userChoice, userProfile.ID);
                            if (isWantClearScreen()) // 2nd if for the 2nd while loop.
                            {
                                clearScreen();
                            }
                        }

                        else // for 1st if of the 2nd while loop.
                        {
                            cout << "You will logout now!" << endl;
                            return; // close the login function.
                        }
                    }
                }

                else // for the 3rd if.
                {
                    failedLoginPasswordAttempts += 1;
                    cout << "\n" << "Failed to login! Invalid Password!\n";

                    if (failedLoginPasswordAttempts >= 3)
                    {
                        cout << "You have been blocked from the system." << endl;
                        updateXLSXFile(userProfile.indexUserInFile, userProfile.ID, true); //blocked mode = true
                        break; // for the 1st while loop.
                    }
                }
            }

            else // for the 2nd if.
            {
                cout << "You are already blocked from the system\n";
                break; // for the 1st while loop.
            }
        }

        else // for the 1st if.
        {
            cout << "Username is not Found, Please try again later or Register with new account!\n";
            break; // for the 1st while loop.
        }
    }
}
//______________________________________________________________________________________________________________________
void executeMainMenu(const int& choice)
{

    if (choice == 1)
    {
        userRegister();
    }

    else
    {
        userLogin();
    }
}
//______________________________________________________________________________________________________________________