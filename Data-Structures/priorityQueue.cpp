#include<stdlib.h>
#include<string.h>
#include"priorityQueue.h"
#include"../Map/map.h"


void swap(Queue* s, int x, int y){
    QueueEntry xEntry = s->heapArr[x];
    QueueEntry yEntry = s->heapArr[y];

    /*
    void* xVoid = malloc(sizeof(xEntry));
    void* yVoid = malloc(sizeof(yEntry));
    memcpy(xVoid,xEntry.data,s->dataSize);
    memcpy(yVoid,yEntry.data,s->dataSize);
    */

    s->locArr[xEntry.data.getID()] = y;
    s->locArr[yEntry.data.getID()] = x;

    s->heapArr[x] = yEntry;
    s->heapArr[y] = xEntry;    

    /*
    free(xVoid);
    free(yVoid);
    */
}

void percolateUp(Queue* s, int currentLoc){
    //Gets location of the current nodes parents
    int parentLoc = (currentLoc - 1) / 2;

    //Gets entries for the current node and its parent
    QueueEntry current = s->heapArr[currentLoc];
    QueueEntry parent = s->heapArr[parentLoc];


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

void percolateDown(Queue* s, int currentLoc){
    //Get first child
    int childLoc = (2 * currentLoc) + 1;

    //Gets the entry at the current location
    QueueEntry current = s->heapArr[currentLoc];

    //While inside the array
    while (childLoc < s->size){
        //Get entry at the first child's location
        QueueEntry child = s->heapArr[childLoc];

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

Queue::Queue(int size){
    heapArr = (QueueEntry*)malloc(sizeof(QueueEntry) * size);
    locArr = (int*)malloc(sizeof(int) * size);
    maxIndex = size - 1 ;

    //s->idFunc = idFunc;
    //s->dataSize = dataSize;

    for(int i =0; i < size; i++){
        locArr[i] = -1;
    }
    this->size =0;
}


QueueEntry::QueueEntry(IDable data, int priority){
    this->data = data;
    this->id = data.getID();
    this->priority = priority;

}

IDable Queue::extractMin(){
    //Extracts the minmum value
    QueueEntry extracted = heapArr[0];
    
    IDable toReturn = extracted.data;

    //Puts the last item to the front
    swap(this,0,size-1);
    locArr[toReturn.getID()] = -1;
    size -= 1;

    //Restores heap order
    percolateDown(this,0);

    return toReturn;
}

IDable Queue::extractMinWithPri(int* priority){
    //Extracts the minmum value
    QueueEntry extracted = heapArr[0];
    *priority = extracted.priority;
    
    IDable toReturn = extracted.data;

    //Puts the last item to the front
    swap(this,0,size-1);
    locArr[toReturn.getID()] = -1;
    size -= 1;

    //Restores heap order
    percolateDown(this,0);

    return toReturn;
}


int Queue::decreasePriority(IDable toDecrease, int newPriority){

    int getAt = locArr[toDecrease.getID()];

    heapArr[getAt].priority = newPriority;
    percolateUp(this,getAt);

    return 0;
}


void Queue::addWithPriority(IDable toAdd, int priority){
    QueueEntry newEntry = QueueEntry(toAdd, priority);

    heapArr[size] =  newEntry;
    locArr[toAdd.getID()] = size;

    percolateUp(this,size);

    size += 1;
}

int Queue::checkInQueue(IDable toCheck){
    int id = toCheck.getID();

    if(id == -1){
        return 0;
    }
    else if(id < 0 || id > maxIndex || locArr[id] == -1){
        return 0;
    }
    else{
        return 1;
    }

}

Queue::~Queue(){
    free(heapArr);
    free(locArr);
    size = 0;
}


