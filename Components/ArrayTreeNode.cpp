/** @file ArrayTreeNode.cpp
 * Array based implementation of Tree node
 */

#ifndef ArrayTreeNode_cpp
#define ArrayTreeNode_cpp

template<class ItemType>
class ArrayTreeNode {
private:
    ItemType item;  // Data stored in the node
    int      left;  // Index of left child in the array (-1 if no child)
    int      right; // Index of right child in the array (-1 if no child)

public:
    // Constructors
    ArrayTreeNode();  // Default constructor
    ArrayTreeNode(const ItemType& anItem);  // Constructor with item
    ArrayTreeNode(const ItemType& anItem, int leftChild, int rightChild);  // Constructor with item and children

    // Getters
    ItemType getItem() const;
    int getLeft() const;
    int getRight() const;

    // Setters
    void setItem(const ItemType& anItem);
    void setLeft(int leftChild);
    void setRight(int rightChild);
};

// Default constructor
template<class ItemType>
ArrayTreeNode<ItemType>::ArrayTreeNode(): left(-1), right(-1) { }

// Constructor with item
template<class ItemType>
ArrayTreeNode<ItemType>::ArrayTreeNode(const ItemType& anItem): item(anItem), left(-1), right(-1) { }

// Constructor with item and children
template<class ItemType>
ArrayTreeNode<ItemType>::ArrayTreeNode(const ItemType& anItem, int leftChild, int rightChild)
    : item(anItem), left(leftChild), right(rightChild) { }

// Getter for item
template<class ItemType>
ItemType ArrayTreeNode<ItemType>::getItem() const {
    return item;
}

// Getter for left child index
template<class ItemType>
int ArrayTreeNode<ItemType>::getLeft() const {
    return left;
}

// Getter for right child index
template<class ItemType>
int ArrayTreeNode<ItemType>::getRight() const {
    return right;
}

// Setter for item
template<class ItemType>
void ArrayTreeNode<ItemType>::setItem(const ItemType& anItem) {
    item = anItem;
}

// Setter for left child index
template<class ItemType>
void ArrayTreeNode<ItemType>::setLeft(int leftChild) {
    left = leftChild;
}

// Setter for right child index
template<class ItemType>
void ArrayTreeNode<ItemType>::setRight(int rightChild) {
    right = rightChild;
}

#endif
