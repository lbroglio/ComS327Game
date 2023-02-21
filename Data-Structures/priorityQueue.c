#include<stdlib.h>
#include<string.h>
#include"priorityQueue.h"
#include"../Map/map.h"


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

    void* xVoid = malloc(sizeof(xEntry));
    void* yVoid = malloc(sizeof(yEntry));
    memcpy(xVoid,xEntry.data,s->dataSize);
    memcpy(yVoid,yEntry.data,s->dataSize);

    s->locArr[s->idFunc(xVoid)] = y;
    s->locArr[s->idFunc(yVoid)] = x;

    s->heapArr[x] = yEntry;
    s->heapArr[y] = xEntry;    

    free(xVoid);
    free(yVoid);
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


    while (currentLoc > 0 &&  current.priority < parent.priority) {  
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
            if (child.priority > s->heapArr[childLoc + 1].priority){
                childLoc += 1;
                child = s->heapArr[childLoc];
            }
            
        }

        //Swap id necessary
        if (current.priority > child.priority){
            swap(s,currentLoc,childLoc);
            
        }

        //Advance to the next node 
        currentLoc = childLoc;
        childLoc = (2 * currentLoc) + 1;
 }

}

void queueInit(queue_t* s, int queueSize,int dataSize, int (*idFunc)(void*)){
    s->heapArr = malloc(sizeof(queueEntry_t) * queueSize);
    s->locArr = malloc(sizeof(int) * queueSize);
    s->idFunc = idFunc;
    s->maxIndex = queueSize - 1;
    s->dataSize = dataSize;

    for(int i =0; i < queueSize; i++){
        s->locArr[i] = -1;
    }
    s->size =0;
}


queueEntry_t queueEntryInit(void* data,int dataSize, int priority, int (*idfunc)(void*)){
    queueEntry_t toReturn;
    toReturn.data = malloc(dataSize);
    memcpy(toReturn.data,data,dataSize);

    toReturn.id = idfunc(data);
    toReturn.priority = priority;

    return toReturn;
}


void* queuePeekMin(queue_t* s){
    queueEntry_t peeked = s->heapArr[0];
    void* toReturn = malloc(s->dataSize);
    memcpy(toReturn,peeked.data,s->dataSize);

    return toReturn;
}


void* queueExtractMin(queue_t* s){
    //Extracts the minmum value
    queueEntry_t extracted = s->heapArr[0];
    
    void* toReturn = malloc(s->dataSize);
    memcpy(toReturn,extracted.data,s->dataSize);

    //Puts the last item to the front
    swap(s,0,s->size-1);
    s->locArr[s->idFunc(toReturn)] = -1;
    s->size -= 1;

    //Restores heap order
    percolateDown(s,0);

    return toReturn;
}


int queueDecreasePriority(queue_t* s,void* toDecrease, int newPriority){

    int getAt = s->locArr[s->idFunc(toDecrease)];

    s->heapArr[getAt].priority = newPriority;
    percolateUp(s,getAt);

    return 0;
}


void queueAddWithPriority(queue_t* s, void* toAdd, int priority){
    queueEntry_t newEntry = queueEntryInit(toAdd, s->dataSize, priority,s->idFunc);

    s->heapArr[s->size] =  newEntry;
    s->locArr[s->idFunc(toAdd)] = s->size;

    percolateUp(s,s->size);

    s->size += 1;
}

int checkInQueue(queue_t* s, void* toCheck){
    int id = s->idFunc(toCheck);

    if(id == -1){
        return 0;
    }
    else if(id < 0 || id > s->maxIndex || s->locArr[id] == -1){
        return 0;
    }
    else{
        return 1;
    }

}

int queueSize(queue_t* s){
    return s->size;
}

void queueDestroy(queue_t* s){
    free(s->heapArr);
    free(s->locArr);
    s->size = 0;
}

