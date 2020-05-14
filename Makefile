CXXFLAGS=-std=gnu++11

all: triad

triad: main.o triad.o
	$(CXX) main.o triad.o -o triad

main.o: src/main.cpp src/triad.hpp src/dictionary.hpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o

triad.o: src/triad.cpp src/triad.hpp src/dictionary.hpp
	$(CXX) $(CXXFLAGS) -c src/triad.cpp -o triad.o

clean:
	-rm -f *.o triad
