//______________________________________________________________________________________________________________________
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application.
// Last Modification Date: xx/05/2022
// Author1 and ID and Group: Mohamed Hussein Hassan Eladwy. ID: 20210335. Group: B. Section: 17 - 18.
// Author2 and ID and Group: Yusuf Elsayed Abdelrahman Bdr. ID: 20210502. Group: B. Section: 17 - 18.
// Author3 and ID and Group: Amr Khalied Elsayed Elhennawy. ID: 20210274. Group: B. Section: 17 - 18.
// Teaching Assistant: Eng.Hagar Ahmed
// Purpose: .......
// File: This is the CPP file that contain the main algorithm of the program.
//______________________________________________________________________________________________________________________
#include <iostream>
#include "LoginFunc.h"
using namespace std;
//______________________________________________________________________________________________________________________
int main()
{
    int userChoice;
    bool CLS, openSystem = true;

    cout << "Welcome in our Login System Application!" << endl;
    fetchXLSXFile();

    while (openSystem)
    {
        printMainMenu();
        userChoice = getUserChoice(3);

        if (userChoice != 3)
        {
            executeMainMenu(userChoice);
            CLS = isClearScreen();
            if (CLS)
            {
                clearScreen();
            }
        }

        else
            openSystem = false;
    }

    printEndApp();
    return 0;
}
//______________________________________________________________________________________________________________________