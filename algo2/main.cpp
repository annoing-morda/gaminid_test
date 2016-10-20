#include <iostream>
#include <string>

std::string ip_int_to_str(unsigned ip) {
	const int digit = 256;
	const int v = 4;						// Number of bytes.
	std::string res;
	for(int i = 0; i < v; ++i) {
		res = std::to_string(ip % digit) + res;
		ip /= digit;
		if (i != v - 1) {
			res = "." + res;
		}
	}
	return res;
}


int main() {
	unsigned ip;
	std::cin >> ip;
	std::cout << ip_int_to_str(ip) << std::endl;
	return 0;
}