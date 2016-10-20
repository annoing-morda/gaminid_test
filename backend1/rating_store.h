#pragma once
#include <string>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <utility>

typedef std::string id_type;

typedef struct {
	id_type id;
	unsigned rating;
} player_info;

class rating_store {
	std::vector <player_info> _leader_board;		
	std::map <id_type, unsigned> _players_map;						// Key is players' id, second is place in leaderboard.
	std::string _filename;										
	void swap(unsigned, unsigned);									// Swaps two players in leaderboard.
public:
	rating_store(std::string);										/** Reads data from file with given name.
																		Format: first string is number of players;
																		in others: id, space, rating.
																		Sorted by rating.  */	
	~rating_store();
	std::list< player_info > get_top(unsigned) const;	/** Returns top-n of players sorted by rating. */
	unsigned get_place(id_type) const;							/** Returns place in rating of player with given id. */
	void add_player(id_type, unsigned);							/** Adds player to collection. */
	void change_rating(id_type, unsigned);						/** Changes players rating. */
	void flush();												/** Writes data to file. */
};