all: proj4.exe

project4.o: project4.cpp LinkedNodeClass.h SortedListClass.h LIFOStackClass.h FIFOQueueClass.h
	g++ -c -Wall -std=c++98 project4.cpp -o project4.o

SortedListClass.o: SortedListClass.cpp SortedListClass.h LinkedNodeClass.h
	g++ -c -Wall -std=c++98 SortedListClass.cpp -o SortedListClass.o

LinkedNodeClass.o: LinkedNodeClass.cpp LinkedNodeClass.h
	g++ -c -Wall -std=c++98 LinkedNodeClass.cpp -o LinkedNodeClass.o

FIFOQueueClass.o: FIFOQueueClass.cpp FIFOQueueClass.h LinkedNodeClass.h
	g++ -c -Wall -std=c++98 FIFOQueueClass.cpp -o FIFOQueueClass.o

LIFOStackClass.o: LIFOStackClass.cpp LIFOStackClass.h LinkedNodeClass.h
	g++ -c -Wall -std=c++98 LIFOStackClass.cpp -o LIFOStackClass.o

proj4.exe: project4.o SortedListClass.o LinkedNodeClass.o FIFOQueueClass.o LIFOStackClass.o
	g++ project4.o SortedListClass.o LinkedNodeClass.o FIFOQueueClass.o LIFOStackClass.o -o proj4.exe

clean:
	rm -f *.o *.exe
