#include "constants.h"
#include "RowColumnClass.h"
#include "ColorClass.h"
#include "RectangleClass.h"
using namespace std;
//Default constructor
RectangleClass::RectangleClass(int startRow, int startCol, int endRow,
                               int endCol) {
    startPosition.setRowCol(startRow, startCol);
    endPosition.setRowCol(endRow, endCol);
}
//function that set the rectangle object color
void RectangleClass::setColor(int optionColor) {
    if (optionColor == COLOR_RED) {
        rectangle.setToRed();
    }
    else if (optionColor == COLOR_GREEN) {
        rectangle.setToGreen();
    }
    else if (optionColor == COLOR_BLUE) {
        rectangle.setToBlue();
    }
    else if (optionColor == COLOR_BLACK) {
        rectangle.setToBlack();
    }
    else if (optionColor == COLOR_WHITE) {
        rectangle.setToWhite();
    }
}

RowColumnClass RectangleClass::getStartPosition() {
    return startPosition;
}

RowColumnClass RectangleClass::getEndPosition() {
    return endPosition;
}

ColorClass RectangleClass::getColor() {
    return rectangle;
}