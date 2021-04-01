#include <iostream>
#include <cstdlib>
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
using namespace std;

//Programmer: Yuefeng Niu
//Date: 12/8/2020
//this is the cpp file for FIFOQueueClass, it defines the functions of
//this class

//default constructor, will create an empty queue
template <class T>
FIFOQueueClass<T>::FIFOQueueClass() {
    head = NULL;
    tail = NULL;
}

//function to clear the queue to the empty state
template <class T>
void FIFOQueueClass<T>::clear() {
    LinkedNodeClass<T> *deleteNode = head;
    LinkedNodeClass<T> *temp = head;
    while (temp != NULL) {
        temp = temp->getNext();
        delete deleteNode;
        deleteNode = temp;
    }
    head = NULL;
    tail = NULL;
}

//default destructor, delete the queue without memory leak
template <class T>
FIFOQueueClass<T>::~FIFOQueueClass() {
    clear();
}

//return the number of nodes in the queue
template <class T>
int FIFOQueueClass<T>::getNumElems() const {
    int numElems = 0;
    LinkedNodeClass<T> *temp = head;
    while (temp != NULL) {
        numElems += 1;
        temp = temp->getNext();
    }
    return numElems;
}

//function to print the content of the queue, first node inserted will
//display first
template <class T>
void FIFOQueueClass<T>::print() const {
    LinkedNodeClass<T> *temp = tail;
    while (temp != NULL) {
        cout<<temp->getValue();
        cout<<" ";
        temp = temp->getPrev();
    }
    cout<<endl;
}

//function to insert the node to the queue
template <class T>
void FIFOQueueClass<T>::enqueue(const T &newItem) {
    LinkedNodeClass<T> *insertNode;
    //if the queue is empty
    if (head == NULL) {
        insertNode = new LinkedNodeClass<T>(NULL, newItem, NULL);
        head = insertNode;
        tail = insertNode;
    }
    //if the queue is not empty, insert a new node to
    //the head of the queue
    else {
        insertNode = new LinkedNodeClass<T>(NULL, newItem, head);
        head = insertNode;
        insertNode->setBeforeAndAfterPointers();
    }
}

//function to delete the last node of the queue
template <class T>
bool FIFOQueueClass<T>::dequeue(T &outItem) {
    bool success = true;
    //if the queue is empty
    if (tail == NULL) {
        success = false;
    }
    //RESUBMISSION CODE UPDATE
    //if the queue is not empty, delete the last node and change
    else if (getNumElems() == 1) {
        LinkedNodeClass<T> *temp = tail;
        outItem = temp->getValue();
        delete temp;
        temp = NULL;
        head = NULL;
        tail = NULL;
    }
    //if there are multiple nodes in the queue, delete the last node in
    //the queue
    else {
        outItem = tail->getValue();
        tail = tail->getPrev();
        delete tail->getNext();
        tail->setNextPointerToNull();
    }
    return success;
}