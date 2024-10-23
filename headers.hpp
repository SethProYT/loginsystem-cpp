#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

typedef nlohmann::json json;

void RegisterAccount(std::string username, std::string password, std::string special = ":3") {
    json NewAccount;
    NewAccount["username"] = username;
    NewAccount["password"] = password;
    NewAccount["special"] = special;
    
    if (std::filesystem::exists("users.json")) {

        std::ifstream read_file("users.json");
        json all_users = json::parse(read_file);
        read_file.close();
        
        all_users.push_back(NewAccount);
        
        std::ofstream write_file("users.json");
        write_file << all_users.dump(4);
        std::cout << "Account registered successfully!" << std::endl;

    } else {
        std::ofstream json("users.json");
        NewAccount["isAdmin"] = true;
        json << json::array({NewAccount}).dump(4);
        std::cout << "Created new users.json with first account!" << std::endl;
    }
}


std::string LoginAccount(std::string username, std::string password, std::string special) {
    if (std::filesystem::exists("users.json")) {
        std::ifstream database("users.json");
        json data = json::parse(database);
        
        for (const auto& user : data) {
            if (user["username"] == username) {
                if (user["password"] == password) {
                    if (user["special"] == special) {
                        if (user["isAdmin"] == true)  {
                            std::cout << "Admin tag found!" << std::endl;
                            return "admin";
                            break;
                        }
                        return "true";
                    } else {
                        return "false";
                    }
                } else {
                    return "false";
                }
            }
        }
        
        std::cout << "User not found. Please register" << std::endl;
        return "false";
    }
    
    std::cout << "No users.json file found!" << std::endl;
    return "false";
}


void Admin(std::string username, std::string password, std::string special) {
    std::ifstream databaseFile("users.json");
    if (!databaseFile.is_open()) {
        std::cerr << "Error opening database file." << std::endl;
        return;
    }

    json data = json::parse(databaseFile);
    databaseFile.close();
    std::cout << "Choose two options: 1. Get users 2. Set admin status for user 3. Set special phrase for user: ";
    char Ans;
    std::cin >> Ans;
    std::string targetUsername;
    bool userFound = false;
    int i = 0;

    switch (Ans) {
        case '3':
            std::cout << "Enter user to replace: ";
            std::cin >> targetUsername;
            for (auto &user : data) {
                if (user["username"] == targetUsername) {
                    std::cout << "Enter the new special phrase: ";
                    std::string newphrase;
                    std::cin >> newphrase;
                    user["special"] = newphrase;
                    userFound = true;
                    break;
                }
            }
            if (!userFound) {
                std::cout << "User not found." << std::endl;
            }
            break;
        case '1':
            for (auto &user : data) {
                i++;
                std::cout << "User " << i << ": " << user["username"] << " " << user["password"] << " " << user["special"] << std::endl;
            }
            break;
        case '2':
            std::cout << "Enter username: ";
            std::cin >> targetUsername;
            for (auto &user : data) {
                if (user["username"] == targetUsername) {
                    user["isAdmin"] = true;
                    break;
                }
            }
            break;
        default:
            std::cout << "Invalid option." << std::endl;
            break;
    }

    // Write the modified data back to the file
    std::ofstream outputFile("users.json");
    if (!outputFile.is_open()) {
        std::cerr << "Error writing to database file." << std::endl;
        return;
    }
    outputFile << data.dump(4);
    outputFile.close();
}



void AccountChanges(const std::string &username, const std::string& password, std::string secret, bool isAdmin = false) {
        std::ifstream databaseFile("users.json");
        if (!databaseFile.is_open()) {
            std::cerr << "Error opening database file." << std::endl;
            return;
        }

        json data = json::parse(databaseFile);
        databaseFile.close();

        if (isAdmin) {
            Admin(username, password, secret);
            return;
        }

        std::cout << "Change the secret: ";
        std::cin >> secret;

        for (auto &user : data) {
            if (user["username"] == username) {
                if (user["password"] == password) {
                    user["special"] = secret;
                }
            }

        std::cout << "Change the secret: ";
        std::cin >> secret;

        for (auto &user : data) {
            if (user["username"] == username) {
                if (user["password"] == password) {
                    user["special"] = secret;
                }
            }
        }

        std::ofstream outputFile("users.json");
        if (!outputFile.is_open()) {
            std::cerr << "Error writing to database file." << std::endl;
            return;
        }

        outputFile << data.dump(4);
        outputFile.close();
    }
}