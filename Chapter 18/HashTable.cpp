/** @file HashTable.cpp
 * Hashed implementation of ADT Dictionary
 */

#ifndef HashTable_cpp
#define HashTable_cpp

#include "./DictionaryInterface.hpp"
#include "../Components/HashedEntry.cpp"
#include <stdexcept>

static const int DEFAULT_SIZE = 101;

template<class KeyType, class ItemType>
class HashTable: public DictionaryInterface<KeyType, ItemType> {
private:
    HashedEntry<KeyType, ItemType>** hashTable;
    int itemCount;
    int hashTableSize;

    int getHashIndex(const KeyType& key) const;
public:
    HashTable();
    ~HashTable();
    
    bool isEmpty() const;
    int getNumberOfItems() const;
    bool add(const KeyType& newKey, const ItemType& newItem);
    bool remove(const KeyType& key);
    void clear();
    ItemType getItem(const KeyType& key) const;
    bool contains(const KeyType& key) const;
    void traverse(void visit(const ItemType &)) const;
};
#endif

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable() {
    hashTable = new HashedEntry<KeyType, ItemType>*[DEFAULT_SIZE]();
    itemCount = 0;
    hashTableSize = DEFAULT_SIZE;
}

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::~HashTable() {
    clear();
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::getNumberOfItems() const {
    return itemCount;
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::add(const KeyType& newKey, const ItemType& newItem) {
    HashedEntry<KeyType, ItemType>* newEntry = new HashedEntry<KeyType, ItemType>(newKey, newItem);
    int index = getHashIndex(newKey);

    if (hashTable[index] != nullptr) {
        HashedEntry<KeyType, ItemType>* existingEntry = hashTable[index];
        newEntry->setNext(existingEntry);
    }

    hashTable[index] = newEntry;

    itemCount++;
    return true;
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::remove(const KeyType& key) {
    if (isEmpty()) {
        throw std::logic_error("Attempting to remove from an empty map!");
    }

    int index = getHashIndex(key);
    HashedEntry<KeyType, ItemType>* currentEntry = hashTable[index];
    HashedEntry<KeyType, ItemType>* prev = nullptr;

    while (currentEntry != nullptr && currentEntry->getKey() != key) {
        prev = currentEntry;
        currentEntry = currentEntry->getNext();
    }

    if (currentEntry == nullptr) {
        return false;
    }

    if (prev == nullptr) {
        // head
        hashTable[index] = currentEntry->getNext();
    } else {
        prev->setNext(currentEntry->getNext());
    }

    delete currentEntry;
    currentEntry = nullptr;
    itemCount--;
    return true;
}

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::clear() {
    for (int i=0; i < hashTableSize; i++) {
        HashedEntry<KeyType, ItemType>* currentEntry = hashTable[i];
        while (currentEntry != nullptr) {
            HashedEntry<KeyType, ItemType>* entryToDelete = currentEntry;
            currentEntry = currentEntry->getNext();
            delete entryToDelete;
            entryToDelete = nullptr;
        }
    }

    delete[] hashTable;
    hashTable = nullptr;
    itemCount = 0;
    hashTableSize = 0;
}

template<class KeyType, class ItemType>
ItemType HashTable<KeyType, ItemType>::getItem(const KeyType& key) const{
    if (isEmpty()) {
        throw std::logic_error("Can not retrieve an item from the empty map!");
    }

    int index = getHashIndex(key);

    if (hashTable[index] == nullptr) {
        throw std::logic_error("There is no entry with the given key");
    }

    HashedEntry<KeyType, ItemType>* currentEntry = hashTable[index];
    while (currentEntry != nullptr && currentEntry->getKey() != key) {
        currentEntry = currentEntry->getNext();
    }
    if (currentEntry == nullptr) {
        throw std::logic_error("There is no entry with the given key");
    }
    return currentEntry->getItem();
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::contains(const KeyType& key) const {
    if (isEmpty()) {
        return false;
    }

    int index = getHashIndex(key);

    HashedEntry<KeyType, ItemType>* currentEntry = hashTable[index];
    while (currentEntry != nullptr && currentEntry->getKey() != key) {
        currentEntry = currentEntry->getNext();
    }

    return currentEntry != nullptr;
}

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::traverse(void visit (const ItemType&)) const{
    for (int i = 0; i < hashTableSize; i++) {
        HashedEntry<KeyType, ItemType>* currentEntry = hashTable[i];
        while (currentEntry != nullptr) {
            visit(currentEntry->getItem());
            currentEntry = currentEntry->getNext();
        }
}

}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::getHashIndex(const KeyType& key) const {
    std::hash<KeyType> hashFunction;
    return static_cast<int>(hashFunction(key) % hashTableSize);
}
