/** @file LinkeStack.cpp
 * Linked based implementation of StackInterface
 */

#ifndef LinkedStack_cpp
#define LinkedStack_cpp

#include  "../Chapter 6/StackInterface.hpp"
#include "../Components/Node.cpp"
#include <stdexcept>

template<class ItemType>
class LinkedStack: public StackInterface<ItemType> {
private:
    Node<ItemType>* top;
public:
    LinkedStack();
    LinkedStack(const LinkedStack<ItemType>& aStack);
    virtual ~LinkedStack();
    bool isEmpty() const;
    bool push(const ItemType& newItem);
    bool pop();
    ItemType peek() const;
    void printStack() const;
};
#endif

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() {
    top = nullptr;
}

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack) {
    if (aStack.top == nullptr)  {
        top = nullptr;
        return;
    }

    top = new Node<ItemType>(aStack.top->getItem());

    Node<ItemType>* originalTop = aStack.top->getNext();
    Node<ItemType>* prevNode = top;

    while (originalTop != nullptr) {
        prevNode->setNext(new Node<ItemType>(originalTop->getItem()));
        prevNode = prevNode->getNext();
        originalTop = originalTop->getNext();
    } 
    prevNode->setNext(nullptr);
}

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack() {
    while (!isEmpty()) {
        pop();
    }
}

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const {
    return top == nullptr;
}

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem) {
    Node<ItemType>* newNode = new Node<ItemType>(newItem, top);
    top = newNode;
    newNode = nullptr;
    
    return true;
}

template<class ItemType>
bool LinkedStack<ItemType>::pop()  {
    if (!isEmpty()) {
        Node<ItemType>* prevTop = top;
        top = top->getNext();

        delete prevTop;
        prevTop = nullptr;
    }
    return false;
}

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const {
    if (isEmpty()) {
        throw std::logic_error("Stack is empty!");
    }
    return top->getItem();
}

template<class ItemType>
void LinkedStack<ItemType>::printStack() const{
    Node<ItemType>* currentNode = top;
    while (currentNode != nullptr) {
        std::cout << currentNode->getItem() << " ";
        currentNode = currentNode->getNext();
    }
}