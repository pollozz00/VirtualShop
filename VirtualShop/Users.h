#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
#include <iomanip>

#include "ASDList.h"
#include "fun_console.h"

using namespace std;

class Users {
public:
    ASD::List<Users> usersList;
    bool isEmployee = false;
    bool isClubMember = false;
    bool hasMadePurchase = false;
    bool loggedIn = false;
    int rank = 0;
    double highestPurchase = 0.0;

    string name;
    string surname;
    string username;
    string password;

public:
    Users() = default;

    string getName() { return name; }
    string getSurname() { return surname; }
    string getUsername() { return username; }
    string getPassword() { return password; }
    int getRank() { return rank; }
    bool getClubMember() { return isClubMember; }
    bool getEmployee() { return isEmployee; }
    bool getHasMadePurchase() { return hasMadePurchase; }
    void setHasMadePurchase(bool value) { hasMadePurchase = value; }
    bool isLoggedIn() { return loggedIn; }
    double getHighestPurchase() { return highestPurchase; }
    void setHighestPurchase(double value) { highestPurchase = value; }

    

    void initializeUsers() {
        Users adminUser;
        adminUser.name = "Admin";
        adminUser.surname = "Admin";
        adminUser.username = "admin";
        adminUser.password = "admin123";
        adminUser.isEmployee = true;
        adminUser.rank = 3;        
        usersList.AddHead(adminUser);

        Users defaultUser;
        defaultUser.name = "name";
        defaultUser.surname = "surname";
        defaultUser.username = "user";
        defaultUser.password = "user123";
        defaultUser.isEmployee = false;
        defaultUser.isClubMember = false;        
        usersList.AddHead(defaultUser);
    }

    void createNewAccount() {
        bool isNumber = false;
        bool size1 = false;
        bool size2 = false;
        bool space = false;

        isEmployee = false;

        int accountType = 0;
        bool errorShown = false;

        do {
            if (errorShown) {
                cout << "Error! Enter a value of 1 or 2." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "You want to create an account\n 1 - Employee\n 2 - Client\n";
            errorShown = true;
        } while (!(cin >> accountType) || (accountType != 1 && accountType != 2));

        cin.ignore();

        if (accountType == 1) {
            isEmployee = true;
        }

        do {
            cout << "Enter name: ";
            getline(cin, name);
            isNumber = containsDigits(name);
            size1 = tooMuchSymbols(name, 15);
            size2 = notEnoughSymbols(name, 3);
            if (isNumber) {
                cout << "The name must not contain a number" << endl;
            }
        } while (isNumber || size1 || size2);

        do {
            cout << "Enter surname: ";
            getline(cin, surname);
            isNumber = containsDigits(surname);
            size1 = tooMuchSymbols(surname, 20);
            size2 = notEnoughSymbols(surname, 4);
            if (isNumber) {
                cout << "The surname must not contain a number" << endl;
            }
        } while (isNumber || size1 || size2);

        do {
            cout << "Enter username: ";
            getline(cin, username);
            size1 = tooMuchSymbols(username, 20);
            size2 = notEnoughSymbols(username, 3);
            if (checkUsernameExists(username)) {
                cout << "Username already exists. Please choose another one." << endl;
            }
        } while (size1 || size2 || checkUsernameExists(username));

        do {
            cout << "Enter password: ";
            getline(cin, password);
            isNumber = containsDigits(password);
            size1 = tooMuchSymbols(password, 32);
            size2 = notEnoughSymbols(password, 6);
            space = containsSpaces(password);
            if (!isNumber) {
                cout << "Password must contain a number" << endl;
            }
        } while (size1 || size2 || space || !isNumber);

        if (isEmployee) {
            while (true) {
                cout << "What is your rank?\n 1 - Employee \n 2 - Manager\n 3 - Member of a management team" << endl;
                cin >> rank;
                if (rank >= 1 && rank <= 3) {
                    break;
                }
                else {
                    cout << "Error! Enter a value of 1, 2 or 3." << endl;
                    cin.clear();
                    cin.ignore();
                }
            }
        }

        int member = 0;
        if (!isEmployee) {
            while (true) {
                cout << "You are a member of the club?\n 1 - Yes \n 2 - No" << endl;
                cin >> member;
                if (member == 1) {
                    isClubMember = true;
                    break;
                }
                else if (member == 2) {
                    isClubMember = false;
                    break;
                }
                else {
                    cout << "Error! Enter a value of 1 or 2" << endl;
                    cin.clear();
                    cin.ignore();
                }
            }
        }

        Users newUser;
        newUser.name = name;
        newUser.surname = surname;
        newUser.username = username;
        newUser.password = password;
        newUser.isEmployee = isEmployee;
        newUser.rank = rank;
        newUser.isClubMember = isClubMember;
        newUser.hasMadePurchase = hasMadePurchase;
        usersList.AddHead(newUser);
    }

    bool containsDigits(string str) {
        for (unsigned char c : str) {
            if (isdigit(int(c))) { return true; }
        }
        return false;
    }

    bool tooMuchSymbols(string str, int s) {
        if (str.length() > s) {
            cout << "Must contain no more than " << s << " characters" << endl;
            return true;
        }
        return false;
    }

    bool notEnoughSymbols(string str, int s) {
        if (str.length() < s) {
            cout << "Must contain more than " << s << " characters" << endl;
            return true;
        }
        return false;
    }

    bool containsSpaces(string str) {
        for (char c : str) {
            if (c == ' ') {
                cout << "Must not contain spaces " << endl;
                return true;
            }
        }
        return false;
    }

    bool checkUsernameExists(std::string& username) {
        ASD::LISTPOSITION pos = usersList.GetHead();
        while (pos) {
            Users user = usersList.GetNext(pos);
            if (user.getUsername() == username) {
                return true;
            }
        }
        return false;
    }

    bool isEmployeeAccount() {
        return isEmployee;
    }

    bool isClientAccount() {
        return !isEmployee;
    }

    void loginToAccount() {
        /*
        int accountType;
        cout << "Login to an existing account\n 1 - Employee\n 2 - Client\n";
        cin >> accountType;
        cin.ignore();
        */

        
        int accountType;
        bool errorShown = false;
        do {
            if (errorShown) {
                cout << "Error! Enter a value of 1 or 2." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Login to an existing account\n 1 - Employee\n 2 - Client\n";
            errorShown = true;
        } while (!(cin >> accountType) || (accountType != 1 && accountType != 2));
        cin.ignore();
    

        string inputUsername, inputPassword;
        cout << "Enter your username: ";
        getline(cin, inputUsername);
        cout << "Enter your password: ";
        getline(cin, inputPassword);

        ASD::LISTPOSITION pos = usersList.GetHead();
        while (pos) {
            Users user = usersList.GetNext(pos);
            if (user.getUsername() == inputUsername && user.getPassword() == inputPassword) {
                loggedIn = true;
                isEmployee = user.isEmployee;
                name = user.name;
                surname = user.surname;
                username = user.username;
                password = user.password;
                rank = user.rank;
                isClubMember = user.isClubMember;
                hasMadePurchase = user.hasMadePurchase;
                return;
            }
        }

        cout << "Invalid username or password. Please try again." << endl;
        loggedIn = false;
    }

    void toStringAllClients() {
        ASD::LISTPOSITION pos = usersList.GetHead();
        int y = 2; 
        int xName = 12; 
        int xSurname = 37; 
        int xUsername = 62; 

        while (pos) {
            Users& user = usersList.GetNext(pos);

            GotoXY(xName, y);
            cout << "Name: " << user.name;

            GotoXY(xSurname, y);
            cout << "Surname: " << user.surname;

            GotoXY(xUsername, y);
            cout << "Username: " << user.username;

            y += 1;
        }
    }    

    void toStringClubMembers() {
        ASD::LISTPOSITION pos = usersList.GetHead();
        int y = 2; 
        int xName = 10; 
        int xSurname = 35; 
        int xUsername = 60; 

        while (pos) {
            Users& user = usersList.GetNext(pos);
            if (user.getClubMember()) {
                GotoXY(xName, y);
                cout << "Name: " << user.name;

                GotoXY(xSurname, y);
                cout << "Surname: " << user.surname;

                GotoXY(xUsername, y);
                cout << "Username: " << user.username;

                y += 1; 
            }
        }
    }

    void toStringClientsWithPurchases() {
        ASD::LISTPOSITION pos = usersList.GetHead();
        while (pos) {
            Users& user = usersList.GetNext(pos);
            if (user.getHasMadePurchase()) {
                cout << user.getName() << " " << user.getSurname() << " (" << user.getUsername() << ")" << endl;
            }
        }
    }

    Users* findClientWithHighestPurchase() {
        Users* highestSpender = nullptr;
        double highestAmount = 0.0;

        ASD::LISTPOSITION pos = usersList.GetHead();
        while (pos) {
            Users& user = usersList.GetNext(pos);
            if (user.getHasMadePurchase() && user.getHighestPurchase() > highestAmount) {
                highestAmount = user.getHighestPurchase();
                highestSpender = &user;
            }
        }

        return highestSpender;
    }


};