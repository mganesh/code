#include <iostream>
#include <vector>

typedef int Type;
typedef std::vector<Type> Container;
const int range = 10;

void CoutingSort(const Container& input) {
	Type count[range+1];
	const int length = input.size();
	// Initialize the count
	for(int i=0; i<range+1; ++i)
		count[i] = 0;

	// find the frequency
	for(int i=0; i<length; ++i)
		count[input[i]+1]++;

	// find the starting index
	for(int i=0; i<range; ++i)
		count[i+1] += count[i];

	// place the element in correct position
	Type *Aux = new Type[length];
	for(int i=0; i<length; ++i) {
		Aux[count[input[i]]++ ] = input[i];
	}

	for(int i=0; i<length; ++i)
		std::cout << Aux[i] << " ";
	std::cout << std::endl;

	delete [] Aux;
}

int main()
{
	int array[] = {5,6,2,1,4,3,7,9, 8, 0};
	const int size = sizeof(array)/sizeof(array[0]);

	Container input(array, array+size);
	CoutingSort(input);
}