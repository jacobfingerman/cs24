FLAGS = -Wall -Wextra -Werror 

main: main.o StarMap.o Helpers.o
	g++ -o main main.o StarMap.o Helpers.o 
	
test: test.o StarMap.o Helpers.o
	g++ -o test test.o StarMap.o Helpers.o 
	
main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

StarMap.o: StarMap.cpp
	g++ ${FLAGS} -c StarMap.cpp

Helpers.o: Helpers.cpp
	g++ ${FLAGS} -c Helpers.cpp

test.o: test.cpp
	g++ ${FLAGS} -c test.cpp


clean:
	-del -f *.exe *.o
	-rm -f *.exe *.o olleh