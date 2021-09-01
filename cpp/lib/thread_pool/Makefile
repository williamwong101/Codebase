CXX=clang++
CXXFLAGS=--std=c++17 -g -pthread

SHELL := /bin/bash
%: %.cpp *.h
	${CXX}  ${CXXFLAGS} $< -o $@

.PHONY: clean

clean:
	@for file_ in $$(ls) ; do file $${file_} | \
	grep -q "ELF" && rm $${file_} && \
	printf "rm $${file_}\n"; done ; true
