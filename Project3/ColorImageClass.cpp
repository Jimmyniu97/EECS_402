#include <iostream>
#include <string>
#include <fstream>
#include "constants.h"
#include "ColorImageClass.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
using namespace std;

//declare class ColorImageClass functions
ColorImageClass::ColorImageClass() {
    imgPt = 0;
}
//check if the PPM file was initialized successfully
bool ColorImageClass::Initialized(string file_name) {
    ifstream inFile;
    inFile.open(file_name.c_str());
    //if the file not correctly opened
    if (inFile.fail()) {
        cout << "File doesn't exist" << endl;
        return false;
    }
    else {
        inFile >> img_type;
        //check if the image type is correct
        if (inFile.fail() || img_type != IMAGE_TYPE) {
            cout << "The image type is not P3!" << endl;
            return false;
        }

        inFile >> width;
        //check if the width is larger than zero
        if (inFile.fail() || width <= SIZE_MIN) {
            cout << "The width of an image must be positive!" << endl;
            return false;
        }
        else {
            inFile >> height;
            //check if the height is lager than 0
            if (inFile.fail() || height <= SIZE_MIN) {
                cout << "The height of an image must be positive!" << endl;
                return false;
            }
        }
        inFile >> pixel;
        //check if the pixel value is in the range of 0 ~ 255
        if (inFile.fail() || pixel < COLOR_MIN ||
            pixel > COLOR_MAX) {
            cout << "The pixel value of the ";
            cout << "image is not in range 0 ~ 255!" << endl;
            return false;
        }
        else {
            //if the image was initialized successfully
            //create a new ColorClass object imgPt to dynamically allocate
            //the RGB values
            imgPt = new ColorClass[width * height];
            int idx; string temp;
            //check if the opened file in the in the end
            while (!inFile.eof()) {
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        //create index that convert 2D array to a 1D array
                        idx = i * width + j;
                        //if the file was successfully read
                        if (imgPt[idx].readFile(inFile,pixel)) {

                        }
                        else {
                            inFile.close();
                            cout << "RGB values are not valid!" <<
                                 endl;
                            return false;
                        }
                    }
                }
            }
            //if the file contains extra strings, close the file
            inFile >> temp;
            if (temp != "") {
                inFile.close();
                cout << "Total number of pixel ";
                cout << "values are not correct!" << endl;
                return false;
            }
        }
    }
    return true;
}
//check if the index is in the range size of PPM image
bool ColorImageClass::idxInRange(int row, int col) {
    if ((row > SIZE_MIN && row < height) &&
    (col > SIZE_MIN && col < width)) {
        return true;
    }
    else {
        return false;
    }
}
//function that add the PPM image to the original PPM image
void ColorImageClass::addImage(ColorImageClass &AddedImg, int startRow,
                               int startCol) {
    //integers of the index of original image and added image
    int idxImg;
    int idxAddedImg;
    for (int i = 0; i < AddedImg.height; i++) {
        for (int j = 0; j < AddedImg.width; j++) {
            //create added image index using dynamic allocation
            idxAddedImg = i * AddedImg.width + j;
            //if the added image's transparency color
            //is different from added image's color
            if (!(AddedImg.getPointer() + idxAddedImg)->
            sameColor(AddedImg.transparency)) {
                //create index of the original image
                idxImg = (startRow + i - 1) * width + (startCol + j - 1);
                //replace the pixel value from the original image
                //with the added image if the pixel value is not transparent
                if (idxInRange(startRow - 1, startCol - 1)) {
                    imgPt[idxImg].setTo(*(AddedImg.getPointer()
                    + idxAddedImg));
                }
            }
        }
    }
}
//add the pattern to the original PPM image
void ColorImageClass::addPattern(PatternClass &pattern, int pRow, int pCol) {
    int idxImg;
    int idxPattern;
    for (int i = 0; i < pattern.getHeight(); i++) {
        for (int j = 0; j < pattern.getWidth(); j++) {
            //create index that convert the 2D array to the 1D array
            idxPattern = i * pattern.getWidth() + j;
            //if the pattern value equal to 1, create the index for the
            //original image and set the color to the pattern color
            if ((pattern.getPt() + idxPattern)->getIndex() == 1) {
                idxImg = (pRow + i -1) * width + (pCol + j - 1);
                if (idxInRange(pRow - 1, pCol - 1)) {
                    imgPt[idxImg].setTo(pattern.getPatternColor());
                }
            }
        }
    }

}
//function that add rectangle to the original PPM image
void ColorImageClass::addRectangle(RectangleClass &rectangle, int fill) {
    //index of the 1D image
    int idxImg;
    //four integers that contains the two positions of the rectangle
    int startRow; int startCol;
    int endRow; int endCol;
    //get the twp positions
    startRow = rectangle.getStartPosition().getRow();
    startCol = rectangle.getStartPosition().getCol();
    endRow = rectangle.getEndPosition().getRow();
    endCol = rectangle.getEndPosition().getCol();
    //if choose to fill, replace all the pixel value from the original PPM
    //image to the rectangle color
    if (fill == CHOICE_TWO) {
        for (int i = startRow - 1; i < endRow; i++) {
            for (int j = startCol -1; j < endCol; j++) {
                //create 1D index for the image
                idxImg = i * width + j;
                if (idxInRange(i, j)) {
                    imgPt[idxImg].setTo(rectangle.getColor());
                }
            }
        }
    }
    //if not choose to fill
    else if (fill == CHOICE_ONE){
        //only set the row from the start row to end row and the
        //column of the start column - 1 to the rectangle color
        for (int i = startRow - 1; i < endRow; i++) {
            idxImg = i * width + (startCol - 1);
            if (idxInRange(i, startCol -1)) {
                imgPt[idxImg].setTo(rectangle.getColor());
            }
            idxImg = i * width + (endCol - 1);
            if (idxInRange(i, endCol - 1)) {
                imgPt[idxImg].setTo(rectangle.getColor());
            }
        }
        //only set the column from start to end and row - 1 with
        //the rectangle color
        for (int j = startCol - 1; j < endCol; j++) {
            idxImg = (startRow - 1) * width + j;
            if (idxInRange(startRow - 1, j)) {
                imgPt[idxImg].setTo(rectangle.getColor());
            }
            idxImg = (endRow - 1) * width + j;
            if (idxInRange(endRow - 1, j)) {
                imgPt[idxImg].setTo(rectangle.getColor());
            }
        }
    }
}
//set the transparency color
void ColorImageClass::setTransparency(int color) {
    if (color == COLOR_RED) {
        transparency.setToRed();
    }
    else if (color == COLOR_GREEN) {
        transparency.setToGreen();
    }
    else if (color == COLOR_BLUE) {
        transparency.setToBlue();
    }
    else if (color == COLOR_BLACK) {
        transparency.setToBlack();
    }
    else if (color == COLOR_WHITE) {
        transparency.setToWhite();
    }
}

string ColorImageClass::getImageType() {
    return img_type;
}

int ColorImageClass::getWidth() {
    return width;
}

int ColorImageClass::getHeight() {
    return height;
}

int ColorImageClass::getPixel() {
    return pixel;
}

ColorClass * ColorImageClass::getPointer() {
    return imgPt;
}
//default destructor
ColorImageClass::~ColorImageClass() {
    delete [] imgPt;
    imgPt = 0;
}