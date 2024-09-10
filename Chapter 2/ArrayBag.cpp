#ifndef ArrayBag_cpp
#define ArrayBag_cpp

#include "../Chapter 1/BagInterface.hpp"

template<class ItemType>
class ArrayBag: public BagInterface<ItemType> {
    private:
    static const int ITEM_SIZE = 6;
    ItemType items[ITEM_SIZE];
    int itemCount;
    int maxItems;

    public:
    ArrayBag();
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
ArrayBag<ItemType>::ArrayBag(): itemCount(0), maxItems(ITEM_SIZE)
{
}

template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const {
    return itemCount;
}

template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newItem) {
    if (itemCount == maxItems) {
        return false;
    }
    items[itemCount] = newItem;
    itemCount++;

    return true;
}


template<class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anItem) {
    int indexOfItem = getIndexOf(anItem);
    bool isRemovable = !isEmpty() && indexOfItem != -1;

    if (isRemovable) {
        itemCount--;
        items[indexOfItem] = items[itemCount];
    }

    return isRemovable;
}

template<class ItemType>
void ArrayBag<ItemType>::clear() {
    itemCount = 0;
}

template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anItem) const {
    if (isEmpty()) {
        return 0;
    }
    int frequency = 0;
    for (int i=0; i < itemCount; i++) {
        if (items[i] == anItem)
            frequency++;
    }
    return frequency;
}

template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anItem) const {
    return getIndexOf(anItem) != -1;
}

template<class ItemType>
std::vector<ItemType> ArrayBag<ItemType>::toVector() const {
    std::vector<ItemType> vector;
    for (int i=0; i < itemCount; i++) {
        vector.push_back(items[i]);
    }

    return vector;
}

template<class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& anItem) const {
    for (int i=0; i < itemCount; i++) {
        if (items[i] == anItem) {
            return i;
        }
    }
    return -1;
}

#endif