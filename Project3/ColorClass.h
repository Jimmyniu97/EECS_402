#ifndef _COLORCLASS_H
#define _COLORCLASS_H

#include <string>
using namespace std;

//declare class ColorClass to define information of a color
class ColorClass{
private:
    int amountOfRed;
    int amountOfGreen;
    int amountOfBlue;
    int patternIndex;

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
    bool setTo(ColorClass inColor);
    //add color from input parameter
    bool addColor(ColorClass &rhs);
    //subtract color from input parameter
    bool subtractColor(ColorClass &rhs);
    //adjust brightness by multiply an input value
    bool adjustBrightness(double adjFactor);
    //read the RGB value from the PPM image and return false if
    //fails
    bool readFile(ifstream &inFile, int bound);
    //check if the color is in the range of 0 ~ 255
    bool checkColor(int value, int bound);
    //set the pattern index
    void setIndex(int idx);
    //return the pattern index
    int getIndex();
    //check if the color is same to compareColor object
    bool sameColor(ColorClass compareColor);
    //print Red value
    int getRed();
    //print Green value
    int getGreen();
    //print Blue value
    int getBlue();

};

#endif //PROJECT3_COLORCLASS_H
