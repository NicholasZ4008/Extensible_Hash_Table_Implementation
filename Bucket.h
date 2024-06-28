#ifndef BUCKET_H
#define BUCKET_H

#include <vector>
#include <iostream>

class Bucket {
public:
    Bucket(int size, int depth);
    Bucket(const Bucket& other);
    Bucket& operator=(const Bucket& other);

    bool insert(int key);
    bool remove(int key);
    bool find(int key);
    void print();
    void clear();
    std::vector<int> getKeys() const;
    int setLocalDepth(int depth);
    int getLocalDepth() const;

private:
    std::vector<int> keys;
    int maxSize;
    int localDepth;
};

#endif // BUCKET_H
