FLAGS = -Wall -Wextra -Werror 

test: test.o List.o
	g++ -o test test.o List.o
	
test.o: test.cpp
	g++ ${FLAGS} -c test.cpp

FibVec.o: List.cpp
	g++ ${FLAGS} -c List.cpp

clean:
	-del -f *.exe *.o
	-rm -f *.exe *.o olleh