/** @file TreeNode.cpp
 * Implementation file for binary tree node.
 */

#ifndef TreeNode_cpp
#define TreeNode_cpp

template<class ItemType>
class TreeNode {
private:
    ItemType            item;
    TreeNode<ItemType>* left;
    TreeNode<ItemType>* right;
public:
    TreeNode();
    TreeNode(const ItemType& newItem);
    TreeNode(const ItemType& newItem, TreeNode<ItemType>* leftNode, TreeNode<ItemType>* rightNode);

    // getters and setters
    ItemType getItem() const;
    TreeNode<ItemType>* getLeft() const;
    TreeNode<ItemType>* getRight() const;

    bool isLeaf() const;

    void setItem(const ItemType& newItem);
    void setLeft(TreeNode<ItemType>* leftNode);
    void setRight(TreeNode<ItemType>* rightNode);
};
#endif

template<class ItemType>
TreeNode<ItemType>::TreeNode():left(nullptr), right(nullptr) {}


template<class ItemType>
TreeNode<ItemType>::TreeNode(const ItemType& newItem) {
    item = newItem;
    left = nullptr;
    right = nullptr;
}

template<class ItemType>
TreeNode<ItemType>::TreeNode(const ItemType& newItem, TreeNode<ItemType>* leftNode, TreeNode<ItemType>* rightNode) {
    item = newItem;
    left = leftNode;
    right = rightNode;
}

template<class ItemType>
ItemType TreeNode<ItemType>::getItem() const {
    return item;
}

template<class ItemType>
TreeNode<ItemType>* TreeNode<ItemType>::getLeft() const{
    return left;
}

template<class ItemType>
TreeNode<ItemType>* TreeNode<ItemType>::getRight() const{
    return right;
}

template<class ItemType>
bool TreeNode<ItemType>::isLeaf() const {
    return (left == nullptr && right == nullptr);
}

template<class ItemType>
void TreeNode<ItemType>::setItem(const ItemType& newItem) {
    item = newItem;
}

template<class ItemType>
void TreeNode<ItemType>::setLeft(TreeNode<ItemType>* leftNode) {
    left = leftNode;
}

template<class ItemType>
void TreeNode<ItemType>::setRight(TreeNode<ItemType>* rightNode) {
    right = rightNode;
}