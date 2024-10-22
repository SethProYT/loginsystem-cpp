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
   std::cout << "Registering account.." << std::endl;

   json NewAccount;

   NewAccount["username"] = username;
   NewAccount["password"] = password; 
   
   // Check if users.json exists
   std::ofstream check("users.json", std::ios::app);

   if (std::filesystem::exists("users.json")) {
      std::cout << "Found users.json!" << std::endl;
      check << NewAccount.dump(4);
      std::cout << "Wrote to users.json instead of overwritting" << std::endl;
      return;
   }

   // New file!!!!
   std::ofstream json("users.json");

   json << NewAccount.dump(4);
}



