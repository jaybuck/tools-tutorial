CXX := g++
CXXFLAGS := -std=c++11 -Wall

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)
BINS := $(SRCS:%.cpp=%)

all: $(BINS)

$(BINS): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

test:
	@echo "SRCS " $(SRCS)
	@echo "OBJS " $(OBJS)
	@echo "BINS " $(BINS)

clean:
	rm -f *.o
	rm $(BINS)
