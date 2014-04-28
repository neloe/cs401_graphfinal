.PHONY: clean flags

CXX = g++
CXXFLAGS = -std=c++0x -g

ifeq (${CXX}, clang++)
	CXXFLAGS = -std=c++11 -g
endif

HEADERS = $(wildcard *.{h,hpp})

SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:%.cpp=%.o)

default: driver

%.o: %.cpp
	@${CXX} ${CXXFLAGS} -c $< -o $@

driver: driver.o lorenz.o
	@${CXX} ${CXXFLAGS} $^ -o $@
	
seq: seq_lorenz.o
	${CXX} ${CXXFLAGS} $^ -o $@

clean:
	-@rm -f seq
	-@rm -f $(OBJS)

flags:
	-@echo ${CXXFLAGS}
