#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Simple hash function to encrypt passwords
string hashPassword(const string& password) {
    // Use a simple hashing method (in practice, use a strong hash like SHA-256)
    stringstream ss;
    for (char c : password) {
        // Convert each character to its ASCII value and add a fixed value (e.g., 5)
        ss << hex << (int(c) + 5);
    }
    return ss.str();
}

// Function to register a new user
void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    // Check if the username already exists
    ifstream checkFile(username + ".txt");
    if (checkFile) {
        cout << "Username already taken. Please try another.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Hash the password before storing it
    string hashedPassword = hashPassword(password);

    // Create a file for the new user and store the hashed password
    ofstream userFile(username + ".txt");
    if (userFile.is_open()) {
        userFile << username << endl;
        userFile << hashedPassword << endl;
        userFile.close();
        cout << "Registration successful!\n";
    } else {
        cout << "Error creating user file. Please try again.\n";
    }
}

// Function to log in an existing user
void loginUser() {
    string username, password, storedUser, storedPass;
    cout << "Enter username: ";
    cin >> username;

    // Open the user's file
    ifstream userFile(username + ".txt");
    if (!userFile) {
        cout << "User does not exist. Please register first.\n";
        return;
    }

    // Read stored username and hashed password
    getline(userFile, storedUser);
    getline(userFile, storedPass);
    userFile.close();

    cout << "Enter password: ";
    cin >> password;

    // Hash the entered password to compare with the stored hashed password
    string hashedPassword = hashPassword(password);

    // Check if the entered credentials match the stored ones
    if (storedUser == username && storedPass == hashedPassword) {
        cout << "Login successful! Welcome " << username << "!\n";
    } else {
        cout << "Invalid credentials. Please try again.\n";
    }
}

// Main function with a looped menu
int main() {
    int choice;
    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice! Please select 1, 2, or 3.\n";
        }
    }

    return 0;
}
