#include "ip_store.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define BYTE_PER_ADDR 4
#define BYTE_MAX 256

#define abs(a) (((a) > 0 ) ? (a) : -(a))

int main() {
	std::srand(std::time(0));
	accurate_store accurate;
	approx_store approx;
	for(int i = 0; i < 100000; ++i) {
		unsigned ip = 0;
		for(int j = 0; j < BYTE_PER_ADDR; ++j) {
			ip += std::rand() % BYTE_MAX;
			ip *= (j != BYTE_PER_ADDR - 1) ? BYTE_MAX : 1;
		}
		accurate.add_ip(ip);
		approx.add_ip(ip);
		accurate.add_ip(ip);
		approx.add_ip(ip);
		double acc_number = (double) accurate.get_unique_users_number();
		double app_number = (double) approx.get_unique_users_number();
		double mistake = abs(acc_number - app_number) / (acc_number);
		if(mistake > 0.05) {
			std::cout<<mistake<<std::endl;
		}
	}
	return 0;
}
