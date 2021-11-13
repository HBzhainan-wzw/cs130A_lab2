all: project2
project1b: project2.cpp 
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out

