#include "players_store.h"
#include <fstream>

player::player(id_type _id, unsigned _level, unsigned _rating) : id(_id), level(_level), rating(_rating) {}

player::player(const player& p) : id(p.id), level(p.level), rating(p.rating) {}

double metric(const player& p1, const player& p2) {	
	double rating_dif = (double) (p1.rating - p2.rating);
	rating_dif *= rating_dif / ((double) MAX_RATING * MAX_RATING);
	double level_dif = p1.level - p2.level;
	level_dif *= level_dif / ((double) MAX_LEVEL * MAX_LEVEL);
	return rating_dif + level_dif;
}

double same_level(double r, const player& p) {
	return (double) MAX_RATING * std::sqrt(r);
}

double same_rating(double r, const player& p) {
	return (double) MAX_LEVEL * std::sqrt(r);
}

bool id_compare::operator()(const player& p1, const player& p2) const {
	return p1.id < p2.id;
}

bool level_compare::operator()(const player& p1, const player& p2) const {
	if(p1.level == p2.level) {
		return p1.rating < p2.rating;
	}
	return p1.level < p2.level;
}

bool rating_compare::operator()(const player& p1, const player& p2) const {
	if(p1.rating == p2.rating) {
		return p1.level <p2.level;
	}
	return p1.rating < p2.rating;
}

std::ostream& operator << (std::ostream &os, const struct player& p) {
	os << p.id << " " << p.rating << " " <<p.level;
	return os;
}

std::istream& operator >> (std::istream& is, struct player& p) {
	is >> p.id >> p.rating >> p.level;
	return is;
}

distance_compare::distance_compare(const player& _p) : p(_p) {}

bool distance_compare::operator() (const player& p1, const player& p2) const {
	return metric(p, p1) < metric (p, p2);
} 

players_store::players_store(const std::string& fname) {
	_filename = fname;
	if(fname.size() != 0) {
		std::ifstream fin;
		fin.open(fname);
		if( !fin.good() ) {
			return;
		}
		unsigned size;
		fin >> size;
		while(size > 0 && ! fin.eof()) {
			--size;
			player new_player;
			fin >> new_player;
			_players_map[new_player.id] = std::make_pair(_level_sorted.insert(new_player).first, 
												   _rating_sorted.insert(new_player).first);
		}
		fin.close();
	}
}

players_store::~players_store () {
	if(_filename.size() != 0) {
		std::ofstream fout;
		fout.open(_filename);
		if(fout.good()) {
			fout << _players_map.size() << std::endl;
			while(!_level_sorted.empty()) {
				fout << *_level_sorted.begin() << std::endl;
				_level_sorted.erase(_level_sorted.begin());
			}
			fout.close();
		}
	}
}

void players_store::flush() const {
	if(_filename.size() != 0) {
		std::ofstream fout;
		fout.open(_filename);

		if(fout.good()) {
			fout << _players_map.size() << std::endl;

			for(auto it = _level_sorted.begin(); it != _level_sorted.end(); ++it) {
				fout << *it << std::endl;
			}

			fout.close();
		}
	}
}

bool players_store::add_player(const id_type& id, unsigned level, unsigned rating) {
	if(_players_map.find(id) != _players_map.end()) {
		return false;
	}
	player new_player(id, level, rating);

	_players_map[id] = std::make_pair(_level_sorted.insert(new_player).first, 
												   _rating_sorted.insert(new_player).first);
	return true;
}

void players_store::set_filename(const std::string& fname) {
	_filename = fname;
}

std::string players_store::get_filename() const {
	return _filename;
}

std::list<player> players_store::get_competitors(const id_type& id, unsigned num) const {
	place_of_player place;
	try {
		place = _players_map.at(id);
	} catch(std::out_of_range&) {
		std::list<player> l;
		return l;
	}
	auto level_it = place.first;
	auto rating_it = place.second;
	auto current_player = *level_it;
	distance_compare comparator(current_player);
	std::set<player, distance_compare> closest_players(comparator);
	// Adding neighbors of given player
	closest_players.insert(*(--level_it));			
	++level_it;
	closest_players.insert(*(++level_it));
	--level_it;
	closest_players.insert(*(--rating_it));			
	++rating_it;
	closest_players.insert(*(++rating_it));
	--rating_it;

	double r = metric (current_player, *(closest_players.begin()));	// We make circle where center is current player
																	// and radius equals distance between current player
																	// and the closest neighbor.
	double level_dif = same_rating(r, current_player);				// Than circumscribe the circle with
	double rating_dif = same_level(r, current_player);				// square having sides parallel to axes.
																	// And chose all players in this square.
	auto it = level_it;

	while(std::abs(it->level - current_player.level) <= level_dif 
		&& std::abs(it->rating - current_player.rating) <= rating_dif) {
		closest_players.insert(*it);
		++it;
	}

	it = level_it;

	while(std::abs(it->level - current_player.level) <= level_dif 
		&& std::abs(it->rating - current_player.rating) <= rating_dif) {
		closest_players.insert(*it);
		--it;
	}

	std::list<player> result;										// Then return as many close players as we can and need.
	auto answer_it = closest_players.begin();
	while(it != closest_players.end() && num > 0) {
		--num;
		result.push_back(*it);
		++it;
	}
	return result;
}