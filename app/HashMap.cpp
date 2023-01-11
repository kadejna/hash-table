#include "HashMap.hpp"
#include "DefaultHash.hpp"

// default constructor
HashMap::HashMap()
    :hashFunction{default_hash}, hashTable{new Node* [HashMap::INITIAL_BUCKET_COUNT]()},
        sz{0}, capacity{HashMap::INITIAL_BUCKET_COUNT}
{
}

// constructor given a hash function
HashMap::HashMap(HashFunction hashFunction)
    :hashFunction{hashFunction}, hashTable{new Node* [HashMap::INITIAL_BUCKET_COUNT]()},
        sz{0}, capacity{HashMap::INITIAL_BUCKET_COUNT}
{
}

// copy constructor
HashMap::HashMap(const HashMap& hm)
    :hashFunction{hm.hashFunction}, hashTable{new Node* [hm.capacity]},
        sz{hm.sz}, capacity{hm.capacity}
{   
    // copies the elements of the hashmap to the hm hashmap
    for (unsigned int i = 0; i < capacity; i++)
    {
        // current is a pointer to the first node in the bucket of hm's array/hashtable
        Node* current = hm.hashTable[i];
        // "before" points to an address of hash table indexed at i -> bucket
        Node** before = hashTable + i;
        *before = nullptr;
        while (current != nullptr)
        {
            // this is the node created with hm's first key/value in the bucket 
            Node* dynamicNode = new Node{current->key, current->value, nullptr};
            // original hash table points to the node created above from hm 
            *before = dynamicNode; 
            // this pointer points to the next element of the hm's first key/value in the bucket
            before = &dynamicNode->next; 
            // update to proceed with the next elements 
            current = current->next; 
        }
    }
}

// destructor
HashMap::~HashMap()
{
    for (unsigned int i = 0; i < capacity; i++)
    {
        Node* current = hashTable[i];
        while (current != nullptr)
        {
            Node* before = current; 
            current = current->next; 
            // delete every key/element
            delete before; 
        }
    }
    // delete the hash table array
    delete[] hashTable;
}

// copy assignment 
HashMap& HashMap::operator=(const HashMap& hm)
{
    // copy to another assignment if the HashMaps are not eqaul to each other
    // this = pointer to the HashMap that I am assigning into
    if (this != &hm)
    {
        // create a new hash table with hm's capacity
        Node** dynamicTable = new Node* [hm.capacity]; 
         // copies the elements of the hashmap to the hm hashmap
         // for every bucket, 
        for (unsigned int i = 0; i < hm.capacity; i++)
        {
            Node* current = hm.hashTable[i];
            // "before" points to an address of hash table indexed at i
            Node** before = dynamicTable + i;
            *before = nullptr;
            while (current != nullptr)
            {
                Node* dynamicNode = new Node{current->key, current->value, nullptr};
                *before = dynamicNode; 
                before = &dynamicNode->next; 
                current = current->next; 
            }
        }
        
        // remaining private variables are "copy assigned" to hm's private variables 
        hashFunction = hm.hashFunction; 
        sz = hm.sz; 
        capacity = hm.capacity; 
        delete[] hashTable; 
        // the hashtable is the table from hm 
        hashTable = dynamicTable;
    }

    return *this; 
}

// checks if the key is contained in an according bucket 
bool HashMap::contains(const std::string& key) const
{   
    // the hash value of a string (the bucket number)
    unsigned int hash = hashFunction(key) % capacity; 
    // the array/table with hash value as a number (the bucket number within that table)
    Node* current = hashTable[hash]; 
    while (current != NULL)
    {   
        // if, within that bucket, we find a key/value pair,
        if (current->key == key)
        {
            return true; 
        }
        // proceed if not found
        current = current->next; 
    }
    // the key/value are not found in the hash map 
    return false; 
}

// all key/value pairs are reHashed to new buckets when the load factor reaches its limit 
void HashMap::reHash()
{
    // previous capacity of the hash map
    int previous = capacity; 
    // the number of buckets/capacity is increased by this formula below
    capacity = previous * 2 + 1;
    // the new hashTable / array is built with the increased capacity 
    Node** table = new Node* [capacity]();

    // for every linkedlist in the previous capacity of the array
    for (unsigned int i = 0; i < previous; i++)
    {
        // for each linkedlist / bucket 
        Node* current = hashTable[i]; 
        // rehash all the key/value
        while (current != nullptr)
        {
            // store the linkedlist to "before"
            Node* before = current; 
            // proceed 
            current = current->next; 
            // same as hashTable[hash], but with the new hashTable
            Node*& bucket = table[hashFunction(before->key) % capacity];
            // changes the bucket of the key/value
            before->next = bucket; 
            bucket = before; 
        }
    }
    delete[] hashTable; 
    // simply update the hash table / array
    hashTable = table; 
}

// this function adds the key, if it does not exist
// in addition, if the load factor is >= 0.8, reHash occurs
void HashMap::add(const std::string& key, const std::string& value)
{
    // if the key is not stored in the HashMap
    if (not contains(key))
    {
        // "hash" is the bucket number of the array hashTable
        unsigned int hash = hashFunction(key) % capacity; 
        // "current" is the pointer to the first node(stores key/value) of the bucket, meaning that 
        // in the hashTable array, indexing the "hash" number will retrieve the according pointer to the bucket 
        Node* current = hashTable[hash];
        Node* before = nullptr;

        while (current != nullptr)
        {
            // store the current node to before
            before = current; 
            // proceed to the next node(key/value) 
            current = current->next; 
        }

        // when the pointer to the node reaches the end of the linked list / bucket
        if (current == nullptr)
        {
            // add the new key/value to that bucket
            current = new Node{key, value}; 
            if (before == nullptr)
            {
                // this adds to the array / hash table 
                hashTable[hash] = current; 
                // size of the hashmap is increased
                sz++;
            }
            else
            {
                // "before"'s next points to that new key/value
                before->next = current; 
                sz++;
            }
        }
    }
    // if the load factor reaches and surpasses 0.8
    if (loadFactor() >= 0.8)
    {
        // all key/value are rehashed into new buckets 
        reHash();
    }
}

// this function returns true if it the key is contained and removed after
// otherwise, it returns false becuase the key cannot be removed 
bool HashMap::remove(const std::string& key)
{   
    // if the key is already present in the hash map 
    if (contains(key))
    {
        unsigned int hash = hashFunction(key) % capacity; 
        Node* before = nullptr; 
        Node* current = hashTable[hash];

        while (current != nullptr && current->key != key)
        {
            before = current; 
            current = current->next;
        }

        if (current == nullptr)
        {   
            // nothing is changed 
            return false;
        }
        else
        {
            if (before == nullptr)
            {
                hashTable[hash] = current->next; 
                sz--;
            }
            else
            {
                before->next = current->next; 
                sz--; 
            }
            // delete the pointer
            delete current; 
            // a key is removed
            return true; 
        }
    }
    // if the element isn't already present, the function returns false
    return false; 
}

// this function returns the according value given a key
std::string HashMap::value(const std::string& key) const
{
    if (contains(key))
    {
        unsigned int hash = hashFunction(key) % capacity; 
        Node* current = hashTable[hash]; 
        while (current->key != key)
        {
            current = current->next; 
        }
        // breaks out of the while loop if current-> key == key
        // returns the value of that key
        return current->value; 
    }
    else
    {
        return "";
    }
}

// this function returns the size of the hash map, meaning how many buckets are filled with key/value
unsigned int HashMap::size() const 
{
    return sz; 
}

// this function returns the number of buckets of hash map available, meaning how many buckets are stored
unsigned int HashMap::bucketCount() const
{
    return capacity; 
}

// this function returns the load factor, which is size / capacity of the hash map
double HashMap::loadFactor() const
{
    return sz / double(capacity); 
}

// this function returns maximum bucket with most key/value pairs stored 
unsigned int HashMap::maxBucketSize() const
{
    unsigned int maximum = 0; 
    for (unsigned int i = 0; i < capacity; i++)
    {
        // determines how many key/value pairs are in a bucket/linked list
        int length = 0; 
        // a pointer to the first node of the bucket 
        Node* current = hashTable[i];
        while (current != nullptr)
        {
            // each key/value pair 
            length++;
            // proceed
            current = current->next; 
        }
        // maximum algorithm
        if (length > maximum)
        {
            maximum = length;
        }
    }
    return maximum; 
}

// this function clears the hash table and its buckets
void HashMap::clear()
{
    for (unsigned int i = 0; i < capacity; i++)
    {
        Node* current = hashTable[i];
        while (current != nullptr)
        {
            Node* before = current; 
            current = current->next;
            // deletes the pointer pointing to key/value pairs 
            delete before; 
        }
        hashTable[i] = nullptr; 
    }
    // size is back to 0 after all key/value pairs in buckets are removed
    sz = 0; 
}