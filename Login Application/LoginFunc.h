//___________________________________________________________________________________________________
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application.
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Ahmed
// Purpose: .......
// File: This is the Header file that contain the prototype of the Functions and its parameters.
//___________________________________________________________________________________________________
#ifndef LOGIN_APPLICATION_LOGINFUNC_H
#define LOGIN_APPLICATION_LOGINFUNC_H
#pragma once
#include <string>
using namespace std;
//___________________________________________________________________________________________________
// general functions for being used in many functions for the project.
//___________________________________________________________________________________________________
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
string getPassword(string type); // Done - Mohamed Eladwy.
void fetchXLSXFile(); // Done - Mohamed Eladwy.
void updateXLSXFile(int& indexUserInFile, string& newPassword, string& userID); // Done - Mohamed Eladwy.
void executeUserChoice(int choice);
//___________________________________________________________________________________________________
// The main functions of the project.
//___________________________________________________________________________________________________
void userRegister(string& ID, string& fullName, string& phoneNumber, string& email); // Done - Mohamed Eladwy.
string userLogin(string ID, string password);
void changePassword();
void forgetPassword();
//___________________________________________________________________________________________________
#endif //LOGIN_APPLICATION_LOGINFUNC_H