#include "ColorClass.h"
using namespace std;

#ifndef _PATTERNCLASS_H
#define _PATTERNCLASS_H

class PatternClass {
private:
    //integers that defines the width and the heights of the pattern
    int width;
    int height;
    //create a ColorClass pointer
    ColorClass* imgPt;
    //create a ColorClass object
    ColorClass patternColor;
public:
    //default constructor
    PatternClass();
    //return true if the pattern file was initialized
    bool initialized(string fileName);
    //set the color of the pattern
    void setColor(int color);
    //return the width of the pattern
    int getWidth();
    //return the height of the pattern
    int getHeight();
    //return the ColorClass pointer
    ColorClass* getPt();
    //return the ColorClass object
    ColorClass getPatternColor();
    //default destructor
    ~PatternClass();

};

#endif //PROJECT3_PATTERNCLASS_H
