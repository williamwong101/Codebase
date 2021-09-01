SHELL := /bin/bash
reflection: reflection.cpp reflection.h
	clang++ --std=c++14 $< -o $@

.PHONY: clean

clean:
	@for file_ in $$(ls) ; do file $${file_} | \
	grep -q "executable" && rm $${file_} && \
	printf "rm $${file_}\n"; done ; True
