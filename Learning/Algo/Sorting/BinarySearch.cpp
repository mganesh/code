#include <iostream>

bool recursive_search(int array[], int begin, int end, int k) {

	if (begin > end) 
		return false;

	if (begin == end) return (array[begin] == k);

	int mid = (end + begin)/2;
	if (array[mid] == k) return true;
	else if (array[mid] > k) 
		return recursive_search(array, begin, mid-1, k);
	else
		return recursive_search(array, mid+1, end, k);

	return false;
}

int main() {
	int array[] = { 2, 4, 5, 6, 7, 8,9};
	const int size = sizeof(array)/sizeof(array[0]);
	std::cout << "Found? " << recursive_search(array, 0, size-1, 3) << std::endl;
	return 0;
}