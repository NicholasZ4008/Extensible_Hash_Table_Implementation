#include "Bucket.h"

Bucket::Bucket(int size, int depth) : maxSize(size), localDepth(depth) {}

//copy operator
Bucket::Bucket(const Bucket& other) {
    keys = other.keys;
    maxSize = other.maxSize;
    localDepth = other.localDepth;
}

//copy assignment operator
Bucket& Bucket::operator=(const Bucket& other) {
    if (this != &other) {
        keys = other.keys;
        maxSize = other.maxSize;
        localDepth = other.localDepth;
    }
    return *this;
}

//First checks if there is space available in the bucket. Returns true if insertion successful, false on failure
bool Bucket::insert(int key) {
    if (keys.size() < maxSize) {
        keys.push_back(key);//inserts key into the back of the bucket with push_back
        return true;
    }
    return false;
}

//Helper remove function
bool Bucket::remove(int key) {
    bool removed = false;
    for (auto it = keys.begin(); it != keys.end(); ) {
        if (*it == key) {
            it = keys.erase(it);
            removed = true;
        } else {
            ++it;
        }
    }
    return removed;
}

//linearly traverse bucket to find key
bool Bucket::find(int key) {
    for (int i : keys) {
        if (i == key) {
            return true;
        }
    }
    return false;
}

//helper print function
void Bucket::print() {
    std::cout << "[";
    //print keys
    for (size_t i = 0; i < keys.size(); ++i) {
        std::cout << keys[i];
        if (i != keys.size() - 1) {
            std::cout << ",";
        }
    }
    for (size_t i = keys.size(); i < maxSize; ++i) {
        std::cout << ",-";
    }
    //finish bracket and print the local depth val
    std::cout << "] (" << localDepth << ")" << std::endl;
}

//clears the Bucket
void Bucket::clear() {
    keys.clear();
}

//helper function that just returns keys so it can be used in the other .cpp file
std::vector<int> Bucket::getKeys() const {
    return keys;
}

//helper function that just returns the localDepth so it can be used in the other .cpp file
int Bucket::getLocalDepth() const {
    return localDepth;
}

//helper function used to set the desired depth as the new localDepth
int Bucket::setLocalDepth(int depth){
    localDepth = depth;
    return localDepth;
}
