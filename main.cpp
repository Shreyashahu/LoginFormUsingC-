#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Temp {
    string email, password, username;
    string sName, sPass, sEmail;
    fstream file;

public:
    void signUp();
    void login();
    void newPass();
} obj;

int main() {
    char choice;
    while (true) {
        cout << "\n1 - Registration" << endl;
        cout << "2 - Login" << endl;
        cout << "3 - Forgot Password" << endl;
        cout << "4 - Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character left in the buffer

        switch (choice) {
            case '1':
                obj.signUp();
                break;
            case '2':
                obj.login();
                break;
            case '3':
                obj.newPass();
                break;
            case '4':
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid Selection" << endl;
        }
    }
}

void Temp::signUp() {
    cout << "\nEnter the username: ";
    getline(cin, username);
    cout << "Enter the email address: ";
    getline(cin, email);
    cout << "Enter the password: ";
    getline(cin, password);

    file.open("loginData.txt", ios::out | ios::app);
    if (!file) {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    file << username << "*" << email << "*" << password << endl;
    file.close();
    cout << "REGISTRATION SUCCESSFUL !" << endl;
}

void Temp::login() {
    cout << "\n-----LOGIN-----" << endl;
    cout << "Enter your username: ";
    getline(cin, sName);
    cout << "Enter your password: ";
    getline(cin, sPass);

    file.open("loginData.txt", ios::in);
    if (!file) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    bool found = false;
    while (getline(file, username, '*') && getline(file, email, '*') && getline(file, password)) {
        if (sName == username) {
            found = true;
            if (sPass == password) {
                cout << "ACCOUNT LOGIN SUCCESSFUL !" << endl;
                cout << "Username: " << username << endl;
                cout << "Email: " << email << endl;
                file.close();
                return;
            } else {
                cout << "Incorrect Password" << endl;
                file.close();
                return;
            }
        }
    }
    file.close();
    if (!found) {
        cout << "Incorrect username" << endl;
    }
}

void Temp::newPass() {
    cout << "\nEnter your username: ";
    getline(cin, sName);
    cout << "Enter your email: ";
    getline(cin, sEmail);

    file.open("loginData.txt", ios::in);
    if (!file) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    bool found = false;
    while (getline(file, username, '*') && getline(file, email, '*') && getline(file, password)) {
        if (username == sName && email == sEmail) {
            found = true;
            cout << "Account Found" << endl;
            cout << "Username: " << username << endl;
            cout << "Password: " << password << endl;
            file.close();
            return;
        }
    }
    file.close();
    if (!found) {
        cout << "Username or Email not found" << endl;
    }
}
