FLAGS = -Wall -Wextra -Werror 

main: main.o Atlas.o Helpers.o
	g++ -o main main.o Atlas.o Helpers.o 
	
main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

Atlas.o: Atlas.cpp
	g++ ${FLAGS} -c Atlas.cpp

Helpers.o: Helpers.cpp
	g++ ${FLAGS} -c Helpers.cpp



clean:
	-del -f *.exe *.o
	-rm -f *.exe *.o olleh