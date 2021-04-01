#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
        const string &paramFname
)
{
    bool success = true;;
    ifstream paramF;

    paramF.open(paramFname.c_str());

    //Check that the file was able to be opened...
    if (paramF.fail())
    {
        success = false;
        cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
    }
    else
    {
        //Now read in all the params, according to the specified format of
        //the text-based parameter file.
        if (success)
        {
            paramF >> randomSeedVal;
            if (paramF.fail() ||
                randomSeedVal < 0)
            {
                success = false;
                cout << "ERROR: Unable to read/set random generatsor seed" << endl;
            }
        }

        if (success)
        {
            paramF >> timeToStopSim;
            if (paramF.fail() ||
                timeToStopSim <= 0)
            {
                success = false;
                cout << "ERROR: Unable to read/set simulation end time" << endl;
            }
        }

        if (success)
        {
            paramF >> eastWestGreenTime >> eastWestYellowTime;
            if (paramF.fail() ||
                eastWestGreenTime <= 0 ||
                eastWestYellowTime <= 0)
            {
                success = false;
                cout << "ERROR: Unable to read/set east-west times" << endl;
            }
        }

        if (success)
        {
            paramF >> northSouthGreenTime >> northSouthYellowTime;
            if (paramF.fail() ||
                northSouthGreenTime <= 0 ||
                northSouthYellowTime <= 0)
            {
                success = false;
                cout << "ERROR: Unable to read/set north-south times" << endl;
            }
        }

        if (success)
        {
            paramF >> eastArrivalMean >> eastArrivalStdDev;
            if (paramF.fail() ||
                eastArrivalMean <= 0 ||
                eastArrivalStdDev < 0)
            {
                success = false;
                cout << "ERROR: Unable to read/set east arrival distribution" << endl;
            }
        }

        if (success)
        {
            paramF >> westArrivalMean >> westArrivalStdDev;
            if (paramF.fail() ||
                westArrivalMean <= 0 ||
                westArrivalStdDev < 0)
            {
                success = false;
                cout << "ERROR: Unable to read/set west arrival distribution" << endl;
            }
        }

        if (success)
        {
            paramF >> northArrivalMean >> northArrivalStdDev;
            if (paramF.fail() ||
                northArrivalMean <= 0 ||
                northArrivalStdDev < 0)
            {
                success = false;
                cout << "ERROR: Unable to read/set north arrival distribution" << endl;
            }
        }

        if (success)
        {
            paramF >> southArrivalMean >> southArrivalStdDev;
            if (paramF.fail() ||
                southArrivalMean <= 0 ||
                southArrivalStdDev < 0)
            {
                success = false;
                cout << "ERROR: Unable to read/set south arrival distribution" << endl;
            }
        }

        if (success)
        {
            paramF >> percentCarsAdvanceOnYellow;
            if (paramF.fail() ||
                percentCarsAdvanceOnYellow < 0 ||
                percentCarsAdvanceOnYellow > 100)
            {
                success = false;
                cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
            }

            //Use the specified seed to seed the random number generator
            setSeed(randomSeedVal);
        }

        paramF.close();
    }

    //Let the caller know whether things went well or not by printing the
    if (!success)
    {
        cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
             "simulation is NOT setup properly!" << endl;
        isSetupProperly = false;
    }
    else
    {
        cout << "Parameters read in successfully - simulation is ready!" << endl;
        isSetupProperly = true;
    }
}

void IntersectionSimulationClass::printParameters() const
{
    cout << "===== Begin Simulation Parameters =====" << endl;
    if (!isSetupProperly)
    {
        cout << "  Simulation is not yet properly setup!" << endl;
    }
    else
    {
        cout << "  Random generator seed: " << randomSeedVal << endl;
        cout << "  Simulation end time: " << timeToStopSim << endl;

        cout << "  East-West Timing -" <<
             " Green: " << eastWestGreenTime <<
             " Yellow: " << eastWestYellowTime <<
             " Red: " << getEastWestRedTime() << endl;

        cout << "  North-South Timing -" <<
             " Green: " << northSouthGreenTime <<
             " Yellow: " << northSouthYellowTime <<
             " Red: " << getNorthSouthRedTime() << endl;

        cout << "  Arrival Distributions:" << endl;
        cout << "    East - Mean: " << eastArrivalMean <<
             " StdDev: " << eastArrivalStdDev << endl;
        cout << "    West - Mean: " << westArrivalMean <<
             " StdDev: " << westArrivalStdDev << endl;
        cout << "    North - Mean: " << northArrivalMean <<
             " StdDev: " << northArrivalStdDev << endl;
        cout << "    South - Mean: " << southArrivalMean <<
             " StdDev: " << southArrivalStdDev << endl;

        cout << "  Percentage cars advancing through yellow: " <<
             percentCarsAdvanceOnYellow << endl;
    }
    cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
        const string &travelDir
)
{
    EventClass scheduleArr;
    //positive normal distributed time that follows given bound's mean
    //and sd
    int deltaTime;
    //delta time plus current time
    int arrivalTime;
    cout<<"Time: "<<currentTime<<" Scheduled ";
    //decide which travel direction
    if (travelDir == EAST_DIRECTION) {
        deltaTime = getPositiveNormal(eastArrivalMean, eastArrivalStdDev);
        arrivalTime = currentTime + deltaTime;
        scheduleArr = EventClass(arrivalTime, EVENT_ARRIVE_EAST);
    }
    else if (travelDir == WEST_DIRECTION) {
        deltaTime = getPositiveNormal(westArrivalMean, westArrivalStdDev);
        arrivalTime = currentTime + deltaTime;
        scheduleArr = EventClass(arrivalTime, EVENT_ARRIVE_WEST);
    }
    else if (travelDir == NORTH_DIRECTION) {
        deltaTime = getPositiveNormal(northArrivalMean, northArrivalStdDev);
        arrivalTime = currentTime + deltaTime;
        scheduleArr = EventClass(arrivalTime, EVENT_ARRIVE_NORTH);
    }
    else if (travelDir == SOUTH_DIRECTION) {
        deltaTime = getPositiveNormal(southArrivalMean, southArrivalStdDev);
        arrivalTime = currentTime + deltaTime;
        scheduleArr = EventClass(arrivalTime, EVENT_ARRIVE_SOUTH);
    }
    //add event class object scheduleArr to the eventlist
    eventList.insertValue(scheduleArr);
    //print the schedule arrival information
    cout<<scheduleArr<<endl;
}

void IntersectionSimulationClass::scheduleLightChange(
)
{
    //create a event class object
    EventClass scheduledLight;
    cout<<"Time: "<<currentTime<<" Scheduled ";
    //decide what is the current light
    if (currentLight == LIGHT_GREEN_EW) {
        scheduledLight = EventClass(currentTime +
                eastWestGreenTime, EVENT_CHANGE_YELLOW_EW);
    }
    else if (currentLight == LIGHT_YELLOW_EW) {
        scheduledLight = EventClass(currentTime +
                eastWestYellowTime, EVENT_CHANGE_GREEN_NS);
    }
    else if (currentLight == LIGHT_GREEN_NS) {
        scheduledLight = EventClass(currentTime +
                northSouthGreenTime, EVENT_CHANGE_YELLOW_NS);
    }
    else if (currentLight == LIGHT_YELLOW_NS) {
        scheduledLight = EventClass(currentTime +
                northSouthYellowTime, EVENT_CHANGE_GREEN_EW);
    }
    //add scheduledLight to the eventlist
    eventList.insertValue(scheduledLight);
    //print the scheduled light information
    cout<<scheduledLight<<endl;
}

bool IntersectionSimulationClass::handleNextEvent(
)
{
    //return false if the simulation has reached end time
    bool doKeepRun = true;
    //create a eventclass object that copy the last event's information
    EventClass lastEvent;
    //while the eventlist is not empty and simulation haven't end,
    //run the loop to simulate
    while ((eventList.getNumElems() != 0) && doKeepRun) {
        //create a EventClass that will always remove the first
        //event in the event list
        EventClass nextEvent;
        //create a car class object that will add to the four-bound queues
        CarClass nextCar;
        eventList.removeFront(nextEvent);
        currentTime = nextEvent.getTimeOccurs();
        //if current time is after the stop simulation time,
        //end the simulation
        if (currentTime > timeToStopSim) {
            lastEvent = nextEvent;
            doKeepRun = false;
        }
        //if the event happens within the time of simulation
        else {
            cout<<"Handling "<<nextEvent<<endl;
            //if the event type is arrive to one of the four bounds,
            //add a car to the queue of the given direction and
            //print the information of the car and the queue, and
            //schedule the arrival event of the given direction
            if (nextEvent.getType() == EVENT_ARRIVE_EAST) {
                nextCar = CarClass(EAST_DIRECTION, currentTime);
                eastQueue.enqueue(nextCar);
                cout<<nextCar<<" queue length: "<<
                eastQueue.getNumElems()<<endl;
                scheduleArrival(EAST_DIRECTION);
            }
            else if (nextEvent.getType() == EVENT_ARRIVE_WEST) {
                nextCar = CarClass(WEST_DIRECTION, currentTime);
                westQueue.enqueue(nextCar);
                cout<<nextCar<<" queue length: "<<
                westQueue.getNumElems()<<endl;
                scheduleArrival(WEST_DIRECTION);
            }
            else if (nextEvent.getType() == EVENT_ARRIVE_NORTH) {
                nextCar = CarClass(NORTH_DIRECTION, currentTime);
                northQueue.enqueue(nextCar);
                cout<<nextCar<<" queue length: "<<
                northQueue.getNumElems()<<endl;
                scheduleArrival(NORTH_DIRECTION);
            }
            else if (nextEvent.getType() == EVENT_ARRIVE_SOUTH) {
                nextCar = CarClass(SOUTH_DIRECTION, currentTime);
                southQueue.enqueue(nextCar);
                cout<<nextCar<<" queue length: "<<
                southQueue.getNumElems()<<endl;
                scheduleArrival(SOUTH_DIRECTION);
            }
            //if the event type is change light, update the current light
            //and dequeue the car from the given direction queue
            else if (nextEvent.getType() == EVENT_CHANGE_YELLOW_EW) {
                currentLight = LIGHT_YELLOW_EW;
                cout<<"Advancing cars on east-west green"<<endl;
                //integers store the start queue length
                int eastQueueNum = eastQueue.getNumElems();
                int westQueueNum = westQueue.getNumElems();
                //advance cars from east bound
                //if the number of cars in the east bound is less or
                //equal to the time tic of EW green light time
                if (eastQueueNum <= eastWestGreenTime) {
                    //dequeue all of the cars in the queue
                    for (int i = 1; i <= eastQueueNum; i++) {
                        CarClass advancedCar;
                        eastQueue.dequeue(advancedCar);
                        cout<<"  ";
                        cout<<"Car #"<<advancedCar.getId()<<
                        " advanced east-bound"<<endl;
                        //add the total number advanced east
                        numTotalAdvancedEast++;
                    }
                }
                //if the east queue is empty
                else if (eastQueueNum == 0){
                    cout<<"  ";
                    cout<<"No east-bound cars "
                          "waiting to advance on green"<<endl;
                }
                //if the number of cars in the east bound is larger
                //than the time of EW green light
                else {
                    //advance the number of green light time cars
                    for (int i = 1; i <= eastWestGreenTime; i++) {
                        CarClass advancedCar;
                        eastQueue.dequeue(advancedCar);
                        cout<<"  ";
                        cout<<"Car #"<<advancedCar.getId()<<
                        " advanced east-bound"<<endl;
                        numTotalAdvancedEast++;
                    }
                }
                //advance cars from west bound
                //if the number of cars in the west queue is less than the
                //green light time
                if (westQueueNum <= eastWestGreenTime) {
                    //advance all the cars in the west queue
                    for (int i = 1; i <= westQueueNum; i++) {
                        CarClass advancedCar2;
                        westQueue.dequeue(advancedCar2);
                        cout<<"  ";
                        cout<<"Car #"<<advancedCar2.getId()<<
                        " advanced west-bound"<<endl;
                        numTotalAdvancedWest++;
                    }
                }
                //if the west queue is empty
                else if (westQueueNum == 0) {
                    cout<<"  ";
                    cout<<"No west-bound cars "
                          "waiting to advance on green"<<endl;
                }
                //if the number of cars in the west queue is larger than the
                //green light time, advance the green light time of cars
                else {
                    for (int i = 1; i <= eastWestGreenTime; i++) {
                        CarClass advancedCar2;
                        westQueue.dequeue(advancedCar2);
                        cout<<"  ";
                        cout<<"Car #"<<advancedCar2.getId()<<
                        " advanced west-bound"<<endl;
                        numTotalAdvancedWest++;
                    }
                }
                //summarize the number of cars advanced from east and west
                //and the remaining cars
                cout<<"East-bound cars advanced on green: "<<
                eastQueueNum - eastQueue.getNumElems();
                cout<<" Remaining queue: "<<eastQueue.getNumElems()<<endl;
                cout<<"West-bound cars advanced on green: "<<
                westQueueNum - westQueue.getNumElems();
                cout<<" Remaining queue: "<<westQueue.getNumElems()<<endl;
                scheduleLightChange();
            }
            //if the event is advanced cars EW in yellow light
            else if (nextEvent.getType() == EVENT_CHANGE_GREEN_NS) {
                //update the current light
                currentLight = LIGHT_GREEN_NS;
                cout<<"Advancing cars on east-west yellow"<<endl;
                //integers store the number of cars in the east and
                //west queue
                int eastQueueNum = eastQueue.getNumElems();
                int westQueueNum = westQueue.getNumElems();
                //advance cars in the east bound in yellow light
                //if the number of cars in east queue is less than the yellow
                //time
                if (eastQueueNum <= eastWestYellowTime) {
                    //return false if the driver decide not to advance
                    bool decideAdvance = true;
                    int i = 1;
                    while(i <= eastQueueNum && decideAdvance) {
                        //generate a random uniform number
                        int driverDecision = getUniform(1, 100);
                        //if driver decide to advance on yellow, dequeue
                        //a car from east queue
                        if (driverDecision >= 1 &&
                            driverDecision <= percentCarsAdvanceOnYellow) {
                            CarClass advancedCar;
                            eastQueue.dequeue(advancedCar);
                            cout<<"  ";
                            cout<<"Next east-bound car "
                                  "will advance on yellow"<<endl;
                            cout<<"  ";
                            cout<<"Car #"<<advancedCar.getId()<<
                                " advanced east-bound"<<endl;
                            numTotalAdvancedEast++;
                        }
                        //if the driver not decide not advance, all the cars
                        //following should not advance either
                        else {
                            decideAdvance = false;
                            cout<<"  ";
                            cout<<"Next east-bound car "
                                  "will NOT advance on yellow"<<endl;
                        }
                        i++;
                    }
                }
                //if the east queue is empty
                else if (eastQueueNum == 0) {
                    cout<<"  ";
                    cout<<"No east-bound cars waiting "
                          "to advance on yellow"<<endl;
                }
                //if the number of cars in the east queue is larger than
                //the yellow light time
                else {
                    //return false if driver not decide not advance
                    bool decideAdvance = true;
                    int i = 1;
                    while(i <= eastWestYellowTime && decideAdvance) {
                        //generate a random uniform number
                        int driverDecision = getUniform(1, 100);
                        //if driver decide to advance on yellow
                        if (driverDecision >= 1 &&
                            driverDecision <= percentCarsAdvanceOnYellow) {
                            CarClass advancedCar;
                            eastQueue.dequeue(advancedCar);
                            cout<<"  ";
                            cout<<"Next east-bound car "
                                  "will advance on yellow"<<endl;
                            cout<<"  ";
                            cout<<"Car #"<<advancedCar.getId()<<
                                " advanced east-bound"<<endl;
                            numTotalAdvancedEast++;
                        }
                        //if the driver decide not to advance, all the
                        //following cars shouldn't advance either
                        else {
                            decideAdvance = false;
                            cout<<"  ";
                            cout<<"Next east-bound car "
                                  "will NOT advance on yellow"<<endl;
                        }
                        i++;
                    }
                }

                //decide if west bound driver will advance on yellow
                //if the west bound queue is less than yellow time
                if (westQueueNum <= eastWestYellowTime) {
                    bool decideAdvance = true;
                    int i = 1;
                    while(i <= westQueueNum && decideAdvance) {
                        int driverDecision = getUniform(1, 100);
                        //if the driver decide to advance on yellow
                        if (driverDecision >= 1 &&
                            driverDecision <= percentCarsAdvanceOnYellow) {
                            CarClass advancedCar;
                            westQueue.dequeue(advancedCar);
                            cout<<"  ";
                            cout<<"Next west-bound car "
                                  "will advance on yellow"<<endl;
                            cout<<"Car #"<<advancedCar.getId()<<
                                " advanced west-bound"<<endl;
                            numTotalAdvancedWest++;
                        }
                        //if the driver decide not to advance
                        else {
                            decideAdvance = false;
                            cout<<"  ";
                            cout<<"Next west-bound car "
                                  "will NOT advance on yellow"<<endl;
                        }
                        i++;
                    }
                }
                //if the west queue is empty
                else if (westQueueNum == 0) {
                    cout<<"  ";
                    cout<<"No west-bound cars waiting "
                          "to advance on yellow"<<endl;
                }
                //if the west queue length is larger than yellow time
                else {
                    bool decideAdvance = true;
                    int i = 1;
                    while(i <= eastWestYellowTime && decideAdvance) {
                        int driverDecision = getUniform(1, 100);
                        //if the driver decide to advance on yellow
                        if (driverDecision >= 1 &&
                            driverDecision <= percentCarsAdvanceOnYellow) {
                            CarClass advancedCar;
                            westQueue.dequeue(advancedCar);
                            cout<<"  ";
                            cout<<"Next west-bound car "
                                  "will advance on yellow"<<endl;
                            cout<<"Car #"<<advancedCar.getId()<<
                                " advanced west-bound"<<endl;
                            numTotalAdvancedWest++;
                        }
                        //if the driver decide not to advance
                        else {
                            decideAdvance = false;
                            cout<<"  ";
                            cout<<"Next west-bound car "
                                  "will NOT advance on yellow"<<endl;
                        }
                        i++;
                    }
                }
                //summarize the east and west bound advanced cars information
                //and the length of the remaining queue
                cout<<"East-bound cars advanced on yellow: "<<
                    eastQueueNum - eastQueue.getNumElems();
                cout<<" Remaining queue: "<<eastQueue.getNumElems()<<endl;
                cout<<"West-bound cars advanced on yellow: "<<
                    westQueueNum - westQueue.getNumElems();
                cout<<" Remaining queue: "<<westQueue.getNumElems()<<endl;
                scheduleLightChange();
            }
            //if the event type is to advance in NS on green light
            else if (nextEvent.getType() == EVENT_CHANGE_YELLOW_NS) {
                //update the current light
                currentLight = LIGHT_YELLOW_NS;
                cout<<"Advancing cars on north-south green"<<endl;
                int northQueueNum = northQueue.getNumElems();
                int southQueueNum = southQueue.getNumElems();
                //advance cars from north bound
                //if the number of cars in the north bound is less or
                //equal to the time of NS green light
                if (northQueueNum <= northSouthGreenTime) {
                    for (int i = 1; i <= northQueueNum; i++) {
                        CarClass advancedCar;
                        northQueue.dequeue(advancedCar);
                        cout<<"  ";
                        cout<<"Car #"<<advancedCar.getId()<<
                        " advanced north-bound"<<endl;
                        numTotalAdvancedNorth++;
                    }
                }
                //if the north queue is empty
                else if (northQueueNum == 0) {
                    cout<<"  ";
                    cout<<"No north-bound cars "
                          "waiting to advance on green"<<endl;
                }
                //if the number of cars in the north queue is larger
                //than the NS green light time
                else {
                    for (int i = 1; i <= northSouthGreenTime; i++) {
                        CarClass advancedCar;
                        northQueue.dequeue(advancedCar);
                        cout<<"  ";
                        cout<<"Car #"<<advancedCar.getId()<<
                        " advanced north-bound"<<endl;
                        numTotalAdvancedNorth++;
                    }
                }
                //advance cars from south bound
                //decide the number of advanced cars by comparing
                //the south queue length to the NS green time
                if (southQueueNum <= northSouthGreenTime) {
                    for (int i = 1; i <= southQueueNum; i++) {
                        CarClass advancedCar2;
                        southQueue.dequeue(advancedCar2);
                        cout<<"  ";
                        cout<<"Car #"<<advancedCar2.getId()<<
                        " advanced south-bound"<<endl;
                        numTotalAdvancedSouth++;
                    }
                }
                //if the south queue is empty
                else if (southQueueNum == 0) {
                    cout<<"  ";
                    cout<<"No south-bound cars "
                          "waiting to advance on yellow"<<endl;
                }

                //if the number of cars in the south queue is larger
                //than the NS green light time
                else {
                    for (int i = 1; i <= northSouthGreenTime; i++) {
                        CarClass advancedCar2;
                        southQueue.dequeue(advancedCar2);
                        cout<<"  ";
                        cout<<"Car #"<<advancedCar2.getId()<<
                        " advanced south-bound"<<endl;
                        numTotalAdvancedSouth++;
                    }
                }
                //summarize the NS advanced cars information
                //and the length of the remaining queue
                cout<<"North-bound cars advanced on green: "<<
                northQueueNum - northQueue.getNumElems();
                cout<<" Remaining queue: "<<northQueue.getNumElems()<<endl;
                cout<<"South-bound cars advanced on green: "<<
                southQueueNum - southQueue.getNumElems();
                cout<<" Remaining queue: "<<southQueue.getNumElems()<<endl;
                scheduleLightChange();
            }
            //if the event type is advance car on NS yellow light
            else if (nextEvent.getType() == EVENT_CHANGE_GREEN_EW) {
                currentLight = LIGHT_GREEN_EW;
                cout<<"Advancing cars on north-south yellow"<<endl;
                int northQueueNum = northQueue.getNumElems();
                int southQueueNum = southQueue.getNumElems();
                //advance cars in north bound in yellow under
                //probability that driver will advance
                if(northQueueNum <= northSouthYellowTime) {
                    bool decideAdvance = true;
                    int i = 1;
                    //run the loop while the driver decide to advance
                    //on yellow light
                    while(i <= northQueueNum && decideAdvance) {
                        int driverDecision = getUniform(1, 100);
                        //if driver decide to advance on yellow
                        if (driverDecision >= 1 &&
                            driverDecision <= percentCarsAdvanceOnYellow) {
                            CarClass advancedCar;
                            northQueue.dequeue(advancedCar);
                            cout<<"  ";
                            cout<<"Next north-bound car "
                                  "will advance on yellow"<<endl;
                            cout<<"  ";
                            cout<<"Car #"<<advancedCar.getId()<<
                                " advanced north-bound"<<endl;
                            numTotalAdvancedNorth++;
                        }
                        //if the driver decide not to advance, all the
                        //following cars shouldn't advance either
                        else {
                            decideAdvance = false;
                            cout<<"  ";
                            cout<<"Next north-bound car "
                                  "will NOT advance on yellow"<<endl;
                        }
                        i++;
                    }
                }
                //if the north queue is empty
                else if (northQueueNum == 0) {
                    cout<<"  ";
                    cout<<"No north-bound cars "
                          "waiting to advance on yellow"<<endl;
                }
                //if the number of cars in the north queue is larger
                //than the yellow light time
                else {
                    bool decideAdvance = true;
                    int i = 1;
                    //run the loop while the driver decide to advance
                    while(i <= northSouthYellowTime && decideAdvance) {
                        int driverDecision = getUniform(1, 100);
                        //if driver decide to advance on yellow
                        if (driverDecision >= 1 &&
                            driverDecision <= percentCarsAdvanceOnYellow) {
                            CarClass advancedCar;
                            northQueue.dequeue(advancedCar);
                            cout<<"  ";
                            cout<<"Next north-bound car "
                                  "will advance on yellow"<<endl;
                            cout<<"  ";
                            cout<<"Car #"<<advancedCar.getId()<<
                                " advanced north-bound"<<endl;
                            numTotalAdvancedNorth++;
                        }
                        //if the driver decide not to advance
                        else {
                            decideAdvance = false;
                            cout<<"  ";
                            cout<<"Next north-bound car "
                                  "will NOT advance on yellow"<<endl;
                        }
                        i++;
                    }
                }

                //advance cars in south bound in yellow under
                //probability that driver will advance
                if (southQueueNum <= northSouthYellowTime) {
                    bool decideAdvance = true;
                    int i = 1;
                    while(i <=southQueueNum && decideAdvance) {
                        int driverDecision = getUniform(1, 100);
                        //if driver decide to advance on yellow
                        if (driverDecision >= 1 &&
                            driverDecision <= percentCarsAdvanceOnYellow) {
                            CarClass advancedCar;
                            southQueue.dequeue(advancedCar);
                            cout<<"  ";
                            cout<<"Next south-bound car "
                                  "will advance on yellow"<<endl;
                            cout<<"  ";
                            cout<<"Car #"<<advancedCar.getId()<<
                                " advanced south-bound"<<endl;
                            numTotalAdvancedSouth++;
                        }
                        //if the driver decide not to advance
                        else {
                            decideAdvance = false;
                            cout<<"  ";
                            cout<<"Next south-bound car "
                                  "will NOT advance on yellow"<<endl;
                        }
                        i++;
                    }
                }
                //if the south queue is empty
                else if (southQueueNum == 0) {
                    cout<<"  ";
                    cout<<"No south-bound cars "
                          "waiting to advance on yellow"<<endl;
                }
                //if the number of cars in the south queue is larger
                //than the yellow light time
                else {
                    bool decideAdvance = true;
                    int i = 1;
                    while(i <=northSouthYellowTime && decideAdvance) {
                        int driverDecision = getUniform(1, 100);
                        //if driver decide to advance on yellow
                        if (driverDecision >= 1 &&
                            driverDecision <= percentCarsAdvanceOnYellow) {
                            CarClass advancedCar;
                            southQueue.dequeue(advancedCar);
                            cout<<"  ";
                            cout<<"Next south-bound car "
                                  "will advance on yellow"<<endl;
                            cout<<"  ";
                            cout<<"Car #"<<advancedCar.getId()<<
                                " advanced south-bound"<<endl;
                            numTotalAdvancedSouth++;
                        }
                        //if the driver decide not to advance, all the
                        //following cars shouldn't advance either
                        else {
                            decideAdvance = false;
                            cout<<"  ";
                            cout<<"Next south-bound car "
                                  "will NOT advance on yellow"<<endl;
                        }
                        i++;
                    }
                }
                //summarize the NS advanced cars information and
                //the length of the remaining queue length
                cout<<"North-bound cars advanced on green: "<<
                    northQueueNum - northQueue.getNumElems();
                cout<<" Remaining queue: "<<northQueue.getNumElems()<<endl;
                cout<<"South-bound cars advanced on green: "<<
                    southQueueNum - southQueue.getNumElems();
                cout<<" Remaining queue: "<<southQueue.getNumElems()<<endl;
                scheduleLightChange();
            }

            //compare if the each queue has the max length, if it's max
            //length, store it as the max queue length
            if (eastQueue.getNumElems() > maxEastQueueLength) {
                maxEastQueueLength = eastQueue.getNumElems();
            }
            if (westQueue.getNumElems() > maxWestQueueLength) {
                maxWestQueueLength = westQueue.getNumElems();
            }
            if (northQueue.getNumElems() > maxNorthQueueLength) {
                maxNorthQueueLength = northQueue.getNumElems();
            }
            if (southQueue.getNumElems() > maxSouthQueueLength) {
                maxSouthQueueLength = southQueue.getNumElems();
            }
            cout<<endl;
        }
    }
    //print the information of the last event right after the simulation
    //stop time
    cout<<"Next event occurs AFTER the simulation end time (";
    cout<<lastEvent<<")"<<endl;
    return doKeepRun;
}

void IntersectionSimulationClass::printStatistics(
) const
{
    cout << "===== Begin Simulation Statistics =====" << endl;
    cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
    cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
    cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
    cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
    cout << "  Total cars advanced east-bound: " <<
         numTotalAdvancedEast << endl;
    cout << "  Total cars advanced west-bound: " <<
         numTotalAdvancedWest << endl;
    cout << "  Total cars advanced north-bound: " <<
         numTotalAdvancedNorth << endl;
    cout << "  Total cars advanced south-bound: " <<
         numTotalAdvancedSouth << endl;
    cout << "===== End Simulation Statistics =====" << endl;
}
