FLAGS = -Wall -Wextra -Werror 

main: main.o Dictionary.o Heap.o Point.o 
	g++ -o main main.o Dictionary.o Heap.o Point.o

test:  test.o Dictionary.o Heap.o Point.o 
	g++ -o test test.o Dictionary.o Heap.o Point.o 
	
main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

Dictionary.o: Dictionary.cpp
	g++ ${FLAGS} -c Dictionary.cpp

Heap.o: Heap.cpp
	g++ ${FLAGS} -c Heap.cpp

Point.o: Point.cpp
	g++ ${FLAGS} -c Point.cpp

test.o: test.cpp
	g++ ${FLAGS} -c test.cpp



clean:
	-del -f *.exe *.o
	-rm -f *.exe *.o olleh