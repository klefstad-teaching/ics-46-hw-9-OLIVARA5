CXX = g++
CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic
LDFLAGS = -lgtest -lgtest_main -pthread  

all: main

main: src/dijkstras_main.cpp dijkstras.o student_gtests.o ladder.o
	$(CXX) $(CXXFLAGS) src/dijkstras_main.cpp -o main dijkstras.o student_gtests.o ladder.o $(LDFLAGS)

dijkstras.o: src/dijkstras.cpp
	$(CXX) $(CXXFLAGS) -c src/dijkstras.cpp -o dijkstras.o


student_gtests.o: gtest/student_gtests.cpp
	$(CXX) $(CXXFLAGS) -c gtest/student_gtests.cpp -o student_gtests.o

ladder.o: src/ladder.cpp
	$(CXX) $(CXXFLAGS) -c src/ladder.cpp -o ladder.o

clean:
	rm -f *.o main