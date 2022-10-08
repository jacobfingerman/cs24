FLAGS = -Wall -Wextra -Werror

test: test.o FibVec.o
	g++ -o test test.o FibVec.o
	
test.o: test.cpp
	g++ ${FLAGS} -c test.cpp

FibVec.o: FibVec.cpp
	g++ ${FLAGS} -c FibVec.cpp

clean:
	-del -f *.exe *.o
	-rm -f *.exe *.o olleh