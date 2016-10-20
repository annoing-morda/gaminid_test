#pragma once
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <list>
#include <ostream>
#include <istream>

#define MAX_RATING 5000
#define MAX_LEVEL 100
#define PARAMS_NUMBER 2

typedef std::string id_type;

class player 	/** Contains info about player: his id, rating, level.*/
{
public:
	id_type id;
	unsigned rating;
	unsigned level;
	friend std::ostream& operator << (std::ostream &os, const struct player&);	/** Outputs players info in order: id, rating, level; separator is space. */
	friend std::istream& operator >> (std::istream &is, struct player&);		/** Inputs players info if it is in order: id, rating, level; separator is space. */
	player(id_type = "", unsigned = 0, unsigned = 0);
	player(const player&);
	friend double metric(const player&, const player&); 	/** Defines distance between two players. 
													Bigger metric means players are less suitable 
													to each other. */
};				

double metric(const player&, const player&); 	/** Defines distance between two players. 
													Bigger metric means players are less suitable 
													to each other. */
	
double same_level(double, const player&);			/** Returns difference between ratings of given player p and
													hypothetical player h with same level and metric(p, h) = r*/

double same_rating(double, const player&);			/** Returns difference between levels of given player p and
													hypothetical player h with same rating and metric(p, h) = r*/

class id_compare
{
public:
	bool operator() (const player&, const player&) const;
};

class level_compare
{
public:
	bool operator() (const player&, const player&) const;
};

class rating_compare
{
public:
	bool operator() (const player&, const player&) const;
};

class distance_compare										/** operator() compares two players by distance to the player p */
{
	player p;
public:
	distance_compare(const player&);
	bool operator() (const player&, const player&) const;
};

typedef std::pair<std::set <player, level_compare>::iterator, 
					std::set <player, rating_compare>::iterator > place_of_player;

class players_store {
	std::set <player, level_compare> _level_sorted;
	std::set <player, rating_compare> _rating_sorted;
	std::map <std::string, place_of_player> _players_map;
	std::string _filename;
public:
	players_store(const std::string& = std::string(""));
	~players_store();
	void flush() const;
	bool add_player (const id_type&, unsigned, unsigned);	/** Adds player, returns true if succeed */
	std::list<player> get_competitors(const id_type&, unsigned = PARAMS_NUMBER * 2) const;	/** Returns list of players close to given. */
	void set_filename(const std::string&);
	std::string get_filename() const;
};