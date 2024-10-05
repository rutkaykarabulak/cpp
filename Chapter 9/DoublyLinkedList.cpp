/** @file DoublyLinkedList.cpp
 * Doubly linked based implementation of ADT list.
 */

#ifndef DoublyLinkedList_cpp
#define DoublyLinkedList_cpp

#include "../Chapter 8/ListInterface.hpp"
#include "../Components/DoublyNode.cpp"
#include <stdexcept>

template<class ItemType>
class DoublyLinkedList: public ListInterface<ItemType> {
private:
    DoublyNode<ItemType>* head;
    DoublyNode<ItemType>* tail;
    int                   itemCount;

    DoublyNode<ItemType>* getNodeAt(int position) const;
public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<ItemType>& aList);
    virtual ~DoublyLinkedList();
    bool isEmpty() const;
    int getLength() const;
    bool insert(int newPosition, const ItemType& newEntry); 
    bool remove(int position);
    void clear();
    ItemType getEntry(int position) const;
    void setEntry(int position, const ItemType& newItem);
    void display() const;
    void displayTail() const;
};
#endif

template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList() {
    head = new DoublyNode<ItemType>(); // dummy node
    tail = new DoublyNode<ItemType>(); // dummy node
    head->setNext(tail);
    tail->setPrevious(head);
    itemCount = 0;
    
}

template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList(const DoublyLinkedList<ItemType>& aList) {
    head = new DoublyNode<ItemType>(); // dummy head
    tail = new DoublyNode<ItemType>(); // dummy tail
    head->setNext(tail);
    tail->setPrevious(head);
    itemCount = 0;

    DoublyNode<ItemType>* currentNode = aList.head->getNext();
    while (currentNode != aList.tail) {  // Copy each node
        insert(itemCount + 1, currentNode->getItem());
        currentNode = currentNode->getNext();
    }
}

template<class ItemType>
DoublyLinkedList<ItemType>::~DoublyLinkedList() {
    clear();
    tail = nullptr;
    head = nullptr;
}

template<class ItemType>
bool DoublyLinkedList<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
int DoublyLinkedList<ItemType>::getLength() const {
    return itemCount;
}

template<class ItemType>
bool DoublyLinkedList<ItemType>::insert(int newPosition, const ItemType& newItem) {
    if (!(1 <= newPosition && newPosition <= itemCount + 1)) {
        throw new std::logic_error("Invalid position!");
    }

    DoublyNode<ItemType>* prevNode = getNodeAt(newPosition-1);
    DoublyNode<ItemType>* newNode = new DoublyNode<ItemType>(newItem);

    newNode->setPrevious(prevNode);
    newNode->setNext(prevNode->getNext());
    prevNode->getNext()->setPrevious(newNode);
    prevNode->setNext(newNode);

    itemCount++;
    return true;
}

template<class ItemType>
bool DoublyLinkedList<ItemType>::remove(int position) {
    if (!(1 <= position && position <= itemCount) || isEmpty()) {
        throw new std::logic_error("Invalid position or attemting to remove from an empty list!");
    }

    DoublyNode<ItemType>* nodeToDelete = getNodeAt(position);
    nodeToDelete->getPrevious()->setNext(nodeToDelete->getNext());
    nodeToDelete->getNext()->setPrevious(nodeToDelete->getPrevious());

    delete nodeToDelete;
    nodeToDelete = nullptr;

    itemCount--;
    return true;
}

template<class ItemType>
void DoublyLinkedList<ItemType>::clear() {
    while (!isEmpty()) {
        remove(1);
    }
}

template<class ItemType>
ItemType DoublyLinkedList<ItemType>::getEntry(int position) const {
    if (!(1 <= position && position <= itemCount) || isEmpty()) {
        throw new std::logic_error("Invalid position!");
    }

    return getNodeAt(position)->getItem();
}

template<class ItemType>
void DoublyLinkedList<ItemType>::setEntry(int position, const ItemType& newItem) {
    if (!(1 <= position && position <= itemCount) || isEmpty()) {
        throw new std::logic_error("Invalid position!");
    }

    getNodeAt(position)->setItem(newItem);
}

template<class ItemType>
void DoublyLinkedList<ItemType>::display() const {
    DoublyNode<ItemType>* currentNode = head->getNext();

    while (currentNode != nullptr && currentNode->getNext() != nullptr) {
        std::cout << currentNode->getItem() << " ";
        currentNode = currentNode->getNext();
    }
}

template<class ItemType>
void DoublyLinkedList<ItemType>::displayTail() const {
    std::cout << tail->getPrevious()->getItem() << " ";
}

template<class ItemType>
DoublyNode<ItemType>* DoublyLinkedList<ItemType>::getNodeAt(int position) const {
    DoublyNode<ItemType>* currentNode = head;
    for (int i=0; i < position; i++)
        currentNode = currentNode->getNext();

    return currentNode;
}