#include <iostream>
#include <cstdlib>
#include "LinkedNodeClass.h"
#include "LIFOStackClass.h"
using namespace std;

//this is the cpp file for LIFOStackClass, it defines the functions
//of this class

//default constructor, will create an empty stack
LIFOStackClass::LIFOStackClass() {
    head = NULL;
    tail = NULL;
}

//default constructor
LIFOStackClass::~LIFOStackClass() {
    clear();
}

//function to clear the content of the stack to the
//empty state without memory leak
void LIFOStackClass::clear() {
    LinkedNodeClass *deleteNode = head;
    LinkedNodeClass *temp = head;
    //use the temp node to go over the stack and delete every node
    while (temp != NULL) {
        temp = temp->getNext();
        delete deleteNode;
        deleteNode = temp;
    }
    head = NULL;
    tail = NULL;
}

//return the number of nodes in the stack
int LIFOStackClass::getNumElems() const {
    int numElems = 0;
    LinkedNodeClass *temp = head;
    while (temp != NULL) {
        numElems += 1;
        temp = temp->getNext();
    }
    return numElems;
}

//print the content of the stack from the head
void LIFOStackClass::print() const {
    LinkedNodeClass *tempNode = head;
    if (getNumElems() == 0) {
        cout<<"This stack is empty!"<<endl;
    }
    else{
        while (tempNode != NULL) {
            cout<<tempNode->getValue();
            cout<<" ";
            tempNode = tempNode->getNext();
        }
        cout<<endl;
    }
}

//add a new node to the stack in the head
void LIFOStackClass::push(const int &newItem) {
    LinkedNodeClass *newNode;
    //if the stack is empty
    if (head == NULL) {
        newNode = new LinkedNodeClass(NULL, newItem, NULL);
        head = newNode;
        tail = newNode;
    }
    //if the stack is not empty, insert the new node in the head
    else {
        newNode = new LinkedNodeClass(NULL, newItem, head);
        newNode->setBeforeAndAfterPointers();
        head = newNode;
    }
}

//delete the first node of the stack, will return the value of the delete node
bool LIFOStackClass::pop(int &outItem) {
    bool success = true;
    //if the stack is empty
    if (getNumElems() == 0) {
        success = false;
    }
    //RESUBMISSION CODE UPDATE
    //if only one node in the stack, delete the node, and set everything
    //else to NULL
    else if (getNumElems() == 1) {
        LinkedNodeClass *temp = head;
        outItem = temp->getValue();
        delete temp;
        temp = NULL;
        head = NULL;
        tail = NULL;
    }
    //if the stack is not empty, delete the first node and make the second
    //as the head
    else {
        outItem = head->getValue();
        head = head->getNext();
        delete head->getPrev();
        head->setPreviousPointerToNull();
    }
    return success;
}