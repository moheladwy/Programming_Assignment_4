// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application.
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Ahmed
// Purpose: .......
// File: This is the CPP file that contain the main algorithm of the program.
//___________________________________________________________________________________________________
#include <iostream>
// #include <regex>
// #include <fstream>
#include "OpenXLSX.hpp"
#include "LoginFunc.h"
using namespace std;
using namespace OpenXLSX;
//___________________________________________________________________________________________________
int main()
{
    cout << "Welcome in Login Application Project!" << endl;
    printMainMenu();
    // initialize XLDocument
    XLDocument doc;
    // create document
    doc.create("./Demo01.xlsx");
    // add worksheet
    auto workSheet = doc.workbook().worksheet("Sheet1");
    // add text
    workSheet.cell(XLCellReference("A2")).value() ="Login Application Project.";
    // save document
    doc.save();
    return 0;
}
//___________________________________________________________________________________________________