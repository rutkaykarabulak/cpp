/** @file  ArraySortedList.cpp
 * Array based implementation of ADT sorted list.
*/

#ifndef ArraySortedList_cpp
#define ArraySortedList_cpp

#include "./SortedListInterface.hpp"
#include <stdexcept>
#include <cmath>

static const int MAX_SIZE = 6;

template<class ItemType>
class ArraySortedList: public SortedListInterface<ItemType>  {
private:
    int itemCount;
    int maxItems;
    ItemType* items;
public:
    ArraySortedList();
    virtual ~ArraySortedList();
    bool isEmpty() const;
    void insertSorted(const ItemType& newEntry);
    bool removeSorted(const ItemType& anEntry);
    bool remove(int position);
    int getPosition(const ItemType& anEntry) const;
    int getLength() const;
    void clear();
    ItemType getEntry(int position) const;
    void display() const;
};
#endif

template<class ItemType>
ArraySortedList<ItemType>::ArraySortedList() {
    itemCount = 0;
    maxItems = MAX_SIZE;
    items = new ItemType[MAX_SIZE];
}

template<class ItemType>
ArraySortedList<ItemType>::~ArraySortedList() {
    itemCount = 0;
    delete[] items;
}

template<class ItemType>
bool ArraySortedList<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
void ArraySortedList<ItemType>::insertSorted(const ItemType& newItem) {
    if (itemCount == maxItems) {
        // double the array size
        ItemType* newArray = new ItemType[maxItems * 2];

        for (int i=0; i < itemCount; i++) {
            newArray[i] = items[i];
        }
        delete[] items;
        items = newArray;
        newArray = nullptr;
    }

    // find the proper place to insert
    int properPosition = std::fabs(getPosition(newItem));
    
    for (int i = itemCount; i > properPosition; i--) {
        items[i] = items[i-1];
    }
    items[properPosition] = newItem;
    itemCount++;
}

template<class ItemType>
bool ArraySortedList<ItemType>::removeSorted(const ItemType& anEntry) {
    if (isEmpty()) {
        throw new std::logic_error("Attempting to remove from an empty list!");
    }
    
    int indexToRemove = -1;
    for (int i=0; i < itemCount; i++) {
        if (items[i] == anEntry) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1) {
        throw new std::out_of_range("There is no such an item in the list to remove!");
    }

    for(int i=indexToRemove; i < itemCount - 1; i++) {
        items[i] = items[i+1];
    }

    itemCount--;
    return true;
}

template<class ItemType>
bool ArraySortedList<ItemType>::remove(int position) {
    if (position < 1 || position > itemCount) {
        throw std::out_of_range("Invalid position!");
    }

    if (isEmpty()) {
        throw std::logic_error("Attempting to remove from an empty list!");
    }

    for(int i=position - 1; i < itemCount - 1; i++) {
        items[i] = items[i+1];
    }

    itemCount--;
    return true;
}

template<class ItemType>
int ArraySortedList<ItemType>::getPosition(const ItemType& anItem) const {
    int currentPosition = 0;
    for (int i=0; i < itemCount; i++) {
        if (items[i] == anItem) {
            return i;
        }
        if (items[i] > anItem) {
            return -i;
        }
        currentPosition++;
    }

    return -currentPosition;
}

template<class ItemType>
int ArraySortedList<ItemType>::getLength() const {
    return itemCount;
}

template<class ItemType>
void ArraySortedList<ItemType>::clear() {
    if (items != nullptr) {
        delete[] items;
        itemCount = 0;
    }
}

template<class ItemType>
ItemType ArraySortedList<ItemType>::getEntry(int position) const {
    if (isEmpty() || (position < 1 || position > itemCount)) {
        throw new std::logic_error("Attempting to retrieve from an empty list or invalid position!");
    }

    return items[position - 1];
}

template<class ItemType>
void ArraySortedList<ItemType>::display() const {
    for (int i=0; i < itemCount; i++) {
        std::cout << items[i] << " ";
    }
}