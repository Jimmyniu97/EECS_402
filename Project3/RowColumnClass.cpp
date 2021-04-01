#include <iostream>
#include "constants.h"
#include "RowColumnClass.h"
using namespace std;

//define class RowColumnClass functions
RowColumnClass::RowColumnClass() {
    rowIndex = DEFAULT_LOCATION;
    columnIndex = DEFAULT_LOCATION;
}

RowColumnClass::RowColumnClass(int inRow, int inCol) {
    rowIndex = inRow;
    columnIndex = inCol;
}

void RowColumnClass::setRowCol(int inRow, int inCol) {
    rowIndex = inRow;
    columnIndex = inCol;
}

void RowColumnClass::setRow(int inRow) {
    rowIndex = inRow;
}

void RowColumnClass::setCol(int inCol) {
    columnIndex = inCol;
}

int RowColumnClass::getRow() {
    return rowIndex;
}

int RowColumnClass::getCol() {
    return columnIndex;
}

void RowColumnClass::addRowColTo(RowColumnClass &inRowCol) {
    rowIndex = rowIndex + inRowCol.rowIndex;
    columnIndex = columnIndex + inRowCol.columnIndex;
}

void RowColumnClass::printRowCol() {
    cout<<"["<<rowIndex<<", "<<columnIndex<<"]";
}