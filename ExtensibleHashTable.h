#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

#include <vector>
#include "Bucket.h"
#include <stdexcept>
#include <iostream>

class ExtensibleHashTable {
public:
    //default constructor
    ExtensibleHashTable();
    //constructor for custom buckets
    ExtensibleHashTable(int bucketSize);
    //destructor
    ~ExtensibleHashTable();
    //copy constructor
    ExtensibleHashTable(const ExtensibleHashTable& other);
    ExtensibleHashTable& operator=(const ExtensibleHashTable& other);

    bool find(int key);
    void insert(int key);
    bool remove(int key);
    void print();

private:
    std::vector<Bucket*> directory;//STL vector of pointers to Buckets
    int bucketSize;
    int globalDepth;

    int hash(int key);
    void splitBucket(int index);
    void doubleDirectory();
    void copyFrom(const ExtensibleHashTable& other);
    void clear();
};

#endif // EXTENSIBLEHASHTABLE_H
