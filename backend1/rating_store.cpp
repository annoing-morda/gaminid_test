#include "rating_store.h"

rating_store::rating_store(std::string filename) {
	_filename = filename;
	std::ifstream fin;
	fin.open(filename);
	unsigned size;
	fin >> size;
	_leader_board.resize(size);
	for(unsigned i = 0; i < size; ++i) {
		fin >> _leader_board[i].id >> _leader_board[i].rating;
		_players_map[_leader_board[i].id] = i;
	}
	fin.close();
}

void rating_store::flush() {
	std::ofstream fout;
	fout.open(_filename);
	fout << _leader_board.size() << std::endl;
	for(auto it = _leader_board.begin(); it != _leader_board.end(); ++it) {
		fout << it->id << " " << it->rating << std::endl;
	}
	fout.close();
}

rating_store::~rating_store() {
	flush();
}

std::list< player_info > rating_store::get_top(unsigned n) const {
	std::list< player_info > res;
	for(int i = 0; (i < n) && (i < _leader_board.size()); ++i) {
		res.push_back(_leader_board[i]);
	}	
	return res;
}

unsigned rating_store::get_place(id_type id) const {
	return _players_map.find(id)->second;
}

void rating_store::swap(unsigned index1, unsigned index2) {
	id_type id1 = _leader_board[index1].id;
	id_type id2 = _leader_board[index2].id;
	_players_map[id1] = index2;
	_players_map[id2] = index1;
	std::swap(_leader_board[index1], _leader_board[index2]);	
}

void rating_store::add_player(id_type id, unsigned rating) {
	if(_players_map.find(id) != _players_map.end()) {
		return;
	}
	player_info new_player;
	new_player.id = id;
	new_player.rating = rating;
	_leader_board.push_back(new_player);
	unsigned new_index = _leader_board.size() - 1;
	while (new_index > 0) {										// Insertion to correct place.
		if (rating > _leader_board[new_index - 1].rating) {
			swap(new_index, new_index - 1);
			--new_index;
		} else {
			break;
		}
	}
	_players_map[id] = new_index;								// Updating map.
}

void rating_store::change_rating(id_type id, unsigned rating) {
	if(_players_map.find(id) == _players_map.end()) {
		return;
	}
	unsigned index = _players_map[id];
	_leader_board[index].rating = rating;
	while (index > 0) {											// Insertion to correct place.
		if (rating > _leader_board[index - 1].rating) {
			swap(index, index - 1);
			--index;
		} else {
			break;
		}
	}	
	while (index < _leader_board.size() - 1) {											// Insertion to correct place.
		if (rating < _leader_board[index + 1].rating) {
			swap(index, index + 1);
			++index;
		} else {
			break;
		}
	}	
	_players_map[id] = index;									// Updating map.
}



