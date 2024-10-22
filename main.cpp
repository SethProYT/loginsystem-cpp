#include <iostream>
#include <string>
#include "headers.hpp"

int main() {
    std::cout << "Do you have an account? y/n: ";
    char answer;
    std::cin >> answer;
    
    std::string username;
    std::string password;

    switch(answer) {
        case 'n':
        case 'N':
            std::cout << "Hello I see you are new enter your username Let's register: ";
            std::cin >> username;
            std::cout << "Now give me your password: ";   
            std::cin >> password;
            RegisterAccount(username, password);
            break;
            
        case 'y':
        case 'Y':
            std::cout << "Username: ";
            std::cin >> username;
            std::cout << "Password: ";
            std::cin >> password;
            LoginAccount(username, password);
            break;
            
        default:
            std::cout << "ANSWER Y OR N!!!!" << std::endl;
            break;
    }
    return 0;
}
