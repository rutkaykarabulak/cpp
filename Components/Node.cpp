/** @file Node.cpp 
 * A component that holds an item and points to the next node.
*/
#ifndef Node_cpp
#define Node_cpp

template<class ItemType>
class Node {
private:
    ItemType        item; // Node's data.
    Node<ItemType>* next; // Pointer to next node.

public:
    Node(); // default constructor
    Node(const ItemType& anItem); // parameterized constructor
    Node(const ItemType& anItem, Node* next); // parameterized constructor

    ItemType getItem() const;
    Node<ItemType>* getNext() const;
    void setNext(Node* next);
    void setItem(const ItemType& anItem);
};

template<class ItemType>
Node<ItemType>::Node():next(nullptr) {}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem):item(anItem), next(nullptr) {}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem,Node<ItemType>* next):item(anItem), next(next) {}

template<class ItemType>
ItemType Node<ItemType>::getItem() const {
    return item;
}

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const {
    return next;
}

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* next) {
    this->next = next;
}

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) {
    item = anItem;
}

#endif