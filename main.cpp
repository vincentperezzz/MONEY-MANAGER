#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

//declaration of global variables

string username, password, fname, lname;
int income;
double balance;
char incomeType;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void initialize_income(string username, int& income);
void initialize_fname(string username, string& fname);
void initialize_lname(string username, string& lname);

int mainfunction();
int mainmenu();
int main();


/* HEADER */
void printTitle() {
    // Set console color to green
    SetConsoleTextAttribute(hConsole, 10);

cout << "+=========================================================+\n";
cout << "|                  $$$ MONEY MANAGER $$$                  |\n";
cout << "|             Your Expense and Budget Tracker             |\n";
cout << "+=========================================================+\n\n";

// Set console color to white
    SetConsoleTextAttribute(hConsole, 7);
}

void printGreeting() {
    cout << " Good day and welcome to MONEY MANAGER!\n\n";
}

/* REGISTER AND LOGIN */

// Function to check if a username already exists in the user data file
bool check_username_exists(string username) {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        if (line.find(username) != string::npos) {
            return true;
        }
    }
    return false;
}

// Function to register a new user
bool register_user() {
    string confirm_password;
    cout << "-----------------------------------------------------------\n";
    cout << " Enter a username: ";
    cin >> username;
    if (check_username_exists(username)) {
        //font color to red
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "      Username already exists. Please choose another.\n";
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ";
        system("pause");
        return true;
    }
    cout << " Enter a password: ";
    cin >> password;
    cout << " Confirm password: ";
    cin >> confirm_password;
    if (password != confirm_password) {
        //font color to red
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "         Passwords do not match. Please try again.\n";
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ";
        system("pause");
        return true;
    }

    cout << endl;
    cout << " First Name\t : ";
    cin >> fname;
    cout << " Last Name\t : ";
    cin >> lname;
    cout << endl;
    
    //ask user if income is monthly or weekly
    cout << " Is your income monthly or weekly? (M/W): ";
    cin >> incomeType;

    if (incomeType == 'M' || incomeType == 'm') {
        cout << " Enter your monthly income: $";
        cin >> income;
    }
    else if (incomeType == 'W' || incomeType == 'w') {
        cout << " Enter your weekly income: $";
        cin >> income;
    //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ";
        system("pause");
    }
    else {
        //font color to red
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "          Invalid input. Please enter 'M' or 'W'.\n";
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ";
        system("pause");
        system("cls");
        main();
    }
    

    // Open the file for appending
    ofstream outfile("users.txt", ios::app);

    // Check if the file was successfully opened
    if (!outfile) {
        cerr << " [SYSTEM] Error opening file for writing." << endl;
        return 1;
    }

    // Write the data to the file
    outfile << username << "," << password << "," << fname << "," << lname << "," << income << endl;

    // Close the file
    outfile.close();

    //font color to green
    SetConsoleTextAttribute(hConsole, 10);
    cout << "-----------------------------------------------------------\n";
    cout << "                  Registration successful.\n";
    cout << "       To access your account, kindly log in again.\n";    
    cout << "-----------------------------------------------------------\n";
    //font color to white
    SetConsoleTextAttribute(hConsole, 7);
    cout << " ";
    system("pause");
    return true;
}

// Function to log in a user
bool login_user() {
    cout << "-----------------------------------------------------------\n";
    cout << " Enter your username: ";
    cin >> username;
    cout << " Enter your password: ";
    cin >> password;
    // Check if username and password match an entry in the user data file
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        // Split the line into fields using commas as the separator
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() >= 2 && fields[0] == username && fields[1] == password) {
            //font color to green
            SetConsoleTextAttribute(hConsole, 10);
            cout << "-----------------------------------------------------------\n";
            cout << "                     Login successful.\n";
            cout << "-----------------------------------------------------------\n";
            //font color to white
            SetConsoleTextAttribute(hConsole, 7);
            cout << " ";
            system("pause");
            return true;
        }
    }
    //font color to red
    SetConsoleTextAttribute(hConsole, 12);
    cout << "-----------------------------------------------------------\n";
    cout << "               Invalid username or password.\n";
    cout << "-----------------------------------------------------------\n";
    //font color to white
    SetConsoleTextAttribute(hConsole, 7);
    cout << " ";
    system("pause");
    system("cls");
    printTitle();
    printGreeting();
    return false;
    return 0;
}

int loadinganimation() {
    system("COLOR 0e");
    system("cls");

    //Set ASCII to print special character.
    //Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\t       Loading...";
    cout << "\n\n\n\t       ";

    for(int i = 0; i < 31; i++)
        cout << (char)bar1;

    cout <<"\r";
    cout <<"\t       ";
    for(int i = 0; i < 31; i++)
    {
        cout << (char)bar2;
        Sleep(150);
    }

    cout<<"\n\t       ";
    system("Pause");

    return 0;
}

/* EDIT YOUR ACCOUNT */
void edit_username(string old_username, string new_username) {
    string line;
    ifstream file("users.txt");
    ofstream temp("temp.txt");
    bool found = false;

    while (getline(file, line)) {
        // Find the line that contains the old username
        if (line.find(old_username + ",") == 0) {
            found = true;
            // Replace the old username with the new username
            line.replace(0, old_username.length(), new_username);
        }
        // Write the line to the temporary file
        temp << line << endl;
    }
    file.close();
    temp.close();

    // Delete the original file
    remove("users.txt");

    if (found) {
        // Rename the temporary file to the original filename
        rename("temp.txt", "users.txt");
        //font color to green
        SetConsoleTextAttribute(hConsole, 10);
        cout << "-----------------------------------------------------------\n";
        cout << "              Username updated successfully!" << endl;
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        //update username in main menu
        username = new_username;
        cout << " ";
        system("pause");
        system ("cls");
        mainmenu();
    }
    else {
        // Delete the temporary file
        remove("temp.txt");
        //font color to red
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "                 Sorry! Username not found.\n";
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ";
        system("pause");
        system ("cls");
        mainmenu();
    }
}

void edit_password(string username, string old_password, string new_password) {
    string line;
    ifstream file("users.txt");
    ofstream temp("temp.txt");
    bool found = false;

    if (!file) {
        cerr << " [SYSTEM] Error opening input file!" << endl;
        return;
    }

    if (!temp) {
        cerr << " [SYSTEM] Error opening output file!" << endl;
        return;
    }

   while (getline(file, line)) {
        // Split the line into fields using ',' as the delimiter
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Check if the username and old password match
        if (fields.size() == 5 && fields[0] == username && fields[1] == old_password) {
            found = true;
            // Replace the old password with the new password
            fields[1] = new_password;
            // Concatenate the fields back into a line
            line = fields[0] + "," + fields[1] + "," + fields[2] + "," + fields[3] + "," + fields[4];
        }
        // Write the line to the temporary file
        temp << line << endl;
    }

    file.close();
    temp.close();

    if (!found) {
        remove("temp.txt");
        //font color to red
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "         Sorry! Username or password is incorrect.\n";
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ";
        system("pause");
        system ("cls");
        mainmenu();
        return;
    }

    // Delete the original file
    if (remove("users.txt") != 0) {
        cerr << " [SYSTEM] Error deleting input file!" << endl;
        return;
    }

    // Rename the temporary file to the original filename
    if (rename("temp.txt", "users.txt") != 0) {
        cerr << " [SYSTEM] Error renaming output file!" << endl;
        return;
    }

    //font color to green
    SetConsoleTextAttribute(hConsole, 10);
    cout << "-----------------------------------------------------------\n";
    cout << "              Password updated successfully!" << endl;        
    cout << "-----------------------------------------------------------\n";
    //font color to white
    SetConsoleTextAttribute(hConsole, 7);
    cout << " ";
    system("pause");
    system ("cls");
    mainmenu();
}


void delete_user(string username) {
    ifstream inFile;
    inFile.open("users.txt");

    ofstream outFile;
    outFile.open("temp.txt");

    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(",");
        string temp = line.substr(0, pos);
        if (temp != username) {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");
    //font color to green
    SetConsoleTextAttribute(hConsole, 10);
    cout << "-----------------------------------------------------------\n";
    cout << "               Account deleted successfully.\n";       
    cout << "-----------------------------------------------------------\n";
    //font color to white
    SetConsoleTextAttribute(hConsole, 7);
    
}

/* EDIT YOUR INCOME*/

void edit_income(string username, int new_income) {
    string line;
    ifstream file("users.txt");
    ofstream temp("temp.txt");
    bool found = false;

    if (!file) {
        cerr << " [SYSTEM] Error opening input file!" << endl;
        mainmenu();
        return;
    }

    if (!temp) {
        cerr << " [SYSTEM] Error opening output file!" << endl;
        mainmenu();
        return;
    }

    while (getline(file, line)) {
        // Split the line into fields using ',' as the delimiter
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Check if the username matches
        if (fields.size() == 5 && fields[0] == username) {
            found = true;
            // Replace the income with the new income
            fields[4] = to_string(new_income);
            // Concatenate the fields back into a line
            line = fields[0] + "," + fields[1] + "," + fields[2] + "," + fields[3] + "," + fields[4];
        }
        // Write the line to the temporary file
        temp << line << endl;
    }

    file.close();
    temp.close();

    if (!found) {
        remove("temp.txt");
        cerr << " [SYSTEM] User not found." << endl;
        mainmenu();
        return;
    }

    // Delete the original file
    if (remove("users.txt") != 0) {
        cerr << " [SYSTEM] Error deleting input file!" << endl;
        mainmenu();
        return;
    }

    // Rename the temporary file to the original filename
    if (rename("temp.txt", "users.txt") != 0) {
        cerr << " [SYSTEM] Error renaming output file!" << endl;
        mainmenu();
        return;
    }
    //font color to green
    SetConsoleTextAttribute(hConsole, 10);
    cout << "-----------------------------------------------------------\n";
    cout << "              Income updated successfully!" << endl;        
    cout << "-----------------------------------------------------------\n";
    //font color to white
    SetConsoleTextAttribute(hConsole, 7);
    cout << " ";
    system("pause");
    system("cls");
    mainmenu();
}

/* TRACK YOUR EXPENSES */

// Function to add a new category
void addCategory(map<string, double >& categories) {
    string category;
    double expenses;
    cout << " Enter a new category: ";
    cin.ignore(); // add this line to clear the input buffer
    getline(cin, category);
    cout << " Enter the initial expense of it: ";
    cin >> expenses;
    categories[category] = expenses;
     //font color to green
    SetConsoleTextAttribute(hConsole, 10);
    cout << "-----------------------------------------------------------\n";
    cout << "                Category added successfully.\n";        
    cout << "-----------------------------------------------------------\n";
    //font color to white
    SetConsoleTextAttribute(hConsole, 7);
}


// Function to remove a category
void removeCategory(map<string, double>& categories) {
    string category;
    cout << " Enter the name of the category you want to remove: ";
    cin.ignore(); // add this line to clear the input buffer
    getline(cin, category);
    if (categories.count(category) > 0) {
        categories.erase(category);
        //font color to green
        SetConsoleTextAttribute(hConsole, 10);
        cout << "-----------------------------------------------------------\n";
        cout << "              Category removed successfully.\n";        
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        
    } else {
        //font color to red
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "                   Category not found.\n";       
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        
    }
}

// Function to add an expense to a category
void addExpenses(map<string, double>& categories) {
    string category;
    double expenses;
    cout << " Enter category name: ";
    cin.ignore(); // add this line to clear the input buffer
    getline(cin, category);
    if (categories.count(category) > 0) {
        cout << " Enter the expense: ";
        cin >> expenses;
        categories[category] += expenses;
        cout << endl;
        //font color to green
        SetConsoleTextAttribute(hConsole, 10);
        cout << "-----------------------------------------------------------\n";
        cout << "                Amount added successfully. \n";        
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        
    }
    else {
        //font color to red
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "                   Category not found. \n";       
        cout << "-----------------------------------------------------------\n";
        //font color to yellow
        SetConsoleTextAttribute(hConsole, 14);
        cout << " [NOTE] The system is case sensitive. \n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        
    }
}

// Function to total all expenses
double totalExpenses(const map<string, double>& categories) {
    double total = 0;
    for (const auto& [category, amount] : categories) {
        total += amount;
    }
    return total;
}

// Functions to view all categories and expenses in different sorting orders
void viewCategoriesAlphabetical(const map<string, double>& categories) {
    cout << " CATEGORIES: (Alphabetical Order)" << endl;
    map<string, double> sorted_categories(categories.begin(), categories.end());
    for (const auto& [category, expenses] : sorted_categories) {
        cout << " " << category << "\t: " << expenses << endl;
    }
}

void viewCategoriesAscending(const map<string, double>& categories) {
    cout << " CATEGORIES: (Ascending Order of Expenses)" << endl;
    vector<pair<string, double>> sorted_categories(categories.begin(), categories.end());
    sort(sorted_categories.begin(), sorted_categories.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });
    for (const auto& [category, expenses] : sorted_categories) {
        cout << " " << category << ": " << expenses << endl;
    }
}

void viewCategoriesDescending(const map<string, double>& categories) {
    cout << " CATEGORIES: (Descending Order of Expenses)" << endl;
    vector<pair<string, double>> sorted_categories(categories.begin(), categories.end());
    sort(sorted_categories.begin(), sorted_categories.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    for (const auto& [category, expenses] : sorted_categories) {
        cout << " " << category << ": " << expenses << endl;
    }
}

/* Initializationa and Declaration of Variables from the database*/

void initialize_income(string username, int& income) {
    ifstream infile("users.txt");
    string line;
    while (getline(infile, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields[0] == username) {
            income = stod(fields[4]);
            break;
        }
    }
}

void initialize_fname(string username, string& fname) {
    ifstream infile("users.txt");
    string line;
    while (getline(infile, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields[0] == username) {
            fname = fields[2];
            break;
        }
    }
}

void initialize_lname(string username, string& lname) {
    ifstream infile("users.txt");
    string line;
    while (getline(infile, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields[0] == username) {
            lname = fields[3];
            break;
        }
    }
}

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
                main();
                continue;
            };
            break;
        case 2:
            if (login_user()) {
                system("cls");
                loadinganimation();
                system("cls");
                mainmenu();
                return 0;
                }
            break;
        case 3:
            //clear the terminal and print the title again
            char exitchoice;
            cout << "-----------------------------------------------------------\n";
            cout << " Are you sure you want to exit? (Y/N): ";
            cin >> exitchoice;
            if (exitchoice == 'Y' || exitchoice == 'y') {
                system("cls");
                printTitle();
                cout << "-----------------------------------------------------------\n";
                cout << "       Thank you for using MONEY MANAGER. Goodbye!         \n";
                cout << "-----------------------------------------------------------\n";
                exit(0);
                break;
            }
            else if (exitchoice == 'N' || exitchoice == 'n') {
                system("cls");
                printTitle();
                printGreeting();
                continue;
                break;
            }
            else {
                //font color to red
                SetConsoleTextAttribute(hConsole, 12);
                cout << "-----------------------------------------------------------\n";
                cout << "         Invalid choice. Please restart the system.\n";
                cout << "-----------------------------------------------------------\n\n";
                //font color to white
                SetConsoleTextAttribute(hConsole, 7);
                exit(0);
                break;
            } 
        default:
            cout << "-----------------------------------------------------------\n";
            //font color to red
            SetConsoleTextAttribute(hConsole, 12);
            cout << "-----------------------------------------------------------\n";
            cout << "         Invalid choice. Please restart the system.\n";
            cout << "-----------------------------------------------------------\n\n";
            //font color to white
            SetConsoleTextAttribute(hConsole, 7);
            exit(0);
            break;
        }
    }
    return 0;
}


/* This is the main menu where the body or the content of the code lies*/

int mainmenu(){
    printTitle();
    initialize_income(username, income);
    initialize_fname(username, fname);
    initialize_lname(username, lname);
    char choice, accountChoice, deleteChoice;
    double spending_status, item_price;
    string old_username, new_username, old_password, new_password, item_name;
    

    int sortChoice = 1;
    map<string, double> categories{
        {"Dorm/Rent", 0},
        {"Electricity", 0},
        {"Water Bill", 0},
        {"Internet", 0},
        {"Food/Grocery", 0},
        {"Entertainment", 0},
        {"Transportation", 0},
        {"Savings", 0}
    };

    loop:    
        cout << " Good day!\n";
        cout << " Let's get started, @" << username << "!\n\n";

        cout << " Here's what you can do:\n";
        cout << " [A] Edit Your Account\n";
        cout << " [B] Edit Your Income\n";
        cout << " [C] Track Your Expenses\n";
        cout << " [D] Your Financial Report\n";
        cout << " [E] Create Your Wishlist\n";
        cout << " [F] Logout\n\n";
        cout << "-----------------------------------------------------------\n";
        cout << " Enter the letter of your choice: ";
        cin >> choice;

        
        switch (choice) {
            case 'A': case 'a': // Edit Your Account
                
                system("cls");
                printTitle();
                cout << " ACCOUNT SETTINGS\n\n";
                cout << " Choose an option:\n";
                cout << " [1] Edit existing Username\n";
                cout << " [2] Edit existing Password\n";
                cout << " [3] Delete Account\n";
                cout << " [4] Back to Menu\n";
                cout << "-----------------------------------------------------------\n";
                cout << " Enter your choice: ";
                cin >> accountChoice;
                switch (accountChoice) {
                    case '1': // New Username
                        
                        cout << " Enter the old username: ";
                        cin >> old_username;

                        cout << " Enter the new username: ";
                        cin >> new_username;

                        edit_username(old_username, new_username);
                        goto loop;
                        break;
                        
                    case '2': // New Password                        
                        cout << " Enter the old password: ";
                        cin >> old_password;

                        cout << " Enter the new password: ";
                        cin >> new_password;

                        edit_password(username, old_password, new_password);
                        goto loop;
                        break;

                    case '3': // Delete Account
                        //font color to yellow
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "-----------------------------------------------------------\n";
                        cout << "     WARNING! THIS WILL PERMANENTLY DELETE THE ACCOUNT!!   \n";
                        cout << "-----------------------------------------------------------\n\n";
                        //font color to white
                        SetConsoleTextAttribute(hConsole, 7);
                        cout << " Are you sure you want to delete your account? (y/n): ";
                        cin >> deleteChoice;

                        if (deleteChoice == 'y' || deleteChoice == 'Y') {
                            delete_user(username);
                            cout << " ";
                            system("pause");
                            system("cls");
                            printTitle();
                            goto loop;
                            return 0;
                        }
                        else {
                            //font color to green
                            SetConsoleTextAttribute(hConsole, 10);
                            cout << "-----------------------------------------------------------\n";
                            cout << "                    Account not deleted.\n";       
                            cout << "-----------------------------------------------------------\n";
                            //font color to white
                            SetConsoleTextAttribute(hConsole, 7);
                            cout << " ";
                            system("pause");
                            system("cls");
                            printTitle();
                            goto loop;
                            return 0;
                        }
                        break;
                    case '4': // Back to Menu
                        cout << "-----------------------------------------------------------\n";
                        system("cls");
                        printTitle();
                        goto loop;
                        break;
                    default:
                        //font color to red
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << "-----------------------------------------------------------\n";
                        cout << "              Invalid choice. Please try again.\n";
                        cout << "-----------------------------------------------------------\n\n";
                        //font color to white
                        SetConsoleTextAttribute(hConsole, 7);
                        goto loop;
                        break;
                }
                break;
            case 'B': case 'b': // Edit Your Income
                char incomechoice;
                if (username != "") {
                    string line;
                    ifstream file("users.txt");
                    if (!file) {
                        cerr << " [SYSTEM] Error opening file!" << endl;
                        goto loop;
                    }
                    while (getline(file, line)) {
                        // Check if the line contains the username
                        if (line.find(username + ",") == 0) {
                            // Get the income from the line
                            string income_str = line.substr(line.rfind(",") + 1);
                            int income = stoi(income_str);
                            cout << "-----------------------------------------------------------\n";
                            cout << " Your current income is: $" << income << endl;
                            cout << "-----------------------------------------------------------\n\n";
                            break;
                        }
                    }
                    file.close();

                    // Ask user if they want to update their income
                    cout << " Do you want to edit your income? (Y/N): ";
                    cin >> incomechoice;
                    if (incomechoice == 'y' || incomechoice == 'Y') {
                        // Prompt the user to enter their new income
                            cout << " Enter your new income: $";
                            int new_income;
                            cin >> new_income;
                           
                            // Edit the income in the file
                            edit_income(username, new_income);
                    }
                    else {
                        system("cls");
                        printTitle();
                        goto loop;
                    }
                }
                break;
                
            case 'C': case 'c': // Track Your Expenses
                
                loop1:
                system("cls");
                printTitle();
                char expensesChoice;

                cout << " TRACK YOUR EXPENSES\n";
                cout << " Income = $" << income << endl << endl;
                if (sortChoice == 1) { // display default categories (alphabetical)
                    viewCategoriesAlphabetical(categories);
                } else if (sortChoice == 2) { // display categories in ascending order
                    viewCategoriesAscending(categories);
                } else if (sortChoice == 3) { // display categories in descending order
                    viewCategoriesDescending(categories);
                }
                cout << endl;

                cout << " Choose an option:\n";
                cout << " [1] Add an Expense to a Category\n";
                cout << " [2] Add a New Category\n";
                cout << " [3] Remove a Category\n";
                cout << " [4] Sort Categories and Expenses\n";
                cout << " [5] Back To Menu\n\n";
                cout << "-----------------------------------------------------------\n";
                cout << " Enter your choice: ";
                cin >> expensesChoice;
                switch (expensesChoice) {
                    case '1': // Add the Expenses to a Category
                        cout << "-----------------------------------------------------------\n";
                        addExpenses(categories);
                        cout << endl;
                        cout << " ";
                        system("pause");
                        goto loop1;
                        break;
                    case '2': // Add a New Category
                        cout << "-----------------------------------------------------------\n";
                        addCategory(categories);
                        cout << endl;
                        cout << " ";
                        system("pause");
                        goto loop1;
                        break;
                    case '3': // Remove a Category
                        cout << "-----------------------------------------------------------\n";
                        removeCategory(categories);
                        cout << endl;
                        system("pause");
                        goto loop1;
                        break;
                    case '4': // Sort Categories and Expenses
                        cout << "-----------------------------------------------------------\n";
                        cout << " How do you want to sort the categories?" << endl << endl;
                        cout << " [1] Sort by alphabetical order of categories" << endl;
                        cout << " [2] Sort by ascending order of expenses" << endl;
                        cout << " [3] Sort by descending order of expenses" << endl << endl;
                        cout << "-----------------------------------------------------------\n";
                        cout << " Enter your choice: ";
                        cin >> sortChoice;
                         cout << "-----------------------------------------------------------\n";
                        if (sortChoice < 1 || sortChoice > 3) {
                            //font color to red
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "-----------------------------------------------------------\n";
                            cout << "              Invalid choice. Please try again.\n";
                            cout << "-----------------------------------------------------------\n\n";
                            //font color to white
                            SetConsoleTextAttribute(hConsole, 7);
                            cout << " ";
                            system("pause");
                            goto loop1;
                        }
                        //font color green
                        SetConsoleTextAttribute(hConsole, 10);
                        cout << "-----------------------------------------------------------\n";
                        cout << "               Categories sorted successfully.\n";
                        cout << "-----------------------------------------------------------\n";
                        //font color white
                        SetConsoleTextAttribute(hConsole, 7);
                        cout << " ";
                        system("pause");
                        goto loop1;
                        break;
                    case '5': // Back to Menu
                        cout << "-----------------------------------------------------------\n";
                        system("cls");
                        printTitle();
                        goto loop;
                        break;
                    default:
                        cout << "-----------------------------------------------------------\n";
                        //font color to red
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << "-----------------------------------------------------------\n";
                        cout << "              Invalid choice. Please try again.\n";
                        cout << "-----------------------------------------------------------\n\n";
                        //font color to white
                        SetConsoleTextAttribute(hConsole, 7);
                        cout << " ";
                        system("pause");
                        system("cls");
                        printTitle();
                        goto loop1;
                        break;
                }
                break;

            case 'D': case 'd': // Your Financial Report
                {
                    while (true) {
                        system("cls");
                        printTitle();
                        char reportChoice;
    
                        cout << " " << fname << " " << lname << "'s Financial Report\n\n";
                        cout << " Choose an option:\n";
                        cout << " [1] Total Expenses and Remaining Balance\n";
                        cout << " [2] Spending Alerts\n";
                        cout << " [3] Back To Menu\n\n";
                        cout << "-----------------------------------------------------------\n";
                        cout << " Enter your choice: ";
                        cin >> reportChoice;

                        switch (reportChoice) {
                            case '1': // Total Expenses and Remaining Balance
                                cout << "-----------------------------------------------------------\n";
                                cout << " Your income is: " << income << endl;
                                cout << " Your total expenses is: " << totalExpenses(categories) << endl;
                                balance = income - totalExpenses(categories);
                                cout << " Your remaining balance is: " << balance << endl << endl;
                                cout << " ";
                                system("pause");
                                break;
                            case '2': // Spending Alerts
                                cout << "-----------------------------------------------------------\n";
                                spending_status = (totalExpenses(categories)/income)*100;
                                cout << " You have spent " << spending_status << "\% of your income!\n\n";
                                if (spending_status == 0) {
                                    //font color yellow
                                    SetConsoleTextAttribute(hConsole, 14);
                                    cout << "-----------------------------------------------------------\n";
                                    cout << "       NOTE: Please add data on TRACK YOUR EXPENSES!\n";
                                    cout << "-----------------------------------------------------------\n";
                                    //font color white
                                    SetConsoleTextAttribute(hConsole, 7);
                                } else if (spending_status >= 50) {
                                    //font color red
                                    SetConsoleTextAttribute(hConsole, 12);
                                    cout << "-----------------------------------------------------------\n";
                                    cout << "                   ALERT: High spending!\n";
                                    cout << "-----------------------------------------------------------\n";
                                    //font color white
                                    SetConsoleTextAttribute(hConsole, 7);
                                } else {
                                    //font color green
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "-----------------------------------------------------------\n";
                                    cout << "                  You're a smart spender!\n";
                                    cout << "-----------------------------------------------------------\n";
                                    //font color white
                                    SetConsoleTextAttribute(hConsole, 7);
                                }
                                cout << " ";
                                system("pause");
                                system("cls");
                                printTitle();
                                goto loop;
                                break;

                            case '3': // Back to Menu
                                cout << "-----------------------------------------------------------\n";
                                system("cls");
                                printTitle();
                                goto loop;
                                break;
                            default:
                                cout << "-----------------------------------------------------------\n";
                                cout << endl;
                                //font color to red
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "-----------------------------------------------------------\n";
                                cout << "              Invalid choice. Please try again.\n";
                                cout << "-----------------------------------------------------------\n\n";
                                //font color to white
                                SetConsoleTextAttribute(hConsole, 7);
                                cout << " ";
                                system("pause");
                                system("cls");
                                printTitle();
                                goto loop;
                                break;
                        }
                    }
                }
                break;

            case 'E': case 'e': // Create Your Wishlist
                system("cls");
                printTitle();
                cout << " CREATE YOUR WISHLIST\n\n";
                cout << "-----------------------------------------------------------\n";
                cout << " Enter the name of the item: ";
                cin.ignore(); // add this line to clear the input buffer
                getline (cin, item_name);
                cout << " Enter the price of the item: ";
                cin >> item_price;
                if (item_price <= balance) {
                    //font color green
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << "-----------------------------------------------------------\n";
                    cout << "       You have enough balance! Money buys happiness!\n";
                    cout << "-----------------------------------------------------------\n\n";
                    //font color white
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << " ";
                    system("pause");
                    system("cls");
                    printTitle();
                    goto loop;
                   
                } else {
                    //font color yellow
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << "-----------------------------------------------------------\n";
                    cout << "           Almost there! You should save more!\n";
                    cout << "-----------------------------------------------------------\n\n";
                    //font color white
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << " ";
                    system("pause");
                    system("cls");
                    printTitle();
                    goto loop;   
                }
                break;

            case 'F': case 'f': // Logout the user and return to regandlogin()
                cout << "-----------------------------------------------------------\n";
                cout << "Do you want to logout? (y/n): ";
                char logoutChoice;
                cin >> logoutChoice;

                if (logoutChoice == 'y' || logoutChoice == 'Y') {
                    system("cls");
                    main();
                } else {
                    system("cls");
                    printTitle();
                    goto loop;
                }
                break;

            default:
            system("cls");
            printTitle();
            //font color to red
            SetConsoleTextAttribute(hConsole, 12);
            cout << "-----------------------------------------------------------\n";
            cout << "              Invalid choice. Please try again.\n";
            cout << "-----------------------------------------------------------\n\n";
            //font color to white
            SetConsoleTextAttribute(hConsole, 7);
            cout << " ";
            system("pause");
            system("cls");
            printTitle();
            printGreeting();
            goto loop;
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


