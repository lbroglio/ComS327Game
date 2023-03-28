#include<iostream>
#include<string>
#include "./Data-Structures/priorityQueue.h"
#include"./Map/map.h"


class qTest : public IDable{
    public:
        int id;
        std::string name;

        qTest(std::string name, int id){
            this->name = name;
            this->id = id;
        }
        qTest(){
            this->id = -1;
            this->name = "Blank";
        }

        ~qTest(){}

        int getID(){return this->id;};
        qTest* clone()
        {
                qTest* temp = new qTest(this->name,this->id);
                return temp;
        };

};

int main(int argc, char* argv[]){
    Queue tQueue = Queue(1482);
    //qTest entries[100];
    int tracker = 0;
    for(int i=1; i< 20; i++){
        for(int j=1; j< 79; j++){
            Point temp = Point(i,j);
            tQueue.addWithPriority(&temp,tracker);
            tracker += 1;
        }
    }


    int size = tQueue.getSize();
    int track = 1481;
    std::cout << convertID(1482) << "\n";
    std::cout << convertID(1481) << "\n";
    

    while(size != 0 && 0 == 1){
        IDable* tempIDable = tQueue.extractMin();
        Point* currEntry = dynamic_cast<Point*>(tempIDable);

        std::cout << *currEntry << " \t";
        delete currEntry;

        size = tQueue.getSize();

        if(track % 2 == 0){
            Point temp = Point(convertID(track));
            if(tQueue.checkInQueue(&temp) != 0){
                tQueue.decreasePriority(&temp,0);
            }
        }
        track -= 1;
    }

    std::cout << std::endl;


}