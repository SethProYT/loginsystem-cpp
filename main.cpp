#include <iostream>
#include <string>
#include "headers.hpp"

int main() {
   std::cout << "Hello I see you are new enter your username Let's register: ";
   std::string user;
   std::cin >> user;

   std::cout << "Now give me your password: ";   
   std::string pass;
   std::cin >> pass;


   RegisterAccount(user, pass);
}
