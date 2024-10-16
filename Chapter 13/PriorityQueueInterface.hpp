/** @file PriorityQueueInterface.hpp 
 * ADT Prioriy queue.
*/

#ifndef PriorityQueueInterface_hpp
#define PriorityQueueInterface_hpp

template<class ItemType>
class PriorityQueueInterface {
public:
        /** Sees whether this queue is empty.
    @return True if the queue is empty, or false if not. */
    virtual bool isEmpty() const = 0;
    /** Adds a new entry to the back of this queue.
    @post If the operation was successful, newEntry is at the
    back of the queue.
    @param newEntry The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
    virtual bool add(const ItemType& newEntry) = 0;
    /** Removes the front of this queue.
    @post If the operation was successful, the front of the queue
    has been removed.
    @return True if the removal is successful or false if not. */
    virtual bool remove() = 0;
    /** Returns the front of this queue.
    @pre The queue is not empty.
    @post The front of the queue has been returned, and the
    queue is unchanged.
    @return The front of the queue. */
    virtual ItemType peek() const = 0;
};
#endif