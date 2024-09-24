/** @file ArrayStack.cpp
 * Array based implementation of stack interface.
 */

#ifndef ArrayStack_cpp
#define ArrayStack_cpp

#include  "../Chapter 6/StackInterface.hpp"
#include <stdexcept>

template<class ItemType>
class ArrayStack: public StackInterface<ItemType> {
private:
    static const int ITEM_SIZE = 6;
    ItemType* items;
    int       itemSize;
    int       maxItems;
public:
    ArrayStack();
    virtual ~ArrayStack();
    bool isEmpty() const;
    bool push(const ItemType& newItem);
    bool pop();
    ItemType peek() const;
    void printStack() const;
};
#endif

template<class ItemType>
ArrayStack<ItemType>::ArrayStack() {
    items = new ItemType[ITEM_SIZE];
    itemSize = 0;
    maxItems = ITEM_SIZE;
}

template<class ItemType>
ArrayStack<ItemType>::~ArrayStack() {
    delete[] items;
    items = nullptr;
    itemSize = 0;
}

template<class ItemType>
bool ArrayStack<ItemType>::isEmpty() const {
    return itemSize == 0;
}

template<class ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newItem) {
    if (itemSize < maxItems) {
        items[itemSize] = newItem;
    } else {
        ItemType* newArray = new ItemType[maxItems * 2];
        
        for (int i = 0; i < itemSize; i++) {
            newArray[i] = items[i];
        }
        
        delete[] items;
        items = newArray;
        
        maxItems *= 2;
    }

    itemSize++;
    return true;
}


template<class ItemType>
bool ArrayStack<ItemType>::pop() {
    if (!isEmpty()) {
        itemSize--;
        return true;
    }
    return false;
}

template<class ItemType>
ItemType ArrayStack<ItemType>::peek() const {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty!");
    }
    return items[itemSize-1];
}

template<class ItemType>
void ArrayStack<ItemType>::printStack() const {
    for (int i=0; i <  itemSize;  i++) {
        std::cout << items[i] << " ";
    }   
}