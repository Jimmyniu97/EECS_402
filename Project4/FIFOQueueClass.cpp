#include <iostream>
#include <cstdlib>
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
using namespace std;

//this is the cpp file for FIFOQueueClass, it defines the functions of
//this class

//default constructor, will create an empty queue
FIFOQueueClass::FIFOQueueClass() {
    head = NULL;
    tail = NULL;
}

//function to clear the queue to the empty state
void FIFOQueueClass::clear() {
    LinkedNodeClass *deleteNode = head;
    LinkedNodeClass *temp = head;
    while (temp != NULL) {
        temp = temp->getNext();
        delete deleteNode;
        deleteNode = temp;
    }
    head = NULL;
    tail = NULL;
}

//default destructor, delete the queue without memory leak
FIFOQueueClass::~FIFOQueueClass() {
    clear();
}

//return the number of nodes in the queue
int FIFOQueueClass::getNumElems() const {
    int numElems = 0;
    LinkedNodeClass *temp = head;
    while (temp != NULL) {
        numElems += 1;
        temp = temp->getNext();
    }
    return numElems;
}

//function to print the content of the queue, first node inserted will
//display first
void FIFOQueueClass::print() const {
    LinkedNodeClass *temp = tail;
    while (temp != NULL) {
        cout<<temp->getValue();
        cout<<" ";
        temp = temp->getPrev();
    }
    cout<<endl;
}

//function to insert the node to the queue
void FIFOQueueClass::enqueue(const int &newItem) {
    LinkedNodeClass *insertNode;
    //if the queue is empty
    if (head == NULL) {
        insertNode = new LinkedNodeClass(NULL, newItem, NULL);
        head = insertNode;
        tail = insertNode;
    }
    //if the queue is not empty, insert a new node to
    //the head of the queue
    else {
        insertNode = new LinkedNodeClass(NULL, newItem, head);
        head = insertNode;
        insertNode->setBeforeAndAfterPointers();
    }
}

//function to delete the last node of the queue
bool FIFOQueueClass::dequeue(int &outItem) {
    bool success = true;
    //if the queue is empty
    if (tail == NULL) {
        success = false;
    }
    //RESUBMISSION CODE UPDATE
    //if the queue is not empty, delete the last node and change
    else if (getNumElems() == 1) {
        LinkedNodeClass *temp = tail;
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