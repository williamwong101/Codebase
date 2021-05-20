CXX = g++
CXXFlAGS = -std=c++17 -g

clean:
	ls | egrep -v "(.+).cc|Makefile" | xargs rm -rf 

% : %.cc
	$(CXX) $(CXXFlAGS) $? -o $@

.PHONY: clean
