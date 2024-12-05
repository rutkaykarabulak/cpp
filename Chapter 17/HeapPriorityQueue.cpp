/** @file HeapPriorityQueue.cpp
 * Heap based implementation of ADT Priority Queue.
 */

#ifndef HeapPriortiyQueue_cpp
#define HeapPriortiyQueue_cpp

#include "../Chapter 13/PriorityQueueInterface.hpp"
#include "./ArrayHeap.cpp"

template<class ItemType>
class HeapPriorityQueue: public PriorityQueueInterface<ItemType>{
private:
    ArrayHeap<ItemType>* heap;
public:
    HeapPriorityQueue();
    ~HeapPriorityQueue();
    bool isEmpty() const;
    bool add(const ItemType& newItem);
    bool remove();
    ItemType peek() const;
};
#endif

template<class ItemType>
HeapPriorityQueue<ItemType>::HeapPriorityQueue() {
    heap = new ArrayHeap<ItemType>();
}

template<class ItemType>
HeapPriorityQueue<ItemType>::~HeapPriorityQueue() {
    delete heap;
    heap = nullptr;
}

template<class ItemType>
bool HeapPriorityQueue<ItemType>::isEmpty() const {
    return heap->isEmpty();
}

template<class ItemType>
bool HeapPriorityQueue<ItemType>::add(const ItemType& newItem) {
    return heap->add(newItem);
}

template<class ItemType>
bool HeapPriorityQueue<ItemType>::remove() {
    return heap->remove();
}

template<class ItemType>
ItemType HeapPriorityQueue<ItemType>::peek() const{
    return heap->peekTop();
}