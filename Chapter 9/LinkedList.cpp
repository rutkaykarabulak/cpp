/** @file LinkedList.cpp
 * Linked based implementation of ADT list.
 */

#ifndef LinkedList_cpp
#define LinkedList_cpp

#include "../Chapter 8/ListInterface.hpp"
#include "../Components/Node.cpp"
#include <stdexcept>

template<class ItemType>
class LinkedList: public ListInterface<ItemType> {
private:
    Node<ItemType>* head;
    int itemCount;
    Node<ItemType>* getNodeAt(int position) const;
public:
    LinkedList();
    LinkedList(const LinkedList<ItemType>& aList);
    virtual ~LinkedList();
    bool isEmpty() const;
    int getLength() const;
    bool insert(int newPosition, const ItemType& newEntry); 
    bool remove(int position);
    void clear();
    ItemType getEntry(int position) const;
    void setEntry(int position, const ItemType& newItem);
    void display() const;

};
#endif

template<class ItemType>
LinkedList<ItemType>::LinkedList():head(new Node<ItemType>()), itemCount(0) {}

template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
    clear();
}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList) {
    itemCount = aList.itemCount;
    if (aList.head == nullptr) {
        head = nullptr;
    } else {
        head = new Node<ItemType>(aList.head->getItem());
        
        Node<ItemType>* originalList = aList.head->getNext();
        Node<ItemType>* latestNode = head;

        while (originalList != nullptr) {
            latestNode->setNext(new Node<ItemType>(originalList->getItem()));
            originalList = originalList->getNext();
            latestNode = latestNode->getNext();
        }

        latestNode->setNext(nullptr);
    }
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const {
    return itemCount;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newItem) {
    if (!(1 <= newPosition && newPosition <= itemCount + 1)) {
        throw new std::logic_error("Invalid position");
    }

    Node<ItemType>* prevNode = getNodeAt(newPosition - 1);
    Node<ItemType>* newNode = new Node<ItemType>(newItem);
    newNode->setNext(prevNode->getNext());
    prevNode->setNext(newNode);

    itemCount++;
    return true;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(int position) {
    if (!(1 <= position && position <= itemCount) || isEmpty()) {
        return false;
    }
    Node<ItemType>* prevNode = getNodeAt(position-1);
    Node<ItemType>* nodeToDelete = prevNode->getNext();
    prevNode->setNext(nodeToDelete->getNext());
    
    delete nodeToDelete;
    itemCount--;
    return true;
}

template<class ItemType>
void LinkedList<ItemType>::clear() {
    while (!isEmpty()) {
        remove(1);
    }
}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const {
    if (isEmpty() || !(1 <= position && position <= itemCount + 1)) {
        throw new std::logic_error("Empty list or invalid position");
    }

    Node<ItemType>* currentNode = head;
    int currentPosition = 1;

    while (currentNode != nullptr && currentPosition < position) {
        currentNode = currentNode->getNext();
        currentPosition++;
    }

    return currentNode->getItem();
}

template<class ItemType>
void LinkedList<ItemType>::setEntry(int position, const ItemType& newItem) {
    if (!(1 <= position && position <= itemCount) || isEmpty()) {
        throw new std::logic_error("Invalid position or empty list!");
    } 
    getNodeAt(position)->setItem(newItem);
}

template<class ItemType>
void LinkedList<ItemType>::display() const {
    Node<ItemType>* currentNode = head->getNext();
    while (currentNode != nullptr) {
        std::cout << currentNode->getItem() << " ";
        currentNode = currentNode->getNext();
    }
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const {
    Node<ItemType>* currentNode = head;
    for (int i=0; i < position; i++)
        currentNode = currentNode->getNext();
    
    return currentNode;
}