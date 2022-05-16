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
int getUserChoice(const int& endRange);

void printMainMenu();
void printLoginMenu();
void printEndApp();
void clearScreen();
void fetchXLSXFile();
void updateXLSXFile(const int& indexUserInFile, const string& userID, const string& infoWantedToChange, const int& colm);
void updateXLSXFile(const int& indexUserInFile, const string& userID, const bool& blockedMood );

bool checkUserChoice(const string& choice, const int& endRange);
bool isvalidID(const string& ID);
bool isValidFullName(const string& fullName);
bool isValidPhoneNumber(const string& phoneNumber); //Done by Amr
bool isValidEmail(const string& email); //Done by Amr
bool isValidPassword(const string& password); // Done - Mohamed Eladwy.
bool doesIDExist(const string& inUsername); // Done - Yusuf Badr
bool doesEmailExists(const string& email); // Done - Mohamed Eladwy.
bool isClearScreen(); // Done - Mohamed Eladwy.
bool isYesOrNo(const string& choice); // Done - Mohamed Eladwy.

string makeLowerCase(string line); // Done - Mohamed Eladwy.
string encryptPassword(const string& plainText); // Done - Yusuf Badr.
string decryptPassword(const string& cipherText); // Done - Yusuf Badr.
string getID(); // Done - Amr.
string getFullName(); // Done - Amr.
string getPhoneNumber(); //Done by Amr
string getEmail(); //Done by Amr
string getPassword(const string& additionalText = ""); // Done - Mohamed Eladwy - Modified - Yusuf Badr.
string getANewPassword(const string& oldPassword = ""); // Done - Mohamed Eladwy - Modified - Yusuf Badr.
//______________________________________________________________________________________________________________________
// The main functions of the project.
//______________________________________________________________________________________________________________________
void userRegister(); // Done - Mohamed Eladwy.
void userLogin(); // Done - Yusuf Bdr - Modified by - Mohamed Eladwy.
void showPersonalData(const string& ID); // Done - Mohamed Eladwy.
void changeFullName(const string& ID); // Done - Mohamed Eladwy.
void changePhoneNumber(const string& ID); // Done - Mohamed Eladwy.
void changeEmail(const string& ID); // Done - Mohamed Eladwy.
void changePassword(const string& ID, bool fromOTP = false); // Done - Yusuf Bdr - Modified by - Mohamed Eladwy.
void executeLoginMenu(const int& choice, const string& ID); // Done - Mohamed Eladwy.
void executeMainMenu(const int& choice); // Done - Mohamed Eladwy.
//______________________________________________________________________________________________________________________
#endif //LOGIN_APPLICATION_LOGINFUNC_H