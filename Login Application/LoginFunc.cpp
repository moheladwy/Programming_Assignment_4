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
using namespace std;
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
};
// operator overloading for struct, you can modify to allow for direct output of each user in the Excel file
ostream& operator<< (ostream& out, user inUser){
    out << inUser.ID << '\n' << inUser.fullName << '\n' << inUser.phoneNumber << '\n' << inUser.email << '\n' << inUser.password;
    return out;
}
vector <user> systemUsers;// no need to use vectors, we can only use maps
map <string, user> getUserStruct {}; // key: userID, value: struct of this exact user
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
bool checkValidYesOrNo(string& choice)
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
string encryptPassword(string plainText) { // Atbash Cipher
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
string decryptPassword(string cipherText) {
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
string userLogin(string ID, string password){// parameter password is assumed to be the plain password
    return "";
}
//___________________________________________________________________________________________________