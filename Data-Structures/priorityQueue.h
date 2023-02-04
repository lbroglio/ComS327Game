#ifndef PRI_QUEUE_H
#define PRI_QUEUE_H

/**
 * @brief Stores an entry in a priority queue representing a spot on the board
 * 
 */
typedef struct queueEntry{
    int rowNum;
    int colNum;
    int  dist;
    int id;
    int heapAd;
    char charHere;
    int prevId;


}queueEntry_t;

/**
 * @brief Struct representing a priority queue backed by a min heap
 * 
 */
typedef struct queue{
    queueEntry_t* heapArr; 
    queueEntry_t* storageArr;
    int size;
}queue_t;


/**
 * @brief Creates a new queue at the given memory address
 * 
 * @param s The memory address of the struct
 * @param queueSize The number of maximum entries for the queue
 */
void queueInit(queue_t* s, int queueSize);

/**
 * @brief Createa a new queue entry
 * 
 * @param rowNum Which row the space this entry represents is at 
 * @param colNum Which column the space this entry represents is at 
 * @param charAt The char at the location this represents
 * @return The created queue entry
 */
queueEntry_t queueEntryInit(int rowNum, int colNum, char charAt);

/**
 * @brief Returns the minmum value of the queue without removing it
 * 
 * @param s Pointer to the queue to get minmum from
 * @return The extracted entry
 */
queueEntry_t peekMin(queue_t* s);

/**
 * @brief Returns the minmum value of the queue and removes it 
 * 
 * @param s Pointer to the queue to get minmum from
 * @return The extracted entry
 */
queueEntry_t extractMin(queue_t* s);

/**
 * @brief Decreases the priority of a given entry in the queue
 * 
 * @param s Pointer to the queue to decrease the entry in
 * @param toDecrease The entry to decrease
 * @param newPriority The number to change the priority to 
 * @return 0 on sucess other on fail
 */
int decreasePriority(queue_t* s,queueEntry_t toDecrease, int newPriority);

/**
 * @brief Adds a new entry to the queue 
 * 
 * @param s The queue to add to 
 * @param toAdd The entry to add to the queue
 * @param priority The priority of this entry
 */
void addWithPriority(queue_t* s, queueEntry_t toAdd, int priority);

/**
 * @brief Gets the size of the queue
 * 
 * @param s Pointer to the queue to get the size of
 * @return The size of the queue
 */
int size(queue_t* s);

#endif