#include "rating_store.h"
#include <iostream>

#define FNAME "file.txt"

int main() {
	rating_store rs(FNAME);
	
	// std::cout << "created \n";
	auto top = rs.get_top(3);

	for(auto it = top.begin(); it != top.end(); ++it) {
		std::cout << it->id << " " << it->rating << std::endl;
	}

	rs.add_player(std::string("2brulit"), 1500);

	// rs.add_player(std::string("kostya"), 1562);

	// rs.add_player(std::string("grablyu_korovany"), 1502);	


	rs.change_rating(std::string("kostya"), 1362);



	return 0;
}