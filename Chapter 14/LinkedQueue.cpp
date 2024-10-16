/** @file LinkedQueue.cpp
 * Linked based implementation of ADT queue.
 */

#ifndef LinkedQueue_cpp
#define LinkedQueue_cpp

#include "../Chapter 13/QueueInterface.hpp"
#include "../Components/Node.cpp"
#include <stdexcept>
template<class ItemType>
class LinkedQueue: public QueueInterface<ItemType>{
private:
    Node<ItemType>* head;
    Node<ItemType>* tail;
public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue<ItemType>& queue);
    ~LinkedQueue();
    bool isEmpty() const;
    bool enqueue(const ItemType& newEntry);
    bool dequeue();
    ItemType peekFront() const;
    void display() const;
};
#endif

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue() {
    head = new Node<ItemType>();
    tail = head;
}

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue() {
    while (head != nullptr) {
        dequeue();
    }
}

template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const {
    return head==nullptr;
}

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newItem) {
    Node<ItemType>* newNode = new Node<ItemType>(newItem);
    
    tail->setNext(newNode);
    tail = newNode;
    return true;
}


template<class ItemType>
bool LinkedQueue<ItemType>::dequeue() {
    if (isEmpty()) {
        throw new std::logic_error("Attemtitng to dequeue from an empty queue...");
    }
    Node<ItemType>* nodeToDelete = head;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->getNext();
    }

    delete nodeToDelete;
    nodeToDelete = nullptr;

    return true;
}

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const {
    return head->getItem();
}

template<class ItemType>
void LinkedQueue<ItemType>::display() const {
    Node<ItemType>* currentNode = head->getNext();

    while (currentNode != nullptr) {
        std::cout << currentNode->getItem() << " ";
        currentNode = currentNode->getNext();
    }
}