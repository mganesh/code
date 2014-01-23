#include <iostream>
#include <vector>
#include <algorithm>


typedef std::vector<int> Container;
void print(const Container& data) {
	const int length = data.size();
	for(int i=0; i<length; ++i)
		std::cout << data[i] << " ";
	std::cout << std::endl;
}

void findNumbers(Container& input, int k) {

	// 1. Sort input - O(n log n)
	std::sort(input.begin(), input.end());
	const int length = input.size();
	

	// 2. Form set S' = { z: z = x-y for some y (- input }
	Container dash;

	// O(n)
	for(int i=0; i<length; ++i)
		dash.push_back( k - (input[i]));
	
	// 3. sort S' O(n log n)

	std::sort(dash.begin(), dash.end());

	// 4. Remove duplicates
	input.erase ( std::unique( input.begin(), input.end()), input.end());
	dash.erase(std::unique(dash.begin(), dash.end()), dash.end());
	print(input);
	print(dash);

	// 4. Merge S & S'
	const int mergelength = input.size() + dash.size();

	Container mergedList;
	mergedList.resize(mergelength);

	std::merge(input.begin(), input.end(),
				dash.begin(), dash.end(),
				mergedList.begin());

	const int n = mergedList.size();

	print(mergedList);

	int first = 0;
	int second = 0;

	for(int i = 1; i < n; ++i) { 
		if (mergedList[i-1] == mergedList[i]) {
			if (!first) first = mergedList[i];
			else second = mergedList[i];
		}

	}

	if (first && second)
		std::cout << first << " + " << second << " = " << k << std::endl;
	else
		std::cout << "No match found" << std::endl;
}

int main() {
	
	int array [] = { 1, 5, 8, 4, 3, 9, 12, 14 , 15, 16};
	const int size = sizeof(array)/sizeof(array[0]);
	std::vector<int> input(array, array+size);
	findNumbers(input, 9);
	return 0;
}