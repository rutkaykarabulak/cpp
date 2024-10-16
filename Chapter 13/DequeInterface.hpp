/** @file DequeInterface.hpp
 * ADT Deque.
 */

#ifndef DequeInterface_hpp
#define DequeInterface_hpp

template<class ItemType>
class DequeInterface {
public:
    /** Sees whether this queue is empty.
    @return True if the queue is empty, or false if not. */
    virtual bool isEmpty() const = 0;
    /** Adds a new entry to the back of this queue.
    @post If the operation was successful, newEntry is at the
    back of the queue.
    @param newEntry The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
    virtual bool enqueue(const ItemType& newEntry) = 0;
    /** Adds a new entry to the front of this queue.
    @post If the operation was successful, newEntry is at the
    front of the queue.
    @param newEntry The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
    virtual bool enqueueFront(const ItemType& newEntry) = 0;
    /** Removes the front of this queue.
    @post If the operation was successful, the front of the queue
    has been removed.
    @return True if the removal is successful or false if not. */
    virtual bool dequeue() = 0;
    /** Removes the back of this queue.
    @post If the operation was successful, the back of the queue
    has been removed.
    @return True if the removal is successful or false if not. */
    virtual bool dequeueBack() = 0;
    /** Returns the front of this queue.
    @pre The queue is not empty.
    @post The front of the queue has been returned, and the
    queue is unchanged.
    @return The front of the queue. */
    virtual ItemType peek() const = 0;
    /** Returns the back of this queue.
    @pre The queue is not empty.
    @post The front of the queue has been returned, and the
    queue is unchanged.
    @return The front of the queue. */
    virtual ItemType peekBack() const = 0;
};
#endif