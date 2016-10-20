all: main

main: main.o ip_store.o
	g++ -std=c++11 $^ -o $@

main.o: main.cpp
	g++ -std=c++11 -c $<

ip_store.o: ip_store.cpp
	g++ -std=c++11 -c $<

clean:
	rm -rf *.o