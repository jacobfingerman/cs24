FLAGS = -Wall -Wextra -Werror 

main: main.o Stack.o AST.o Nodes.o 
	g++ -o main main.o Stack.o AST.o Nodes.o

test:  test.o Stack.o AST.o Nodes.o 
	g++ -o test test.o Stack.o AST.o Nodes.o 
	
main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

Stack.o: Stack.cpp
	g++ ${FLAGS} -c Stack.cpp

AST.o: AST.cpp
	g++ ${FLAGS} -c AST.cpp

Nodes.o: Nodes.cpp
	g++ ${FLAGS} -c Nodes.cpp

test.o: test.cpp
	g++ ${FLAGS} -c test.cpp



clean:
	-del -f *.exe *.o
	-rm -f *.exe *.o olleh