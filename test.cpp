#include "ExtensibleHashTable.h"
#include <iostream>

void testInsertAndPrint(ExtensibleHashTable& eht, int key) {
    std::cout << "Inserting key: " << key << std::endl;
    eht.insert(key);
    eht.print();
    std::cout << "-------------------------" << std::endl;
}

void testFind(ExtensibleHashTable& eht, int key) {
    bool found = eht.find(key);
    std::cout << "Finding key: " << key << " - " << (found ? "Found" : "Not Found") << std::endl;
}

void testRemoveAndPrint(ExtensibleHashTable& eht, int key) {
    bool removed = eht.remove(key);
    std::cout << "Removing key: " << key << " - " << (removed ? "Removed" : "Not Found") << std::endl;
    eht.print();
    std::cout << "-------------------------" << std::endl;
}

int main() {
    ExtensibleHashTable eht;

    // Test inserting keys
    testInsertAndPrint(eht, 10);
    testInsertAndPrint(eht, 22);
    testInsertAndPrint(eht, 31);
    testInsertAndPrint(eht, 4);
    testInsertAndPrint(eht, 15);
    testInsertAndPrint(eht, 28);
    testInsertAndPrint(eht, 17);
    testInsertAndPrint(eht, 18);

    // Test finding keys
    testFind(eht, 10);
    testFind(eht, 22);
    testFind(eht, 99); // This key does not exist

    // Test removing keys
    testRemoveAndPrint(eht, 22);
    testRemoveAndPrint(eht, 31);
    testRemoveAndPrint(eht, 99); // This key does not exist

    // Final state of the hash table
    std::cout << "Final state of the hash table:" << std::endl;
    eht.print();

    return 0;
}
