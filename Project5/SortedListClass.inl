#include <iostream>
#include <cstdlib>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
using namespace std;

//Programmer: Yuefeng Niu
//Date: 12/8/2020
//this is the cpp file for SortedListClass, it defines the functions of
//this class

//default constructor, create an empty list
template <class T>
SortedListClass<T>::SortedListClass() {
    head = NULL;
    tail = NULL;
}

//copy constructor, will copy another list that will not affect each other
template <class T>
SortedListClass<T>::SortedListClass(const SortedListClass<T> &rhs) {
    head = NULL;
    LinkedNodeClass<T> *tempNode = rhs.head;
    while (tempNode != NULL) {
        this->insertValue(tempNode->getValue());
        tempNode = tempNode->getNext();
    }
}

//default destructor, will prevent memory leak
template <class T>
SortedListClass<T>::~SortedListClass() {
    clear();
}

//print the sorted list from head
template <class T>
void SortedListClass<T>::printForward() const {
    LinkedNodeClass<T> *temp = head;
    cout<<"Forward List Contents Follow: "<<endl;
    while (temp != NULL) {
        cout<<"  "<<temp->getValue()<<endl;
        temp = temp->getNext();
    }
    cout<<"End Of List Contents"<<endl;
}

//print the sorted list from tail
template <class T>
void SortedListClass<T>::printBackward() const {
    LinkedNodeClass<T> *temp = tail;
    //if the list is not empty
    cout<<"Backward List Contents Follow: "<<endl;
    while (temp != NULL) {
        cout<<"  "<<temp->getValue()<<endl;
        temp = temp->getPrev();
    }
    cout<<"End Of List Contents"<<endl;


}

//delete the first node
template <class T>
bool SortedListClass<T>::removeFront(T &theVal) {
    //if the list is empty, return false
    if (getNumElems() == 0) {
        head = NULL;
        tail = NULL;
        return false;
    }
    //RESUBMISSION CODE UPDATE
    //if only one node in the list, delete the node and set everything
    //left to NULL
    else if (getNumElems() == 1) {
        LinkedNodeClass<T> *temp = head;
        theVal = temp->getValue();
        delete temp;
        temp = NULL;
        head = NULL;
        tail = NULL;
        return false;
    }
    //if there are multiple nodes in the list , delete the first node
    else {
        theVal = head->getValue();
        head = head->getNext();
        delete head->getPrev();
        head->setPreviousPointerToNull();
        return true;
    }
}

//delete the last node
template <class T>
bool SortedListClass<T>::removeLast(T &theVal) {
    //if the list is empty
    if (getNumElems() == 0) {
        head = NULL;
        tail = NULL;
        return false;
    }
    //RESUBMISSION CODE UPDATE
    //if there is only one node, delete the node and set everything
    //else to NULL
    else if (getNumElems() == 1) {
        LinkedNodeClass<T> *temp = tail;
        theVal = temp->getValue();
        delete temp;
        temp = NULL;
        head = NULL;
        tail = NULL;
        return false;
    }
    //if there are more than one node in the list, delete the last node
    else {
        theVal = tail->getValue();
        tail = tail->getPrev();
        delete tail->getNext();
        tail->setNextPointerToNull();
        return true;
    }
}

//clear the list to the empty state
template <class T>
void SortedListClass<T>::clear() {
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

template <class T>
void SortedListClass<T>::insertValue(const T &valToInsert) {
    //if the list is empty
    if (getNumElems() == 0) {
        LinkedNodeClass<T> *newNode;
        newNode = new LinkedNodeClass<T>(NULL, valToInsert, NULL);
        head = newNode;
        tail = newNode;
    }
    else {
        LinkedNodeClass<T> *temp = head;
        LinkedNodeClass<T> *newNode;
        //while loop to make the newNode to be inserted in the right position
        //in the list
        while ((temp != NULL) && (temp->getValue() <= valToInsert)) {
            temp = temp->getNext();
        }
        //if the node inserts at head
        if (temp == head) {
            newNode = new LinkedNodeClass<T>(NULL, valToInsert, head);
            newNode->setBeforeAndAfterPointers();
            head = newNode;
        }
        //if the node inserts at tail
        else if (temp == NULL) {
            newNode = new LinkedNodeClass<T>(tail, valToInsert, NULL);
            newNode->setBeforeAndAfterPointers();
            tail = newNode;
        }
        //if the node inserts at middle
        else {
            newNode = new LinkedNodeClass<T>(temp->getPrev(), valToInsert, temp);
            newNode->setBeforeAndAfterPointers();
        }
    }
}

//return the number of nodes in the list
template <class T>
int SortedListClass<T>::getNumElems() const {
    int numElems = 0;
    LinkedNodeClass<T> *temp = head;
    while (temp != NULL) {
        numElems += 1;
        temp = temp->getNext();
    }
    return numElems;
}

//return the node value at given index
template <class T>
bool SortedListClass<T>::getElemAtIndex(const int index, T &outVal) const {
    //if the index is out of range, the outVal would be unassigned
    if (index < 0 || index >= getNumElems()){
        return false;
    }
    //if the index is correct
    else {
        int indexNum = 0;
        LinkedNodeClass<T> *temp = head;
        while (temp != NULL) {
            if (indexNum == index) {
                outVal = temp->getValue();
            }
            temp = temp->getNext();
            indexNum++;
        }
        return true;
    }
}