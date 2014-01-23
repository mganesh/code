#include <iostream>

void rec_permute(std::string sofar, std::string rest) {
	if (rest == "") {
		std::cout << sofar << std::endl;
		return;
	} else {
		for(int i=0; i<rest.length() ; ++i) {
			std::string next = sofar + rest[i];
			std::string remaining = rest.substr(0, i) + rest.substr(i+1);
			//std::cout << "Next: " << next << ", remaining: " << remaining << std::endl;
			rec_permute(next, remaining);
		}
	}
}

void RecSubsets(std::string sofar, std::string rest) {
	if (rest == "") {
		std::cout << sofar << std::endl;
	}
	else {
		RecSubsets(sofar + rest[0], rest.substr(1));
		RecSubsets(sofar, rest.substr(1));
	}
}

void ListSubsets(std::string input) {
	RecSubsets("", input);
}

void permute(const std::string input) {
	rec_permute("", input);
}

int main() {
	std::string input = "abc";
	//permute(input);
	ListSubsets(input);

	return 0;
}