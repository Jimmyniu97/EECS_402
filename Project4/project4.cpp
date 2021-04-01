#include <iostream>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "LIFOStackClass.h"
#include "FIFOQueueClass.h"
using namespace std;

//Programmer: Yuefeng Niu
//Date: 11.23.20
//This project builds classes for Linked node, doubly sorted list, stack
//and queue, this script tests the functions of these classes

//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
    //This is just a placeholder main function - it does exceptionally
    //little actual testing, so you'll want to add your own tests here.
    //Feel free to leave your tests in the version of this file you
    //submit, but we will not be running your main function, so the
    //output, etc., of your main doesn't need to match anything from
    //a sample output, etc.
    cout<<"Testing Sorted List functions"<<endl;
    cout<<endl;

    cout<<"Printing an empty list forward:"<<endl;
    SortedListClass testList;
    testList.printForward();
    cout<<endl;

    cout<<"Inserting values to the list and print backward:"<<endl;
    testList.insertValue(42);
    testList.insertValue(54);
    testList.insertValue(54);
    testList.insertValue(1);
    testList.insertValue(5);
    testList.printBackward();
    cout<<endl;

    cout<<"Print the copied list forward:"<<endl;
    SortedListClass testList2(testList);
    testList2.printForward();
    cout<<endl;

    cout<<"Testing with remove all values from list"<<endl;
    int val1;
    int val2;
    int val3;
    int val4;
    int val5;
    testList.removeFront(val1);
    testList.removeFront(val2);
    testList.removeFront(val3);
    testList.removeFront(val4);
    testList.removeFront(val5);
    cout<<"Removed value "<<val1<<" "<<val2<<" "<<val3<<" "
    <<val4<<" "<<val5<<" from list"<<endl;
    cout<<endl;

    cout<<"Inserting and deleting value to the copied list:"<<endl;
    testList2.insertValue(50);
    testList2.insertValue(23);
    int val6;
    testList2.removeLast(val6);
    testList2.printForward();
    cout<<endl;

    cout<<"Testing with removing value from empty list:"<<endl;
    int val = 0;
    int tempVal = val;
    testList.removeFront(val);
    if (tempVal == val) {
        cout<<"Passed test"<<endl;
    }
    else {
        cout<<"Test failed with removing value from emptied list"<<endl;
    }
    cout<<endl;

    cout<<"Testing with inserting value, get value at index, "
          "and delete backward:"<<endl;
    testList.insertValue(22);
    testList.insertValue(33);
    testList.insertValue(11);
    int indexOneValue;
    testList.getElemAtIndex(1, indexOneValue);
    if (indexOneValue == 22) {
        cout<<"Test passed"<<endl;
    }
    else {
        cout<<"Test failed"<<endl;
    }
    int val7;
    int val8;
    int val9;
    testList.removeLast(val7);
    testList.removeLast(val8);
    testList.removeLast(val9);
    cout<<"Removing value "<<val7<<" "<<val8<<" "<<val9<<" from list"<<endl;
    cout<<endl;

    cout<<"--------------------------------------"<<endl;
    cout<<"Testing queue functions: "<<endl;
    cout<<endl;

    cout<<"Adding values to the queue:"<<endl;
    FIFOQueueClass testQueue;
    testQueue.enqueue(32);
    testQueue.enqueue(44);
    testQueue.enqueue(1);
    testQueue.print();
    cout<<endl;

    cout<<"Test with removing and adding values to the queue"<<endl;
    int outVal;
    testQueue.dequeue(outVal);
    testQueue.enqueue(62);
    testQueue.print();
    cout<<endl;

    cout<<"Removing all values from queue:"<<endl;
    int outVal2;
    int outVal3;
    int outVal4;
    testQueue.dequeue(outVal2);
    testQueue.dequeue(outVal3);
    testQueue.dequeue(outVal4);
    cout<<"Removed value "<<outVal2<<" "<<outVal3<<" "<<
        outVal4<<" from queue"<<endl;
    testQueue.print();
    cout<<endl;

    cout<<"Testing with remove value from emptied queue:"<<endl;
    int outVal5 = 0;
    int tempOutVal = outVal5;
    testQueue.dequeue(outVal5);
    if (tempOutVal == outVal5) {
        cout<<"Test passed"<<endl;
    }
    else {
        cout<<"Test failed"<<endl;
    }
    cout<<endl;

    cout<<"--------------------------------------"<<endl;
    cout<<"Testing stack functions"<<endl;
    cout<<endl;

    cout<<"Inserting nodes:"<<endl;
    LIFOStackClass testStack;
    testStack.push(202);
    testStack.push(3);
    testStack.push(46);
    testStack.print();
    cout<<endl;

    cout<<"Deleting and inserting nodes:"<<endl;
    int out;
    testStack.pop(out);
    testStack.push(92);
    testStack.print();
    cout<<endl;

    cout<<"Deleting all nodes from stack:"<<endl;
    int out2;
    int out3;
    int out4;
    testStack.pop(out2);
    testStack.pop(out3);
    testStack.pop(out4);
    cout<<"Removing values "<<out2<<" "<<out3<<" "<<out4<<" from stack"<<endl;
    cout<<endl;

    cout<<"Deleting a node from empty stack"<<endl;
    int out5 = 0;
    int tempOut = out5;
    testStack.pop(out5);
    if (tempOut == out5) {
        cout<<"Test passed"<<endl;
    }
    else {
        cout<<"Test failed"<<endl;
    }
    return 0;
}

#endif