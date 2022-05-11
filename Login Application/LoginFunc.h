//______________________________________________________________________________________________________________________
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application.
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Ahmed
// Purpose: .......
// File: This is the Header file that contain the prototype of the Functions and its parameters.
//______________________________________________________________________________________________________________________
#ifndef LOGIN_APPLICATION_LOGINFUNC_H
#define LOGIN_APPLICATION_LOGINFUNC_H
#pragma once
#include <string>
using namespace std;
//______________________________________________________________________________________________________________________
// general functions for being used in many functions for the project.
//______________________________________________________________________________________________________________________
void printMainMenu(); // Done - Mohamed Eladwy.
void printEndApp(); // Done - Mohamed Eladwy.
void clearScreen(); // Done - Mohamed Eladwy.
bool isClearScreen(); // Done - Mohamed Eladwy.
bool isYesOrNo(string& choice); // Done - Mohamed Eladwy.
string makeLowerCase(string line); // Done - Mohamed Eladwy.
bool checkUserChoice(string choice); // Done - Mohamed Eladwy.
int getUserChoice(); // Done - Mohamed Eladwy.
string encryptPassword(const string& plainText); // Done - Yusuf Badr.
string decryptPassword(const string& cipherText); // Done - Yusuf Badr.
bool isvalidID(string& ID);
bool isValidFullName(string& fullName);
bool isValidPhoneNumber(string& phoneNumber); //Done by Amr
bool isValidEmail(string& email); //Done by Amr
bool isValidPassword(string& password); // Done - Mohamed Eladwy.
string getID();
string getFullName();
string getPhoneNumber(); //Done by Amr
string getEmail(); //Done by Amr
string getPassword(const string& additionalText = ""); // Done - Mohamed Eladwy - Modified - Yusuf Badr.
string getANewPassword(); // Modified - Yusuf Badr
bool doesIDExist(const string& inUsername); // Done - Yusuf Badr
bool doesEmailExists(const string& email); // Done - Mohamed Eladwy.
string userLogin(); // Done - Yusuf Badr
void changePassword();
void fetchXLSXFile(); // Done - Mohamed Eladwy.
void updateXLSXFile(const int& indexUserInFile, const string& userID, const string& newPassword); // Done - Mohamed Eladwy.
void updateXLSXFile(const int& indexUserInFile, const string& userID, const bool& blockedMood ); // Done - Mohamed Eladwy.
void executeUserChoice(const int& choice);
//______________________________________________________________________________________________________________________
// The main functions of the project.
//______________________________________________________________________________________________________________________
void userRegister(); // Done - Mohamed Eladwy.
string userLogin(string ID, string password);
void changePassword();
void forgetPassword();
//______________________________________________________________________________________________________________________
#endif //LOGIN_APPLICATION_LOGINFUNC_H