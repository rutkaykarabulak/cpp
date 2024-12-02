/** @file ArrayHeap.cpp */

#ifndef ArrayHeap_cpp
#define ArrayHeap_cpp

#include "HeapInterface.hpp"
#include <algorithm>

const int MAX_ITEM_COUNT = 10; 

template<class ItemType>
class ArrayHeap: public HeapInterface<ItemType> {
private:
    ItemType* items;
    int itemCount;

    int getLeftChildIndex(int nodeIndex) const;
    int getRightChildIndex(int nodeIndex) const;
    int getParentIndex(int nodeIndex) const;
    bool isLeaf(int nodeIndex) const;
    void rebuildHeap(int index);
    void convertArrayToHeap();
    
public:
    ArrayHeap();
    ArrayHeap(const ItemType& root);
    ArrayHeap(const ItemType arr[], int itemSize);
    ~ArrayHeap();
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
ArrayHeap<ItemType>::ArrayHeap() {
    items = new ItemType[MAX_ITEM_COUNT];
    itemCount = 0;
}

template<class ItemType>
ArrayHeap<ItemType>::ArrayHeap(const ItemType& root) {
    items = new ItemType[MAX_ITEM_COUNT];
    items[0] = root; 
    itemCount = 1;
}
template<class ItemType>
ArrayHeap<ItemType>::ArrayHeap(const ItemType arr[], int itemSize) {
    items = new ItemType[itemSize * 2];
    itemCount = itemSize;

    for (int i=0; i < itemSize; i++) {
        items[i] = arr[i];
    }

    convertArrayToHeap();
}
template<class ItemType>
void ArrayHeap<ItemType>::convertArrayToHeap() {
    for (int i=itemCount/2 - 1; i >= 0; i--) {
        rebuildHeap(i);
    }
}

template<class ItemType>
ArrayHeap<ItemType>::~ArrayHeap() {
    clear();
}

template<class ItemType>
int ArrayHeap<ItemType>::getLeftChildIndex(int index) const{
    return (2*index)+1;
}

template<class ItemType>
int ArrayHeap<ItemType>::getRightChildIndex(int index) const{
    return (2*index)+2;
}

template<class ItemType>
int ArrayHeap<ItemType>::getParentIndex(int index) const{
    return (index-1) / 2;
}

template<class ItemType>
bool ArrayHeap<ItemType>::isLeaf(int index) const{
    return getLeftChildIndex(index) >= itemCount;
}

template<class ItemType>
bool ArrayHeap<ItemType>::isEmpty() const {
    return itemCount ==  0;
}

template<class ItemType>
int ArrayHeap<ItemType>::getNumberOfNodes() const{
    return itemCount;
}

template<class ItemType>
ItemType ArrayHeap<ItemType>::peekTop() const {
    if (isEmpty()) {
        throw std::logic_error("Can not access the peek of empty heap");
    }
    
    return items[0];
}

template<class ItemType>
int ArrayHeap<ItemType>::getHeight() const {
    return 0;
}

template<class ItemType>
bool ArrayHeap<ItemType>::remove() {
    if (isEmpty()) return false;

    items[0] = items[itemCount - 1];
    itemCount--;

    rebuildHeap(0);

    return true;
}

template<class ItemType>
void ArrayHeap<ItemType>::rebuildHeap(int index) {
    int leftChildIndex = (2 * index) + 1;
    int rightChildIndex = (2  * index)+ 2;
    
    bool leftExists = (leftChildIndex < itemCount);
    bool rightExists = (rightChildIndex < itemCount);
    if (leftExists || rightExists) {
        int largerChildIndex = leftExists ?  leftChildIndex : rightChildIndex;

        if (leftExists && rightExists) {
            largerChildIndex = items[leftChildIndex] > items[rightChildIndex] ? leftChildIndex : rightChildIndex; 
        }

        if (items[index] < items[largerChildIndex]) {
            std::swap(items[index], items[largerChildIndex]);
            rebuildHeap(largerChildIndex);
        }
    } // else the given index is leaf, nothing to do
}

template<class ItemType>
bool ArrayHeap<ItemType>::add(const ItemType& newItem) {
    if (itemCount >= MAX_ITEM_COUNT) {
        ItemType* newArray = new ItemType[itemCount * 2];
        for (int i=0; i < itemCount; i++)
            newArray[i] = items[i];
        delete items;
        items = newArray;
        newArray = nullptr;
    }
    items[itemCount] = newItem;
    int index = itemCount;
    int parentIndex = (index - 1) / 2;

    while (index > 0 && items[index] > items[parentIndex]) {
        std::swap(items[index], items[parentIndex]);
        index = parentIndex;
        parentIndex = (index - 1 ) / 2;
    }

    itemCount++;
    return true;
}

template<class ItemType>
void ArrayHeap<ItemType>::clear() {
    delete[] items;
    items = nullptr;
    itemCount = 0;
}
