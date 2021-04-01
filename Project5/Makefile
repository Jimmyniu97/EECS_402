all: proj5.exe

project5.o: project5.cpp IntersectionSimulationClass.h random.h constants.h
	g++ -c -Wall -std=c++98 project5.cpp -o project5.o

CarClass.o: CarClass.cpp CarClass.h constants.h
	g++ -c -Wall -std=c++98 CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h constants.h
	g++ -c -Wall -std=c++98 EventClass.cpp -o EventClass.o

random.o: random.cpp random.h
	g++ -c -Wall -std=c++98 random.cpp -o random.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h SortedListClass.h SortedListClass.inl LinkedNodeClass.h LinkedNodeClass.inl FIFOQueueClass.h FIFOQueueClass.inl EventClass.h CarClass.h constants.h random.h
	g++ -c -Wall -std=c++98 IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

proj5.exe: project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o
	g++ project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o -o proj5.exe

clean:
	rm -f *.o *.exe
