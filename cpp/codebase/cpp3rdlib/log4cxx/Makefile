SHELL := /bin/bash
CXX=clang++
CXXFLAGS=--std=c++17
%: %.cpp
	${CXX}  ${CXXFLAGS} $^ -o $@

log: log.cpp
	${CXX}  ${CXXFLAGS} -I/usr/local/Cellar/log4cxx/0.12.0/include \
	-L/usr/local/Cellar/log4cxx/0.12.0/lib -llog4cxx $^ -o $@ 

.PHONY: clean

clean:
	@for file_ in $$(ls) ; do file $${file_} | \
	grep -q "executable" && rm $${file_} && \
	printf "rm $${file_}\n"; done ; True
