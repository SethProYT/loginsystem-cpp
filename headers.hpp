#pragma once

#include <iostream>
#include <string>
// We will use this later #include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

typedef nlohmann::json json;

// Register function (haha im adding comments to look like ChatGPT that's what you're thinking aren't you?)
void RegisterAccount(std::string username, std::string password) {
    json NewAccount;
    NewAccount["username"] = username;
    NewAccount["password"] = password;
    
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
        json << json::array({NewAccount}).dump(4);
        std::cout << "Created new users.json with first account!" << std::endl;
    }
}


bool LoginAccount(std::string username, std::string password) {
    if (std::filesystem::exists("users.json")) {
        std::ifstream database("users.json");
        json data = json::parse(database);
        
        for (const auto& user : data) {
            if (user["username"] == username) {
                if (user["password"] == password) {
                    std::cout << "Correct password and username" << std::endl;
                    return true;
                } else {
                    std::cout << "Correct user, but wrong password" << std::endl;
                    return false;
                }
            }
        }
        
        std::cout << "User not found. Please register" << std::endl;
        return false;
    }
    
    std::cout << "No users.json file found!" << std::endl;
    return false;
}
