all: main

main: main.o players_store.o
	g++ -std=c++11 $^ -o $@

main.o: main.cpp
	g++ -std=c++11 -c $<

players_store.o: players_store.cpp
	g++ -std=c++11 -c $<

clean:
	rm -rf *.o main