/** @file SortedList.cpp
 * Link based implementation of ADT sorted list.
 */

#ifndef SortedList_cpp
#define SortedList_cpp

#include "./SortedListInterface.hpp"
#include "../Components/DoublyNode.cpp"
#include <stdexcept>

template<class ItemType>
class SortedList: public SortedListInterface<ItemType> {
private:
    int                     itemCount;
    DoublyNode<ItemType>*   head;
    DoublyNode<ItemType>*   tail;

    // finds the correct position
    DoublyNode<ItemType>* getNode(const ItemType& anEntry) const;
public:
    SortedList();
    SortedList(const SortedList<ItemType>& aList);
    virtual ~SortedList();
    bool isEmpty() const;
    void insertSorted(const ItemType& newEntry);
    bool removeSorted(const ItemType& anEntry);
    bool remove(int position);
    int getPosition(const ItemType& anEntry) const;
    int getLength() const;
    void clear();
    ItemType getEntry(int position) const;
    void display() const;
};
#endif

template<class ItemType>
SortedList<ItemType>::SortedList() {
    itemCount = 0;
    head = new DoublyNode<ItemType>(); // dummy node
    tail = new DoublyNode<ItemType>(); // dummy node

    head->setNext(tail);
    tail->setPrevious(head);
}

template<class ItemType>
SortedList<ItemType>::SortedList(const SortedList<ItemType>& aList) {
    std::cout << "Copy constructor is triggered";
    head = new DoublyNode<ItemType>(); // dummy node
    tail = new DoublyNode<ItemType>(); // dummy node

    head->setNext(tail);
    tail->setPrevious(head);

    DoublyNode<ItemType>* originalNode = aList.head->getNext();
    while (originalNode != nullptr && originalNode != aList.tail) {
        insertSorted(originalNode->getItem());
        originalNode = originalNode->getNext();
    }

}

template<class ItemType>
SortedList<ItemType>::~SortedList() {
    clear();
}

template<class ItemType>
bool SortedList<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
void SortedList<ItemType>::insertSorted(const ItemType& newItem) {
    // assuming the list is in ascending order
    
    DoublyNode<ItemType>* currentNode = head;

    while (currentNode != nullptr && currentNode->getNext() != nullptr && newItem >= currentNode->getItem()) {
        currentNode = currentNode->getNext();
    }

    DoublyNode<ItemType>* newNode = new DoublyNode<ItemType>(newItem);
    DoublyNode<ItemType>* prevNode = currentNode->getPrevious();

    newNode->setPrevious(prevNode);
    newNode->setNext(prevNode->getNext());
    prevNode->getNext()->setPrevious(newNode);
    prevNode->setNext(newNode);

    itemCount++;
}

template<class ItemType>
bool SortedList<ItemType>::removeSorted(const ItemType& anEntry) {
    if (isEmpty())
        return false;
    
    DoublyNode<ItemType>* nodeToRemove = getNode(anEntry);
    if (nodeToRemove == nullptr)
        return false;

    nodeToRemove->getPrevious()->setNext(nodeToRemove->getNext());
    nodeToRemove->getNext()->setPrevious(nodeToRemove->getPrevious());

    delete nodeToRemove;
    nodeToRemove = nullptr;
    itemCount--;

    return true;
}

template<class ItemType>
int SortedList<ItemType>::getPosition(const ItemType& anEntry) const {
    if (isEmpty()) {
        return -1;
    }

    int currentPosition = 0;
    DoublyNode<ItemType>* currentNode = head;
    while (currentNode != nullptr && currentNode->getNext() != nullptr) {
        if (currentNode->getItem() == anEntry) {
            return currentPosition;
        }
        if (currentNode->getItem() > anEntry)
            return -currentPosition;
        currentNode = currentNode->getNext();
        currentPosition++;
    }

    return -currentPosition;
}

template<class ItemType>
int SortedList<ItemType>::getLength() const {
    return itemCount;
}

template<class ItemType>
void SortedList<ItemType>::clear() {
    while (!isEmpty()) {
        remove(1);
    }
}

template<class ItemType>
ItemType SortedList<ItemType>::getEntry(int position) const {
    if (position < 1 || position > itemCount)
    {
        throw std::out_of_range("Invalid position!");
    }
    DoublyNode<ItemType>* currentNode = head;

    for (int i=0; i < position; i++)
        currentNode = currentNode->getNext();

    return currentNode->getItem();;
}

template<class ItemType>
bool SortedList<ItemType>::remove(int position) {
    if (!( 1 <= position && position <= itemCount) || isEmpty()) {
        return false;
    }

    DoublyNode<ItemType>* currentNode;

    if (position <= itemCount / 2)
    {
        currentNode = head->getNext();
        for (int i = 1; i < position; i++)
        {
            currentNode = currentNode->getNext();
        }
    }
    else
    {
        currentNode = tail->getPrevious();
        for (int i = itemCount; i > position; i--)
        {
            currentNode = currentNode->getPrevious();
        }
    }

    currentNode->getNext()->setPrevious(currentNode->getPrevious());
    currentNode->getPrevious()->setNext(currentNode->getNext());

    delete currentNode;
    currentNode = nullptr;
    itemCount--;

    return true;
}

template<class ItemType>
void SortedList<ItemType>::display() const {
    DoublyNode<ItemType>* currentNode = head->getNext();
    while (currentNode != nullptr && currentNode->getNext() != nullptr) {
        std::cout << currentNode->getItem() << " ";
        currentNode = currentNode->getNext();
    }
}

template<class ItemType>
DoublyNode<ItemType>* SortedList<ItemType>::getNode(const ItemType& anEntry) const {
    if (isEmpty()) {
        return nullptr;
    }

    DoublyNode<ItemType>* currentNode = head;

    while (currentNode != nullptr && currentNode->getNext() != nullptr && currentNode->getItem() != anEntry)
        currentNode = currentNode->getNext();
    
    return currentNode->getItem() == anEntry ? currentNode : nullptr;
}