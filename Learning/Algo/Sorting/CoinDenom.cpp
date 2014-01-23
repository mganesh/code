#include <iostream>
#include <limits>

void init(int *input, int size) {
	for(int i=0 ;i<size; ++i)
		input[i] = 0;
}

void print(int *input, int size) {
	for(int i=0; i<size; ++i)
		std::cout << input[i] << " ";
	std::cout << std::endl;
}

void changePlease(int denom[], int denomSize, int Note) {

	int *coin = new int[Note+1];
	int *picks = new int [Note+1];

	init(coin, Note+1);
	init(picks, Note+1);

	coin[0] = 0;
	int coins = -1;

	for(int i=1; i<=Note; ++i) {
		int min = std::numeric_limits<int>::max();


		for(int j=1; j< denomSize; ++j) {
			if ( denom[j] <= i) {

				int index = 0;
				if (i - denom[j] > 0)
					index = i - denom[j];

				int new_min = 1+coin[index];
				
				if (new_min < min) {
					min = new_min;
					coins = i;
				}
			}
		}
		coin[i] = min;
		picks[i] = coins;
	}

	print(coin, Note+1);
	print(picks, Note+1);

}

int main() {
	int denom[] = { 1, 2, 5, 10, 25, 50 };
	const int size = sizeof(denom)/sizeof(denom[0]);

	changePlease(denom, size, 7);
	return 0;
}