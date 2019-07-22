CXX=g++
CXXFLAGS=-std=c++11 -Wall
BIN=mylist_main
SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o
	rm $(BIN)

test:
	@echo "SRC " $(SRC)
	@echo "OBJ " $(OBJ)
	@echo "BIN " $(BIN)
