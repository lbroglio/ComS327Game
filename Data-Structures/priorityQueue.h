#ifndef PRI_QUEUE_H
#define PRI_QUEUE_H

#include"../Map/map.h"

/**
 * @brief Stores an entry in a priority queue representing a spot on the board
 * 
 */
typedef struct queueEntry{
    void* data;
    int  priority;
    int id;

}queueEntry_t;

/**
 * @brief Struct representing a priority queue backed by a min heap
 * 
 */
typedef struct queue{
    queueEntry_t* heapArr; 
    int* locArr;
    int maxIndex;
    int size;
    int dataSize;
    int (*idFunc)(void*);

}queue_t;


/**
 * @brief Creates a new queue at the given memory address
 * 
 * @param s The memory address of the struct
 * @param queueSize The number of maximum entries for the queue
 */
void queueInit(queue_t* s, int queueSize,int dataSize, int (*idFunc)(void*));

/**
 * @brief Createa a new queue entry
 * 
 * @param data The data to create an entry for
 * @param dist The starting distance from the source
 * @return The created entry 
 */
queueEntry_t queueEntryInit(void* data,int dataSize, int priority, int (*idfunc)(void*));

/**
 * @brief Returns the minmum value of the queue without removing it
 * 
 * @param s Pointer to the queue to get minmum from
 * @return The extracted entry
 */
void* queuePeekMin(queue_t* s);

/**
 * @brief Returns the minmum value of the queue and removes it 
 * 
 * @param s Pointer to the queue to get minmum from
 * @return The extracted entry
 */
void* queueExtractMin(queue_t* s);

/**
 * @brief Decreases the priority of a given entry in the queue
 * 
 * @param s Pointer to the queue to decrease the entry in
 * @param toDecrease The entry to decrease
 * @param newPriority The number to change the priority to 
 * @return 0 on sucess other on fail
 */
int queueDecreasePriority(queue_t* s,void* toDecrease, int newPriority);

/**
 * @brief Adds a new entry to the queue 
 * 
 * @param s The queue to add to 
 * @param toAdd The entry to add to the queue
 * @param priority The priority of this entry
 */
void queueAddWithPriority(queue_t* s, void* toAdd, int priority);

/**
 * @brief Checks to see if a given data is currently in the queue
 * 
 * @param s - The queue to check for the data
 * @param toCheck The data to check
 * @return 1 if it is in the queue. 0 if it isnt
 */
int checkInQueue(queue_t* s, void* toCheck);
/**
 * @brief Gets the size of the queue
 * 
 * @param s Pointer to the queue to get the size of
 * @return The size of the queue
 */
int queueSize(queue_t* s);

/**
 * @brief Destroys a queue freeing the memory in it
 * 
 * @param s The queue to destroy
 */
void queueDestroy(queue_t* s);




#endif