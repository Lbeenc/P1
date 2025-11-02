CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2

OBJS := main.o scanner.o testScanner.o

P1: $(OBJS)
	$(CXX) $(CXXFLAGS) -o P1 $(OBJS)

main.o: main.cpp scanner.h token.h
scanner.o: scanner.cpp scanner.h token.h
testScanner.o: testScanner.cpp scanner.h token.h

clean:
	rm -f $(OBJS) P1
