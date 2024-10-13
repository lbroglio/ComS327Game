#ifndef POINT_H
#define POINT_H

#include"../Data-Structures/priorityQueue.h"

/**
 * @brief Stores a point on the map. Also used as unit vectors sometimes
 * 
 */
struct Point : public IDable{
    /**The row this point is in*/
    int rowNum;
    /**The column this point is in*/
    int colNum;
    /**
     * @brief Converts a point to an ID and then downshifts it to be used as its location in arrays.
     * Invalid points return -1
     * 
     * @param toConvert The point to get the ID for
     * @return The downshifted ID
     */
    int getID();

    /**
     * @brief Creates a copy of the point object.
     * Includes memory allocation returned to the user
     * 
     * @return A pointer to the created copy
     */
    Point* clone();
    /**
     * @brief Creates a new point struct with the given row and column
     * 
     * @param row The row the point is in
     * @param col The column the point is in
     * @return The newly created point
     */
    Point(int row, int col);
    /**
     * @brief Construct a new Point object
     * Default Constructor
     */
    Point();
    
    /**
    * @brief Converts a given point to its NONDOWNSHIFTEDinteger id
    * 
    * @param toConvert The point to convert
    * @return The ID 
    */
    int convertPoint(){ return (rowNum * 80) + colNum;}
};
 

 #endif