/*
This the Functions that we will work on it.
amr have the functions [1:5]
eladwy have the functions [6:10]
bdr have the functions [11:15]
*/
//____________________________________________________________________________________________
string getFileName()
{
    string fileName;
    cout << "Enter the Name of the File with it's Extention: ";
    cin >> fileName;    
    return fileName;
}
//____________________________________________________________________________________________
void mainMenu()
{
    cout << "1. Add new text to the end of the file." << endl;
    cout << "2. Display the content of the file." << endl;
    cout << "3. Empty the file." << endl;
    cout << "4. Encrypt the file content." << endl;
    cout << "5. Decrypt the file content." << endl;
    cout << "6. Merge another file." << endl;
    cout << "7. Count the number of words in the file." << endl;
    cout << "8. Count the number of characters in the file." << endl;
    cout << "9. Count the number of lines in the file." << endl;
    cout << "10. Search for a word in the file." << endl;
    cout << "11. Count the number of times a word exists in the file." << endl;
    cout << "12. Turn the file content to upper case." << endl;
    cout << "13. Turn the file content to lower case." << endl;
    cout << "14. Turn file content to 1st caps (1st char of each word is capital)." << endl;
    cout << "15. Save." << endl;
    cout << "16. Exit." << endl;
}
//____________________________________________________________________________________________
void clearScreen()
{
    system("CLS");
    cout << flush;
    system("CLS");
}
//____________________________________________________________________________________________