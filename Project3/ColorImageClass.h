#ifndef _COLORIMAGECLASS_H
#define _COLORIMAGECLASS_H

#include <string>
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "RectangleClass.h"
#include "PatternClass.h"
using namespace std;

//declare class ColorImageClass to restore information of an image
class ColorImageClass{
private:
    int width;
    int height;
    int pixel;
    string img_type;
    ColorClass* imgPt;
    ColorClass transparency;
    bool validRange(int val, int size);
public:
    ColorImageClass();//default constructor
    //return true if the image file was initialized successfully
    bool Initialized(string file_name);
    //return image type
    string getImageType();
    //return the width of the image
    int getWidth();
    //return the height of the image
    int getHeight();
    //return the pixel value of the image
    int getPixel();
    bool idxInRange(int row, int col);
    void setTransparency(int color);
    void addPattern(PatternClass &pattern, int pRow, int pCol);
    void addRectangle(RectangleClass &rectangle, int fill);
    void addImage(ColorImageClass &AddedImg, int startRow, int startCol);
    //return pointer to the ColorClass
    ColorClass* getPointer();
    //destructor of the ColorImageClass
    ~ColorImageClass();

};


#endif //PROJECT3_COLORIMAGECLASS_H
