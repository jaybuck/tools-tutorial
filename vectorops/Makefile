C := clang
CFLAGS := -O2
CXX := g++
CXXFLAGS := -O2 -std=c++17 -Wall

CSRC := $(wildcard *.c)
CBIN := $(CSRC:%.c=%)

CPPSRC := $(wildcard *.cpp)
CPPBIN := $(CPPSRC:%.cpp=%)

all: $(CBIN) $(CPPBIN)

$(CBIN): %: %.c
	$(C) $(CFLAGS) -o $@ $<

$(CPPBIN): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

test:
	@echo "CSRC " $(CSRC)
	@echo "CBIN " $(CBIN)
	@echo "CPPSRC " $(CPPSRC)
	@echo "CPPBIN " $(CPPBIN)

clean:
	rm $(CBIN) $(CPPBIN)
