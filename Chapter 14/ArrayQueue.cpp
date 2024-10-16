/** @file ArrayQueue.cpp
 * Array based implementation of ADT queue.
 */

#ifndef ArrayQueue_cpp
#define ArrayQueue_cpp

#include "../Chapter 13/QueueInterface.hpp"
#include <stdexcept>


static const int MAX_ITEMS = 6;

template<class ItemType>
class ArrayQueue: public QueueInterface<ItemType> {
private:
    ItemType* items;
    int headIndex;
    int tailIndex;
    int maxSize;
    int itemCount;
public:
    ArrayQueue();
    ArrayQueue(const ArrayQueue<ItemType>& array);
    ~ArrayQueue();
    bool isEmpty() const;
    bool enqueue(const ItemType& newEntry);
    bool dequeue();
    ItemType peekFront() const;
    void display() const;
};
#endif

template<class ItemType>
ArrayQueue<ItemType>::ArrayQueue() {
    items = new ItemType[MAX_ITEMS];
    headIndex = 0;
    tailIndex = 0;
    maxSize = MAX_ITEMS;
    itemCount = 0;
}

template<class ItemType>
ArrayQueue<ItemType>::~ArrayQueue() {
    delete items;
    items = nullptr;
}

template<class ItemType>
ArrayQueue<ItemType>::ArrayQueue(const ArrayQueue<ItemType>& array) {
    // do nothing so far
}

template<class ItemType>
bool ArrayQueue<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
bool ArrayQueue<ItemType>::enqueue(const ItemType& newItem) {
    if (itemCount == maxSize) {
        ItemType* newArray = new ItemType[maxSize * 2];
        for (int i=headIndex; i <= tailIndex; i++) {
            newArray[i] = items[i];
        }
        delete items;
        items = newArray;
        newArray = nullptr;
    }

    items[tailIndex] = newItem;
    tailIndex = (tailIndex + 1) % maxSize;
    itemCount++;

    return true;
}

template<class ItemType>
bool ArrayQueue<ItemType>::dequeue() {
    if (isEmpty()) {
        return false;
    } 

    headIndex = (headIndex + 1) % maxSize;  // Wrap head index in circular fashion
    itemCount--;

    return true;
}

template<class ItemType>
ItemType ArrayQueue<ItemType>::peekFront() const {
    return items[headIndex];
}

template<class ItemType>
void ArrayQueue<ItemType>::display() const {
    int index = headIndex;
    for (int i = 0; i < itemCount; i++) {
        std::cout << items[index] << " ";
        index = (index + 1) % maxSize;  // Move index in circular fashion
    }
    std::cout << std::endl;
}