/** @file BinaryTree.cpp
 * Link based implementation of ADT binary tree.
 */

#ifndef BinaryNodeTree_cpp
#define BinaryNodeTree_cpp

#include "../Chapter 15/BinaryTreeInterface.hpp"
#include "../Components/TreeNode.cpp"
#include <algorithm>

template <class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
private:
    TreeNode<ItemType> *root;

protected:
    TreeNode<ItemType> *copyTree(const TreeNode<ItemType> *node) const;
    void destroyTree(TreeNode<ItemType> *tree);
    int getHeightRecursive(const TreeNode<ItemType> *tree) const;
    int getNumberOfNodesRecursive(const TreeNode<ItemType> *tree) const;
    TreeNode<ItemType> *balancedAdd(TreeNode<ItemType> *tree, TreeNode<ItemType> *newNode);
    TreeNode<ItemType> *findNode(TreeNode<ItemType> *tree, const ItemType &target) const;
    TreeNode<ItemType> *removeRecursive(TreeNode<ItemType> *tree, const ItemType &target);

    void preorder(void visit(ItemType &), TreeNode<ItemType> *tree) const;
    void inorder(void visit(ItemType &), TreeNode<ItemType> *tree) const;
    void postorder(void visit(ItemType &), TreeNode<ItemType> *tree) const;

public:
    BinaryNodeTree();
    BinaryNodeTree(const ItemType &rootItem);
    BinaryNodeTree(const ItemType &rootItem, const BinaryNodeTree<ItemType> *leftTree, const BinaryNodeTree<ItemType> *rightTree);
    BinaryNodeTree(const BinaryNodeTree<ItemType> &tree);
    ~BinaryNodeTree();
    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;
    ItemType getRootData() const;
    void setRootData(const ItemType &anItem);
    bool add(const ItemType &newItem);
    bool remove(const ItemType &anItem);
    void clear();
    ItemType getEntry(const ItemType &anItem) const;
    bool contains(const ItemType &anEntry) const;
    void replace(const ItemType& anEntry, const ItemType& newEntry);

    void preorderTraverse(void visit(ItemType &)) const;
    void inorderTraverse(void visit(ItemType &)) const;
    void postorderTraverse(void visit(ItemType &)) const;
};

#endif

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree()
{
    root = nullptr;
}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType &rootItem)
{
    root = new TreeNode<ItemType>(rootItem);
}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType &rootItem, const BinaryNodeTree<ItemType> *leftTree, const BinaryNodeTree<ItemType> *rightTree)
{
    root = new TreeNode<ItemType>(rootItem, copyTree(leftTree->root), copyTree(rightTree->root));
}

template <class ItemType>
TreeNode<ItemType> *BinaryNodeTree<ItemType>::copyTree(const TreeNode<ItemType> *node) const
{
    TreeNode<ItemType> *newNode = nullptr;

    if (node != nullptr)
    {
        newNode = new TreeNode<ItemType>(node->getItem());
        newNode->setLeft(copyTree(node->getLeft()));
        newNode->setRight(copyTree(node->getRight()));
    }

    return newNode;
}

template <class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(TreeNode<ItemType> *tree)
{
    if (tree != nullptr)
    {
        destroyTree(tree->getLeft());
        destroyTree(tree->getRight());
        delete tree;
        tree = nullptr;
    }
}

template <class ItemType>
int BinaryNodeTree<ItemType>::getHeightRecursive(const TreeNode<ItemType> *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + std::max(getHeightRecursive(node->getLeft()), getHeightRecursive(node->getRight()));
    }
}

template <class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesRecursive(const TreeNode<ItemType> *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + getNumberOfNodesRecursive(node->getLeft()) + getNumberOfNodesRecursive(node->getRight());
    }
}

template <class ItemType>
TreeNode<ItemType> *BinaryNodeTree<ItemType>::balancedAdd(TreeNode<ItemType> *tree, TreeNode<ItemType> *newNode)
{
    if (tree == nullptr)
    {
        return newNode;
    }
    else
    {
        TreeNode<ItemType> *left = tree->getLeft();
        TreeNode<ItemType> *right = tree->getRight();

        if (getHeightRecursive(left) > getHeightRecursive(right))
        {
            right = balancedAdd(right, newNode);
            tree->setRight(right);
        }
        else
        {
            left = balancedAdd(left, newNode);
            tree->setLeft(left);
        }
        return tree;
    }
}

template <class ItemType>
TreeNode<ItemType> *BinaryNodeTree<ItemType>::findNode(TreeNode<ItemType> *tree, const ItemType &target) const
{
    if (tree == nullptr)
    {
        return nullptr;
    }
    else if (tree->getItem() == target)
    {
        return tree;
    }
    else
    {
        TreeNode<ItemType> *result = findNode(tree->getLeft(), target);
        if (result == nullptr)
        {
            result = findNode(tree->getRight(), target);
        }
        return result;
    }
}

template<class ItemType>
TreeNode<ItemType>* BinaryNodeTree<ItemType>::removeRecursive(TreeNode<ItemType>* tree, const ItemType& anItem) {
    if (tree == nullptr) {
        return nullptr;
    }

    if (tree->getItem() == anItem) {
        if (tree->isLeaf()) {
            delete tree;
            tree = nullptr;
            return nullptr;
        }

        if (tree->getLeft() == nullptr) {
            TreeNode<ItemType>* temp = tree->getRight();
            delete tree;
            return temp;
        } else if (tree->getRight() == nullptr) {
            TreeNode<ItemType>* temp = tree->getLeft();
            delete tree;
            return temp;
        } else {
            TreeNode<ItemType>* successor = tree->getRight();
            while (successor != nullptr && successor->getLeft()) {
                successor = successor->getLeft();
            }
            tree->setItem(successor->getItem());
            tree->setRight(removeRecursive(tree->getRight(), successor->getItem()));
        }

    } else {
        tree->setLeft(removeRecursive(tree->getLeft(), anItem));
        tree->setRight(removeRecursive(tree->getRight(), anItem));
    }
    return tree;
}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType> &tree)
{
    if (tree != nullptr && tree.root != nullptr)
        root = copyTree(tree.root);
}

template <class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
    clear();
}

template <class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
    return root == nullptr;
}

template <class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
    return getHeightRecursive(root);
}

template <class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
    return getNumberOfNodesRecursive(root);
}

template <class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const
{
    return root->getItem();
}

template <class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType &newItem)
{
    if (root == nullptr)
    {
        root = new TreeNode<ItemType>(newItem);
    }
    else
    {
        root->setItem(newItem);
    }
}

template <class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType &newItem)
{
    TreeNode<ItemType> *newNode = new TreeNode<ItemType>(newItem);
    root = balancedAdd(root, newNode);

    return true;
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& anItem) {
    root = removeRecursive(root, anItem);

    return root != nullptr;
}

template <class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
    destroyTree(root);
    root = nullptr;
}

template <class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType &anEntry) const
{
    TreeNode<ItemType>* node = findNode(root, anEntry);

    if (node == nullptr) {
        throw std::logic_error("There is no entry found with the given entry.");
    }

    return node->getItem();
}

template <class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType &anItem) const
{
    return findNode(root, anItem) != nullptr;
}

template <class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType &)) const
{
    preorder(visit, root);
}

template <class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType &), TreeNode<ItemType> *tree) const
{
    if (tree != nullptr)
    {
        ItemType item = tree->getItem();
        preorder(visit, tree->getLeft());
        preorder(visit, tree->getRight());
    }
}

template <class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType &)) const
{
    inorder(visit, root);
}

template <class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType &), TreeNode<ItemType> *tree) const
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
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType &)) const
{
    postorder(visit, root);
}

template <class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType &), TreeNode<ItemType> *tree) const
{
    if (tree != nullptr)
    {
        postorder(visit, tree->getLeft());
        postorder(visit, tree->getRight());
        ItemType item = tree->getItem();
        visit(item);
    }
}
template <class ItemType>
void BinaryNodeTree<ItemType>::replace(const ItemType& anEntry, const ItemType& newEntry) {
    TreeNode<ItemType>* nodeToReplace = findNode(root, anEntry);

    if (nodeToReplace == nullptr) {
        add(newEntry);
    } else {
        nodeToReplace->setItem(newEntry);
    }
}