#include <iostream>
#include <cstdlib>
#include "LinkedNodeClass.h"
using namespace std;

//Programmer: Yuefeng Niu
//Date: 12/8/2020
//this is the cpp file for LinkedNodeClass, it defines the functions of
//this class



//default constructor, will create a node that contains information about
//previous, next node and the current node value
template <class T>
LinkedNodeClass<T>::LinkedNodeClass(LinkedNodeClass<T> *inPrev, const T &inVal,
                                 LinkedNodeClass<T> *inNext) {
    nodeVal = inVal;
    prevNode = inPrev;
    nextNode = inNext;
}

//return the value of the node
template <class T>
T LinkedNodeClass<T>::getValue() const {
    return nodeVal;
}

//return the previous node
template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getPrev() const {
    return prevNode;
}

//return the next node
template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getNext() const {
    return nextNode;
}

//set the previous node to 0
template <class T>
void LinkedNodeClass<T>::setPreviousPointerToNull() {
    prevNode = NULL;
}

//set the next node to 0
template <class T>
void LinkedNodeClass<T>::setNextPointerToNull() {
    nextNode = NULL;
}

//try to connect this node to the previous and next node
template <class T>
void LinkedNodeClass<T>::setBeforeAndAfterPointers() {
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