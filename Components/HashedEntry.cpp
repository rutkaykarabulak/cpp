/** @file HashedEntry.cpp
 * Hashed version of the @file Entry.cpp
 */

#ifndef HashedEntry_cpp
#define HashedEntry_cpp

#include "./MapEntry.cpp"

template<class KeyType, class ItemType>
class HashedEntry: public MapEntry<KeyType, ItemType> {
private:
    HashedEntry<KeyType, ItemType>* next;
public:
    HashedEntry();
    HashedEntry(KeyType key, ItemType item);
    HashedEntry(KeyType key, ItemType item, HashedEntry<KeyType, ItemType>* nextPtr);
    void setNext(HashedEntry<KeyType, ItemType>* next);
    HashedEntry<KeyType, ItemType>* getNext() const;
};

#endif

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry() 
    : MapEntry<KeyType, ItemType>(), next(nullptr) {}


template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(KeyType key, ItemType item)
    : MapEntry<KeyType, ItemType>(key, item), next(nullptr) {}

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(KeyType key, ItemType item, HashedEntry<KeyType, ItemType>* nextPtr)
    : MapEntry<KeyType, ItemType>(key, item), next(nextPtr) {}


template<class KeyType, class ItemType>
void HashedEntry<KeyType, ItemType>::setNext(HashedEntry<KeyType,ItemType>* next) {
    this->next = next;
}

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>* HashedEntry<KeyType, ItemType>::getNext() const{
    return next;
}