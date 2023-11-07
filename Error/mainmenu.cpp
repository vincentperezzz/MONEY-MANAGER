#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <iostream>
using namespace std;

string username, password, fname, lname;
double income;

void printTitle() {
    // Set console color to green
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);

cout << "+=========================================================+\n";
cout << "|                  $$$ MONEY MANAGER $$$                  |\n";
cout << "|             Your Expense and Budget Tracker             |\n";
cout << "+=========================================================+\n\n";

// Set console color to white
    SetConsoleTextAttribute(hConsole, 7);
}

void printGreeting() {
    // Set console color to white
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);

    // Get current time and print greeting message
    
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int hour = ltm->tm_hour;
    string greetingMsg;
    if (hour >= 0 && hour < 12) {
        greetingMsg = " Good morning";
    }
    else if (hour >= 12 && hour < 18) {
        greetingMsg = " Good afternoon";
    }
    else {
        greetingMsg = " Good evening";
    }
    cout << greetingMsg << ", and welcome to MONEY MANAGER!\n\n";
}


// ============================================================================
//REGISTER AND LOGIN 

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
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "      Username already exists. Please choose another.\n";
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        system("pause");
        return true;
    }
    cout << " Enter a password: ";
    cin >> password;
    cout << " Confirm password: ";
    cin >> confirm_password;
    if (password != confirm_password) {
        //font color to red
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "         Passwords do not match. Please try again.\n";
        cout << "-----------------------------------------------------------\n";
        //font color to white
        SetConsoleTextAttribute(hConsole, 7);
        system("pause");
        return true;
    }

    cout << endl;
    cout << " First Name: ";
    cin >> fname;
    cout << " Last Name: ";
    cin >> lname;
    cout << " Income: ";
    cin >> income;

    // Open the file for appending
    ofstream outfile("users.txt", ios::app);

    // Check if the file was successfully opened
    if (!outfile) {
        cerr << " Error opening file for writing." << endl;
        return 1;
    }

    // Write the data to the file
    outfile << username << "," << password << "," << fname << "," << lname << "," << income << endl;

    // Close the file
    outfile.close();

    //font color to green
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    cout << "-----------------------------------------------------------\n";
    cout << "                 Registration successful.\n";
    cout << "-----------------------------------------------------------\n";
    //font color to white
    SetConsoleTextAttribute(hConsole, 7);
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
    size_t pos = 0;
    string field;
    int fieldNum = 1; // keep track of the field number we're currently reading
        while ((pos = line.find(",")) != string::npos) {
            field = line.substr(0, pos);
            line.erase(0, pos + 1); // move to the next field
            if (fieldNum == 1 && field == username && line == password) {
            //font color to green
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10);
            cout << "-----------------------------------------------------------\n";
            cout << "                     Login successful.\n";
            cout << "-----------------------------------------------------------\n";
            //font color to white
            SetConsoleTextAttribute(hConsole, 7);
            system("pause");
            return true;
        }
    }
    //font color to red
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    cout << "-----------------------------------------------------------\n";
    cout << "               Invalid username or password.\n";
    cout << "-----------------------------------------------------------\n";
    //font color to white
    SetConsoleTextAttribute(hConsole, 7);
    system("pause");
    system("cls");
    printTitle();
    printGreeting();
    return false;
}
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
        cout << "Username updated successfully!" << endl;
    }
    else {
        // Delete the temporary file
        remove("temp.txt");
        cout << "Username not found." << endl;
    }
}

void edit_password(string old_password, string new_password) {
    string line;
    ifstream file("users.txt");
    ofstream temp("temp.txt");
    bool found = false;

    while (getline(file, line)) {
        // Find the line that contains the old password
        if (line.find(old_password + ",") == 0) {
            found = true;
            // Replace the old password with the new password
            line.replace(0, old_password.length(), new_password);
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
        cout << "Password updated successfully!" << endl;
    }
    else {
        // Delete the temporary file
        remove("temp.txt");
        cout << "Password not found." << endl;
    }
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
    cout << "User data deleted successfully.\n";
}

