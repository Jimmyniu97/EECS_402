#include <iostream>
#include <cstdlib>
#include "LinkedNodeClass.h"
using namespace std;

//this is the cpp file for LinkedNodeClass, it defines the functions of
//this class

//default constructor, will create a node that contains information about
//previous, next node and the current node value
LinkedNodeClass::LinkedNodeClass(LinkedNodeClass *inPrev, const int &inVal,
                                 LinkedNodeClass *inNext) {
    nodeVal = inVal;
    prevNode = inPrev;
    nextNode = inNext;
}

//return the value of the node
int LinkedNodeClass::getValue() const {
    return nodeVal;
}

//return the previous node
LinkedNodeClass* LinkedNodeClass::getPrev() const {
    return prevNode;
}

//return the next node
LinkedNodeClass* LinkedNodeClass::getNext() const {
    return nextNode;
}

//set the previous node to 0
void LinkedNodeClass::setPreviousPointerToNull() {
    prevNode = NULL;
}

//set the next node to 0
void LinkedNodeClass::setNextPointerToNull() {
    nextNode = NULL;
}

//try to connect this node to the previous and next node
void LinkedNodeClass::setBeforeAndAfterPointers() {
    if (prevNode != NULL) {
        if (nextNode != NULL) {
            prevNode->nextNode = this;
            nextNode->prevNode = this;
        }
        else {
            prevNode->nextNode = this;
        }
    }
    else {
        if (nextNode != NULL) {
            nextNode->prevNode = this;
        }
    }

}