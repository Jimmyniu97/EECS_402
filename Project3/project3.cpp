#include <iostream>
#include <fstream>
#include <string>
#include "constants.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "RectangleClass.h"
#include "PatternClass.h"
using namespace std;

//Programmer: Yuefeng Niu
//Date: 11/8/2020
//This is the project 3 to design classes to modify images
//in PPM format

//function that calls the main menu and do the error checking
int mainMenuOption();
//function that calls the menu to choose the color and do the error checking
int colorOption(string type);
//function that ask if the user wants to fill and do the error checking
int fillOption();
//function that above three function calls that checks if the input is
//in the range
int validInputRange(string question, int lowerBound, int upperBound);

int main() {
    //file name of the input PPM image
    string fileName;
    //create a ColorImageClass object
    //that store the information of the PPM image
    ColorImageClass image;
    //get the file name of the image
    cout << "Enter string for PPM image file name to load: ";
    cin >> fileName;
    //if the image object was initialized as ColorImageClass object
    if (image.Initialized(fileName)) {
        int option = 0;
        //repeat the main menu until the user wants to exit
        while (option != CHOICE_FIVE) {
            //return the choice that user want from main menu
            option = mainMenuOption();
            //if user choose Annotate image with rectangle
            if (option == CHOICE_ONE){
                //integer that stores the rectangle
                //specification method choice
                int option;
                //integer that stores the color of the rectangle
                int optionColor;
                //integer that stores if the user want to fill the rectangle
                int optionFill;
                //default question that ask user to enter input
                string question;
                //bool that is true if the user's input is correct
                bool validInput = false;
                //integer that stores the two position of the rectangle
                int startRow; int startCol; int endRow; int endCol;
                cout << "1.  Specify upper left and ";
                cout << "lower right corners of rectangle" << endl;
                cout << "2.  Specify upper left ";
                cout << "corner and dimensions of rectangle" << endl;
                cout << "3.  Specify extent from center of rectangle" << endl;
                question = "Enter int for rectangle specification method: ";
                //integer that stores the user's option
                option = validInputRange(question,CHOICE_ONE, CHOICE_THREE);

                //if user select rectangle specification method 1
                if (option == CHOICE_ONE) {
                    cout << "Enter upper left corner row and column: ";
                    //error checking if the user entered integers
                    while (!validInput) {
                        cin >> startRow; cin >> startCol;
                        if (cin.fail() || startRow <= SIZE_MIN ||
                        startCol <= SIZE_MIN) {
                            cin.clear();
                            cin.ignore(200,'\n');
                            cout << "Please enter valid integers!" << endl;
                            cout << "Enter upper left corner row and column: ";
                        }

                        else {
                            validInput = true;
                            bool validInput2 = false;
                            cout << "Enter lower right ";
                            cout << "corner row and column: ";
                            //error checking if the user entered integers
                            while (!validInput2) {
                                cin >> endRow; cin >> endCol;
                                if (cin.fail() || endRow <= SIZE_MIN ||
                                endCol <= SIZE_MIN) {
                                    cin.clear();
                                    cin.ignore(200,'\n');
                                    cout << "Please enter ";
                                    cout << "valid integers!" << endl;
                                    cout << "Enter lower right ";
                                    cout << "corner row and column: ";
                                }
                                else {
                                    validInput2 = true;
                                    optionColor =
                                            colorOption("rectangle");
                                    optionFill = fillOption();
                                    //create a RectangleClass object that
                                    //stores the two positions
                                    RectangleClass rect(startRow,startCol,
                                                        endRow,endCol);
                                    //set the color of the rectangle
                                    rect.setColor(optionColor);
                                    //add the rectangle to the image object
                                    image.addRectangle(rect,optionFill);

                                }
                            }
                        }
                    }
                }

                //if user select rectangle specification method 2
                else if (option == CHOICE_TWO) {
                    int row; int col;
                    cout << "Enter upper left corner row and column: ";
                    //error checking if the user entered integers
                    while (!validInput) {
                        cin >> startRow; cin >> startCol;
                        if (cin.fail() || startRow <= SIZE_MIN ||
                        startCol <= SIZE_MIN){
                            cin.clear();
                            cin.ignore(200,'\n');
                            cout << "Please enter valid integers!" << endl;
                            cout << "Enter upper left corner row and column: ";
                        }
                        else {
                            validInput = true;
                            bool validInput2 = false;
                            cout << "Enter int for number of rows: ";
                            //error checking if the user entered integers
                            while (!validInput2) {
                                cin >> row;
                                if (cin.fail() || row <= SIZE_MIN) {
                                    cin.clear();
                                    cin.ignore(200,'\n');
                                    cout << "Please enter ";
                                    cout << "valid integers!" << endl;
                                    cout << "Enter int for number of rows: ";
                                }
                                else {
                                    validInput2 = true;
                                    bool validInput3 = false;
                                    cout << "Enter int ";
                                    cout << "for number of columns: ";
                                    while (!validInput3) {
                                        cin >> col;
                                        if (cin.fail() || col <= SIZE_MIN) {
                                            cin.clear();
                                            cin.ignore(200,'\n');
                                            cout << "Please enter";
                                            cout << "valid integers!" << endl;
                                            cout << "Enter int for ";
                                            cout << "number of columns";
                                        }
                                        else {
                                            validInput3 = true;
                                            optionColor =
                                                    colorOption
                                                    ("rectangle");
                                            optionFill = fillOption();
                                            //defines the position of the
                                            // end row and columns
                                            endRow = startRow + row;
                                            endCol = startCol + col;
                                            //create the RectangleClass object
                                            RectangleClass rect(startRow,
                                                                startCol,
                                                                endRow,endCol);
                                            rect.setColor(optionColor);
                                            image.addRectangle(rect,
                                                               optionFill);
                                        }
                                    }

                                }
                            }
                        }
                    }
                }

                //if user select rectangle specification method 3
                else if (option == CHOICE_THREE) {
                    //four integers that stores the position from user
                    int rowCenter;
                    int colCenter;
                    int rowHalf;
                    int colHalf;
                    cout << "Enter rectangle center row and column: ";
                    //error checking if the user entered the integer
                    while (!validInput) {
                        cin >> rowCenter; cin >> colCenter;
                        if (cin.fail() || rowCenter <= SIZE_MIN ||
                        colCenter <= SIZE_MIN) {
                            cin.clear();
                            cin.ignore(200,'\n');
                            cout << "Please enter valid integers!" << endl;
                            cout << "Enter rectangle center row and column: ";
                        }
                        else {
                            validInput = true;
                            bool validInput2 = false;
                            cout << "Enter int for half number of rows: ";
                            //error checking if the user entered the integer
                            while (!validInput2) {
                                cin >> rowHalf;
                                if (cin.fail() || rowHalf <= SIZE_MIN) {
                                    cin.clear();
                                    cin.ignore(200,'\n');
                                    cout << "Please enter a ";
                                    cout << "valid integer!" << endl;
                                    cout << "Enter int for ";
                                    cout << "half number of rows: ";
                                }
                                else {
                                    validInput2 =true;
                                    bool validInput3 = false;
                                    cout << "Enter int for ";
                                    cout << "half number of columns: ";
                                    while (!validInput3) {
                                        cin >> colHalf;
                                        if (cin.fail() ||
                                        colHalf <= SIZE_MIN) {
                                            cin.clear();
                                            cin.ignore(200,'\n');
                                            cout << "Please enter a ";
                                            cout << "valid integer" << endl;
                                            cout << "Enter int for ";
                                            cout << "half number of columns: ";
                                        }
                                        else {
                                            validInput3 = true;
                                            optionColor
                                            =colorOption("rectangle");
                                            optionFill = fillOption();
                                            //defines the two positions
                                            //of the rectangle
                                            startRow = rowCenter - rowHalf;
                                            endRow = rowCenter + rowHalf;
                                            startCol = colCenter - colHalf;
                                            endCol = colCenter + colHalf;
                                            RectangleClass rect(startRow,
                                                                startCol,
                                                                endRow,endCol);
                                            rect.setColor(optionColor);
                                            image.addRectangle(rect,
                                                               optionFill);
                                        }
                                    }
                                }

                            }

                        }
                    }
                }
            }
            //if the user want to annotate image with pattern
            else if (option == CHOICE_TWO) {
                //string that stores the pattern file name
                string patternName;
                //integer that stores the color of the pattern
                int optionColor;
                //create a PatternClass object
                PatternClass pattern;
                bool validInput = false;
                //two integers that stores the upper left row and col
                //of the pattern
                int pRow;
                int pCol;
                cout << "Enter string for file name containing pattern: ";
                cin >> patternName;
                //if the pattern file was initialized successfully
                if (pattern.initialized(patternName)) {
                    cout << "Enter upper left ";
                    cout << "corner of pattern row and column: ";
                    //error checking if the user entered the integer
                    while (!validInput) {
                        cin >> pRow; cin >> pCol;
                        if (cin.fail() || pRow <= SIZE_MIN ||
                        pCol <= SIZE_MIN) {
                            cin.clear();
                            cin.ignore();
                            cout << "Please enter valid integers!" << endl;
                            cout << "corner of pattern row and column: ";
                        }
                        else {
                            validInput = true;
                            optionColor = colorOption("pattern");
                            //create a PatternClass object that stores the
                            //color
                            pattern.setColor(optionColor);
                            //add pattern to the image object
                            image.addPattern(pattern, pRow, pCol);

                        }
                    }
                }
                else {
                    cout << "The file address is not correct!" << endl;
                }
            }
            //if the user wants to insert another image
            else if (option == CHOICE_THREE) {
                bool validInput = false;
                string imgName;
                //integers of row and column of
                //the upper left corner of the inserted image
                int irow;
                int icol;
                int optionColor;
                cout << "Enter string for file name of PPM image to insert:";
                cin >> imgName;
                //create a new ColorImageClass object that represents
                //the inserted image
                ColorImageClass inserted_image;
                if (inserted_image.Initialized(imgName)) {
                    cout << "Enter upper left ";
                    cout << "corner to insert image row and column: ";
                    while (!validInput) {
                        cin >> irow; cin >> icol;
                        if (cin.fail() ||
                        irow <= SIZE_MIN || icol <= SIZE_MIN) {
                            cin.clear();
                            cin.ignore(200,'\n');
                            cout << "Please enter valid integers!" << endl;
                            cout << "Enter upper left ";
                            cout << "corner to insert image row and column: ";
                        }
                        else {
                            validInput = true;
                            optionColor = colorOption("transparency");
                            //set the color of the
                            //inserted image transparency
                            inserted_image.setTransparency(optionColor);
                            image.addImage(inserted_image,irow,icol);
                        }
                    }
                }

            }
            //if the user wants to export the image
            else if (option == CHOICE_FOUR) {
                //file name that user wants to export
                string fileName;
                bool validInput = false;
                cout << "Enter string for PPM file name to output: ";
                //error checking if the user entered valid string name
                while (!validInput) {
                    cin >> fileName;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(200,'\n');
                        cout << "Please enter a valid file name!" << endl;
                        cout <<"Enter string for PPM file name to output: ";
                    }
                    else {
                        validInput = true;
                        ofstream outFile;
                        outFile.open(fileName.c_str());
                        //error checking if the outFile can't open
                        if (outFile.fail()) {
                            cout << "Error found when writing a file" << endl;
                        }
                        else {
                            //write out the PPM file with the same
                            //image information as the image object
                            outFile << image.getImageType() << " ";
                            outFile << image.getWidth() << " ";
                            outFile << image.getHeight() << " ";
                            outFile << image.getPixel() << " ";
                            for (int i = 0;
                            i < image.getWidth() * image.getHeight(); i++) {
                                //using the loop to write out the RGB value
                                outFile << (image.getPointer() + i)->getRed();
                                outFile << " ";
                                outFile << (image.getPointer()
                                + i)->getGreen();
                                outFile << " ";
                                outFile << (image.getPointer()
                                + i)->getBlue();
                                outFile << " ";
                            }
                        }
                        outFile.close();
                    }
                    cin.clear();
                    cin.ignore(200,'\n');
                }
            }
        }
        //user choose option 5 and program ends
        cout << "Thank you for using this program" << endl;
    }
    //user entered invalid image and program ends
    else {
        cout << "Error found when ";
        cout << "trying to access an invalid image! " << endl;
        cout << "Program ends!" << endl;
    }

    return 0;
}
//main menu function that return the valid input from user
int mainMenuOption() {
    int option;
    string question;
    cout << "1.  Annotate image with rectangle" << endl;
    cout << "2.  Annotate image with pattern from file" << endl;
    cout << "3.  Insert another image" << endl;
    cout << "4.  Write out current image" << endl;
    cout << "5.  Exit the program" << endl;
    question = "Enter int for main menu choice: ";
    //calls the validInputRange function that do the error checking
    option = validInputRange(question, CHOICE_ONE, CHOICE_FIVE);
    return option;
}

int colorOption(string type) {
    int option;
    string question;
    cout << "1.  Red" << endl;
    cout << "2.  Green" << endl;
    cout << "3.  Blue" << endl;
    cout << "4.  Black" << endl;
    cout << "5.  White" << endl;
    //decide which type option
    if (type == "rectangle") {
        question = "Enter int for rectangle color: ";
    }
    else if (type == "transparency") {
        question = "Enter int for transparency color: ";
    }
    else if (type == "pattern") {
        question = "Enter int for pattern color: ";
    }
    option = validInputRange(question, COLOR_RED, COLOR_WHITE);
    return option;
}
//function that ask if user wants to fill the color
int fillOption() {
    int option;
    string question = "Enter int for rectangle fill option: ";
    cout << "1.  No" << endl;
    cout << "2.  Yes" << endl;
    option = validInputRange(question, CHOICE_ONE, CHOICE_TWO);
    return option;
}
//function that do the error checking
int validInputRange(string question, int lowerBound, int upperBound) {
    int input;
    bool validInput = false;
    cout << question;
    while (!validInput) {
        cin >> input;
        if (cin.fail() || input < lowerBound || input > upperBound){
            cin.clear();
            cin.ignore(200,'\n');
            cout << "Please enter a number between " << lowerBound;
            cout << " to " << upperBound << endl;
            cout << question;
        }
        else {
            validInput = true;
        }
    }
    return input;
}

