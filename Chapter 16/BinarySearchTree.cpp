/** @file BinarySearchTree.cpp
 * BST implementation of ADT BinaryTree
 * @author rutkaykarabulak@gmail.com
 */

#ifndef BinarySearchTree_cpp
#define BinarySearchTree_cpp

#include "../Chapter 15/BinaryTreeInterface.hpp"
#include "../Components/TreeNode.cpp"
#include <algorithm>

template<class ItemType>
class BinarySearchTree: public BinaryTreeInterface<ItemType> {
private:
    TreeNode<ItemType>* root;
protected:

    // Creates a tree structure with the given tree node and returns the created tree.
    TreeNode<ItemType>* copyTree(const TreeNode<ItemType>* tree) const;
    int getHeightRecursive(const TreeNode<ItemType>* tree) const;
    int getNumberOfNodesRecursive(const TreeNode<ItemType>* tree) const;
    TreeNode<ItemType>* insertInOrder(const ItemType& newItem, TreeNode<ItemType>* tree);
    TreeNode<ItemType>* removeRecursively(const ItemType& anItem, TreeNode<ItemType>* tree);
    void destroyTree(TreeNode<ItemType>* tree);
    TreeNode<ItemType>* findNode(TreeNode<ItemType> *tree, const ItemType &target) const;

    // traverses
    void preorder(void visit(ItemType &), TreeNode<ItemType> *tree) const;
    void inorder(void visit(ItemType &), TreeNode<ItemType> *tree) const;
    void postorder(void visit(ItemType &), TreeNode<ItemType> *tree) const;

public:
    BinarySearchTree();
    BinarySearchTree(const ItemType& rootItem);
    BinarySearchTree(const ItemType& rootItem, const TreeNode<ItemType> *leftTree, const TreeNode<ItemType> *rightTree);
    ~BinarySearchTree();
    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;
    ItemType getRootData() const;
    void setRootData(const ItemType& newItem);
    bool add(const ItemType& newItem);
    bool remove(const ItemType& anItem);
    void clear();
    ItemType getEntry(const ItemType &anEntry) const;
    bool contains(const ItemType &anEntry) const;


    void preorderTraverse(void visit(ItemType &)) const;
    void inorderTraverse(void visit(ItemType &)) const;
    void postorderTraverse(void visit(ItemType &)) const;
    

};
#endif

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() {
    root = nullptr;
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {
    clear();
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) {
    root = new TreeNode<ItemType>(rootItem);
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem, const TreeNode<ItemType> *leftTree, const TreeNode<ItemType> *rightTree) {
    root = new TreeNode<ItemType>(rootItem, copyTree(leftTree), copyTree(rightTree));
}

template<class ItemType>
TreeNode<ItemType>* BinarySearchTree<ItemType>::copyTree(const TreeNode<ItemType>* tree) const {
    TreeNode<ItemType>* node = nullptr;

    if (tree != nullptr) {
        node = new TreeNode<ItemType>(tree->getItem());
        node->setLeft(tree->getLeft());
        node->setRight(tree->getRight());
    }
   return node;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const {
    return root == nullptr;
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const {
    return getHeightRecursive(root);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeightRecursive(const TreeNode<ItemType>* tree) const {
    if (tree == nullptr) {
        return 0;
    }

    return 1 + std::max(getHeightRecursive(tree->getLeft()), getHeightRecursive(tree->getRight()));
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {
    return getNumberOfNodesRecursive(root);
}
template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodesRecursive(const TreeNode<ItemType>* tree) const {
    if (tree == nullptr) {
        return 0;
    }

    return 1 + getNumberOfNodesRecursive(tree->getLeft()) + getNumberOfNodesRecursive(tree->getLeft());
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const {
    return root->getItem();
}
template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newItem) {
    root->setItem(newItem);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newItem) {
    insertInOrder(newItem, root);
    return true;
}

template<class ItemType>
TreeNode<ItemType>* BinarySearchTree<ItemType>::insertInOrder(const ItemType& newItem, TreeNode<ItemType>* tree) {
    if (root == nullptr) {
        root = new TreeNode<ItemType>(newItem); // special case
        return root;
    }
    if (tree == nullptr) {
        return new TreeNode<ItemType>(newItem);
    }

    if (tree->getItem() > newItem) {
        tree->setLeft(insertInOrder(newItem, tree->getLeft()));
    } else {
        tree->setRight(insertInOrder(newItem, tree->getRight()));
    }

    return tree;
}

template<class ItemType>
bool BinarySearchTree<ItemType>:: remove(const ItemType& anItem) {
    TreeNode<ItemType>* deletedNode = removeRecursively(anItem, root);
    return true ? deletedNode != nullptr : false;
}

template<class ItemType>
TreeNode<ItemType>* BinarySearchTree<ItemType>::removeRecursively(const ItemType& anItem, TreeNode<ItemType>* tree) {
     if (tree == nullptr) {
        return nullptr;
    }

    if (tree->getItem() == anItem) {
        if (tree->isLeaf()) {
            // case 1 leaf node
            delete tree;
            tree = nullptr;
        } else if (tree->getRight() == nullptr) {
            // case 2 node with only one node
            TreeNode<ItemType>* temp = tree->getLeft();
            tree->setLeft(nullptr);
            delete tree;
            tree = temp;
            temp = nullptr;
        } else if (tree->getLeft() == nullptr){
            // case 2 node with only one node
            TreeNode<ItemType>* temp = tree->getRight();
            tree->setRight(nullptr);
            delete tree;
            tree = temp;
            temp = nullptr;
        } else {
            // case 3 node with two child
            // find the inorder successor, leftmost of the right child
            TreeNode<ItemType>* temp = tree->getRight();
            while (temp->getLeft() != nullptr) {
                temp =  temp->getLeft();
            }
            tree->setItem(temp->getItem());
            tree->setRight(removeRecursively(temp->getItem(), tree->getRight()));
        }
    } else {
        if (tree->getItem() > anItem) {
            tree->setLeft(removeRecursively(anItem, tree->getLeft()));
        } else {
            tree->setRight(removeRecursively(anItem, tree->getRight()));
        }
    }

    return tree;
}

template<class ItemType>
void BinarySearchTree<ItemType>::clear() {
    destroyTree(root);
}

template<class ItemType>
void BinarySearchTree<ItemType>::destroyTree(TreeNode<ItemType>* tree) {
    while (tree !=  nullptr) {
        destroyTree(tree->getLeft());
        destroyTree(tree->getRight());
        delete tree;
        tree = nullptr;
    }
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const
{
    return findNode(root, anEntry)->getItem();
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const {
    return findNode(root, anEntry) != nullptr;
}

template<class ItemType>
TreeNode<ItemType>* BinarySearchTree<ItemType>::findNode(TreeNode<ItemType>* tree, const ItemType& target) const {
    if (tree == nullptr) {
        return nullptr;
    }

    if (tree->getItem() == target) {
        return tree;
    } else {
        TreeNode<ItemType>* result = findNode(tree->getRight(), target);
        if (result == nullptr) {
            result = findNode(tree->getLeft(), target);
        }

        return result;
    }
}

template <class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType &)) const
{
    preorder(visit, root);
}

template <class ItemType>
void BinarySearchTree<ItemType>::preorder(void visit(ItemType &), TreeNode<ItemType> *tree) const
{
    if (tree != nullptr)
    {
        ItemType item = tree->getItem();
        preorder(visit, tree->getLeft());
        preorder(visit, tree->getRight());
    }
}

template <class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType &)) const
{
    inorder(visit, root);
}

template <class ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(ItemType &), TreeNode<ItemType> *tree) const
{
    if (tree != nullptr)
    {
        inorder(visit, tree->getLeft());
        ItemType theItem = tree->getItem();
        visit(theItem);
        inorder(visit, tree->getRight());
    }
}

template <class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType &)) const
{
    postorder(visit, root);
}

template <class ItemType>
void BinarySearchTree<ItemType>::postorder(void visit(ItemType &), TreeNode<ItemType> *tree) const
{
    if (tree != nullptr)
    {
        postorder(visit, tree->getLeft());
        postorder(visit, tree->getRight());
        ItemType item = tree->getItem();
        visit(item);
    }
}