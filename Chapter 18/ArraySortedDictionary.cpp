/** @file ArraySortedDictionary.cpp
 * Array based (sorted) implementation of ADT Dictinary.
 */

#ifndef ArraySortedDictionary_cpp
#define ArraySortedDictionary_cpp
#define throw(...)

#include "./DictionaryInterface.hpp"
#include "../Components/MapEntry.cpp"


const int MAX_SIZE = 10;

template<class KeyType, class ItemType>
class ArraySortedDictionary: public DictionaryInterface<KeyType, ItemType> {
private:
    MapEntry<KeyType, ItemType>* items;
    int itemCount;
    int maxSize;

    int findEntryIndex(const KeyType& key) const;
    int binarySearch(int first, int last, MapEntry<KeyType, ItemType>* items, const KeyType& target) const;
public:
    ArraySortedDictionary();
    ~ArraySortedDictionary();
    bool isEmpty() const;
    int getNumberOfItems() const;
    bool add(const KeyType& newKey, const ItemType& newItem);
    bool remove(const KeyType& key);
    void clear();
    ItemType getItem(const KeyType& key) const throw(NotFoundException);
    bool contains(const KeyType& key) const;
    void traverse(void visit(const ItemType &)) const;

};
#endif

template<class KeyType, class ItemType>
ArraySortedDictionary<KeyType, ItemType>::ArraySortedDictionary() {
    items = new MapEntry<KeyType, ItemType>[MAX_SIZE];
    itemCount = 0;
    maxSize = MAX_SIZE;
}

template<class KeyType, class ItemType>
ArraySortedDictionary<KeyType, ItemType>::~ArraySortedDictionary() {
    clear();
}

template<class KeyType, class ItemType>
void ArraySortedDictionary<KeyType, ItemType>::clear() {
    delete[] items;
    items = nullptr;
    itemCount = 0;
}

template<class KeyType, class ItemType>
bool ArraySortedDictionary<KeyType, ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class KeyType, class ItemType>
int ArraySortedDictionary<KeyType, ItemType>::getNumberOfItems() const {
    return itemCount;
}

template<class KeyType, class ItemType>
bool ArraySortedDictionary<KeyType, ItemType>::add(const KeyType& newKey, const ItemType& newItem) {
    if (itemCount == maxSize) {
        maxSize *= 2;
        MapEntry<KeyType, ItemType>* newItems = new MapEntry<KeyType, ItemType>[maxSize];
        for (int i=0; i < itemCount; i++)
            newItems[i] = items[i];
        delete[] items;
        items = newItems;
        newItems = nullptr;
    }

    int index = itemCount;
    while (index > 0 && newKey < items[index - 1].getKey()) {
        items[index] = items[index-1];
        index--;
    }
    items[index] = MapEntry<KeyType, ItemType>(newKey, newItem);
    itemCount++;
    return true;
}

template<class KeyType, class ItemType>
int ArraySortedDictionary<KeyType, ItemType>::findEntryIndex(const KeyType& key) const {
    for (int i=0; i < itemCount; i++) {
        if (items[i].getKey() == key)
            return i;
    }

    return -1;
}

template<class KeyType, class ItemType>
bool ArraySortedDictionary<KeyType, ItemType>::remove(const KeyType& key) {
    int index = findEntryIndex(key);

    if (isEmpty() || index == -1) return false;

    for (int i=index; i < itemCount - 1; i++) {
        items[i] = items[i+1];
    }

    itemCount--;
    return true;
}

template<class KeyType, class ItemType>
ItemType ArraySortedDictionary<KeyType, ItemType>::getItem(const KeyType& key) const throw(NotFoundException){
    if (isEmpty()) {
        throw std::logic_error("Can not retrieve an item from the empty map!");
    };
    // apply binary search
    int index = binarySearch(0, itemCount-1, items, key);

    return items[index].getItem();

}

template<class KeyType, class ItemType>
bool ArraySortedDictionary<KeyType, ItemType>::contains(const KeyType& key) const{
    if (isEmpty()) {
        throw std::logic_error("Can not retrieve an item from the empty map!");
    }

    return findEntryIndex(key) != -1;   
}

template<class KeyType, class ItemType>
void ArraySortedDictionary<KeyType, ItemType>::traverse(void visit(const ItemType &)) const {
    for (int i=0; i < itemCount; i++) 
        visit(items[i].getItem());
}

template<class KeyType, class ItemType>
int ArraySortedDictionary<KeyType, ItemType>::binarySearch(int first, int last, MapEntry<KeyType, ItemType>* items, const KeyType& target) const {
    if (first <= last) {
        int mid = first + (last - first) / 2;
        if (items[mid].getKey() == target) {
            return mid;
        } else if (target > items[mid].getKey()) {
            return binarySearch(mid+1, last, items, target);
        } else {
            return binarySearch(first, mid-1, items, target);
        }
    }
    return -1;
}