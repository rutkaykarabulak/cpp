/** @file DynamicArrayBag.cpp
 * Instead of having fixed size array, enlarge array each team when it becomes full.
 */
#ifndef DynamicArrayBag_cpp
#define DynamicArrayBag_cpp
#include "../Chapter 1/BagInterface.hpp"

template<class ItemType>
class DynamicArrayBag: public BagInterface<ItemType>{
private:
    static const int ITEM_SIZE = 3;
    ItemType* items;
    int itemCount;
    int maxItems;
public:
    DynamicArrayBag();
    ~DynamicArrayBag();
    int getCurrentSize() const;
    bool isEmpty() const;
    bool add(const ItemType& newItem);
    bool remove(const ItemType& anItem);
    void clear();
    int getFrequencyOf(const ItemType& anItem) const;
    bool contains(const ItemType& anItem) const;
    std::vector<ItemType> toVector() const;
    int getIndexOf(const ItemType& anItem) const;
};

template<class ItemType>
DynamicArrayBag<ItemType>::DynamicArrayBag() {
    items = new ItemType[ITEM_SIZE];
    itemCount = 0;
    maxItems = ITEM_SIZE;
}

template<class ItemType>
DynamicArrayBag<ItemType>::~DynamicArrayBag() {
    clear();
}

template<class ItemType>
int DynamicArrayBag<ItemType>::getCurrentSize() const {
    return itemCount;
}

template<class ItemType>
bool DynamicArrayBag<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
bool DynamicArrayBag<ItemType>::add(const ItemType& anItem) {
    if (itemCount == maxItems) {
        ItemType* oldArray = items;
        items = new ItemType[itemCount * 2];
        for (int i=0; i < itemCount; i++) {
            items[i] = oldArray[i];
        }
        delete oldArray;
        oldArray = nullptr;
        maxItems = itemCount * 2;
    }

    items[itemCount] = anItem;
    itemCount++;
    return true;;
}

template<class ItemType>
bool DynamicArrayBag<ItemType>::remove(const ItemType& anItem) {
    return false; // stub
}

template<class ItemType>
void DynamicArrayBag<ItemType>::clear() {
    delete items;
    items = nullptr;
    itemCount = 0;
    maxItems = 0;
}

template<class ItemType>
int DynamicArrayBag<ItemType>::getFrequencyOf(const ItemType& anItem) const {
    return 0; // stub
}

template<class ItemType>
bool DynamicArrayBag<ItemType>::contains(const ItemType& anItem) const {
    return false; // stub
}

template<class ItemType>
int DynamicArrayBag<ItemType>::getIndexOf(const ItemType& anItem) const {
    return 0; // stub
}

template<class ItemType>
std::vector<ItemType> DynamicArrayBag<ItemType>::toVector() const {
    std::vector<ItemType> vector;
    for (int i=0; i < itemCount; i++) {
        vector.push_back(items[i]);
    }
    return vector;
}

#endif