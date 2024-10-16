/** @file ListQueue.cpp
 * List based implementation of ADT queue.
 */

#ifndef ListQueue_cpp
#define ListQueue_cpp

#include "../Chapter 9/LinkedList.cpp"
#include "../Chapter 13/QueueInterface.hpp"

template<class ItemType>
class ListQueue: public QueueInterface<ItemType> {
private:
    LinkedList<ItemType>* list;
public:
    ListQueue();
    ListQueue(const ListQueue& aQueue); 
    ~ListQueue();
    bool isEmpty() const;
    bool enqueue(const ItemType& newEntry);
    bool dequeue();
    ItemType peekFront() const;
    void display() const;
};
#endif

template<class ItemType>
ListQueue<ItemType>::ListQueue() {
    list = new LinkedList<ItemType>();
}

template<class ItemType>
ListQueue<ItemType>::~ListQueue() {
    list->clear();
}

template<class ItemType>
ListQueue<ItemType>::ListQueue(const ListQueue& aQueue) {

}

template<class ItemType>
bool ListQueue<ItemType>::isEmpty() const{
    return list->isEmpty();
}

template<class ItemType>
bool ListQueue<ItemType>::enqueue(const ItemType& newItem) {
    return list->insert(list->getLength()+1, newItem);
}

template<class ItemType>
bool ListQueue<ItemType>::dequeue() {
    return list->remove(1);
}

template<class ItemType>
ItemType ListQueue<ItemType>::peekFront() const {
    return list->getEntry(1);
}

template<class ItemType>
void ListQueue<ItemType>::display() const {
    list->display();
}