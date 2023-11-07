#include "regandlogin.h"
#include "mainmenu.h"
#include <windows.h>
#include <iostream>
using namespace std;

string username, password, fname, lname;
double income;

int mainfunction();
void edit_username(string old_username, string new_username);
void edit_password(string old_password, string new_password);
void delete_user(string username);


/* REGISTER AND LOGIN */
int regandlogin() {
    int choice;
    while (true) {
    cout << " [1] Register\n [2] Login\n [3] Exit\n\n";
    cout << "-----------------------------------------------------------\n";
    cout << " Enter your choice: ";
    cin >> choice;

        
    switch (choice) {
        case 1:
            if (register_user()) {
                system("cls");
                printTitle();
                printGreeting();
                continue;
            };
            break;
        case 2:
            if (login_user()) {
                system("cls");
                loadinganimation();
                system("cls");
                printTitle();
                
                return 0;
                }
            break;
        case 3:
            //clear the terminal and print the title again
            system("cls");
            printTitle();
            cout << "|       Thank you for using MONEY MANAGER. Goodbye!       |\n";
            cout << "+=========================================================+\n";
            return false;
            break;
        default:
            system("cls");
            printTitle();
            //font color to red
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "-----------------------------------------------------------\n";
            cout << "              Invalid choice. Please try again.\n";
            cout << "-----------------------------------------------------------\n\n";
            //font color to white
            SetConsoleTextAttribute(hConsole, 7);
            system("pause");
            system("cls");
            printTitle();
            printGreeting();
            continue;
            break;
        }
    }
    return 0;
}

/* This is the main menu where the body or the content of the code lies*/

int mainmenu(){
    char choice;
    string old_username, new_username, old_password, new_password;
    char accountChoice, deleteChoice;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout << " Good day!\n";
        cout << " Let's get started, @" << username << "!\n\n";

        cout << " Here's what you can do:\n";
        cout << " [A] Edit Your Account\n";
        cout << " [B] Edit Your Income\n";
        cout << " [C] Set your Budget\n";
        cout << " [D] Track Your Expenses\n";
        cout << " [E] Summary/Report\n";
        cout << " [F] Wishlist\n";
        cout << " [G] Logout\n\n";
        cout << "-----------------------------------------------------------\n";
        cout << " Enter the letter of your choice: ";
        cin >> choice;

        loop:
        switch (choice) {
            case 'A':
            case 'a': // Edit Your Account
                
                system("cls");
                printTitle();
                cout << " Choose an option:\n";
                cout << " 1. New Username\n";
                cout << " 2. New Password\n";
                cout << " 3. Delete Account\n";
                cin >> accountChoice;
                switch (accountChoice) {
                    case '1': // New Username
                        
                        cout << "Enter the old username: ";
                        cin >> old_username;

                        cout << "Enter the new username: ";
                        cin >> new_username;

                        edit_username(old_username, new_username);
                        goto loop;
                        break;
                        
                    case '2': // New Password
                        cout << "Enter the old password: ";
                        cin >> old_password;

                        cout << "Enter the new password: ";
                        cin >> new_password;

                        edit_password(old_password, new_password);
                        goto loop;
                        break;

                    case '3': // Delete Account
                        //font color to red
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << "-----------------------------------------------------------\n";
                        cout << "     WARNING! THIS WILL PERMANENTLY DELETE THE ACCOUNT!!   \n";
                        cout << "-----------------------------------------------------------\n\n";
                        //font color to white
                        SetConsoleTextAttribute(hConsole, 7);
                        cout << " Are you sure you want to delete your account? (y/n)\n";
                        cin >> deleteChoice;

                        if (deleteChoice == 'y') {
                            delete_user(username);
                            cout << "Account deleted successfully.\n";
                            system("pause");
                            regandlogin();
                            return 0;
                        }
                        else {
                            cout << "Account not deleted.\n";
                            system("pause");
                            goto loop;
                            return 0;
                        }
                        break;
                        default:
                        cout << "Invalid option.\n";
                        goto loop;
                        break;
                }
                break;
            case 'B':
            case 'b': // Edit Your Income
                // code to change income
                break;
            case 'C':
            case 'c': // Set Your Budget
                char budgetChoice;
                cout << "Choose an option:\n";
                cout << "1. Edit Categories\n";
                cin >> budgetChoice;
                switch (budgetChoice) {
                    case '1': // Edit Categories
                        // code to edit budget categories
                        break;
                    default:
                        cout << "Invalid option.\n";
                        break;
                }
                break;
            case 'D':
            case 'd': // Track Your Expenses
                char expensesChoice;
                cout << "Choose an option:\n";
                cout << "1. Edit Categories\n";
                cin >> expensesChoice;
                switch (expensesChoice) {
                    case '1': // Edit Categories
                        // code to edit expense categories
                        break;
                    default:
                        cout << "Invalid option.\n";
                        break;
                }
                break;
            case 'E':
            case 'e': // Your Financial Report
                char reportChoice;
                cout << "Choose an option:\n";
                cout << "1. Line Bar\n";
                cout << "2. Total Expenses\n";
                cout << "3. Remaining Balance\n";
                cout << "4. Spending Alerts\n";
                cin >> reportChoice;
                switch (reportChoice) {
                    case '1': // Line Bar
                        // code to display line bar report
                        break;
                    case '2': // Total Expenses
                        // code to display total expenses
                        break;
                    case '3': // Remaining Balance
                        // code to display remaining balance
                        break;
                    case '4': // Spending Alerts
                        // code to display spending alerts
                        break;
                    default:
                        cout << "Invalid option.\n";
                        break;
                }
                break;
            case 'F':
            case 'f': // Create Your Wishlist
                // code to create wishlist
                break;
            default:
                cout << "Invalid option.\n";
                break;
    




                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
        }
    return 0;              
}


// ============================================================================


int main() {
    //size of the terminal
    system("mode con: cols=60");
    system("mode con: lines=30");
    printTitle();
    printGreeting();
    regandlogin();

    return 0;
}

