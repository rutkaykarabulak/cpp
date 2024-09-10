/** @file LinkedBag.cpp
 * A linked based implementation of BagInterface
 */
#ifndef LinkedBag_cpp
#define LinkedBag_cpp

#include "../Components/Node.cpp"
#include "../Chapter 1/BagInterface.hpp"

template<class ItemType>
class LinkedBag: public BagInterface<ItemType> {
private:
    int itemCount;
    Node<ItemType>* headPtr;
public:
    LinkedBag();
    LinkedBag(const LinkedBag<ItemType>& bag); // copy constructor
    virtual ~LinkedBag();
    int getCurrentSize() const;
    bool isEmpty() const;
    bool add(const ItemType& newEntry);
    bool remove(const ItemType& anEntry);
    void clear();
    bool contains(const ItemType& anEntry) const;
    int getFrequencyOf(const ItemType& anEntry) const;
    std::vector<ItemType> toVector() const;
};

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() {
    itemCount = 0;
    headPtr = nullptr;
}

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag() {
    clear();
}

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& bag) {
    itemCount = bag.getCurrentSize();
    headPtr = nullptr;

    if (!bag.isEmpty()) {
        headPtr = new Node<ItemType>(bag.headPtr->getItem());
        Node<ItemType>* latestNode = headPtr;
        Node<ItemType>* currentNode = bag.headPtr->getNext();
        
        while (currentNode != nullptr) {
            Node<ItemType>* newNode = new Node<ItemType>(currentNode->getItem());
            latestNode->setNext(newNode);
            latestNode = newNode;
            currentNode = currentNode->getNext();
        }
    }
}

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry) {
    Node<ItemType>* newNode = new Node<ItemType>(newEntry);
    newNode->setNext(headPtr);
    headPtr = newNode;
    itemCount++;

    return true;
}

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
    return itemCount;
}

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
    return headPtr == nullptr;
}

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry) {
    if (isEmpty()) {
        return false;
    }

    if (headPtr->getItem() == anEntry) {
        Node<ItemType>* nodeToRemove = headPtr;
        headPtr = headPtr->getNext();
        // break the chain
        nodeToRemove->setNext(nullptr);
        delete nodeToRemove;
        nodeToRemove = nullptr;
        itemCount--;
        return true;
    }

    Node<ItemType>* prevNode = headPtr;
    Node<ItemType>* currentNode = headPtr->getNext();
    while (currentNode != nullptr) {
        if (currentNode->getItem() == anEntry) {
            Node<ItemType>* nodeToRemove = currentNode;
            prevNode->setNext(nodeToRemove->getNext());
            // break the chain, fail-safe programming
            nodeToRemove->setNext(nullptr);
            delete nodeToRemove;
            nodeToRemove=nullptr;
            itemCount--;
            return true;
        }
        prevNode = currentNode;
        currentNode = currentNode->getNext();
    }

    return false;
}

template<class ItemType>
void LinkedBag<ItemType>::clear() {
    while (headPtr != nullptr) {
        Node<ItemType>* nodeToRemove = headPtr;
        headPtr = headPtr->getNext();

        delete nodeToRemove;
        nodeToRemove = nullptr;
    }
    itemCount = 0;
}

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const {
    Node<ItemType>* currentNode = headPtr;

    while (currentNode != nullptr) {
        if (currentNode->getItem() == anEntry) {
            return true;
        }
        currentNode = currentNode->getNext();
    }

    return false;
}

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
    int result = 0;
    Node<ItemType>* currentNode = headPtr;
    while (currentNode != nullptr) {
        if (currentNode->getItem() == anEntry) {
            result++;
        }
        currentNode = currentNode->getNext();
    }
    return result;
}

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const {
    std::vector<ItemType> result;
    Node<ItemType>* currentNode = headPtr;
    while (currentNode != nullptr) {
        result.push_back(currentNode->getItem());
        currentNode = currentNode->getNext();
    }
    currentNode = nullptr;
    return result;
}

#endif