/** @file MinArrayHeap.cpp */

#ifndef MinArrayHeap_cpp
#define MinArrayHeap_cpp

#include "HeapInterface.hpp"
#include <algorithm>

const int MAX_SIZE = 10;

template<class ItemType>
class MinArrayHeap: public HeapInterface<ItemType> {
private:
    ItemType* items;
    int itemCount;

    void rebuildHeap(int index);
    void convertArrayToHeap();
    int getHeightRecursive(int index) const;
public:
    MinArrayHeap();
    MinArrayHeap(const ItemType& root);
    MinArrayHeap(const ItemType arr[], int itemSize);
    ~MinArrayHeap();
    bool isEmpty() const;
    int getNumberOfNodes() const;
    int getHeight() const;
    ItemType peekTop() const;
    bool add(const ItemType& newItem);
    bool remove();
    void clear();
};
#endif

template<class ItemType>
MinArrayHeap<ItemType>::MinArrayHeap() {
    items = new ItemType[MAX_SIZE];
    itemCount = 0;
}

template<class ItemType>
MinArrayHeap<ItemType>::MinArrayHeap(const ItemType& root) {
    items = new ItemType[MAX_SIZE];
    items[0] = root;
    itemCount = 1;
}

template<class ItemType>
MinArrayHeap<ItemType>::MinArrayHeap(const ItemType arr[], int itemSize) {
    items = new ItemType[itemSize];

    for (int i=0; i < itemSize; i++) {
        items[i] = arr[i];
    }
    itemCount = itemSize;
    convertArrayToHeap();
}

template<class ItemType>
MinArrayHeap<ItemType>::~MinArrayHeap() {
    clear();
}

template<class ItemType>
bool MinArrayHeap<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
int MinArrayHeap<ItemType>::getNumberOfNodes() const {
    return itemCount;
}

template<class ItemType>
int MinArrayHeap<ItemType>::getHeightRecursive(int index) const {
    if (index >= itemCount) {
        return 0;
    }

    return 1 + std::max(getHeightRecursive((index * 2) + 1), getHeightRecursive((index * 2) + 2));
}

template<class ItemType>
int MinArrayHeap<ItemType>::getHeight() const {
    return getHeightRecursive(0);
}

template<class ItemType>
ItemType MinArrayHeap<ItemType>::peekTop() const {
    if (isEmpty()) {
        throw std::logic_error("Can not peek an empty heap!");
    }

    return items[0];
}

template<class ItemType>
bool MinArrayHeap<ItemType>::add(const ItemType& newItem) {
    items[itemCount] = newItem;
    int index = itemCount;
    int parentIndex = (index - 1) / 2;

    while (index > 0 && items[index] < items[parentIndex]) {
        std::swap(items[index], items[parentIndex]);
        index = parentIndex;
        parentIndex = (index - 1) / 2;
    }

    itemCount++;
    return true;
}

template<class ItemType>
void MinArrayHeap<ItemType>::rebuildHeap(int index) {
    int leftChildIndex = (index * 2) + 1;

    bool leftChildExists = leftChildIndex < itemCount;
    bool rightChildExists = leftChildIndex+1 < itemCount;

    if (leftChildExists || rightChildExists) {
        int smallerChildIndex = leftChildExists ? leftChildIndex : leftChildIndex+1;

        if (leftChildExists && rightChildExists) {
            smallerChildIndex = items[leftChildIndex] < items[leftChildIndex+1] ? leftChildIndex : leftChildIndex + 1;
        }

        if (items[index] > items[smallerChildIndex]) {
            std::swap(items[index], items[smallerChildIndex]);
            rebuildHeap(smallerChildIndex);
        }
    }
}

template<class ItemType>
bool MinArrayHeap<ItemType>::remove() {
    if (isEmpty()) return false;

    std::swap(items[0], items[itemCount-1]);
    itemCount--;

    rebuildHeap(0);
    return true;
}

template<class ItemType>
void MinArrayHeap<ItemType>::clear() {
    delete items;
    items = nullptr;
    itemCount = 0;
}

template<class ItemType>
void MinArrayHeap<ItemType>::convertArrayToHeap() {
    for (int i=itemCount/2; i>=0; i--) {
        rebuildHeap(i);
    }
}