FLAGS = -Wall -Wextra -Werror 

test: test.o Set.o Node.o
	g++ -o test test.o Set.o Node.o 
	
test.o: test.cpp
	g++ ${FLAGS} -c test.cpp

Set.o: Set.cpp
	g++ ${FLAGS} -c Set.cpp

Node.o: Node.cpp
	g++ ${FLAGS} -c Node.cpp



clean:
	-del -f *.exe *.o
	-rm -f *.exe *.o olleh