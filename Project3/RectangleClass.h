
#ifndef _RECTANGLECLASS_H
#define _RECTANGLECLASS_H
#include <string>
#include "RowColumnClass.h"
#include "ColorClass.h"
using namespace std;

class RectangleClass{
private:
    //create a RowColumnClass object that defines the start position
    //of the rectangle
    RowColumnClass startPosition;
    //create a RowColumnClass object that defines the end position
    //of the rectangle
    RowColumnClass endPosition;
    //create a ColorClass object that defines the color of rectangle
    ColorClass rectangle;
public:
    //Default constructor that takes upper left row, column and
    //lower right row and column of the rectangle
    RectangleClass(int startRow, int startCol, int endRow, int endCol);
    //function that set the rectangle object color
    void setColor(int optionColor);
    //return the position of the start row and column
    RowColumnClass getStartPosition();
    //return the position of the end row and column
    RowColumnClass getEndPosition();
    //return the rectangle object
    ColorClass getColor();
};

#endif
