#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include <string>
#include "HashMap.hpp"

class UserCommand
{
public:
    UserCommand();
    // the loop that the user will see on their interface 
    void user_loop();


private:
    // the hash map that the user will store their username/password
    HashMap hm; 
    // the command of the user
    std::string command; 
    // the username given by the user
    std::string username; 
    // the password given by the user
    std::string password;
    // the variable to keep track if debug is on/off
    bool debug;

    // create a username/password combination and stores it in the program's collection
    void create();
    // after checking if the username and password exist and are valid, it allows the user to log in
    void login();
    // removes the username/password if it is removable, otherwhise, it does not 
    void remove();
    // the debug commands when the debug is on
    void debug_commands();
    // the function gets the user input into one line 
    void get_input();
};



#endif