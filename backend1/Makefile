all: main

main: main.o rating_store.o
	g++ -std=c++11 $^ -o $@

main.o: main.cpp
	g++ -std=c++11 -c $^

rating_store.o: rating_store.cpp
	g++ -std=c++11 -c $^

clean:
	rm -rf *.o main	