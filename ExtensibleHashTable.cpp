#include "ExtensibleHashTable.h"
#include <iostream>

//(Public) Constructor: Initializes with default bucket size 4
ExtensibleHashTable::ExtensibleHashTable() : bucketSize(4), globalDepth(1) {
    directory.resize(2);
    directory[0] = new Bucket(bucketSize, 1);
    directory[1] = new Bucket(bucketSize, 1);
}

//(Public) Constructor: Initializes with custom bucket size
ExtensibleHashTable::ExtensibleHashTable(int bucketSize) : bucketSize(bucketSize), globalDepth(1) {
    directory.resize(2);
    directory[0] = new Bucket(bucketSize, 1);
    directory[1] = new Bucket(bucketSize, 1);
}

//(Public) Destructor: Clears resources
ExtensibleHashTable::~ExtensibleHashTable() {
    clear();
}

//(Private) Copy constructor: Copies another hash table
ExtensibleHashTable::ExtensibleHashTable(const ExtensibleHashTable& other) {
    copyFrom(other);
}

//Overloaded Assignment operator: Assigns another hash table for overloaded asignments
ExtensibleHashTable& ExtensibleHashTable::operator=(const ExtensibleHashTable& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

//Find: Using hash function value, goes to target bucket and finds key
bool ExtensibleHashTable::find(int key) {
    int index = hash(key);
    return directory[index]->find(key);
}

//Insert: checks if bucket is full or not. If full, split the bucket, double the directory and retry insertion
void ExtensibleHashTable::insert(int key) {
    int index = hash(key);
    if (!directory[index]->insert(key)) {//returns false on individual buckets being full
        //continues on full bucket
        if (directory[index]->getLocalDepth() == globalDepth) {
            doubleDirectory();
        }
        splitBucket(index);
        insert(key); //Retry insertion after splitting
    }
}


//Helper function to double the directory
void ExtensibleHashTable::doubleDirectory() {
    size_t oldSize = directory.size(); //save the current size of the directory
    directory.resize(oldSize * 2); //Double the size of the directory

    //Copy existing entries to the new positions
    for (size_t i = 0; i < oldSize; ++i) {
        directory[oldSize + i] = directory[i];
    }
    ++globalDepth;
}

//split bucket function
void ExtensibleHashTable::splitBucket(int index) {
    int localDepth = directory[index]->getLocalDepth();
    int newLocalDepth = localDepth + 1;

    //Create a new bucket with the increased local depth
    Bucket* newBucket = new Bucket(bucketSize, newLocalDepth);
    directory[index]->setLocalDepth(newLocalDepth);

    //Update the directory entries
    size_t mask = (1 << localDepth);
    for (size_t i = 0; i < directory.size(); ++i) {
        if ((i & (mask - 1)) == (index & (mask - 1))) {
            if (i & mask) {
                directory[i] = newBucket;
            }
        }
    }

    //Redistribute keys
    std::vector<int> keys = directory[index]->getKeys();
    directory[index]->clear();
    for (int key : keys) {
        int hashedKey = hash(key);
        if ((hashedKey & mask) != 0) {
            newBucket->insert(key);
        } else {
            directory[index]->insert(key);
        }
    }
}


//Helper keys remove function
bool ExtensibleHashTable::remove(int key) {
    int index = hash(key);
    return directory[index]->remove(key);
}

//print 
void ExtensibleHashTable::print() {
    std::vector<Bucket*> printedBuckets; // Vector to track printed buckets

    for (size_t i = 0; i < directory.size(); ++i) {
        std::cout << i << ": " << directory[i] << " --> ";
        
        // Check if the current bucket has already been printed
        if (std::find(printedBuckets.begin(), printedBuckets.end(), directory[i]) == printedBuckets.end()) {
            directory[i]->print();
            printedBuckets.push_back(directory[i]);
        } else {
            std::cout << std::endl;
        }
    }
}


//Hash function: Computes the array index of the hash value
int ExtensibleHashTable::hash(int key) {
    return key & ((1 << globalDepth) - 1);
}

//Helper function to copy from another hash table
void ExtensibleHashTable::copyFrom(const ExtensibleHashTable& other) {
    bucketSize = other.bucketSize;
    globalDepth = other.globalDepth;
    directory.resize(other.directory.size());
    for (size_t i = 0; i < other.directory.size(); ++i) {
        directory[i] = new Bucket(*other.directory[i]);
    }
}

//Helper clear function
void ExtensibleHashTable::clear() {
    std::vector<Bucket*> alreadyDeletedBuckets; // Vector to track unique bucket deletions

    for (auto bucket : directory) {
        // Check if the current bucket has already been deleted
        if (std::find(alreadyDeletedBuckets.begin(), alreadyDeletedBuckets.end(), bucket) == alreadyDeletedBuckets.end()) {
            delete bucket;
            alreadyDeletedBuckets.push_back(bucket);
        }
    }
    directory.clear();
}
