#include <iostream>
#include <fstream>
#include "constants.h"
#include "ColorClass.h"

//class ColorClass functions definition
ColorClass::ColorClass() {
    amountOfRed = COLOR_MAX;
    amountOfGreen = COLOR_MAX;
    amountOfBlue = COLOR_MAX;
}

//assign color value and clip if necessary
ColorClass::ColorClass(int inRed, int inGreen, int inBlue) {
    //assigning red color value
    if (inRed > COLOR_MAX) {
        amountOfRed = COLOR_MAX;
    }
    else if(inRed < COLOR_MIN) {
        amountOfRed = COLOR_MIN;
    }
    else{
        amountOfRed = inRed;
    }
    //assign green color value
    if (inGreen >COLOR_MAX) {
        amountOfGreen = COLOR_MAX;
    }
    else if (inGreen < COLOR_MIN) {
        amountOfGreen = COLOR_MIN;
    }
    else{
        amountOfGreen = inGreen;
    }
    //assign blue color value
    if (inBlue > COLOR_MAX) {
        amountOfBlue = COLOR_MAX;
    }
    else if (inBlue < COLOR_MIN) {
        amountOfBlue = COLOR_MIN;
    }
    else{
        amountOfBlue = inBlue;
    }
}

bool ColorClass::checkColorRange(int colorValue) {
    if (colorValue > COLOR_MAX || colorValue < COLOR_MIN) {
        return false;
    }
    else{
        return true;
    }
}
//check if the pixel is in the range of 0 ~ 255
bool ColorClass::checkColor(int value, int bound) {
    if (value < COLOR_MIN || value > bound) {
        return false;
    }
    return true;
}

int ColorClass::setToColor(int colorValue) {
    int returnVal;
    if (checkColorRange(colorValue)) {
        returnVal = colorValue;
    }
    else if (colorValue > COLOR_MAX) {
        returnVal = COLOR_MAX;
    }
    else {
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

bool ColorClass::setTo(ColorClass inColor) {
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
        checkColorRange(inBlue)) {
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
//read RGB value from PPM file and return false if the pixel is not
//in the range
bool ColorClass::readFile(ifstream &inFile, int bound) {
    inFile >> amountOfRed >> amountOfGreen >> amountOfBlue;
    if (!checkColor(amountOfRed, bound)) {
        return false;
    }
    else if (!checkColor(amountOfGreen,bound)) {
        return false;
    }
    else if (!checkColor(amountOfBlue,bound)) {
        return false;
    }
    return true;
}
//function to compare if the RGB value of two ColorClass object are same
bool ColorClass::sameColor(ColorClass compareColor) {
    if (amountOfRed != compareColor.amountOfRed) {
        return false;
    }
    else if (amountOfGreen != compareColor.amountOfGreen) {
        return false;
    }
    else if (amountOfBlue != compareColor.amountOfBlue) {
        return false;
    }
    return true;
}

void ColorClass::setIndex(int idx) {
    patternIndex = idx;
}

int ColorClass::getIndex() {
    return patternIndex;
}

int ColorClass::getRed() {
    return amountOfRed;
}

int ColorClass::getGreen() {
    return amountOfGreen;
}

int ColorClass::getBlue() {
    return amountOfBlue;
}

