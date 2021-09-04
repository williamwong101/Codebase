CXX=g++
CXXFLAGS=-std=c++17 -g

all: client server

%: %.cpp %.h
	${CXX} ${CXXFLAGS} $< -o $@

.PHONY: clean

clean:
	rm client server core
