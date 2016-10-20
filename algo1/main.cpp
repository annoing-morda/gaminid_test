#include "list.h"
int main(){
	list<int> l;
	for(int i = 0; i < 10; ++i) {
		l.add(i);
	}
	l.reverse_print();
	return 0;
}