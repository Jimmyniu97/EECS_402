#include <iostream>
#include <string>
#include <fstream>
#include "constants.h"
#include "PatternClass.h"
#include "ColorClass.h"
using namespace std;
//default constructor
PatternClass::PatternClass() {
    imgPt = 0;
}
//default destructor
PatternClass::~PatternClass() {
    delete [] imgPt;
    imgPt = 0;
}

int PatternClass::getWidth() {
    return width;
}

int PatternClass::getHeight() {
    return height;
}

ColorClass PatternClass::getPatternColor() {
    return patternColor;
}
//function that checks if the pattern object was initiallized successfully
bool PatternClass::initialized(string fileName) {
    ifstream inFile;
    inFile.open(fileName.c_str());
    if (inFile.fail()) {
        cout << "File doesn't exist!" << endl;
        return false;
    }
    //checks if the width and height of the pattern is larger than 0
    inFile >> width;
    if (inFile.fail() || width <= SIZE_MIN) {
        cout << "Please enter a positive integer!" << endl;
        return false;
    }
    else {
        inFile >> height;
        if (inFile.fail() || height <= SIZE_MIN) {
            cout << "Please enter a positive integer!" << endl;
            return false;
        }
    }
    //create a new ColorClass object that stores 2D array using 1D index
    imgPt = new ColorClass[width * height];
    //index of the pattern
    int idx;
    //temp value that's either 1 or 0
    int tmp;
    string info;
    while (!inFile.eof()) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                //create 1D index
                idx = i * width + j;
                inFile >> tmp;
                if (inFile.fail()) {
                    cout << "Input value should ";
                    cout << "be positive integer!" << endl;
                    return false;
                }
                //if the temp value is neither 1 nor 0
                else if (tmp != 0 && tmp != 1) {
                    cout << "Input should be 1 or 0!" << endl;
                    return false;
                }
                //set the color to the pattern color
                //and store the pattern index
                else {
                    imgPt[idx].setTo(patternColor);
                    imgPt[idx].setIndex(tmp);
                }
            }
        }
        //if there are more string information contains,
        //close the inFile
        inFile >> info;
        if (info != "") {
            inFile.close();
            cout << "Total number of input is larger than"
                    "pattern size!" << endl;
            return false;
        }
    }
    return true;
}
//function that set the color of the pattern
void PatternClass::setColor(int color) {
    if (color == COLOR_RED) {
        patternColor.setToRed();
    }
    else if (color == COLOR_GREEN) {
        patternColor.setToGreen();
    }
    else if (color == COLOR_BLUE) {
        patternColor.setToBlue();
    }
    else if (color == COLOR_BLACK) {
        patternColor.setToBlack();
    }
    else if (color == COLOR_WHITE) {
        patternColor.setToWhite();
    }
}
//function that return the pointer of the ColorClass
ColorClass* PatternClass::getPt() {
    return imgPt;
}