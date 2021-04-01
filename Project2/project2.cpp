#include<iostream>
using namespace std;
//
// Programmer: Yuefeng Niu
// Date: 10/10/20.
// Develop classes to represent color and images
//

const int COLOR_MAX = 1000;//default color max value
const int COLOR_MIN = 0;//default color min value
const int DEFAULT_LOCATION = -99999;//default row& column value
const int ROW_SIZE = 10;//default row size
const int COLUMN_SIZE = 18;//default column size

//declare class ColorClass to define information of a color
class ColorClass{
private:
    int amountOfRed;
    int amountOfGreen;
    int amountOfBlue;

    bool checkColorRange(int colorValue);
    int setToColor(int colorValue);
public:
    ColorClass();//default constructor
    //initialize RGB values
    ColorClass(int inRed, int inGreen, int inBlue);

    void setToBlack();//set color to black
    void setToRed();//set color to red
    void setToGreen();//set color to green
    void setToBlue();//set color to blue
    void setToWhite();//set color to white
    //set object to the provided RGB values
    bool setTo(int inRed, int inGreen, int inBlue);
    //set the color's component same as "inColor" input parameter
    bool setTo(ColorClass &inColor);
    //add color from input parameter
    bool addColor(ColorClass &rhs);
    //subtract color from input parameter
    bool subtractColor(ColorClass &rhs);
    //adjust brightness by multiply an input value
    bool adjustBrightness(double adjFactor);
    //print the component color values
    void printComponentValues();
};

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

//declare class ColorImageClass to restore information of an image
class ColorImageClass{
private:
    ColorClass Image[ROW_SIZE][COLUMN_SIZE];
    bool validRange(int val, int size);
public:
    ColorImageClass();//default constructor
    //initialize all image value to the provided value
    void initializeTo(ColorClass &inColor);
    //performs image-wide addition
    bool addImageTo(ColorImageClass &rhsImg);
    //set image's pixel values to the sum of the corresponding pixels
    bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd []);
    //set color value at specific location
    bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);
    //get color value at specific location
    bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);
    //print the contents of the image
    void printImage();
};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main(){
    ColorClass testColor;
    RowColumnClass testRowCol;
    RowColumnClass testRowColOther(111, 222);
    ColorImageClass testImage;
    ColorImageClass testImages[3];

    //Test some basic ColorClass operations...
    cout << "Initial: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setToBlack();
    cout << "Black: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setToGreen();
    cout << "Green: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.adjustBrightness(0.5);
    cout << "Dimmer Green: ";
    testColor.printComponentValues();
    cout << endl;

    //Test some basic RowColumnClass operations...
    cout << "Want defaults: ";
    testRowCol.printRowCol();
    cout << endl;

    testRowCol.setRowCol(2, 8);
    cout << "Want 2,8: ";
    testRowCol.printRowCol();
    cout << endl;

    cout << "Want 111, 222: ";
    testRowColOther.printRowCol();
    cout << endl;

    testRowColOther.setRowCol(4, 2);
    testRowCol.addRowColTo(testRowColOther);
    cout << "Want 6,10: ";
    testRowCol.printRowCol();
    cout << endl;

    //Test some basic ColorImageClass operations...
    testColor.setToRed();
    testImage.initializeTo(testColor);

    testRowCol.setRowCol(555, 5);
    cout << "Want: Color at [555,5]: Invalid Index!" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor)){
        testColor.printComponentValues();
    }
    else{
        cout << "Invalid Index!";
    }
    cout << endl;

    testRowCol.setRow(4);
    cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor)){
        testColor.printComponentValues();
    }
    else{
        cout << "Invalid Index!";
    }
    cout << endl;

    //Set up an array of images of different colors
    testColor.setToRed();
    testColor.adjustBrightness(0.25);
    testImages[0].initializeTo(testColor);
    testColor.setToBlue();testColor.adjustBrightness(0.75);
    testImages[1].initializeTo(testColor);testColor.setToGreen();
    testImages[2].initializeTo(testColor);

    //Modify a few individual pixel colors
    testRowCol.setRowCol(4, 2);
    testColor.setToWhite();
    testImages[1].setColorAtLocation(testRowCol, testColor);

    testRowCol.setRowCol(2, 4);
    testColor.setToBlack();
    testImages[2].setColorAtLocation(testRowCol, testColor);

    //Add up all images in testImages array and assign result
    // to the testImage image
    testImage.addImages(3, testImages);

    //Check some certain values
    cout << "Added values:" << endl;
    for (int colInd = 0; colInd < 8; colInd += 2){
        testRowCol.setRowCol(4, colInd);
        cout << "Color at ";
        testRowCol.printRowCol();
        cout << ": ";
        if (testImage.getColorAtLocation(testRowCol, testColor)){
            testColor.printComponentValues();
        }
        else{
            cout << "Invalid Index!";
        }
        cout << endl;
    }

    for (int rowInd = 0; rowInd < 8; rowInd += 2){
        testRowCol.setRowCol(rowInd, 4);
        cout << "Color at ";
        testRowCol.printRowCol();
        cout << ": ";
        if (testImage.getColorAtLocation(testRowCol, testColor)){
            testColor.printComponentValues();
        }
        else{cout << "Invalid Index!";
        }
        cout << endl;
    }

    cout << "Printing entire test image:" << endl;
    testImage.printImage();

    return 0;
};

#endif

//class ColorClass functions definition
ColorClass::ColorClass() {
    amountOfRed = COLOR_MAX;
    amountOfGreen = COLOR_MAX;
    amountOfGreen = COLOR_MAX;
}

//assign color value and clip if necessary
ColorClass::ColorClass(int inRed, int inGreen, int inBlue) {
    //assigning red color value
    if (inRed > COLOR_MAX){
        amountOfRed = COLOR_MAX;
    }
    else if(inRed < COLOR_MIN){
        amountOfRed = COLOR_MIN;
    }
    else{
        amountOfRed = inRed;
    }
    //assign green color value
    if (inGreen >COLOR_MAX){
        amountOfGreen = COLOR_MAX;
    }
    else if (inGreen < COLOR_MIN){
        amountOfGreen = COLOR_MIN;
    }
    else{
        amountOfGreen = inGreen;
    }
    //assign blue color value
    if (inBlue > COLOR_MAX){
        amountOfBlue = COLOR_MAX;
    }
    else if (inBlue < COLOR_MIN){
        amountOfBlue = COLOR_MIN;
    }
    else{
        amountOfBlue = inBlue;
    }
}

bool ColorClass::checkColorRange(int colorValue) {
    if (colorValue > COLOR_MAX || colorValue < COLOR_MIN){
        return false;
    }
    else{
        return true;
    }
}

int ColorClass::setToColor(int colorValue) {
    int returnVal;
    if (checkColorRange(colorValue)){
        returnVal = colorValue;
    }
    else if (colorValue > COLOR_MAX){
        returnVal = COLOR_MAX;
    }
    else{
        returnVal = COLOR_MIN;
    }
    return returnVal;
}

void ColorClass::setToBlack() {
    amountOfRed = COLOR_MIN;
    amountOfGreen = COLOR_MIN;
    amountOfBlue = COLOR_MIN;
}

void ColorClass::setToRed() {
    amountOfRed = COLOR_MAX;
    amountOfGreen = COLOR_MIN;
    amountOfBlue = COLOR_MIN;
}

void ColorClass::setToGreen() {
    amountOfRed = COLOR_MIN;
    amountOfGreen = COLOR_MAX;
    amountOfBlue = COLOR_MIN;
}

void ColorClass::setToBlue() {
    amountOfRed = COLOR_MIN;
    amountOfGreen = COLOR_MIN;
    amountOfBlue = COLOR_MAX;
}

void ColorClass::setToWhite() {
    amountOfRed = COLOR_MAX;
    amountOfGreen = COLOR_MAX;
    amountOfBlue = COLOR_MAX;
}

bool ColorClass::setTo(ColorClass &inColor) {
    amountOfRed = inColor.amountOfRed;
    amountOfGreen = inColor.amountOfGreen;
    amountOfBlue = inColor.amountOfBlue;
    return 0;
}

bool ColorClass::setTo(int inRed, int inGreen, int inBlue) {
    amountOfRed = setToColor(inRed);
    amountOfGreen = setToColor(inGreen);
    amountOfBlue = setToColor(inBlue);
    if (checkColorRange(inRed) && checkColorRange(inGreen) &&
        checkColorRange(inBlue)){
        return false;
    }
    return true;
}

bool ColorClass::addColor(ColorClass &rhs) {
    bool clipped;//return true if the color value was clipped
    clipped = setTo(int(amountOfRed + rhs.amountOfRed),
                    int(amountOfGreen + rhs.amountOfGreen),
                    int(amountOfBlue + rhs.amountOfBlue));
    return clipped;
}

bool ColorClass::subtractColor(ColorClass &rhs) {
    bool clipped;
    clipped = setTo(int(amountOfRed - rhs.amountOfRed),
                    int(amountOfGreen - rhs.amountOfGreen),
                    int(amountOfBlue - rhs.amountOfBlue));
    return clipped;
}

bool ColorClass::adjustBrightness(double adjFactor) {
    bool clipped;
    clipped = setTo(int(amountOfRed * adjFactor),
                    int(amountOfGreen * adjFactor),
                    int(amountOfBlue * adjFactor));
    return clipped;
}

void ColorClass::printComponentValues() {
    cout<<"R: "<<amountOfRed<<" G: "<<amountOfGreen<<" B: "<<amountOfBlue;
}

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

//declare class ColorImageClass functions
ColorImageClass::ColorImageClass() {
    for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COLUMN_SIZE; j++){
            Image[i][j].setToBlack();
        }
    }
}

void ColorImageClass::initializeTo(ColorClass &inColor) {
    for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COLUMN_SIZE; j++){
            Image[i][j].setTo(inColor);
        }
    }
}

bool ColorImageClass::validRange(int val, int size) {
    if (val <0 || val > size -1){
        return false;
    }
    else{
        return true;
    }
}

bool ColorImageClass::addImageTo(ColorImageClass &rhsImg){
    int clipped = 0;
    for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COLUMN_SIZE; j++){
            clipped += Image[i][j].addColor(rhsImg.Image[i][j]);
        }
    }
    if (clipped >0){
        return true;
    }
    else{
        return false;
    }
}

bool ColorImageClass::addImages(int numImgsToAdd,
                                ColorImageClass imagesToAdd[]) {
    int clipped = 0;
    for (int a = 0; a < numImgsToAdd; a++){
        clipped += imagesToAdd[0].addImageTo(imagesToAdd[a]);
    }
    for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COLUMN_SIZE; j++){
            Image[i][j] = imagesToAdd[0].Image[i][j];
        }
    }
    if (clipped > 0){
        return true;
    }
    else{
        return false;
    }
}

bool ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &inColor) {
    if (validRange(inRowCol.getRow(), ROW_SIZE) &&
        validRange(inRowCol.getCol(), COLUMN_SIZE)){
        Image[inRowCol.getRow()][inRowCol.getCol()].setTo(inColor);
        return true;
    }
    else{
        return false;
    }
}

bool ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &outColor) {
    if (validRange(inRowCol.getRow(), ROW_SIZE) &&
        validRange(inRowCol.getCol(), COLUMN_SIZE)){
        outColor.setTo(Image[inRowCol.getRow()][inRowCol.getCol()]);
        return true;
    }
    else{
        return false;
    }
}

void ColorImageClass::printImage() {
    for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COLUMN_SIZE; j++){
            Image[i][j].printComponentValues();
            if (j < COLUMN_SIZE - 1){
                cout<<"--";
            }
        }
    }
    cout<<endl;
}











