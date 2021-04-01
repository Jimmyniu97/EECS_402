#ifndef _ROWCOLUMNCLASS_H
#define _ROWCOLUMNCLASS_H
//declare class RowColumnClass to specify the pixel value in a image
class RowColumnClass{
private:
    int rowIndex;
    int columnIndex;
public:
    RowColumnClass();//default constructor
    //set the row& column values to corresponding values
    RowColumnClass(int inRow, int inCol);
    //set row and column values to the provided values
    void setRowCol(int inRow,int inCol);
    //set row value to the provided value
    void setRow(int inRow);
    //set column value to the provided value
    void setCol(int inCol);
    int getRow();//return row value
    int getCol();//return column value
    //add row and column index values in the input parameter
    // to the row and column index of the object
    void addRowColTo(RowColumnClass &inRowCol);
    //prints this object's attribute's in the format "[<row>,<col>]"
    void printRowCol();
};
#endif //PROJECT3_ROWCOLUMNCLASS_H
