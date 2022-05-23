

CXXFLAGS= -Wall 


main: main.o Graf.o UI.o
	g++ -Wall -o main main.o Graf.o UI.o

main.o: main.cpp UI.h Graf.h
	g++ -c ${CXXFLAGS} -o main.o main.cpp

Graf.o: Graf.cpp Graf.h struktury.h
	g++ -c ${CXXFLAGS} -o Graf.o Graf.cpp

UI.o: UI.cpp UI.h
	g++ -c ${CXXFLAGS} -o UI.o UI.cpp