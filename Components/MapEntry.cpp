/** @file MapEntry.cpp
 * Object that represents map entry. It contains key and item.
 */

#ifndef MapEntry_cpp
#define MapEntry_cpp
template<class KeyType, class ItemType>
class MapEntry {
private:
    KeyType key;
    ItemType item;
protected:
    void setKey(const KeyType& newKey);
public:
    MapEntry();
    MapEntry(KeyType key, ItemType item);
    ~MapEntry();
    KeyType getKey() const;
    ItemType getItem() const;
    void setItem(const ItemType& newItem);
    
    bool operator==(const MapEntry<KeyType, ItemType>& rightHandItem) const;
    bool operator>(const MapEntry<KeyType, ItemType>& rightHandItem) const;
};
#endif

template<class KeyType, class ItemType>
MapEntry<KeyType, ItemType>::MapEntry() : key(KeyType()), item(ItemType()) {}

template<class KeyType, class ItemType>
MapEntry<KeyType, ItemType>::MapEntry(KeyType key, ItemType item) : key(key), item(item) {}

template<class KeyType, class ItemType>
MapEntry<KeyType, ItemType>::~MapEntry() {}

template<class KeyType, class ItemType>
KeyType MapEntry<KeyType, ItemType>::getKey() const {
    return key;
}

template<class KeyType, class ItemType>
ItemType MapEntry<KeyType, ItemType>::getItem() const {
    return item;
}

template<class KeyType, class ItemType>
void MapEntry<KeyType, ItemType>::setItem(const ItemType& newItem) {
    item = newItem;
}

template<class KeyType, class ItemType>
void MapEntry<KeyType, ItemType>::setKey(const KeyType& newKey) {
    key = newKey;
}

template<class KeyType, class ItemType>
bool MapEntry<KeyType, ItemType>::operator==(const MapEntry<KeyType, ItemType>& rightHandItem) const {
    return key == rightHandItem.key;
}

template<class KeyType, class ItemType>
bool MapEntry<KeyType, ItemType>::operator>(const MapEntry<KeyType, ItemType>& rightHandItem) const {
    return key > rightHandItem.key;
}
