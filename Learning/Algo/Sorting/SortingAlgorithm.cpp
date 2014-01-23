#include <iostream>

void print(int *array, int size) {
	for(int i=0; i<size; ++i)
		std::cout << array[i] << " ";
	std::cout << std::endl;
	return;
}

void exch(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selection(int *array, int size) {

	/* Selection Sort:
		1. Find the minimum element in the array
		2. Place it in the 1st position
	*/

	for(int i=0; i<size; ++i) {
		int min = i;
		for(int j=i+1; j<size; ++j) {
			if (array[min] > array[j]) {
				min = j;
			}
		}
		exch(&array[i], &array[min]);
	}
	return;
}

void insertion(int *array, int size) {
	for(int i = 1; i<size; ++i) {
		for(int j =i; j > 0 && array[j] < array[j-1]; --j)
			exch(&array[j], &array[j-1]);
	}
}

void mergeSort(int *array, int *temp, int low, int pivot, int high) {
	
	int h = low;
	int i = low; // index on temp
	int j = pivot+1;

	while( (h<=pivot) && j <= high) {

		if (array[h] <= array[j]) {
			temp[i++] = array[h++];
		}
		else {
			temp[i++] = array[j++];
		}
	}

	// copy the remaining items
	for(int k=h; k<=pivot; ++k)
		temp[i++] = array[k];

	for(int k=j; k<= high; ++k)
		temp[i++] = array[k];

	for(int i=low; i<=high; ++i)
		array[i] = temp[i];

}
void mergeSort(int *array, int *temp, int l, int h) {
	
	if (l < h) {
		print(array, 9);
		int pivot = l+ (h-l)/2;
		mergeSort(array, temp, l, pivot);
		mergeSort(array, temp, pivot+1, h);
		mergeSort(array, temp, l, pivot, h);
	}
}

int partition(int *array, int low, int high) {
	int pivot = array[low];
	int left = low;
	int right = high;
	while ( left < right) {
		while(array[left] <= pivot) ++left;
		while(array[right] > pivot) --right;
		if (left < right)
			exch(&array[left], &array[right]);
	}

	array[low] = array[right];
	array[right] = pivot;
	return right;
 }

void quickSort(int *array, int low, int high) {

	if (low < high) {
		int pivot = partition(array, low, high);
		quickSort(array, low, pivot);
		quickSort(array, pivot+1, high);
	}
}


int main() {
	int array[] = { 9,4,5,6,1,3,2,7,8};
	const int size = sizeof(array)/sizeof(array[0]);
	int temp[size+1];

	//selection(array, size);
	//insertion(array, size);
	
	//mergeSort(array, temp, 0, size);
	quickSort(array, 0, size);
	print(array, size);

	return 0;
}