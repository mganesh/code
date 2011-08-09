// modify boolalpha flag
#include <iostream>

int main () {

	bool b;
	b=true;
	std::cout << boolalpha << b << std::endl;
	std::cout << noboolalpha << b << std::endl;
	return 0;
}
