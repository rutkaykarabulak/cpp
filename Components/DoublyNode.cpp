/** @file DoublyNode.cpp
 * Implementation of doubly node that points both previous and next node.
 */

#ifndef DoublyNode_cpp
#define DoublyNode_cpp

template<class ItemType>
class DoublyNode {
private:
    ItemType              item;
    DoublyNode<ItemType>* next;
    DoublyNode<ItemType>* previous;
public:
    DoublyNode();
    DoublyNode(const ItemType& anItem);
    DoublyNode(const ItemType& anItem, DoublyNode<ItemType>* next, DoublyNode<ItemType>* previous);
    
    ItemType getItem() const;
    DoublyNode<ItemType>* getNext() const;
    DoublyNode<ItemType>* getPrevious() const;

    void setItem(const ItemType& newItem);
    void setNext(DoublyNode<ItemType>* next);
    void setPrevious(DoublyNode<ItemType>* previous);
};
#endif

template<class ItemType>
DoublyNode<ItemType>::DoublyNode() {
    next = nullptr;
    previous = nullptr;
}

template<class ItemType>
DoublyNode<ItemType>::DoublyNode(const ItemType& anItem) {
    item = anItem;
    next = nullptr;
    previous = nullptr;
}

template<class ItemType>
DoublyNode<ItemType>::DoublyNode(const ItemType& anItem, DoublyNode<ItemType>* next, DoublyNode<ItemType>* previous) {
    item = anItem;
    this->next = next;
    this->previous = previous;
}

template<class ItemType>
ItemType DoublyNode<ItemType>::getItem() const {
    return item;
}

template<class ItemType>
DoublyNode<ItemType>* DoublyNode<ItemType>::getNext() const {
    return next;
}

template<class ItemType>
DoublyNode<ItemType>* DoublyNode<ItemType>::getPrevious() const {
    return previous;
}

template<class ItemType>
void DoublyNode<ItemType>::setItem(const ItemType& newItem) {
    item = newItem;
}

template<class ItemType>
void DoublyNode<ItemType>::setNext(DoublyNode<ItemType>* next) {
    this->next = next;
}

template<class ItemType>
void DoublyNode<ItemType>::setPrevious(DoublyNode<ItemType>* previous) {
    this->previous = previous;
}
