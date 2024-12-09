/** @file BSTDictionary.cpp
 * BST based implementation of ADT dictionary.
 */

#ifndef BSTDictionary_cpp
#define BSTDictionary_cpp

#include "./DictionaryInterface.hpp"
#include "../Chapter 16/BinarySearchTree.cpp"
#define throw(...)

template<class KeyType, class ItemType>
class BSTDictionary: public DictionaryInterface<KeyType,ItemType>{
private:
    BinarySearchTree<MapEntry<KeyType,ItemType>>* tree;
public:
    BSTDictionary();
    BSTDictionary(const BSTDictionary<KeyType, ItemType>& dict);
    virtual ~BSTDictionary();
    bool isEmpty() const;
    int getNumberOfItems() const;
    bool add(const KeyType& newKey, const ItemType& newItem);
    bool remove(const KeyType& key);
    void clear();
    ItemType getItem(const KeyType& key) const throw(NotFoundException);
    bool contains(const KeyType& key) const;
    void traverse(void visit(const ItemType &)) const;
};
#endif

template<class KeyType, class ItemType>
BSTDictionary<KeyType, ItemType>::BSTDictionary() {
    tree = new BinarySearchTree<MapEntry<KeyType, ItemType>>();
}

template<class KeyType, class ItemType>
BSTDictionary<KeyType, ItemType>::~BSTDictionary() {
    clear();
}

template<class KeyType, class ItemType>
BSTDictionary<KeyType, ItemType>::BSTDictionary(const BSTDictionary<KeyType, ItemType>& dict) {
    tree = new BinarySearchTree<MapEntry<KeyType, ItemType>>();
    tree->copyTree(dict->tree);
}

template<class KeyType, class ItemType>
bool BSTDictionary<KeyType, ItemType>::isEmpty() const {
    return tree->isEmpty();
}

template<class KeyType, class ItemType>
int BSTDictionary<KeyType, ItemType>::getNumberOfItems() const {
    return tree->getNumberOfNodes();
}

template<class KeyType, class ItemType>
bool BSTDictionary<KeyType, ItemType>::add(const KeyType& newKey, const ItemType& newItem) {
    return tree->add(MapEntry<KeyType, ItemType>(newKey, newItem));
}

template<class KeyType, class ItemType>
bool BSTDictionary<KeyType, ItemType>::remove(const KeyType& key) {
    return tree->remove(MapEntry<KeyType, ItemType>(key, ItemType()));
}

template<class KeyType, class ItemType>
void BSTDictionary<KeyType, ItemType>::clear() {
    tree->clear();
}

template<class KeyType, class ItemType>
bool BSTDictionary<KeyType, ItemType>::contains(const KeyType& key) const{
    return tree->contains(MapEntry<KeyType, ItemType>(key, ItemType()));
}

template<class KeyType, class ItemType>
void BSTDictionary<KeyType, ItemType>::traverse(void visit(const ItemType &)) const {
    // do nothing so far
}

template<class KeyType, class ItemType>
ItemType BSTDictionary<KeyType, ItemType>::getItem(const KeyType& key) const throw(NotFoundException) {
    // Search for the MapEntry with the specified key
    MapEntry<KeyType, ItemType> searchEntry(key, ItemType());
    if (tree->contains(searchEntry)) {
        // Get the actual MapEntry object from the tree
        MapEntry<KeyType, ItemType> foundEntry = tree->getEntry(searchEntry);
        return foundEntry.getItem();
    } else {
        throw NotFoundException("Key not found in dictionary.");
    }
}
