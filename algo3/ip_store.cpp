#include "ip_store.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))

accurate_store::accurate_store(){}

accurate_store::~accurate_store(){}

void accurate_store::add_ip(unsigned ip) {
	_store.insert(ip);
}

unsigned accurate_store::get_unique_users_number() const {
	return _store.size();
}

approx_store::approx_store() {
	_capacity = 256;
	degradation_number = 0;
	degradation_size = 0;
	_table.resize(_capacity);
}

approx_store::~approx_store(){}

std::pair <bool, unsigned> hash_table_insert (std::vector<std::list <unsigned> >& table, unsigned val) {		// Returns true if this ip is new in the node and insertion index.
	unsigned insertion_index = val % table.size();
	std::list<unsigned> & l = table[insertion_index];
	for(auto it = l.begin(); it != l.end(); ++it) {
		if (*it == val) {
			return std::make_pair(false, insertion_index);;
		}
	}
	bool res = l.empty();
	l.push_back(val);
	return std::make_pair(res, insertion_index);
}

void approx_store::rebuild_table(unsigned new_size) {
	std::vector<std::list <unsigned> > new_table(new_size);
	_fill = 0;
	degradation_size = degradation_number = 0;
	for(int i = 0; i < _capacity; ++i) {
		std::list<unsigned> & l = _table[i];
		for(auto it = l.begin(); it != l.end(); ++it) {
			_fill += (hash_table_insert(new_table, *it).first) ? 1 : 0;
		}
	}
	_table = std::move(new_table);
	_capacity = new_size;
	for(auto it = _table.begin(); it != _table.end(); ++it) {
		if(it->size() >= 2) {
			++degradation_number;
			degradation_size = max(it->size(), degradation_number);
		}
	}
	if(mistake_too_big()) {
		rebuild_table(_capacity * 2);
	}
}

unsigned approx_store::get_unique_users_number() const {
	return _fill + (degradation_number * degradation_size) / 2;
}

inline bool approx_store::mistake_too_big() const {
	double deviation = (double)(degradation_number * degradation_size) / 2.0;
	double mistake = deviation / ((double)_fill + deviation);
	return mistake > MAX_MISTAKE;
}

void approx_store::add_ip(unsigned ip) {
	auto insertion_res = hash_table_insert(_table, ip);
	if(insertion_res.first) {
		++_fill;
		return;
	}
	unsigned index = insertion_res.second;
	if(_table[index].size() > degradation_size) {
		++degradation_size;
	}
	if(_table[index]. size() == 2) {				// We have new degradates node.
		++degradation_number;
	}
	if(mistake_too_big()) {
		rebuild_table(_capacity * 2);	
	}
}