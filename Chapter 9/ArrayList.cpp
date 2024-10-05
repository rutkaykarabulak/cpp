/** @file ArrayList.cpp
 * Array based implementation of ADT list.
 */

#ifndef ArrayList_cpp
#define ArrayList_cpp

#include "../Chapter 8/ListInterface.hpp"
static const int ITEM_SIZE = 6;
template<class ItemType>
class ArrayList: public ListInterface<ItemType> {
private:
    ItemType* items; // Pointer to save items
    int       itemCount; // Item count
    int       maxItems; // Maximum allowed items
public:
    ArrayList();
    virtual ~ArrayList();
    bool isEmpty() const;
    int getLength() const;
    bool insert(int position, const ItemType& newItem);
    bool remove(int position);
    void clear();
    ItemType getEntry(int position) const;
    void setEntry(int positino, const ItemType& newItem);
    void display() const;
};

#endif

template<class ItemType>
ArrayList<ItemType>::ArrayList() {
    items = new ItemType[ITEM_SIZE];
    itemCount = 0;
    maxItems = ITEM_SIZE;
}

template<class ItemType>
ArrayList<ItemType>::~ArrayList() {
    clear();
}

template<class ItemType>
bool ArrayList<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
int ArrayList<ItemType>::getLength() const {
    return itemCount;
}

template<class ItemType>
bool ArrayList<ItemType>::insert(int position, const ItemType& newItem) {
    if (!(position >=1 && position <= itemCount + 1)) {
        return false;
    }

    if (position <= itemCount) {
        setEntry(position, newItem);
        return true;
    }

    if (itemCount == maxItems) {
        // double the array
        ItemType* newArray = new ItemType[maxItems * 2];
        for (int i=0; i < itemCount; i++) {
            newArray[i] = items[i];
        }
        maxItems *= 2;
        delete[] items;
        items = newArray;
        newArray = nullptr;
    }
    for (int i = itemCount; i >= position; i--)
        items[i] = items[i-1];

    items[position-1] = newItem;
    itemCount++;
    return true;
}

template<class ItemType>
bool ArrayList<ItemType>::remove(int position) {
    if (isEmpty() || position < 1 || position > itemCount) {
        return false;
    }

    for (int i=position-1; i < itemCount - 1; i++) {
        items[i] = items[i+1];
    }
    itemCount--;
    return true;
}

template<class ItemType>
void ArrayList<ItemType>::clear() {
    delete[] items;
    items = nullptr;
    itemCount = 0;
}

template<class ItemType>
ItemType ArrayList<ItemType>::getEntry(int position) const {
    if (isEmpty()) {
        throw new std::logic_error("Can not retrieve an element from the empty list!");
    }

    if (!(1 <= position <= itemCount + 1)) {
        throw new std::logic_error("Invalid position!");
    }

    return items[position-1];
}

template<class ItemType>
void ArrayList<ItemType>::setEntry(int position, const ItemType& newItem) {
    if (isEmpty()) {
        return;
    }
    if (!(1 <= position <= itemCount + 1)) {
        throw std::logic_error("invalid position");
    }

    items[position-1] = newItem;
}

template<class ItemType>
void ArrayList<ItemType>::display() const {
    for (int i=0; i < itemCount; i++) {
        std::cout << items[i] << " ";
    }
}