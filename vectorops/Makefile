C := clang
CFLAGS := -O2
CXX := g++
CXXFLAGS := -std=c++11 -Wall

CSRC := $(wildcard *.c)
CBIN := $(CSRC:%.c=%)

all: $(CBIN)

$(CBIN): %: %.c
	$(C) $(CFLAGS) -o $@ $<

test:
	@echo "CSRC " $(CSRC)
	@echo "CBIN " $(CBIN)

clean:
	rm $(CBIN)
