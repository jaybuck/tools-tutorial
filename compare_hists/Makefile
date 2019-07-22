CXX=g++
CXXFLAGS=-std=c++11 -Wall

SRC=jb_histogram.cc
OBJ=$(SRC:%.cc=%.o)
BINSRC=compare.cc compare-test.cc
BINOBJ=$(BINSRC:%.cc=%.o)
BIN=compare compare-test

all: $(OBJ) $(BINOBJ)
	$(CXX) $(CXXFLAGS) -o compare compare.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o compare-test compare-test.o $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o
	rm $(BIN)
