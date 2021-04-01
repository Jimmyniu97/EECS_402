all: proj3.exe

project3.o: project3.cpp RowColumnClass.h RectangleClass.h ColorImageClass.h ColorClass.h PatternClass.h constants.h
	g++ -c -Wall -std=c++98 project3.cpp -o project3.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h
	g++ -c -Wall -std=c++98 RowColumnClass.cpp -o RowColumnClass.o

RectangleClass.o: RectangleClass.cpp RectangleClass.h
	g++ -c -Wall -std=c++98 RectangleClass.cpp -o RectangleClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h
	g++ -c -Wall -std=c++98 ColorImageClass.cpp -o ColorImageClass.o

ColorClass.o: ColorClass.cpp ColorClass.h
	g++ -c -Wall -std=c++98 ColorClass.cpp -o ColorClass.o

PatternClass.o: PatternClass.cpp PatternClass.h
	g++ -c -Wall -std=c++98 PatternClass.cpp -o PatternClass.o

proj3.exe: RowColumnClass.o RectangleClass.o project3.o ColorImageClass.o ColorClass.o PatternClass.o
	g++ RowColumnClass.o RectangleClass.o project3.o ColorImageClass.o ColorClass.o PatternClass.o -o proj3.exe

clean:
	rm -f *.o *.exe
