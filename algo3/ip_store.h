#pragma once
#include <set>
#include <vector>
#include <list>

class a_store {
public:
	virtual void add_ip(unsigned) = 0;						/** Adds ip to the store. */
	virtual unsigned get_unique_users_number() const = 0;	/** Returns number of unique users. */
};

class accurate_store : public a_store {			/** Class for accurate definition of unique users number. */
	std::set<unsigned> _store;
public:
	accurate_store();
	~accurate_store();
	virtual void add_ip(unsigned);
	unsigned get_unique_users_number() const;
};

class approx_store : public a_store {			/** Class for approximal definition of unique users number. */
	std::vector<std::list<unsigned> > _table;	// Hash-table.
	int _capacity, _fill;						// Size of table and numer of filled nodes.
	int degradation_number, degradation_size;	// Number of nodes with more than one ip
	const double MAX_MISTAKE = 0.05;				// Available mistake of unique users number.
	void rebuild_table(unsigned);
	inline bool mistake_too_big() const;
public:
	approx_store();
	~approx_store();
	virtual void add_ip(unsigned);
	unsigned get_unique_users_number() const;

};
