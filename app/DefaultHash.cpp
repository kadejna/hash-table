#include "DefaultHash.hpp"

// the non-static member function to the class HashMap, default_hash, is a function that
// a HashMap class constructor with no arguments take 
unsigned int default_hash(const std::string& key)
{
    unsigned int hash = 0; 
    for (unsigned int i = 0; i < key.length(); i++)
    {
        // for each character of a string, we add to the current hash value * a prime number 
        hash = hash * 31 + key[i];
    }
    return hash;
}