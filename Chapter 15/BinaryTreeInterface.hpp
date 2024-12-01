/** @file BinaryTreeInterface.hpp
 * ADT binary tree.
 */

#ifndef BinaryTreeInterface_hpp
#define BinaryTreeInterface_hpp

template <class ItemType>
class BinaryTreeInterface
{
public:
    /** Tests whether this binary tree is empty.
    @return True if the binary tree is empty, or false if not. */
    virtual bool isEmpty() const = 0;
    /** Gets the height of this binary tree.
     * @return The height of the binary tree. */
    virtual int getHeight() const = 0;
    /** Gets the number of nodes in this binary tree. 
     * @return The number of nodes in the binary tree. */
    virtual int getNumberOfNodes() const = 0;
    /** Gets the data that is in the root of this binary tree.
    @pre The binary tree is not empty.
    @post The root’s data has been returned, and the binary tree is unchanged. 
    @return The data in the root of the binary tree. */
    virtual ItemType getRootData() const = 0;
    /** Sets the given item to the root's item */
    virtual void setRootData(const ItemType &newItem) = 0;
    /** Adds a new node containing the given data to this binary tree. 
    @param newData The data for the new node.
    @post The binary tree contains a new node.
    @return True if the addition is successful, or false not. */
    virtual bool add(const ItemType &newItem) = 0;
    /** Removes the node containing the given data item from this binary tree. 
    @param data The data value to remove from the binary tree.
    @return True if the removal is successful, or false not. */
    virtual bool remove(const ItemType &anItem) = 0;
    /** Removes all nodes from this binary tree. */
    virtual void clear() = 0;
    /** Gets a specific entry in this binary tree.
    @post The desired entry has been returned, and the binary tree
    is unchanged. If no such entry was found, an exception is thrown. 
    @param anEntry The entry to locate.
    @return The entry in the binary tree that matches the given entry. */
    virtual ItemType getEntry(const ItemType &anEntry) const = 0;
    /** Tests whether a given entry occurs in this binary tree.
    @post The binary search tree is unchanged.
    @param anEntry The entry to find.
    @return True if the entry occurs in the tree, or false if not. */
    virtual bool contains(const ItemType &anEntry) const = 0;

    /** Traverses this binary tree in preorder (inorder, postorder) and calls the function visit once for each node.
    @param visit A client-defined function that performs an operation on or with the data in each visited node. */
    virtual void preorderTraverse(void visit(ItemType &)) const = 0;
    virtual void inorderTraverse(void visit(ItemType &)) const = 0;
    virtual void postorderTraverse(void visit(ItemType &)) const = 0;
    
    /**
     * Replaces the anEntry with the given newEntry only if the anEntry exists. If does not, adds the newEntry to the ADT tree.
     */
    virtual void replace(const ItemType& anEntry, const ItemType& newEntry) = 0;
};

#endif