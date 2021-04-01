//
//This is the Project 1 for EECS 402
// Created by Yuefeng Niu on 9/18/20.
//
#include<iostream>
using namespace std;

const int BALANCE_LOWER_LIMIT = 1000;
const int BALANCE_HIGHER_LIMIT = 15000;
const double LOW_INTEREST_RATE = 0.0015;
const double MEDIUM_INTEREST_RATE = 0.00225;
const double HIGH_INTEREST_RATE = 0.004;

bool accrueInterest(double &balanceAmt, const int numMonths,
                    const bool doPrintEachMonth);
bool accrueOneMonthsInterest(double &balanceAmt, const bool doPrintInfo);

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main(){
    double balanceAmt; int numMonths; double initialBalance;
    char userAnswer; bool printInfo; bool operationSuccess;

    cout<<"Enter the initial balance of the account: "<<endl;
    cin>>balanceAmt;
    cout<<"Enter the number of months to accrue interest: "<<endl;
    cin>>numMonths;
    cout<<"Show month-by-month results -'y' for yes, any other for no: "<<endl;
    cin>>userAnswer;

    //Store the initial balance value
    initialBalance = balanceAmt;

    //Decide whether print information based on user's answer
    if (userAnswer == 'y'){
        printInfo=true;
    }
    else{
        printInfo=false;
    }

    operationSuccess=accrueInterest(balanceAmt, numMonths, printInfo);

    //Check if the deposit function operated successful
    if (operationSuccess){
        cout<<"Initial balance: "<<initialBalance<<endl;
        cout<<"Total interest accrued: "<<balanceAmt-initialBalance<<endl;
        cout<<"Final balance: "<<balanceAmt<<endl;
    }
    else{
        cout<<"Sorry, an error was detected.  Unable to provide results!"<<endl;
    }

    return 0;
}

#endif

bool accrueInterest(double &balanceAmt, const int numMonths,
                    const bool doPrintEachMonth){
    int month;
    bool operationSuccess;
    if (numMonths <= 0){
        cout<<"ERROR in accrueInterest: numMonths must be > 0, but the value "<<
        numMonths<<" was provided!"<<endl;
        return false;
    }
    else{
        for (month = 1; month <= numMonths; month++){
            operationSuccess =
                    accrueOneMonthsInterest(balanceAmt,doPrintEachMonth);
            if (!operationSuccess){
                return false;
            }
        }
        cout<<"Interest accrued for "<<numMonths<<" months!"<<endl;
        return true;
    }
}

bool accrueOneMonthsInterest(double &balanceAmt, const bool doPrintInfo){
    double interestRate;

    if (balanceAmt < BALANCE_LOWER_LIMIT){
        interestRate = LOW_INTEREST_RATE;
    }
    else if (balanceAmt >= BALANCE_HIGHER_LIMIT){
        interestRate = HIGH_INTEREST_RATE;
    }
    else if (balanceAmt >= BALANCE_LOWER_LIMIT &&
    balanceAmt < BALANCE_HIGHER_LIMIT){
        interestRate = MEDIUM_INTEREST_RATE;
    }

    if (balanceAmt < 0){
        cout<<"ERROR in accrueOneMonthsInterest: "
              "balanceAmt must be >= 0, but the value "<<
        balanceAmt<<" was provided!"<<endl;
        return false;
    }
    else{
        if (doPrintInfo) {
            cout << "Accruing interest for 1 month: " << endl;
            cout<<"Initial balance: "<<balanceAmt<<endl;
            cout<<"Initial rate: "<<interestRate<<endl;
            cout<<"Interest accrued: "<<interestRate * balanceAmt<<endl;
            balanceAmt = (1+interestRate) * balanceAmt;
            cout<<"New balance: "<<balanceAmt<<endl;
        }
        else{
            balanceAmt = (1 + interestRate) * balanceAmt;
        }
        return true;
    }
}
