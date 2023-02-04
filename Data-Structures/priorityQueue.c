#include<priorityQueue.h>


/**
 * @brief Swaps the entries at two locations within the heap
 * 
 * @param s Pointer to the queue holding the heap to swap the nodes in
 * @param x The location of the first entry
 * @param y The location of the second entry
 */
void swap(queue_t* s, int x, int y){
    queueEntry_t xEntry = s->heapArr[x];
    queueEntry_t yEntry = s->heapArr[y];

    s->storageArr[xEntry.id].heapAd = y;
    s->storageArr[yEntry.id].heapAd = x;

    s->heapArr[x] = yEntry;
    s->heapArr[y] = xEntry;    
}

/**
 * @brief Moves an entry up to restore the heap order property
 * 
 * @param s Pointer to the heap to operate in
 * @param currentLoc The location of entry to start with
 */
void percolateUp(queue_t* s, int currentLoc){
    //Gets location of the current nodes parents
    int parentLoc = (currentLoc - 1) / 2;

    //Gets entries for the current node and its parent
    queueEntry_t current = s->heapArr[currentLoc];
    queueEntry_t parent = s->heapArr[parentLoc];


    while (currentLoc > 0 &&  current.dist < parent.dist) {  
        //Swaps the current up
        swap(s,currentLoc,parentLoc);

        //Moves the current node to the parents location
        currentLoc = parentLoc;
        parentLoc = (currentLoc - 1) / 2;

        //Gets the entries
        current = s->heapArr[currentLoc];
        parent = s->heapArr[parentLoc];
    }
 
}

/**
 * @brief Moves an entry down to restore the heap order property
 * 
 * @param s Pointer to the queue with the heap to operate in
 * @param currentLoc The location of entry to start with
 */
void percolateDown(queue_t* s, int currentLoc){
    //Get first child
    int childLoc = (2 * currentLoc) + 1;

    //Gets the entry at the current location
    queueEntry_t current = s->heapArr[currentLoc];

    //While inside the array
    while (childLoc < s->size){
        //Get entry at the first child's location
        queueEntry_t child = s->heapArr[childLoc];

        //Check to see if second child is smaller
        if ((childLoc + 1) < s->size){
            if (child.dist > s->heapArr[childLoc + 1].dist){
                child = s->heapArr[childLoc + 1];
            }
            
        }

        //Swap id necessary
        if (current.dist > child.dist){
            swap(s,currentLoc,childLoc);
            
        }

        //Advance to the next node 
        currentLoc = childLoc;
        childLoc = (2 * current.id) + 1;
 }

}

void queueInit(queue_t* s, int queueSize){
    s->heapArr = malloc(sizeof(queueEntry_t) * queueSize);
    s->storageArr = malloc(sizeof(queueEntry_t) * queueSize);
    s->size =0;
}


queueEntry_t queueEntryInit(int rowNum, int colNum, int dist, char charHere){
    queueEntry_t toReturn;

    toReturn.rowNum = rowNum;
    toReturn.colNum = colNum;
    toReturn.id = (rowNum * 80) + colNum;
    toReturn.dist = dist;
    toReturn.charHere = charHere;

    return toReturn;
}


queueEntry_t peekMin(queue_t* s){
    return s->queueArr[0];
}


queueEntry_t extractMin(queue_t* s){
    //Extracts the minmum value
    queueEntry_t toReturn = s->heapArr[0];

    //Puts the last item to the front
    s->heapArr[0] = s->heapArr[s.size-1];
    s->size -= 1;

    //Restores heap order
    percolateDown(s,0);

    return toReturn;
}


int decreasePriority(queue_t* s,queueEntry_t toDecrease, int newPriority){
    int getAt = toDecrease.heapAd;

    percolateUp(s,getAt);
    return 0;
}


void addWithPriority(queue_t* s, queueEntry_t toAdd, int priority){
    toAdd.heapAd = s->size;
    s->heapArr[s->size] =  toAdd;
    s->storageArr[toAdd.id] = toAdd;

    percolateUp(s,s->size);

    s->size += 1;
}


int size(queue_t* s){
    return s->size;
}
