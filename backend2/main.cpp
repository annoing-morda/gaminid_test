#include "players_store.h"
#include <string>
#include <ctime>
#include <iostream>

int main() {
	std::srand(std::time(0));
	players_store ps("file.txt");
	auto l = ps.get_competitors("player41", 5);
	for(auto it = l.begin(); it != l.end(); ++it) {
		std::cout<<*it<<std::endl;
	}
	//int counter = 0;
	//for(int i = 0; i < 1000; ++i) {
	//	counter += ps.add_player(std::string ("player" + std::to_string(i)), 
	//		std::rand() % (MAX_LEVEL + 1), 
	//		std::rand() % (MAX_RATING + 1)) ? 1 : 0;
	//}
	// ps.set_filename("file.txt");
	// std::cout<<ps.get_filename();
	return 0;
}