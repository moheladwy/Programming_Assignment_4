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
bool isValidPhoneNumber(const string& phoneNumber); 
bool isValidEmail(const string& email); 
bool isValidPassword(const string& password);
bool doesIDExist(const string& inUsername); 
bool doesEmailExists(const string& email);
bool isClearScreen();
bool isYesOrNo(const string& choice);

string makeLowerCase(string line);
string encryptPassword(const string& plainText); 
string decryptPassword(const string& cipherText); 
string getID(); 
string getFullName(); 
string getPhoneNumber(); 
string getEmail(); 
string getPassword(const string& additionalText = ""); 
string getANewPassword(const string& oldPassword = ""); 
//______________________________________________________________________________________________________________________
// The main functions of the project.
//______________________________________________________________________________________________________________________
void userRegister();
void userLogin(); 
void showPersonalData(const string& ID);
void changeFullName(const string& ID);
void changePhoneNumber(const string& ID);
void changeEmail(const string& ID);
void changePassword(const string& ID, bool fromOTP = false); 
void executeLoginMenu(const int& choice, const string& ID);
void executeMainMenu(const int& choice);
//______________________________________________________________________________________________________________________
#endif //LOGIN_APPLICATION_LOGINFUNC_H