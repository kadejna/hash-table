#include <string> 
#include <sstream>
#include <iostream>
#include "UserCommand.hpp"

UserCommand::UserCommand()
    :debug{false}
{
}

void UserCommand::user_loop()
{
    while (command != "QUIT")
    {
        // asks the user for input 
        get_input();

        // creates username/password
        if (command == "CREATE" && username != "" && password != "")
        {
            create();
        }
        // logs in the user 
        else if (command == "LOGIN" && username != "" && password != "")
        {
            login();
        }
        // removes the username/password
        else if (command == "REMOVE" && username != "")
        {
            remove();
        }
        // clears all 
        else if (command == "CLEAR" && username == "" && password == "")
        {
            hm.clear();
            std::cout << "CLEARED" << std::endl; 
        }
        // quits the program
        else if (command == "QUIT")
        {
            std::cout << "GOODBYE" << std::endl;
            break;
        }
        // debugging is on for the programmer
        else if (command == "DEBUG" && username == "ON" && password == "")
        {   
            // if the debug is already on 
            if (debug)
            {
                std::cout << "ON ALREADY" << std::endl; 
            }
            // if the debug is not on 
            else
            {
                debug = true; 
                std::cout << "ON NOW" << std::endl; 
            }
        }
        // debugging is off
        else if (command == "DEBUG" && username == "OFF" && password == "")
        {
            // if debug is on 
            if (debug)
            {
                debug = false; 
                std::cout << "OFF NOW" << std::endl; 
            }
            // if debug is off
            else 
            {
                std::cout << "OFF ALREADY" << std::endl;
            }   
        }
        else if (debug)
        {
            debug_commands();
        }
        else
        {
            std::cout << "INVALID" << std::endl;
        }
    }
}

void UserCommand::create()
{
    // if the username is already in the collection
    if (hm.contains(username))
    {
        std::cout << "EXISTS" << std::endl; 
    }
    // if the username is not in the collection
    else
    {
        // creates a new password
        hm.add(username, password);
        std::cout << "CREATED" << std::endl; 
    }
}

void UserCommand::login()
{
    // if the username is in the collection and the value matches the password
    if (hm.contains(username) && hm.value(username) == password)
    {
        std::cout << "SUCCEEDED" << std::endl;
    }
    // if the username is not in the collection or the value does not match the password
    else
    {
        std::cout << "FAILED" << std::endl; 
    }
}

void UserCommand::remove()
{
    // if the username is removable 
    if (hm.remove(username))
    {
        std::cout << "REMOVED" << std::endl; 
    }
    // if the username is not removable 
    else
    {
        std::cout << "NONEXISTENT" << std::endl; 
    }
}


void UserCommand::debug_commands()
{   
    // the number of username/password combinations currently stored
    if (command == "LOGIN" && username == "COUNT" && password == "")
    {
        std::cout << hm.size() << std::endl; 
    }
    // the number of buckets in the hash table 
    else if (command == "BUCKET" && username == "COUNT" && password == "")
    {
        std::cout << hm.bucketCount() << std::endl; 
    }
    // the load factor of the hash table 
    else if (command == "LOAD" && username == "FACTOR" && password == "")
    {
        std::cout << hm.loadFactor() << std::endl; 
    }
    // the length of the largest bucket 
    else if (command == "MAX" && username == "BUCKET" && password == "SIZE")
    {
        std::cout << hm.maxBucketSize() << std::endl; 
    }
    else 
    {
        std::cout << "INVALID" << std::endl;
    }
}

void UserCommand::get_input()
{
    std::string line; 

    // gets the line of input
    std::getline(std::cin, line);
    
    command = "";
    username = "";
    password = "";

    std::istringstream split(line);
    // splits the line into command, username, and password
    split >> command >> username >> password;
}
