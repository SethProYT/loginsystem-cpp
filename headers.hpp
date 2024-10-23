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
                            std::cout << "Admin Tag Found!" << std::endl;
                            return "admin";
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


void AccountChanges(const std::string &username, const std::string& password, std::string secret, bool isAdmin = false) {
    std::ifstream databaseFile("users.json");
    if (!databaseFile.is_open()) {
        std::cerr << "Error opening database file." << std::endl;
        return;
    }

    json data = json::parse(databaseFile);
    databaseFile.close();

    if (isAdmin) {
        std::cout << "You may change the special phrase of any user." << std::endl;
        std::cout << "Enter the username of the user you want to change: ";
        std::string targetUsername;
        std::cin >> targetUsername;

        for (auto &user : data) {
            if (user["username"] == targetUsername) {
                std::cout << "Enter the new special phrase: ";
                std::string newphrase;
                std::cin >> newphrase;
                user["special"] = newphrase;
                return;
            } else {
                std::cout << "User not found." << std::endl;
                return;
            }
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
