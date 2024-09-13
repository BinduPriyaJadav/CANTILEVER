//PROJECT2-SIMPLE SOCIAL NETWORK
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> // Include this header to use istringstream
#include <algorithm>

using namespace std;

// User class representing a user profile in the social network
class User {
private:
    string username;
    int age;
    vector<string> friends;
    vector<string> messages;

public:
    // Constructor to initialize the user profile
    User(const string& name, int userAge)
        : username(name), age(userAge) {}

    // Getters
    string getUsername() const { return username; }
    int getAge() const { return age; }
    vector<string> getFriends() const { return friends; }
    vector<string> getMessages() const { return messages; }

    // Function to add a friend to the user's friend list
    void addFriend(const string& friendName) {
        if (find(friends.begin(), friends.end(), friendName) == friends.end()) {
            friends.push_back(friendName);
            cout << friendName << " added to your friends list.\n";
        } else {
            cout << friendName << " is already in your friends list.\n";
        }
    }

    // Function to post a message
    void postMessage(const string& message) {
        messages.push_back(message);
        cout << "Message posted.\n";
    }

    // Function to display user profile information
    void displayProfile() const {
        cout << "Username: " << username << "\nAge: " << age << "\nFriends: ";
        for (const auto& friendName : friends) {
            cout << friendName << " ";
        }
        cout << "\nMessages:\n";
        for (const auto& msg : messages) {
            cout << "- " << msg << "\n";
        }
        cout << "----------------------------\n";
    }

    // Function to save the user profile to a file
    void saveToFile() const {
        ofstream outFile("users.txt", ios::app);
        if (outFile.is_open()) {
            outFile << username << "," << age << "\n";
            for (const auto& friendName : friends) {
                outFile << friendName << ",";
            }
            outFile << "\n";
            for (const auto& msg : messages) {
                outFile << msg << "\n";
            }
            outFile.close();
            cout << "Profile saved.\n";
        } else {
            cout << "Error saving profile.\n";
        }
    }
};

// Function to load users from the file
void loadUsers(vector<User>& users) {
    ifstream inFile("users.txt");
    string line;

    while (getline(inFile, line)) {
        // Extract username and age
        string username;
        int age;
        istringstream ss(line);  // String stream to parse the line
        getline(ss, username, ',');
        ss >> age;

        // Create a new user with the extracted data
        User user(username, age);

        // Load friends from the next line
        if (getline(inFile, line)) {
            istringstream ssFriends(line);  // String stream to parse friends
            string friendName;
            while (getline(ssFriends, friendName, ',')) {
                if (!friendName.empty()) {  // Check to avoid adding empty friends
                    user.addFriend(friendName);
                }
            }
        }

        // Load messages from subsequent lines until an empty line is found
        while (getline(inFile, line) && !line.empty()) {
            user.postMessage(line);
        }

        // Add the fully loaded user to the users vector
        users.push_back(user);
    }

    inFile.close();
    cout << "Users loaded successfully.\n";
}

// Main function to run the social network application
int main() {
    vector<User> users;
    int choice;

    // Load existing users from file
    loadUsers(users);

    do {
        cout << "1. Create Profile\n2. Add Friend\n3. Post Message\n4. View Profile\n5. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int age;
            cout << "Enter username: ";
            cin >> name;
            cout << "Enter age: ";
            cin >> age;
            users.emplace_back(name, age);
            cout << "Profile created successfully.\n";
        } else if (choice == 2 && !users.empty()) {
            string friendName;
            cout << "Enter friend's username: ";
            cin >> friendName;
            users[0].addFriend(friendName); // Assuming the first user for simplicity
        } else if (choice == 3 && !users.empty()) {
            string message;
            cout << "Enter your message: ";
            cin.ignore();
            getline(cin, message);
            users[0].postMessage(message);
        } else if (choice == 4 && !users.empty()) {
            users[0].displayProfile(); // Assuming the first user for simplicity
        } else if (choice != 5) {
            cout << "Invalid option or no profiles available.\n";
        }
    } while (choice != 5);

    // Save all users to the file when exiting
    for (const auto& user : users) {
        user.saveToFile();
    }

    return 0;
}
