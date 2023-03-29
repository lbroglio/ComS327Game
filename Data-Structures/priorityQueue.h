#ifndef PRI_QUEUE_H
#define PRI_QUEUE_H

/**
 * @brief Interface for items that possess an ID function. Used by the queue
 */
class IDable{
    public:
        /** Gets the ID of the IDable object*/
        virtual int getID() = 0; 
        /**Creates a clone of the IDable object*/
        virtual IDable* clone() = 0;
        /**Virtual destructor for IDable*/
        virtual ~IDable(){}
};


/**
 * @brief Stores an entry in a priority queue representing a spot on the board
 * 
 */
struct QueueEntry{
    /**Data stored in this entry*/
    IDable* data;
    /**The priority this entry is at*/
    int  priority;
    /**The id of the data in this entry*/
    int id;
    /**
     * @brief Constructor for a Queue Entry
     * 
     * @param data Pointer to the data to create an entry for. The data will be copied
     * @param priority The starting priority for this entry
     * 
     * @return The created entry 
     */
    QueueEntry(IDable* data, int priority);
    //ADD DOC
    //QueueEntry();

    //Saved just in case
    //~QueueEntry(){}
    //QueueEntry operator=(const QueueEntry &p);
};


/**
 * @brief Class representing a priority queue backed by a min heap
 * 
 */
class Queue{
    public:
        /**
         * @brief Constructor for a queue object
         * 
         * @param size The number of maximum entries for the queue
         */
        Queue(int size);

        /**
         * @brief Destroy the Queue object
         * 
         */
        ~Queue();

        /**
         * @brief Returns the minmum value of the queue without removing it
         * 
         * @param s Pointer to the queue to get minmum from
         * @return The extracted entry
         */
        IDable* peekMin(){return (heapArr[0].data);}

        /**
         * @brief Returns the minmum value of the queue and removes it 
         * 
         * @return The extracted entry
         */
        IDable* extractMin();

        /**
         * @brief Returns the minmum value of the queue and removes it. Also sets its priority to the given integer pointer
         * 
         * @param priority The location to store the extracted entries priority
         * @return The extracted entry
         */
        IDable* extractMinWithPri(int* priority);

        /**
         * @brief Decreases the priority of a given entry in the queue
         * 
         * @param toDecrease The entry to decrease
         * @param newPriority The number to change the priority to 
         * @return 0 on sucess other on fail
         */
        int decreasePriority(IDable* toDecrease, int newPriority);

        /**
         * @brief Adds a new entry to the queue 
         * 
         * @param toAdd The entry to add to the queue
         * @param priority The priority of this entry
         */
        void addWithPriority(IDable* toAdd, int priority);

        /**
         * @brief Checks to see if a given data is currently in the queue
         * 
         * @param toCheck The data to check
         * @return 1 if it is in the queue. 0 if it isnt
         */
        int checkInQueue(IDable* toCheck);
        /**
         * @brief Gets the size of the queue
         * 
         * @return The size of the queue
         */
        int getSize(){return this->size;};

    private:
        /**The array of entries representing conisting of the heap which backs the queue*/
        QueueEntry* heapArr; 
        /**Array which stores the location of everything in the queue by ID*/
        int* locArr;
        /**The maximum possible index in the location array*/
        int maxIndex;
        /**The number of entries in this queue */
        int size;
    
    /**
     * @brief Swaps the entries at two locations within the heap
     * 
     * @param s Pointer to the queue holding the heap to swap the nodes in
     * @param x The location of the first entry
     * @param y The location of the second entry
     */
    friend void swap(Queue* s, int x, int y);
    /**
     * @brief Moves an entry up to restore the heap order property
     * 
     * @param s Pointer to the heap to operate in
     * @param currentLoc The location of entry to start with
     */
    friend void percolateUp(Queue* s, int currentLoc);
    /**
     * @brief Moves an entry down to restore the heap order property
     * 
     * @param s Pointer to the queue with the heap to operate in
     * @param currentLoc The location of entry to start with
     */
    friend void percolateDown(Queue* s, int currentLoc);
    
    //int dataSize;
    //int (*idFunc)(void*);

};




#endif